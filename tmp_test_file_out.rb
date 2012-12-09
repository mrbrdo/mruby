
##
# Array
#
# ISO 15.2.12
class Array

  ##
  # Calls the given block for each element of +self+
  # and pass the respective element.
  #
  # ISO 15.2.12.5.10
  def each(&block)
    idx = 0
    while(idx < length)
      block.call(self[idx])
      idx += 1
    end
    self
  end

  ##
  # Calls the given block for each element of +self+
  # and pass the index of the respective elment.
  #
  # ISO 15.2.12.5.11
  def each_index(&block)
    idx = 0
    while(idx < length)
      block.call(idx)
      idx += 1
    end
    self
  end

  ##
  # Calls the given block for each element of +self+
  # and pass the respective element. Each element will
  # be replaced by the resulting values.
  #
  # ISO 15.2.12.5.7
  def collect!(&block)
    self.each_index{|idx|
      self[idx] = block.call(self[idx])
    }
    self
  end

  ##
  # Alias for collect!
  #
  # ISO 15.2.12.5.20
  alias map! collect!

  ##
  # Private method for Array creation.
  #
  # ISO 15.2.12.5.15
  def initialize(size=0, obj=nil, &block)
    raise TypeError, "expected Integer for 1st argument" unless size.kind_of? Integer
    raise ArgumentError, "negative array size" if size < 0

    self.clear
    if size > 0
      self[size - 1] = nil  # allocate

      idx = 0
      while(idx < size)
        self[idx] = (block)? block.call(idx): obj
        idx += 1
      end
    end

    self
  end

  ##
  # Delete element with index +key+
  def delete(key, &block)
    while i = self.index(key)
      self.delete_at(i)
      ret = key
    end
    if ret == nil && block
      block.call
    else
      ret
    end
  end
end

##
# Array is enumerable and comparable
module Enumerable; end
module Comparable; end
class Array
  # ISO 15.2.12.3
  include Enumerable
  include Comparable

  ##
  # Sort all elements and replace +self+ with these
  # elements.
  def sort!(&block)
    self.replace(self.sort(&block))
  end
end
##
# Enumerable
#
#  ISO 15.3.2
#
#  The <code>Enumerable</code> mixin provides collection classes with
#  several traversal and searching methods, and with the ability to
#  sort. The class must provide a method <code>each</code>, which
#  yields successive members of the collection. If
#  <code>Enumerable#max</code>, <code>#min</code>, or
#  <code>#sort</code> is used, the objects in the collection must also
#  implement a meaningful <code><=></code> operator, as these methods
#  rely on an ordering between members of the collection.

