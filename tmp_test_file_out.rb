
  #include 'mrblib/array.rb'
  #include 'mrblib/enum.rb'
  #include 'mrblib/class.rb'
  #include 'mrblib/compar.rb'
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

  #include 'mrblib/hash.rb'
  #include 'mrblib/hash.rb'
  #include 'mrblib/kernel.rb'
  #include 'mrblib/numeric.rb'
  #include 'mrblib/print.rb'
  #include 'mrblib/range.rb'
  #include 'mrblib/string.rb'
  #include 'mrblib/struct.rb'

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
  #include 'test/t/bs_block.rb'
  #include 'test/t/exception.rb'

def exception_test14
  UnknownConstant
end

assert('Exception 14') do
  a = :ng
  begin
    send(:exception_test14)
  rescue
    a = :ok
  end

  a == :ok
end

report
