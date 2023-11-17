/**
 * @file database.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief This file define interface for database
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef ROUTER_COMUNICATION_CORE_DATABASE_IDATABASE_H_
#define ROUTER_COMUNICATION_CORE_DATABASE_IDATABASE_H_
#include <cstdint>
#include <string>

#include "app/database/database_element.h"
#include "results/result.h"

namespace simba {
namespace database {
class IDatabase {
 private:
 public:
  virtual simba::core::Result<DatabaseElement> GetService(
      const std::uint16_t service_id) = 0;
  virtual bool ServiceExist(const std::uint16_t service_id) = 0;
  virtual void AddService(const std::uint16_t service_id,
                          const DatabaseElement& element) = 0;
  virtual DatabaseElement CreatDatabaseElement(const std::string& ip,
                                               const int16_t port) = 0;
};
}  // namespace database
}  // namespace simba
#endif  // ROUTER_COMUNICATION_CORE_DATABASE_IDATABASE_H_