module Enumerable

  ##
  # Call the given block for each element
  # which is yield by +each+. Return false
  # if one block value is false. Otherwise
  # return true. If no block is given and
  # +self+ is false return false.
  #
  # ISO 15.3.2.2.1
  def all?(&block)
    st = true
    if block
      self.each{|val|
        unless block.call(val)
          st = false
          break
        end
      }
    else
      self.each{|val|
        unless val
          st = false
          break
        end
      }
    end
    st
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Return true
  # if one block value is true. Otherwise
  # return false. If no block is given and
  # +self+ is true object return true.
  #
  # ISO 15.3.2.2.2
  def any?(&block)
    st = false
    if block
      self.each{|val|
        if block.call(val)
          st = true
          break
        end
      }
    else
      self.each{|val|
        if val
          st = true
          break
        end
      }
    end
    st
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Append all
  # values of each block together and
  # return this value.
  #
  # ISO 15.3.2.2.3
  def collect(&block)
    ary = []
    self.each{|val|
      ary.push(block.call(val))
    }
    ary
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Return
  # +ifnone+ if no block value was true.
  # Otherwise return the first block value
  # which had was true.
  #
  # ISO 15.3.2.2.4
  def detect(ifnone=nil, &block)
    ret = ifnone
    self.each{|val|
      if block.call(val)
        ret = val
        break
      end
    }
    ret
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Pass an
  # index to the block which starts at 0
  # and increase by 1 for each element.
  #
  # ISO 15.3.2.2.5
  def each_with_index(&block)
    i = 0
    self.each{|val|
      block.call(val, i)
      i += 1
    }
    self
  end

  ##
  # Return an array of all elements which
  # are yield by +each+.
  #
  # ISO 15.3.2.2.6
  def entries
    ary = []
    self.each{|val|
      ary.push val
    }
    ary
  end

  ##
  # Alias for find
  #
  # ISO 15.3.2.2.7
  alias find detect

  ##
  # Call the given block for each element
  # which is yield by +each+. Return an array
  # which contains all elements whose block
  # value was true.
  #
  # ISO 15.3.2.2.8
  def find_all(&block)
    ary = []
    self.each{|val|
      ary.push(val) if block.call(val)
    }
    ary
  end

  ##
  # Call the given block for each element
  # which is yield by +each+ and which return
  # value was true when invoking === with
  # +pattern+. Return an array with all
  # elements or the respective block values.
  #
  # ISO 15.3.2.2.9
  def grep(pattern, &block)
    ary = []
    self.each{|val|
      if pattern === val
        ary.push((block)? block.call(val): val)
      end
    }
    ary
  end

  ##
  # Return true if at least one element which
  # is yield by +each+ returns a true value
  # by invoking == with +obj+. Otherwise return
  # false.
  #
  # ISO 15.3.2.2.10
  def include?(obj)
    st = false
    self.each{|val|
      if val == obj
        st = true
        break
      end
    }
    st
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Return value
  # is the sum of all block values. Pass
  # to each block the current sum and the
  # current element.
  #
  # ISO 15.3.2.2.11
  def inject(*args, &block)
    raise ArgumentError, "too many arguments" if args.size > 2
    if Symbol === args[-1]
      sym = args[-1]
      block = ->(x,y){x.send(sym,y)}
      args.pop
    end
    if args.empty?
      flag = true  # no initial argument
      result = nil
    else
      flag = false
      result = args[0]
    end
    self.each{|val|
      if flag
        # push first element as initial
        flag = false
        result = val
      else
        result = block.call(result, val)
      end
    }
    result
  end
  alias reduce inject

  ##
  # Alias for collect
  #
  # ISO 15.3.2.2.12
  alias map collect

  ##
  # Return the maximum value of all elements
  # yield by +each+. If no block is given <=>
  # will be invoked to define this value. If
  # a block is given it will be used instead.
  #
  # ISO 15.3.2.2.13
  def max(&block)
    flag = true  # 1st element?
    result = nil
    self.each{|val|
      if flag
        # 1st element
        result = val
        flag = false
      else
        if block
          result = val if block.call(val, result) > 0
        else
          result = val if (val <=> result) > 0
        end
      end
    }
    result
  end

  ##
  # Return the minimum value of all elements
  # yield by +each+. If no block is given <=>
  # will be invoked to define this value. If
  # a block is given it will be used instead.
  #
  # ISO 15.3.2.2.14
  def min(&block)
    flag = true  # 1st element?
    result = nil
    self.each{|val|
      if flag
        # 1st element
        result = val
        flag = false
      else
        if block
          result = val if block.call(val, result) < 0
        else
          result = val if (val <=> result) < 0
        end
      end
    }
    result
  end

  ##
  # Alias for include?
  #
  # ISO 15.3.2.2.15
  alias member? include?

  ##
  # Call the given block for each element
  # which is yield by +each+. Return an
  # array which contains two arrays. The
  # first array contains all elements
  # whose block value was true. The second
  # array contains all elements whose
  # block value was false.
  #
  # ISO 15.3.2.2.16
  def partition(&block)
    ary_T = []
    ary_F = []
    self.each{|val|
      if block.call(val)
        ary_T.push(val)
      else
        ary_F.push(val)
      end
    }
    [ary_T, ary_F]
  end

  ##
  # Call the given block for each element
  # which is yield by +each+. Return an
  # array which contains only the elements
  # whose block value was false.
  #
  # ISO 15.3.2.2.17
  def reject(&block)
    ary = []
    self.each{|val|
      ary.push(val) unless block.call(val)
    }
    ary
  end

  ##
  # Alias for find_all.
  #
  # ISO 15.3.2.2.18
  alias select find_all

  ##
  # TODO
  # Does this OK? Please test it.
  def __sort_sub__(sorted, work, src_ary, head, tail, &block)
    if head == tail
      sorted[head] = work[head] if src_ary == 1
      return
    end

    # on current step, which is a src ary?
    if src_ary == 0
      src, dst = sorted, work
    else
      src, dst = work, sorted
    end

    key = src[head]    # key value for dividing values
    i, j = head, tail  # position to store on the dst ary

    (head + 1).upto(tail){|idx|
      if ((block)? block.call(src[idx], key): (src[idx] <=> key)) > 0
        # larger than key
        dst[j] = src[idx]
        j -= 1
      else
        dst[i] = src[idx]
        i += 1
      end
    }

    sorted[i] = key

    # sort each sub-array
    src_ary = (src_ary + 1) % 2  # exchange a src ary
    __sort_sub__(sorted, work, src_ary, head, i - 1, &block) if i > head
    __sort_sub__(sorted, work, src_ary, i + 1, tail, &block) if i < tail
  end
