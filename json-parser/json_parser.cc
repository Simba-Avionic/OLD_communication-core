#ifndef ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_
#define ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_
#include "json-parser/Ijson_parser.h"
#include "database/app_element.h"

namespace simba {
namespace database {
namespace json {
class Ijson_parser {
    private:
     virtual void ParseJson(const nlohmann::json& data, AppElement& result) = 0;
    public:
     virtual void LoadJson(const std::string& path, AppElement& result) = 0;
};
} //namespace simba
} //namespace database
} //namespace json
#endif ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_