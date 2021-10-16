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
  std::function<void()> Null;
  std::function<void(bool b)> Bool;
  std::function<void(int i)> Int;
  std::function<void(unsigned u)> Uint;
  std::function<void(int64_t i)> Int64;
  std::function<void(uint64_t i)> Uint64;
  std::function<void(double i)> Double;
  std::function<void(const char* str, SizeType length, bool copy)> String;
  std::function<void()> StartObject;
  std::function<void(const char* str, SizeType length, bool copy)> Key;
  std::function<void(SizeType memberCount)> EndObject;
  std::function<void()> StartArray;
  std::function<void(SizeType elementCount)> EndArray;
};

inline bool parse(const char* json, const Handlers& functions) {
  struct ReaderHandler : public BaseReaderHandler<UTF8<>, ReaderHandler> {
    ReaderHandler(const Handlers& functions) : functions_(functions) {}

    bool Null() {
      if (functions_.Null) {
        functions_.Null();
      }
      return true;
    }

    bool Bool(bool b) {
      if (functions_.Bool) {
        functions_.Bool(b);
      }
      return true;
    }

    bool Int(int i) {
      if (functions_.Int) {
        functions_.Int(i);
      }
      return true;
    }

    bool Uint(unsigned u) {
      if (functions_.Uint) {
        functions_.Uint(u);
      }
      return true;
    }

    bool Int64(int i) {
      if (functions_.Int64) {
        functions_.Int64(i);
      }
      return true;
    }

    bool Uint64(unsigned u) {
      if (functions_.Uint64) {
        functions_.Uint64(u);
      }
      return true;
    }

    bool Double(double d) {
      if (functions_.Double) {
        functions_.Double(d);
      }
      return true;
    }

    bool String(const char* str, SizeType length, bool copy) {
      if (functions_.String) {
        functions_.String(str, length, copy);
      }
      return true;
    }

    bool StartObject() {
      if (functions_.StartObject) {
        functions_.StartObject();
      }
      return true;
    }

    bool Key(const char* str, SizeType length, bool copy) {
      if (functions_.Key) {
        functions_.Key(str, length, copy);
      }
      return true;
    }

    bool EndObject(SizeType memberCount) {
      if (functions_.EndObject) {
        functions_.EndObject(memberCount);
      }
      return true;
    }

    bool StartArray() {
      if (functions_.StartArray) {
        functions_.StartArray();
      }
      return true;
    }

    bool EndArray(SizeType elementCount) {
      if (functions_.EndArray) {
        functions_.EndArray(elementCount);
      }
      return true;
    }

    const Handlers& functions_;
    std::string key_;
  };

  StringStream ss(json);
  ReaderHandler handler(functions);

  Reader reader;
  return reader.Parse(ss, handler);
}

inline bool parse(const std::string& json, const Handlers& functions) {
  return parse(json.data(), functions);
}

};  // namespace jsonlib