#  private :__sort_sub__

  ##
  # Return a sorted array of all elements
  # which are yield by +each+. If no block
  # is given <=> will be invoked on each
  # element to define the order. Otherwise
  # the given block will be used for
  # sorting.
  #
  # ISO 15.3.2.2.19
  def sort(&block)
    ary = []
    self.each{|val| ary.push(val)}
    unless ary.empty?
      __sort_sub__(ary, ::Array.new(ary.size), 0, 0, ary.size - 1, &block)
    end
    ary
  end

  ##
  # Alias for entries.
  #
  # ISO 15.3.2.2.20
  alias to_a entries
end
class Module
  # 15.2.2.4.13
  def attr_reader(*names)
    names.each{|name|
      name2 = ('@'+name.to_s).intern
      define_method(name){self.instance_variable_get(name2)}
    }
  end
  # 15.2.2.4.14
  def attr_writer(*names)
    names.each{|name|
      name2 = ('@'+name.to_s).intern
      name = (name.to_s+"=").intern
      define_method(name){|v|self.instance_variable_set(name2,v)}
    }
  end
  # 15.2.2.4.12
  def attr_accessor(*names)
    attr_reader(*names)
    attr_writer(*names)
  end
  # 15.2.2.4.11
  def attr(name)
    attr_reader(name)
  end
end
##
# Comparable
#
# ISO 15.3.3
module Comparable

  ##
  # Return true if +self+ is less
  # than +other+. Otherwise return
  # false.
  #
  # ISO 15.3.3.2.1
  def < other
    cmp = self <=> other
    if cmp.nil?
      false
    elsif cmp < 0
      true
    else
      false
    end
  end

  ##
  # Return true if +self+ is less
  # than or equal to +other+.
  # Otherwise return false.
  # 
  # ISO 15.3.3.2.2
  def <= other
    cmp = self <=> other
    if cmp.nil?
      false
    elsif cmp <= 0
      true
    else
      false
    end
  end

  ##
  # Return true if +self+ is equal
  # to +other+. Otherwise return
  # false.
  #
  # ISO 15.3.3.2.3
  def == other
    cmp = self <=> other
    if cmp == 0
      true
    else
      false
    end
  end

  ##
  # Return true if +self+ is greater
  # than +other+. Otherwise return
  # false.
  #
  # ISO 15.3.3.2.4
  def > other
    cmp = self <=> other
    if cmp.nil?
      false
    elsif cmp > 0
      true
    else
      false
    end
  end

  ##
  # Return true if +self+ is greater
  # than or equal to +other+.
  # Otherwise return false.
  #
  # ISO 15.3.3.2.5
  def >= other
    cmp = self <=> other
    if cmp.nil?
      false
    elsif cmp >= 0
      true
    else
      false
    end
  end

  ##
  # Return true if +self+ is greater 
  # than or equal to +min+ and
  # less than or equal to +max+.
  # Otherwise return false.
  #
  # ISO 15.3.3.2.6
  def between?(min, max)
    if self < min or self > max
      false
    else
      true
    end
  end
end
##
# Exception
#
# ISO 15.2.22
class Exception

  ##
  # Raise an exception.
  #
  # ISO 15.2.22.4.1
  def self.exception(*args, &block)
    self.new(*args, &block)
  end
end

# ISO 15.2.24
class ArgumentError < StandardError
end

# ISO 15.2.25
class LocalJumpError < StandardError
end

# ISO 15.2.26
class RangeError < StandardError
end

class FloatDomainError < RangeError
end

# ISO 15.2.26
class RegexpError < StandardError
end

# ISO 15.2.29
class TypeError < StandardError
end

# ISO 15.2.31
class NameError < StandardError
end

# ISO 15.2.32
class NoMethodError < NameError
end

# ISO 15.2.33
class IndexError < StandardError
end

class KeyError < IndexError
end

class NotImplementedError < ScriptError
end

