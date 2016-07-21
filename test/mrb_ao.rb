##
## Ao Test
##

assert("Ao#hello") do
  t = Ao.new "hello"
  assert_equal("hello", t.hello)
end

assert("Ao#bye") do
  t = Ao.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Ao.hi") do
  assert_equal("hi!!", Ao.hi)
end
