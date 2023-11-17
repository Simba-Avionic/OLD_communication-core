/**
 * @file ipc_socket.h
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef COMUNICATION_CORE_SOCKETS_IPC_SOCKET_H_
#define COMUNICATION_CORE_SOCKETS_IPC_SOCKET_H_
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <thread>
#include <memory>

#include "sockets/Isocket.h"
namespace simba {
namespace com {
namespace soc {
class IpcSocket : public ISocket {
 private:
  int server_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr, peer_sock;
    char buf[256*2];

  std::unique_ptr<std::thread> rx_thred;
  void Loop();
  RXCallback callback_;
 public:
  /**
   * @brief Socket init function
   *
   * @param config Config file
   * @return core::ErrorCode initialiaze status
   */
  core::ErrorCode Init(const SocketConfig& config) override;
  /**
   * @brief Setter for rx callback
   *
   * @param callback
   */
  void SetRXCallback(RXCallback callback) override;
  /**
   * @brief Function to send data by socket
   *
   * @param ip target ip or path
   * @param port target port or 0 for ipcs
   * @param payload payload to send
   * @return core::ErrorCode status
   */
  core::ErrorCode Transmit(const std::string& ip, const std::uint16_t port,
                           std::vector<std::uint8_t> payload) override;
  /**
   * @brief This function start RX thread
   *
   */
  void StartRXThread() override;
};
}  // namespace soc
}  // namespace com
}  // namespace simba

#endif  // COMUNICATION_CORE_SOCKETS_IPC_SOCKET_H_