##
# Hash
#
# ISO 15.2.13
class Hash

  ##
  # Delete the element with the key +key+.
  # Return the value of the element if +key+
  # was found. Return nil if nothing was
  # found. If a block is given, call the
  # block with the value of the element.
  #
  # ISO 15.2.13.4.8
  def delete(key, &block)
    if block && ! self.has_key?(key)
      block.call(key)
    else
      self.__delete(key)
    end
  end

  ##
  # Calls the given block for each element of +self+
  # and pass the key and value of each element.
  #
  # ISO 15.2.13.4.9
  def each(&block)
    self.keys.each{|k| block.call([k, self[k]])}
    self
  end

  ##
  # Calls the given block for each element of +self+
  # and pass the key of each element.
  #
  # ISO 15.2.13.4.10
  def each_key(&block)
    self.keys.each{|k| block.call(k)}
    self
  end

  ##
  # Calls the given block for each element of +self+
  # and pass the value of each element.
  #
  # ISO 15.2.13.4.11
  def each_value(&block)
    self.keys.each{|k| block.call(self[k])}
    self
  end

  ##
  # Create a direct instance of the class Hash.
  #
  # ISO 15.2.13.4.16
  def initialize(*args, &block)
    self.__init_core(block, *args)
  end

  ##
  # Return a hash which contains the content of
  # +self+ and +other+. If a block is given
  # it will be called for each element with
  # a duplicate key. The value of the block
  # will be the final value of this element.
  # 
  # ISO 15.2.13.4.22
  def merge(other, &block)
    h = {}
    raise "can't convert argument into Hash" unless other.respond_to?(:to_hash)
    other = other.to_hash
    self.each_key{|k| h[k] = self[k]}
    if block
      other.each_key{|k|
        h[k] = (self.has_key?(k))? block.call(k, self[k], other[k]): other[k]
      }
    else
      other.each_key{|k| h[k] = other[k]}
    end
    h
  end

  # 1.8/1.9 Hash#reject! returns Hash; ISO says nothing.
  def reject!(&b)
    keys = []
    self.each_key{|k|
      v = self[k]
      if b.call(k, v)
        keys.push(k)
      end
    }
    return nil if keys.size == 0
    keys.each{|k|
      self.delete(k)
    }
    self
  end

  # 1.8/1.9 Hash#reject returns Hash; ISO says nothing.
  def reject(&b)
    h = {}
    self.each_key{|k|
      v = self[k]
      unless b.call(k, v)
        h[k] = v
      end
    }
    h
  end

  # 1.9 Hash#select! returns Hash; ISO says nothing.
  def select!(&b)
    keys = []
    self.each_key{|k|
      v = self[k]
      unless b.call(k, v)
        keys.push(k)
      end
    }
    return nil if keys.size == 0
    keys.each{|k|
      self.delete(k)
    }
    self
  end

  # 1.9 Hash#select returns Hash; ISO says nothing.
  def select(&b)
    h = {}
    self.each_key{|k|
      v = self[k]
      if b.call(k, v)
        h[k] = v
      end
    }
    h
  end
end

##
# Hash is enumerable
#
# ISO 15.2.13.3
module Enumerable; end
class Hash
  include Enumerable
end
##
# Kernel
#
# ISO 15.3.1
module Kernel
  ##
  # Calls the given block repetitively.
  #
  # ISO 15.3.1.2.8
  def self.loop #(&block)
    while(true)
      yield
    end
  end

  # 15.3.1.2.3
  def self.eval(s)
    raise NotImplementedError.new("eval not implemented")
  end

  # 15.3.1.3.12
  def eval(s)
    Kernel.eval(s)
  end

  ##
  # Alias for +Kernel.loop+.
  #
  # ISO 15.3.1.3.29
  def loop #(&block)
    while(true)
      yield
    end
  end
end
##
# Integer
#
# ISO 15.2.8
class Integer

  ##
  # Calls the given block once for each Integer
  # from +self+ downto +num+.
  #
  # ISO 15.2.8.3.15
  def downto(num, &block)
    i = self
    while(i >= num)
      block.call(i)
      i -= 1
    end
    self
  end

  ##
  # Calls the given block +self+ times.
  #
  # ISO 15.2.8.3.22
  def times(&block)
    i = 0
    while(i < self)
      block.call(i)
      i += 1
    end
    self
  end

  ##
  # Calls the given block once for each Integer
  # from +self+ upto +num+.
  #
  # ISO 15.2.8.3.27
  def upto(num, &block)
    i = self
    while(i <= num)
      block.call(i)
      i += 1
    end
    self
  end

  ##
  # Calls the given block from +self+ to +num+
  # incremented by +step+ (default 1).
  #
  def step(num, step=1, &block)
    i = if num.kind_of? Float then self.to_f else self end
    while(i <= num)
      block.call(i)
      i += step
    end
    self
  end
end

##
# Numeric is comparable
#
# ISO 15.2.7.3
module Comparable; end
class Numeric
  include Comparable
