
  #include 'mrblib/array.rb'
  #include 'mrblib/enum.rb'
  #include 'mrblib/class.rb'
  #include 'mrblib/compar.rb'
  #include 'mrblib/error.rb'
  #include 'mrblib/hash.rb'
  #include 'mrblib/kernel.rb'
  #include 'mrblib/numeric.rb'
  #include 'mrblib/print.rb'
  #include 'mrblib/range.rb'
  #include 'mrblib/string.rb'
  #include 'mrblib/struct.rb'

  #include 'test/assert.rb'

# Failing:
  #include 'test/t/kernel.rb'

  # test with block
  l = __send__(:lambda) do
    true
  end

  #l.call and l.class == Proc and
    # test with argument
    __send__(:respond_to?, :nil?) #and
    # test without argument and without block
   # __send__(:public_methods).class == Array
#report
