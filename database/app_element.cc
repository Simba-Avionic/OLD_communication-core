#include "database/app_element.h"

namespace simba {
namespace database {
namespace objects {

void AppElement::setName(const std::string& newName) {
    name = newName;
}

void AppElement::addPublicMethod(const std::string& methodName, const MethodElement& method) {
    
}

void AppElement::addRequestEvent(const std::string& eventName, const EventElement& event) {
    
}

void AppElement::addPublicEvent(const std::string& eventName, const EventElement& event) {
    
}

void AppElement::addDatabaseMethod(const std::string& methodName, const MethodElement& method) {
    
}

const std::string& AppElement::getName() const {
    return name;
}

const NetInterfaceElement& AppElement::getNetInterface() const {
    return net_interface;
}

const std::unordered_map<uint16_t, std::string>& AppElement::getPublicMethods() const {
    return pub_methods;
}

const std::unordered_map<std::string, EventElement>& AppElement::getRequestEvents() const {
    return req_events;
}

const std::unordered_map<std::string, EventElement>& AppElement::getPublicEvents() const {
    return pub_events;
}

const std::unordered_map<std::string, MethodElement>& AppElement::getDatabaseMethods() const {
    return db;
}

}  // namespace objects
}  // namespace database
}  // namespace simba