/**
 * @file Isocket.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef COMUNICATION_CORE_SOCKETS_ISOCKET_H_
#define COMUNICATION_CORE_SOCKETS_ISOCKET_H_
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "sockets/socket_config.h"
#include "common/error_code.h"
namespace simba {
namespace com {
namespace soc {
using RXCallback =
    std::function<void(const std::string& ip, const std::uint16_t& port,
                       std::vector<std::uint8_t>)>;
class ISocket {
 public:
  /**
   * @brief Socket init function
   *
   * @param config Config file
   * @return core::ErrorCode initialiaze status
   */
  virtual core::ErrorCode Init(const SocketConfig& config) = 0;
  /**
   * @brief Setter for rx callback
   *
   * @param callback
   */
  virtual void SetRXCallback(RXCallback callback) = 0;
  /**
   * @brief Function to send data by socket
   *
   * @param ip target ip or path
   * @param port target port or 0 for ipcs
   * @param payload payload to send
   * @return core::ErrorCode status
   */
  virtual core::ErrorCode Transmit(const std::string& ip,
                                   const std::uint16_t port,
                                   std::vector<std::uint8_t> payload) = 0;
  /**
   * @brief This function start RX thread
   *
   */
  virtual void StartRXThread() = 0;
  virtual ~ISocket() {}
};

}  // namespace soc
}  // namespace com
}  // namespace simba

#endif  // COMUNICATION_CORE_SOCKETS_ISOCKET_H_