##
## Ao Test
##

assert("Ao.render(\"filename\")") do
  cmd = Ao.render("aotest.ppm")
  assert_equal(nil, cmd)
end
