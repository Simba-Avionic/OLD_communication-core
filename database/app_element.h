#ifndef ROUTER_COMUNICATION_CORE_DATABASE_APP_ELEMENT_H_
#define ROUTER_COMUNICATION_CORE_DATABASE_APP_ELEMENT_H_

#include <iostream>

#include "database/net_interface_element.h"
#include "database/method_element.h"
#include "database/event_element.h"
#include <string>
#include "unordered_map"

namespace simba {
namespace database {
namespace objects {
class AppElement {
 private:
    std::string name;
    NetInterfaceElement net_interface;
    std::unordered_map<std::string, std::string> pub_methods;
    std::unordered_map<std::string, EventElement> req_events;
    std::unordered_map<std::string, EventElement> pub_events;
    std::unordered_map<std::string, MethodElement> db;
    std::unordered_map<std::string, std::string> conf;
    


   public:
    AppElement();
    ~AppElement() = default;

    void setName(const std::string& newName);
    void setNetInterface(const NetInterfaceElement& newNetInterface);
    void addPublicMethod(const std::string& methodName, const MethodElement& method);
    void addRequestEvent(const std::string& eventName, const EventElement& event);
    void addPublicEvent(const std::string& eventName, const EventElement& event);
    void addDatabaseMethod(const std::string& methodName, const MethodElement& method);

    const std::string& getName() const;
    const NetInterfaceElement& getNetInterface() const;
    const std::unordered_map<uint16_t, std::string>& getPublicMethods() const;
    const std::unordered_map<std::string, EventElement>& getRequestEvents() const;
    const std::unordered_map<std::string, EventElement>& getPublicEvents() const;
    const std::unordered_map<std::string, MethodElement>& getDatabaseMethods() const;
    const std::unordered_map<std::string, MethodElement>& getConf() const;
};
}  // namespace database
}  // namespace simba
}  // namespace objects
#endif  // ROUTER_COMUNICATION_CORE_DATABASE_DATABASE_APP_H_