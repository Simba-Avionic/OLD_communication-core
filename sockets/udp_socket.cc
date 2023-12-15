/**
 * @file udp_socket.cc
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "sockets/udp_socket.h"

#include "unistd.h"
#include "iostream"
#include "vector"


namespace simba{
namespace com{
namespace soc{


core::ErrorCode UdpSocket::Init(const SocketConfig& config){
    memset(&server_sockaddr,0,sizeof(struct sockaddr_un));
    server_sock=socket(AF_INET,SOCK_DGRAM,0);
    if(server_sock == -1){
        return core::ErrorCode::kInitializeError;
    }
    server_sockaddr.sin_family=AF_INET;
    server_sockaddr.sin_addr.s_addr=inet_addr(config.GetIp().c_str());
    server_sockaddr.sin_port=config.GetRxPort();
    this->len=sizeof(server_sockaddr);
    unlink(config.GetIp().c_str());
    return core::ErrorCode::kOk;
}

void UdpSocket::SetRXCallback(RXCallback callback){}

core::ErrorCode UdpSocket::Transmit(const std::string& ip,
                                    const std::uint16_t port,
                                    std::vector<std::uint8_t> payload){
    int client_socket,rc;
    struct sockaddr_in remote;
    memset(&remote,0,sizeof(struct sockaddr_in));
    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    if(client_socket==-1){
        return core::ErrorCode::kError;
    }
    remote.sin_family=AF_INET;
    remote.sin_addr.s_addr=inet_addr(ip.c_str());
    remote.sin_port=port;
    std::uint8_t* buffor = new std::uint8_t[payload.size()];
    std::copy(payload.begin(),payload.end(),buffor);
    rc=sendto(client_socket,buffor,payload.size(),0,
                (struct sockaddr*)&remote,sizeof(remote));
    delete[] buffor;
    if(rc==-1){
        return core::ErrorCode::kError;
    }
    rc=close(client_socket);
    return core::ErrorCode::kOk;
}

void UdpSocket::StartRXThread(){
    if(rx_thread!=nullptr){
        return;
    }
    this->rx_thread=std::make_unique<std::thread>([&](){
        this->Loop();
    });
}

void UdpSocket::Loop(){
    rc=bind(server_sock,(struct sockaddr*)&server_sockaddr,len);
    if(rc==-1){
        return;
    }
    while(true){
        std::array<char,256*2> buffor;
        bytes_rec=recvfrom(server_sock,reinterpret_cast<char*>(&buffor),256*2,
        0,(struct sockaddr*)&peer_sock,(socklen_t*)&len);
        if(bytes_rec>=0){
            if(this->callback_){
                this->callback_(
                    "UDP",0,std::vector<uint8_t>{buffor.begin(),buffor.begin()+bytes_rec});
            }
        }
    }
    close(server_sock);
}




}  //  namespace soc
}  //  namespace com
}  //  namespace simba