end
##
# Kernel
#
# ISO 15.3.1
module Kernel
  unless Kernel.respond_to?(:__printstr__)
    def print(*a)
      raise NotImplementedError.new('print not available')
    end
    def puts(*a)
      raise NotImplementedError.new('puts not available')
    end
    def p(*a)
      raise NotImplementedError.new('p not available')
    end
    def printf(*args)
      raise NotImplementedError.new('printf not available')
    end
  else
    unless Kernel.respond_to?(:sprintf)
      def printf(*args)
        raise NotImplementedError.new('printf not available')
      end
      def sprintf(*args)
        raise NotImplementedError.new('sprintf not available')
      end
    end


    ##
    # Invoke method +print+ on STDOUT and passing +*args+
    #
    # ISO 15.3.1.2.10
    def print(*args)
      i = 0
      len = args.size
      while i < len
        __printstr__ args[i].to_s
        i += 1
      end
    end

    ##
    # Invoke method +puts+ on STDOUT and passing +*args*+
    #
    # ISO 15.3.1.2.11
    def puts(*args)
      i = 0
      len = args.size
      while i < len
        s = args[i].to_s
        __printstr__ s
        __printstr__ "\n" if (s[-1] != "\n")
        i += 1
      end
      __printstr__ "\n" if len == 0
      nil
    end

    ##
    # Print human readable object description
    #
    # ISO 15.3.1.3.34
    def p(*args)
      i = 0
      len = args.size
      while i < len
        __printstr__ args[i].inspect
        __printstr__ "\n"
        i += 1
      end
      args[0]
    end

    def printf(*args)
      __printstr__(sprintf(*args))
      nil
    end
  end
end
##
# Range
#
# ISO 15.2.14
class Range

  ##
  # Calls the given block for each element of +self+
  # and pass the respective element.
  #
  # ISO 15.2.14.4.4
  def each(&block)
    val = self.first
    unless val.respond_to? :succ
      raise TypeError, "can't iterate"
    end

    last = self.last
    return self if (val <=> last) > 0

    while((val <=> last) < 0)
      block.call(val)
      val = val.succ
    end

    block.call(val) unless exclude_end?

    self
  end
end

##
# Range is enumerable
#
# ISO 15.2.14.3
module Enumerable; end
class Range
  include Enumerable
end
##
# String
#
# ISO 15.2.10
class String

  ##
  # Calls the given block for each line
  # and pass the respective line.
  #
  # ISO 15.2.10.5.15
  def each_line(&block)
    # expect that str.index accepts an Integer for 1st argument as a byte data
    offset = 0
    while(pos = self.index(0x0a, offset))
      block.call(self[offset, pos + 1 - offset])
      offset = pos + 1
    end
    block.call(self[offset, self.size - offset]) if self.size > offset
    self
  end

  ##
  # Replace all matches of +pattern+ with +replacement+.
  # Call block (if given) for each match and replace
  # +pattern+ with the value of the block. Return the
  # final value.
  #
  # ISO 15.2.10.5.18
  def gsub(*args, &block)
    unless (args.size == 1 && block) || args.size == 2
      raise ArgumentError, "wrong number of arguments"
    end

    ### *** TODO *** ###
    unless Object.const_defined?(:Regexp)
      raise NotImplementedError, "gsub not available (yet)"
    end
  end

  ##
  # Replace all matches of +pattern+ with +replacement+.
  # Call block (if given) for each match and replace
  # +pattern+ with the value of the block. Modify
  # +self+ with the final value.
  #
  # ISO 15.2.10.5.19
  def gsub!(*args, &block)
    str = self.gsub(*args, &block)
    if str != self
      self.replace(str)
      self
    else
      nil
    end
  end

  ##
  # Calls the given block for each match of +pattern+
  # If no block is given return an array with all
  # matches of +pattern+.
  #
  # ISO 15.2.10.5.32
  def scan(reg, &block)
    ### *** TODO *** ###
    unless Object.const_defined?(:Regexp)
      raise NotImplementedError, "scan not available (yet)"
    end
  end

  ##
  # Replace only the first match of +pattern+ with
  # +replacement+. Call block (if given) for each
  # match and replace +pattern+ with the value of the
  # block. Return the final value.
  #
  # ISO 15.2.10.5.36
  def sub(*args, &block)
    unless (args.size == 1 && block) || args.size == 2
      raise ArgumentError, "wrong number of arguments"
    end

    ### *** TODO *** ###
    unless Object.const_defined?(:Regexp)
      raise NotImplementedError, "sub not available (yet)"
    end
  end

  ##
  # Replace only the first match of +pattern+ with
  # +replacement+. Call block (if given) for each
  # match and replace +pattern+ with the value of the
  # block. Modify +self+ with the final value.
  #
  # ISO 15.2.10.5.37
  def sub!(*args, &block)
    str = self.sub(*args, &block)
    if str != self
      self.replace(str)
      self
    else
      nil
    end
  end

  ##
  # Call the given block for each character of
  # +self+.
  def each_char(&block)
    pos = 0
    while(pos < self.size)
      block.call(self[pos])
      pos += 1
    end
    self
  end

  ##
  # Call the given block for each byte of +self+.
  def each_byte(&block)
    bytes = self.bytes
    pos = 0
    while(pos < bytes.size)
      block.call(bytes[pos])
      pos += 1
    end
    self
  end

  ##
  # Modify +self+ by replacing the content of +self+
  # at the position +pos+ with +value+.
  def []=(pos, value)
    b = self[0, pos]
    a = self[pos+1..-1]
    self.replace([b, value, a].join(''))
  end
