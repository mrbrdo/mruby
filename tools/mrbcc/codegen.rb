# encoding: utf-8
require 'active_support/core_ext'
require 'securerandom'

path = File.expand_path("..", __FILE__)

str = %x[cd "#{path}/../../" && bin/mrbc tmp_test_file.rb]
parser = RiteParser.new(File.expand_path("../../../tmp_test_file.mrb"))

puts "INPUT:"
puts str
puts
puts "OUTPUT:"

ireps = str.split("irep ").reject(&:blank?)
$irepinfo = Hash.new
ireps.map! do |str|
  str.gsub!(/\A(\d+)(.*)/, "")
  idx = $1.to_i
  $irepinfo[idx] = Hash[$2.split(/\s+/).map{|v| v.split("=")}]
  [idx, str]
end
ireps = Hash[ireps]

opcode_impl = Hash.new
Dir[File.expand_path("../codegen_rb/opcode_*.c", __FILE__)].each do |fn|
  contents = File.read(fn)

  ops = contents.split("CASE(OP_")
  ops.each do |op|
    op =~ /\A([^\)]+)\)(.*)/m
    if $1.present?
      opcode_impl["OP_#{$1}"] = $2.strip
    end
  end
end

# fix body for OP_CMP

opcode_impl.each_pair do |k,v|
  opcode_impl[k] = v.gsub(/OP_CMP\(([^\)]*)\)/) do
    "int a = GETARG_A(i); OP_CMP(#{$1})"
  end
end

$opcode_impl = opcode_impl
def opcode_impl
  $opcode_impl
end

$ireps = ireps
def ireps
  $ireps
end

class OpcodeParser
  attr_reader :name
  def initialize(name, iseq, iseq_info)
    @name = name || "met_#{SecureRandom.hex}"
    @iseq = iseq
    @iseq_info = iseq_info
  end

  def label(i = nil)
    i ||= @line_number
    "L_#{@name.upcase}_#{i}"
  end

  def process_iseq
    iseq = @iseq
    @outf = StringIO.new
    @outf.write(method_prelude)
    iseq.strip.each_line do |line|
      puts line
      line =~ /\A(\d+)\s+([^\s]+)\s*(.*)/
      @line_number = $1.to_i
      @opcode = $2
      # better parsing of args, what if str = "la\" la"
      @args = ($3 || String.new).split(/(\s+|:?"[^"]*")/).reject(&:blank?)
      @args = parse_args(@args)

      @instr_body = opcode_impl[@opcode].dup
      if respond_to?(@opcode.downcase)
        send(@opcode.downcase)
      end

      gsub_args
      fix_jumps
      # symbols
      @instr_body.gsub!(/syms\[([^\]]+)\]/) do
        "mrb_intern(mrb, #{$1})"
      end
      # remove stuff
      @instr_body.gsub!("mrb->arena_idx = ai;", "")

      @outf.write("\n  // #{line.strip}")
      @outf.write("\n  #{label}:\n  ")
      @outf.write(@instr_body)
    end
    wrap_body(@outf.string)
  end

  def wrap_body(body)
    "#{body}\n}\n"
  end

  def method_prelude
    prelude = File.read(File.expand_path("../codegen_rb/met_start.c", __FILE__))
    prelude.gsub("FUNC_NREGS", @iseq_info["nregs"]).
      gsub("MET_NAME", @name)
  end

  def parse_args(args)
    args.map do |arg|
      if arg =~ /\AR(\d+)\z/
        $1
      elsif arg =~ /\A:/
        sym_str = arg[1, arg.length-1]
        #"mrb_intern(mrb, \"#{sym_str}\")"
        "\"#{sym_str}\""
      elsif arg =~/\A"/
        arg
      elsif arg =~/\A\d+\z/
        arg
      elsif arg =~ /\AI\((\d+)\)\z/
        parser = OpcodeParser.new(nil, ireps[$1.to_i], $irepinfo[$1.to_i])
        str = parser.process_iseq
        @outf = StringIO.new(str + @outf.string)
        @outf.seek(0, IO::SEEK_END)
        parser.name
      else
        arg
      end
    end
  end

  def gsub_args
    if @args.count > 0
      ["GETARG_A", "GETARG_Ax"].each do |search_str|
        @instr_body.gsub!("#{search_str}(i)", @args[0])
      end
    end
    if @args.count > 1
      ["GETARG_B", "GETARG_Bx", "GETARG_sBx", "GETARG_b"].each do |search_str|
        @instr_body.gsub!("#{search_str}(i)", @args[1])
      end
    end
    if @args.count > 2
      ["GETARG_C", "GETARG_c"].each do |search_str|
        @instr_body.gsub!("#{search_str}(i)", @args[2])
      end
    end
  end

  def fix_jumps
    # jumps
    @instr_body.gsub!(/JUMP_TO_PC\((\d+)\)/) do
      "goto #{label($1.to_i)}"
    end
  end

# OPCODES
  def op_return
    # todo
    @instr_body.gsub!("GETARG_B(i)", "OP_R_RETURN")
  end

  def op_send
    send_args = (1..@args[2].to_i).map { |i| "regs[a+#{i}]" }
    send_args = send_args.unshift(@args[2]).join(", ")
    @instr_body.gsub!("DYNAMIC_SEND_ARGS", send_args)
  end

  def op_sendb
    op_send
  end

  def op_subi
    @instr_body.gsub!(/default.+goto L_SEND;/m, "")
    # TODO
  end

  def op_mul
    @instr_body.gsub!(/default.+goto L_SEND;/m, "")
    # TODO
  end

  def op_enter
    nums = @args.first.split(":").map(&:to_i)
    num_all = (nums[0] << 18) |
      (nums[1] << 13) |
      (nums[2] << 12) |
      (nums[3] << 7) |
      (nums[4] << 2) |
      (nums[5] << 1) |
      (nums[6])
    @args[0] = num_all.to_s

    len = nums.slice(0, 4).reduce(&:+)
    # jumps
    @instr_body.gsub!(/if \(o == 0\)([^;]+;)\s*else([^;]+;)/m) do
      if nums[1] == 0
        $1
      else
        $2
      end
    end
    @instr_body.gsub!("pc++", "goto #{label(@line_number+1)}")
    @instr_body.gsub!("pc += argc - m1 - m2 + 1;") do
      str = "switch(argc) {\n"
      (0..len-1).each do |i|
        str += "  case #{i}: goto #{label(@line_number+i-nums[0]-nums[3]+1)};\n"
      end
      str += "}\n"
      str
    end
    @instr_body.gsub!("pc += o + 1;", "goto #{label(@line_number+nums[1]+1)};")
    @instr_body.gsub!("JUMP;", "");
  end

  def op_jmp
    @instr_body = "goto #{label(@args[0].to_i)};"
  end
end

outf = File.open(File.expand_path("../codegen_rb/out.c", __FILE__), "w")
outf.write(OpcodeParser.new("rb_main", ireps[0], $irepinfo[0]).process_iseq)
outf.close
