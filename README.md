# cpp-jsonlib

A C++17 single-file header-only library for [RapidJSON SAX interface](https://rapidjson.org/md_doc_sax.html)

```cpp
#include <iostream>
#include "jsonlib.h"

int main(void) {
  std::string json;
  while (std::getline(std::cin, json)) {
    std::string key;
    jsonlib::parse(json, {
      .Key = [&](auto str, auto len) {
        key.assign(str, len);
      },
      .String = [&](auto str, auto len) {
        std::cout << key << ": " << std::string(str, len) << std::endl;
      }
    });
  }
}
```
