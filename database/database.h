/**
 * @file database.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief This file define database for router
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef ROUTER_COMUNICATION_CORE_DATABASE_DATABASE_H_
#define ROUTER_COMUNICATION_CORE_DATABASE_DATABASE_H_
#include <cstdint>
#include <string>

#include "database/Idatabase.h"
#include "database/database_element.h"
#include "unordered_map"
namespace simba {
namespace database {
class Database : public IDatabase {
 private:
  std::unordered_map<std::uint16_t, DatabaseElement> db{};

 public:
  simba::core::Result<DatabaseElement> GetService(
      const std::uint16_t service_id) override;
  bool ServiceExist(const std::uint16_t service_id) override;
  void AddService(const std::uint16_t service_id,
                  const DatabaseElement& element) override;
  DatabaseElement CreatDatabaseElement(const std::string& ip,
                                       const int16_t port) override;

 public:
};
}  // namespace database
}  // namespace simba
#endif  // ROUTER_COMUNICATION_CORE_DATABASE_DATABASE_H_