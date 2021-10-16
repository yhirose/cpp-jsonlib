//
//  jsonlib.h
//
//  Copyright (c) 2021 Yuji Hirose. All rights reserved.
//  MIT License
//

#pragma once

#include <rapidjson/reader.h>

#include <functional>
#include <string>

namespace jsonlib {

using namespace rapidjson;

struct Handlers {
  std::function<bool()> Null;
  std::function<bool(bool b)> Bool;
  std::function<bool(int i)> Int;
  std::function<bool(unsigned u)> Uint;
  std::function<bool(int64_t i)> Int64;
  std::function<bool(uint64_t i)> Uint64;
  std::function<bool(double i)> Double;
  std::function<bool(const char* str, SizeType length, bool copy)> String;
  std::function<bool()> StartObject;
  std::function<bool(const char* str, SizeType length, bool copy)> Key;
  std::function<bool(SizeType memberCount)> EndObject;
  std::function<bool()> StartArray;
  std::function<bool(SizeType elementCount)> EndArray;
};

inline void parse(const char* json, const Handlers& functions) {
  struct ReaderHandler : public BaseReaderHandler<UTF8<>, ReaderHandler> {
    ReaderHandler(const Handlers& functions) : functions_(functions) {}

    bool Null() {
      if (functions_.Null) {
        return functions_.Null();
      }
      return true;
    }

    bool Bool(bool b) {
      if (functions_.Bool) {
        return functions_.Bool(b);
      }
      return true;
    }

    bool Int(int i) {
      if (functions_.Int) {
        return functions_.Int(i);
      }
      return true;
    }

    bool Uint(unsigned u) {
      if (functions_.Uint) {
        return functions_.Uint(u);
      }
      return true;
    }

    bool Int64(int i) {
      if (functions_.Int64) {
        return functions_.Int64(i);
      }
      return true;
    }

    bool Uint64(unsigned u) {
      if (functions_.Uint64) {
        return functions_.Uint64(u);
      }
      return true;
    }

    bool Double(double d) {
      if (functions_.Double) {
        return functions_.Double(d);
      }
      return true;
    }

    bool String(const char* str, SizeType length, bool copy) {
      if (functions_.String) {
        return functions_.String(str, length, copy);
      }
      return true;
    }

    bool StartObject() {
      if (functions_.StartObject) {
        return functions_.StartObject();
      }
      return true;
    }

    bool Key(const char* str, SizeType length, bool copy) {
      if (functions_.Key) {
        return functions_.Key(str, length, copy);
      }
      return true;
    }

    bool EndObject(SizeType memberCount) {
      if (functions_.EndObject) {
        return functions_.EndObject(memberCount);
      }
      return true;
    }

    bool StartArray() {
      if (functions_.StartArray) {
        return functions_.StartArray();
      }
      return true;
    }

    bool EndArray(SizeType elementCount) {
      if (functions_.EndArray) {
        return functions_.EndArray(elementCount);
      }
      return true;
    }

    const Handlers& functions_;
    std::string key_;
  };

  StringStream ss(json);
  ReaderHandler handler(functions);

  Reader reader;
  reader.Parse(ss, handler);
}

inline void parse(const std::string& json, const Handlers& functions) {
  parse(json.data(), functions);
}

};  // namespace jsonlib