end

##
# String is comparable
#
# ISO 15.2.10.3
module Comparable; end
class String
  include Comparable
end
##
# Struct
#
# ISO 15.2.18

if Object.const_defined?(:Struct)
  class Struct

    ##
    # Calls the given block for each element of +self+
    # and pass the respective element.
    #
    # ISO 15.2.18.4.4
    def each(&block)
      self.class.members.each{|field|
        block.call(self[field])
      }
      self
    end

    ##
    # Calls the given block for each element of +self+
    # and pass the name and value of the respectiev
    # element.
    #
    # ISO 15.2.18.4.5
    def each_pair(&block)
      self.class.members.each{|field|
        block.call(field.to_sym, self[field])
      }
      self
    end

    ##
    # Calls the given block for each element of +self+
    # and returns an array with all elements of which
    # block is not false.
    #
    # ISO 15.2.18.4.7
    def select(&block)
      ary = []
      self.class.members.each{|field|
        val = self[field]
        ary.push(val) if block.call(val)
      }
      ary
    end
  end
end


$ok_test = 0
$ko_test = 0
$kill_test = 0
$asserts  = []
$test_start = Time.now if Object.const_defined?(:Time)

##
# Print the assertion in a readable way
def print_assertion_string(str, iso)
  print(str)
  if(iso != '')
    print(' [')
    print(iso)
    print(']')
  end
end

##
# Verify a code block.
#
# str : A remark which will be printed in case
#       this assertion fails
# iso : The ISO reference code of the feature
#       which will be tested by this
#       assertion
def assert(str = 'Assertion failed', iso = '')
  begin
    if(!yield)
      $asserts.push(['Fail: ', str, iso])
      $ko_test += 1
      print('F')
    else
      $ok_test += 1
      print('.')
    end
  rescue Exception => e
    $asserts.push(['Error: ', str, iso, e])
    $kill_test += 1
    print('X')
  end
end

##
# Report the test result and print all assertions
# which were reported broken.
def report()
  print "\n"
  $asserts.each do |err, str, iso, e|
    print(err);
    print_assertion_string(str, iso)
    if e
      print(" => ")
      print(e.message)
    end
    print("\n")
  end

  $total_test = $ok_test.+($ko_test)
  print('Total: ')
  print($total_test)
  print("\n")

  print('   OK: ')
  print($ok_test)
  print("\n")
  print('   KO: ')
  print($ko_test)
  print("\n")
  print('Crash: ')
  print($kill_test)
  print("\n")

  if Object.const_defined?(:Time)
    print(' Time: ')
    print(Time.now - $test_start)
    print(" seconds\n")
  end
end

##
# Performs fuzzy check for equality on methods returning floats
# on the basis of the Math::TOLERANCE constant.
def check_float(a, b)
  tolerance = Math::TOLERANCE
  a = a.to_f
  b = b.to_f
  if a.finite? and b.finite?
    (a-b).abs < tolerance
  else
    true
  end
end

