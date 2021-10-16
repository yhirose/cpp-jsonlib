# cpp-jsonlib

A C++17 single-file header-only library for RapidJSON SAX interface

```cpp
std::string key;

jsonlib::parse(json, {
  .Key = [&](auto str, auto length, auto copy) {
    key.assign(str, length);
    return true;
  },
  .String = [&](auto str, auto length, auto copy) {
    std::cout << key << ": " << std::string(str, length) << std::endl;
    return true;
  }});
```
