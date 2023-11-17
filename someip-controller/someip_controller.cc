/**
 * @file someip_controller.cc
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "someip-controller/someip_controller.h"

#include "json-parser/database_json_parser.h"
#include "results/result.h"
#include "someip/message_code.h"
#include "someip/message_type.h"
#include "someip/someip_header.h"

namespace simba {
namespace com {
namespace someip {
simba::core::Result<std::vector<uint8_t>> SomeIpController::Request(
    const uint16_t service_id, const uint16_t method_id,
    const std::vector<uint8_t> payload) {}

bool SomeIpController::RequestNoResponse(const uint16_t service_id,
                                         const uint16_t method_id,
                                         const std::vector<uint8_t> payload) {
  const auto service_data = db_.GetService(service_id);
  if (!service_data.HasValue()) {
    this->logger_->Error("[SOMEIPCONTROLLER] Service_id: " +
                         std::to_string(service_id) + " not found!");
    return;
  }
  const auto transfer = GetTransferID();
  auto req = header_factory.CreateRequest(service_id, method_id);
  auto req_payload = msg_factory.GetBuffor(req, service_id_, transfer, payload);
  auto trans = this->AddTransfer(transfer);

  this->socket_->Transmit(service_data.Value().GetIp(),service_data.Value().GetPort(),req_payload);
  trans->GetPayload
}

simba::core::ErrorCode SomeIpController::AddMethod(const uint16_t method_id,
                                                   SomeIPMethod callback) {}

simba::core::ErrorCode SomeIpController::AddEventValue(
    const uint16_t event_id, const std::vector<uint8_t> payload) {}

simba::core::ErrorCode SomeIpController::Init() {
  /// TODO: Do this better with config
  if (this->socket_->Init(this->config_) == simba::core::ErrorCode::kOk) {
    this->socket_->StartRXThread();
    logger_->Info("[SOMEIPCONTROLLER] Socket started RX Thhread");
  }
}

void SomeIpController::RxCallback(const std::string& ip,
                                  const std::uint16_t& port,
                                  std::vector<std::uint8_t> payload) {}

SomeIpController::SomeIpController(
    const uint16_t service_id, std::unique_ptr<soc::IpcSocket> socket,
    std::shared_ptr<simba::core::logger::ILogger> logger,
    const soc::SocketConfig& config)
    : socket_{std::move(socket)},
      service_id_{service_id},
      logger_{logger},
      config_{config} {
  socket_->SetRXCallback([&](const std::string& ip, const std::uint16_t& port,
                             std::vector<std::uint8_t> payload) {
    this->RxCallback(ip, port, payload);
  });
}

simba::core::ErrorCode SomeIpController::LoadServiceList(
    const std::string& path) {
  database::json::DatabaseJsonParser::LoadJson(this->db_, path);
  logger_->Info("[SOMEIPCONTROLLER] loaded config file with services");
  return simba::core::ErrorCode::kOk;
}

}  // namespace someip
}  // namespace com
}  // namespace simba