# Failing:
  #include 'test/t/argumenterror.rb'
  #include 'test/t/array.rb'
  #include 'test/t/basicobject.rb'
  #include 'test/t/bs_block.rb'
  #include 'test/t/bs_literal.rb'
  #include 'test/t/class.rb'
  #include 'test/t/comparable.rb'
  #include 'test/t/enumerable.rb'
  #include 'test/t/exception.rb'
  #include 'test/t/false.rb'
  #include 'test/t/float.rb'
  #include 'test/t/hash.rb'
  #include 'test/t/indexerror.rb'
  #include 'test/t/integer.rb'
  #include 'test/t/kernel.rb'
  #include 'test/t/literals.rb'
  #include 'test/t/localjumperror.rb'
  #include 'test/t/math.rb'
  #include 'test/t/module.rb'
  #include 'test/t/nameerror.rb'
  #include 'test/t/nil.rb'
  #include 'test/t/nomethoderror.rb'
  #include 'test/t/numeric.rb'
  #include 'test/t/object.rb'
  #include 'test/t/proc.rb'
  #include 'test/t/range.rb'
  #include 'test/t/rangeerror.rb'
  #include 'test/t/regexperror.rb'
  #include 'test/t/runtimeerror.rb'
  #include 'test/t/standarderror.rb'
  #include 'test/t/string.rb'
  #include 'test/t/struct.rb'
  #include 'test/t/symbol.rb'
assert('super', '11.3.4') do
  test = false
  begin
    super
  rescue NoMethodError
    test = true
  end

  class SuperFoo
    def foo
      true
    end
    def bar(*a)
      a
    end
  end
  class SuperBar < SuperFoo
    def foo
      super
    end
    def bar(*a)
      super(*a)
    end
  end
  bar = SuperBar.new
  test &&= bar.foo
  test &&= (bar.bar(1,2,3) == [1,2,3])
  test
end

assert('yield', '11.3.5') do
  begin
    yield
  rescue LocalJumpError
    true
  else
    false
  end
end

assert('Abbreviated variable assignment', '11.4.2.3.2') do
  a ||= 1
  b &&= 1
  c = 1
  c += 2
  a == 1 and b == nil and c == 3
end

assert('Nested const reference') do
  module Syntax4Const
    CONST1 = "hello world"
    class Const2
      def const1
        CONST1
      end
    end
  end
  Syntax4Const::CONST1 == "hello world" and
  Syntax4Const::Const2.new.const1 == "hello world"
end

assert('Abbreviated variable assignment as returns') do
  module Syntax4AbbrVarAsgnAsReturns
    class A
      def b
        @c ||= 1
      end
    end
  end
  Syntax4AbbrVarAsgnAsReturns::A.new.b == 1
end
##
# Time ISO Test

