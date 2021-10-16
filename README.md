# cpp-jsonlib

A C++17 single-file header-only library for RapidJSON SAX interface

```cpp
std::string key;

auto ret = jsonlib::parse(json, {
  .Key = [&](auto str, auto length, auto copy) {
    key.assign(str, length);
  },
  .String = [&](auto str, auto length, auto copy) {
    std::cout << key << ": " << std::string(str, length) << std::endl;
  }});
```
