# encoding: utf-8
require 'active_support/core_ext'
str = <<-END
000 OP_STRING R1  "lol"
001 OP_SETGLOBAL  :$hello R1
002 OP_GETGLOBAL  R1  :$hello
003 OP_STRING R2  "hej"
004 OP_ADD  R1  :+  1
005 OP_SETGLOBAL  :$hello R1
006 OP_LOADSELF R1
007 OP_GETGLOBAL  R2  :$hello
008 OP_SEND R1  :puts 1
009 OP_STOP
END

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

outf = File.open(File.expand_path("../codegen_rb/out.c", __FILE__), "w")
str.strip.each_line do |line|
  puts line
  line =~ /\A(\d+)\s+([^\s]+)\s*(.*)/
  line_number = $1.to_i
  opcode = $2
  puts "OPCODE: " + opcode
  # better parsing of args, what if str = "la\" la"
  args = ($3 || String.new).split(/(\s+|:?"[^"]*")/).reject(&:blank?)

  args.map! do |arg|
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
    else
      arg
    end
  end

  body = opcode_impl[opcode].dup
  if args.count > 0
    ["GETARG_A", "GETARG_Ax"].each do |search_str|
      body.gsub!("#{search_str}(i)", args[0])
    end
  end
  if args.count > 1
    ["GETARG_B", "GETARG_Bx", "GETARG_sBx"].each do |search_str|
      body.gsub!("#{search_str}(i)", args[1])
    end
  end
  if args.count > 2
    ["GETARG_C"].each do |search_str|
      body.gsub!("#{search_str}(i)", args[2])
    end
  end
  # jumps
  body.gsub!(/JUMP_TO_PC\((\d+)\)/) do
    "goto L_MAIN_#{$1.to_i}"
  end
  # send
  if opcode == "OP_SEND"
    send_args = (1..args[2].to_i).map { |i| "regs[a+#{i}]" }
    send_args = send_args.unshift(args[2]).join(", ")
    body.gsub!("DYNAMIC_SEND_ARGS", send_args)
  end
  # symbols
  body.gsub!(/syms\[([^\]]+)\]/) do
    "mrb_intern(mrb, #{$1})"
  end

  outf.write("\n// #{line}\n")
  outf.write("\nL_MAIN_#{line_number}:\n")
  outf.write(body)

  puts args.inspect
end
outf.close
