#ifndef ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_
#define ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_
#include "json-parser/Ijson_parser.h"

namespace simba {
namespace database {
namespace json {
class Json_parser : public Ijson_parser {
    private:
     virtual void ParseJson(const nlohmann::json& data, simba::database::objects::AppElement& result) override;
    public:
     Json_parser() = default;
     ~Json_parser() = default;
     void LoadJson(const std::string& path, simba::database::objects::AppElement& result) override;
};
} //namespace simba
} //namespace database
} //namespace json
#endif ROUTER_COMUNICATION_CORE_JSON_PARSER_JSON_PARSER_H_