#include "json_parser.h"
#include <fstream>

namespace simba {
namespace database {
namespace json {

void Json_parser::LoadJson(const std::string& path, simba::database::objects::AppElement& result) {
    std::ifstream file(path);
    if (file.is_open()) {
        nlohmann::json data;
        file >> data;
        file.close();

        ParseJson(data, result);
    } else {
        // Handle file open error
    }
}

void Json_parser::ParseJson(const nlohmann::json& data, simba::database::objects::AppElement& result) {
    result.setName(data["name"]);
    
}

} // namespace json
} // namespace database
} // namespace simba
