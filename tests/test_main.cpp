#include "external/JSON/json.hpp"
#include <string>
using json = nlohmann::json;
#include <fstream>
#include <iostream>

namespace structs {
struct testStruct {
    std::string firstString;
    std::string innerString;

    int firstInt;
    int innerInt;
};

void to_json(json& j, const testStruct& l)
{
    j = json {
        { "Object1", { { "firstString", l.firstString }, { "firstInt", l.firstInt }, { "Object2", { { "innerString", l.innerString }, { "innerInt", l.innerInt } } } } }
    };
}
void from_json(const json& j, testStruct& l)
{
    json Object1 = j.at("Object1").get<json>();
    l.firstString = Object1.at("firstString").get<std::string>();
}
}

int main()
{
    std::cout << "Hello!" << std::endl;
    std::ifstream i("D:\\Users\\Joris\\Documents\\HBO-ICT\\Jaar 4\\Minor\\Project\\Push_d_out\\tests\\testjson.JSON");
    json j;
    i >> j;

    std::cout << j << "\n"
              << std::endl;
    structs::testStruct s = j;
    std::cout << "firstString: " << s.firstString << std::endl;
    return 0;
};
