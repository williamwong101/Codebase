#include <cstdio>
#include <memory>
#include <sys/types.h>         
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include "socket_manager.h"
namespace cb {

class SimpleClient {
public:
    SimpleClient(const std::string&, const std::string&);
    ~SimpleClient();
    SimpleClient(const SimpleClient&) = delete;
    SimpleClient& operator=(const SimpleClient&) = delete;

    int build();
    int send_message(const std::string&);

private:
    int get_addr_info();

    std::unique_ptr<SocketManager> socket_;
    struct addrinfo* to_addr_info_;

    std::string to_host_;
    std::string to_port_;

};

inline SimpleClient::SimpleClient(const std::string& host_in, const std::string& port_in) {
    to_host_ = host_in;
    to_port_ = port_in;
}

inline SimpleClient::~SimpleClient(){
    freeaddrinfo(to_addr_info_);
}

inline int SimpleClient::build() {
    // get to address info
    if (get_addr_info() == -1) {
        return -1;
    }

    // init socket
    int socket_fd_ = socket(to_addr_info_->ai_family, to_addr_info_->ai_socktype, to_addr_info_->ai_protocol);
    socket_ = std::make_unique<SocketManager>(socket_fd_);
    if (socket_->get() == -1) {
        fprintf(stderr, "[SimpleClient::build] socket() error: %d\n", socket_->get());
        return -1;
    }

    // connect to address
    int connect_status = connect(socket_->get(), to_addr_info_->ai_addr, to_addr_info_->ai_addrlen);
    if (connect_status == -1) {
        fprintf(stderr, "[SimpleClient::build] connect() error: %d\n", connect_status);
        return -1;
    }
    return 0;
}

inline int SimpleClient::send_message(const std::string & message) {
    int send_status = send(socket_->get(), message.c_str(), message.size(), MSG_NOSIGNAL);
    if (send_status == -1) {
        fprintf(stderr, "[SimpleClient::send_message] send() error: %d\n", send_status);
        return -1;
    }
    printf("[SimpleClient] message sent: %s\n", message.c_str());
    return 0;
}

inline int SimpleClient::get_addr_info() {
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(to_host_.c_str(), to_port_.c_str(), &hints, &to_addr_info_);
    if (status != 0) {
        fprintf(stderr, "[SimpleClient::get_addr_info] getaddrinfo() error: %d", status);
        return -1;
    }
    return 1;
}


}