if Object.const_defined?(:Time)
  assert('Time.new', '15.2.3.3.3') do
    Time.new.class == Time
  end

  assert('Time', '15.2.19') do
    Time.class == Class
  end

  assert('Time superclass', '15.2.19.2') do
    Time.superclass == Object
  end

  assert('Time.at', '15.2.19.6.1') do
    Time.at(1300000000.0)
  end

  assert('Time.gm', '15.2.19.6.2') do
    Time.gm(2012, 12, 23)
  end

  assert('Time.local', '15.2.19.6.3') do
    Time.local(2012, 12, 23)
  end

  assert('Time.mktime', '15.2.19.6.4') do
    Time.mktime(2012, 12, 23)
  end

  assert('Time.now', '15.2.19.6.5') do
    Time.now.class == Time
  end

  assert('Time.utc', '15.2.19.6.6') do
    Time.utc(2012, 12, 23)
  end

  assert('Time#+', '15.2.19.7.1') do
    t1 = Time.at(1300000000.0)
    t2 = t1.+(60)

    t2.utc.asctime == "Sun Mar 13 07:07:40 UTC 2011"
  end

  assert('Time#-', '15.2.19.7.2') do
    t1 = Time.at(1300000000.0)
    t2 = t1.-(60)

    t2.utc.asctime == "Sun Mar 13 07:05:40 UTC 2011"
  end

  assert('Time#<=>', '15.2.19.7.3') do
    t1 = Time.at(1300000000.0)
    t2 = Time.at(1400000000.0)
    t3 = Time.at(1500000000.0)

    t2.<=>(t1) == 1 and
      t2.<=>(t2) == 0 and
      t2.<=>(t3) == -1 and
      t2.<=>(nil) == nil
  end

  assert('Time#asctime', '15.2.19.7.4') do
    Time.at(1300000000.0).utc.asctime == "Sun Mar 13 07:06:40 UTC 2011"
  end

  assert('Time#ctime', '15.2.19.7.5') do
    Time.at(1300000000.0).utc.ctime == "Sun Mar 13 07:06:40 UTC 2011"
  end

  assert('Time#day', '15.2.19.7.6') do
    Time.gm(2012, 12, 23).day == 23
  end

  assert('Time#dst?', '15.2.19.7.7') do
    not Time.gm(2012, 12, 23).utc.dst?
  end

  assert('Time#getgm', '15.2.19.7.8') do
    Time.at(1300000000.0).getgm.asctime == "Sun Mar 13 07:06:40 UTC 2011"
  end

  assert('Time#getlocal', '15.2.19.7.9') do
    t1 = Time.at(1300000000.0)
    t2 = Time.at(1300000000.0)
    t3 = t1.getlocal

    t1 == t3 and t3 == t2.getlocal
  end

  assert('Time#getutc', '15.2.19.7.10') do
    Time.at(1300000000.0).getutc.asctime == "Sun Mar 13 07:06:40 UTC 2011"
  end

  assert('Time#gmt?', '15.2.19.7.11') do
    Time.at(1300000000.0).utc.gmt?
  end

  # ATM not implemented
  # assert('Time#gmt_offset', '15.2.19.7.12') do

  assert('Time#gmtime', '15.2.19.7.13') do
    Time.at(1300000000.0).gmtime
  end

  # ATM not implemented
  # assert('Time#gmtoff', '15.2.19.7.14') do

  assert('Time#hour', '15.2.19.7.15') do
    Time.gm(2012, 12, 23, 7, 6).hour == 7
  end

  # ATM doesn't really work
  # assert('Time#initialize', '15.2.19.7.16') do

  assert('Time#initialize_copy', '15.2.19.7.17') do
    time_tmp_2 = Time.at(7.0e6)
    time_tmp_2.clone == time_tmp_2
  end

  assert('Time#localtime', '15.2.19.7.18') do
    t1 = Time.at(1300000000.0)
    t2 = Time.at(1300000000.0)

    t1.localtime
    t1 == t2.getlocal
  end

  assert('Time#mday', '15.2.19.7.19') do
    Time.gm(2012, 12, 23).mday == 23
  end

  assert('Time#min', '15.2.19.7.20') do
    Time.gm(2012, 12, 23, 7, 6).min == 6
  end

  assert('Time#mon', '15.2.19.7.21') do
    Time.gm(2012, 12, 23).mon == 12
  end

  assert('Time#month', '15.2.19.7.22') do
    Time.gm(2012, 12, 23).month == 12
  end

  assert('Times#sec', '15.2.19.7.23') do
    Time.gm(2012, 12, 23, 7, 6, 40).sec == 40
  end

  assert('Time#to_f', '15.2.19.7.24') do
    Time.at(1300000000.0).to_f == 1300000000.0
  end

  assert('Time#to_i', '15.2.19.7.25') do
    Time.at(1300000000.0).to_i == 1300000000
  end

  assert('Time#usec', '15.2.19.7.26') do
    Time.at(1300000000.0).usec == 0
  end

  assert('Time#utc', '15.2.19.7.27') do
    Time.at(1300000000.0).utc
  end

  assert('Time#utc?', '15.2.19.7.28') do
    Time.at(1300000000.0).utc.utc?
  end

  # ATM not implemented
  # assert('Time#utc_offset', '15.2.19.7.29') do

  assert('Time#wday', '15.2.19.7.30') do
    Time.gm(2012, 12, 23).wday == 0
  end

  assert('Time#yday', '15.2.19.7.31') do
    Time.gm(2012, 12, 23).yday == 358
  end

  assert('Time#year', '15.2.19.7.32') do
    Time.gm(2012, 12, 23).year == 2012
  end

  assert('Time#zone', '15.2.19.7.33') do
    Time.at(1300000000.0).utc.zone == 'UTC'
  end

  # Not ISO specified

  assert('Time#to_s') do
    Time.at(1300000000.0).utc.to_s == "Sun Mar 13 07:06:40 UTC 2011"
  end

  assert('Time#inspect') do
    Time.at(1300000000.0).utc.inspect == "Sun Mar 13 07:06:40 UTC 2011"
  end
end

##
# TrueClass ISO Test

assert('TrueClass', '15.2.5') do
  TrueClass.class == Class
end

assert('TrueClass superclass', '15.2.5.2') do
  TrueClass.superclass == Object
end

assert('TrueClass true', '15.2.5.1') do
  true
end

assert('TrueClass#&', '15.2.5.3.1') do
  true.&(true) and not true.&(false)
end

assert('TrueClass#^', '15.2.5.3.2') do
  not true.^(true) and true.^(false)
end

assert('TrueClass#to_s', '15.2.5.3.3') do
  true.to_s == 'true'
end

assert('TrueClass#|', '15.2.5.3.4') do
  true.|(true) and true.|(false)
end
##
# TypeError ISO Test

assert('TypeError', '15.2.29') do
  TypeError.class == Class
end

assert('TypeError superclass', '15.2.29.2') do
  TypeError.superclass == StandardError
end

report
