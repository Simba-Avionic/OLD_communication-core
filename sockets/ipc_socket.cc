/**
 * @file ipc_socket.cc
 * @author Bartosz Snieg (snieg45@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "sockets/ipc_socket.h"

#include <unistd.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

namespace simba {
namespace com {
namespace soc {
core::ErrorCode IpcSocket::Init(const SocketConfig& config) {
  memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
  server_sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (server_sock == -1) {
    return core::ErrorCode::kInitializeError;
  }
  server_sockaddr.sun_family = AF_UNIX;
  strcpy(server_sockaddr.sun_path, config.GetIp().c_str());
  len = sizeof(server_sockaddr);
  unlink(config.GetIp().c_str());
  return core::ErrorCode::kOk;
}

void IpcSocket::SetRXCallback(RXCallback callback) {}

core::ErrorCode IpcSocket::Transmit(const std::string& ip,
                                    const std::uint16_t port,
                                    std::vector<std::uint8_t> payload) {
  int client_socket, rc;
  struct sockaddr_un remote;
  memset(&remote, 0, sizeof(struct sockaddr_un));

  client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (client_socket == -1) {
    return core::ErrorCode::kError;
  }

  remote.sun_family = AF_UNIX;
  strcpy(remote.sun_path, ip.c_str());

  std::uint8_t* buffor = new std::uint8_t[payload.size()];
  std::copy(payload.begin(), payload.end(), buffor);

  rc = sendto(client_socket, buffor, payload.size(), 0,
              (struct sockaddr*)&remote, sizeof(remote));
  delete[] buffor;
  if (rc == -1) {
    return core::ErrorCode::kError;
  }

  rc = close(client_socket);
  return core::ErrorCode::kOk;
}

void IpcSocket::StartRXThread() {
  if (rx_thred != nullptr) {
    return;
  }
  this->rx_thred = std::make_unique<std::thread>([&]() { this->Loop(); });
}

void IpcSocket::Loop() {
  rc = bind(server_sock, (struct sockaddr*)&server_sockaddr, len);
  if (rc == -1) {
    return;
  }
  while (true) {
    std::array<char, 256 * 2> buffor;
    bytes_rec = recvfrom(server_sock, reinterpret_cast<char*>(&buffor), 256 * 2,
                         0, (struct sockaddr*)&peer_sock, (socklen_t*)&len);
    if (bytes_rec >= 0) {
      if (this->callback_) {
                this->callback_(
            "IPC", 0,
            std::vector<uint8_t>{buffor.begin(), buffor.begin() + bytes_rec});
      }
    }
  }
  close(server_sock);
}
}  // namespace soc
}  // namespace com
}  // namespace simba
