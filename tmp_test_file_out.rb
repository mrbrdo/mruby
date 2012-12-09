def met(*args, &block)
  p args
  p block
  block.call
end

met(1, 3) do
  puts "ok"
end
