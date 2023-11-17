/**
 * @file someip_controller.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef COMUNICATION_CORE_SOMEIP_CONTROLLER_SOMEIP_CONTROLLER_H_
#define COMUNICATION_CORE_SOMEIP_CONTROLLER_SOMEIP_CONTROLLER_H_
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "common/error_code.h"
#include "database/database.h"
#include "logger/ILogger.h"
#include "memory"
#include "results/result.h"
#include "sockets/ipc_socket.h"
#include "sockets/socket_config.h"
#include "someip-controller/Isomeip_controller.h"
#include "someip-controller/transfer.h"
#include "someip/factory/someip_header_factory.h"
#include "someip/factory/someip_message_factory.h"

namespace simba {
namespace com {
namespace someip {
class SomeIpController : public ISomeIpController {
 private:
  void RxCallback(const std::string& ip, const std::uint16_t& port,
                  std::vector<std::uint8_t> payload);
  std::unique_ptr<soc::IpcSocket> socket_;
  std::shared_ptr<simba::core::logger::ILogger> logger_;
  const std::uint16_t service_id_;
  const soc::SocketConfig config_;
  database::Database db_{};
  com::core::someip::factory::SomeIpHeaderFactory header_factory{};
  com::core::someip::factory::SomeIpMessageFactory msg_factory{};
  uint16_t transfer_id = 0;

  inline const uint16_t GetTransferID() { return transfer_id++; }

  std::atomic<std::vector<std::shared_ptr<data::Transfer>>> transfers{};

  std::shared_ptr<data::Transfer> AddTransfer(const uint16_t transfer) {
    auto res = std::make_shared<data::Transfer>(transfer);
    this->transfers.load().push_back(res);
    return res;
  }

 public:
  simba::core::Result<std::vector<uint8_t>> Request(
      const uint16_t service_id, const uint16_t method_id,
      const std::vector<uint8_t> payload) override;

  bool RequestNoResponse(const uint16_t service_id, const uint16_t method_id,
                         const std::vector<uint8_t> payload) override;

  simba::core::ErrorCode AddMethod(const uint16_t method_id,
                                   SomeIPMethod callback) override;

  simba::core::ErrorCode AddEventValue(
      const uint16_t event_id, const std::vector<uint8_t> payload) override;
  simba::core::ErrorCode Init() override;
  simba::core::ErrorCode LoadServiceList(const std::string& path) override;
  SomeIpController(const uint16_t service_id,
                   std::unique_ptr<soc::IpcSocket> socket,
                   std::shared_ptr<simba::core::logger::ILogger> logger_,
                   const soc::SocketConfig& config);
};
}  // namespace someip
}  // namespace com
}  // namespace simba

#endif  // COMUNICATION_CORE_SOMEIP_CONTROLLER_SOMEIP_CONTROLLER_H_
