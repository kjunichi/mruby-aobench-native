# mruby-aobench-native   [![Build Status](https://travis-ci.org/kjunichi/mruby-aobench-native.svg?branch=master)](https://travis-ci.org/kjunichi/mruby-aobench-native)
Ao class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'kjunichi/mruby-aobench-native'
end
```
## example
```ruby
p Ao.hi
#=> "hi!!"
t = Ao.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
