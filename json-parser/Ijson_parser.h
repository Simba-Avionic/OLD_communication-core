#ifndef ROUTER_COMUNICATION_CORE_JSON_PARSER_IJSON_PARSER_H_
#define ROUTER_COMUNICATION_CORE_JSON_PARSER_IJSON_PARSER_H_
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "unordered_map"
#include "database/app_element.h"

namespace simba {
namespace database {
namespace json {
class Ijson_parser {
    private:
     virtual void ParseJson(const nlohmann::json& data, simba::database::objects::AppElement& result) = 0;
    public:
     virtual void LoadJson(const std::string& path, simba::database::objects::AppElement& result) = 0;
};
} //namespace simba
} //namespace database
} //namespace json
#endif ROUTER_COMUNICATION_CORE_JSON_PARSER_IJSON_PARSER_H_