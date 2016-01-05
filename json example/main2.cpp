// rapidjson/example/simpledom/simpledom.cpp`
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace rapidjson;
int main() {
    std::string k = "{\"project\":\"rapidjson\",\"stars\":10}";
    // 1. Parse a JSON string into

    Document d;
    d.Parse<0>(k.c_str());
    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}
//this file is purely made to check if the standard example compiles with rapidJson
//and check if the library is properly accesed
