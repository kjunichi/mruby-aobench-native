# mruby-aobench-native   [![Build Status](https://travis-ci.org/kjunichi/mruby-aobench-native.svg?branch=master)](https://travis-ci.org/kjunichi/mruby-aobench-native)

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
ppmimg = Ao.render()
Ao.render("ao.ppm")
```


## License
under the MIT License:
- see LICENSE file
