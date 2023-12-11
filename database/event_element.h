/**
 * @file events_element.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-12-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef COMUNICATION_CORE_DATABASE_EVENTS_ELEMENT_H_
#define COMUNICATION_CORE_DATABASE_EVENTS_ELEMENT_H_
#include <stdint.h>

#include <vector>

#include "database/services_element.h"

namespace simba {
namespace database {
namespace objects {
class EventElement {
 private:
  const uint16_t event_id_;
  std::vector<ServiceElement> client_lists_{};

 public:
  EventElement(const uint16_t& event_id) : event_id_{event_id} {}
  void AddService(const ServiceElement& item) { client_lists_.push_back(item); }
  const std::vector<ServiceElement>& GetLists() const {
    return this->client_lists_;
  }
};
}  // namespace objects
}  // namespace database
}  // namespace simba
#endif  // COMUNICATION_CORE_DATABASE_EVENTS_ELEMENT_H_
