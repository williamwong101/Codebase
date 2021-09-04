#include <sys/types.h>         
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <functional>
#include <memory>
#include <string>
#include "socket_manager.h"
namespace cb {

class SimpleServer {
public:
    SimpleServer(const std::string& port_in="12345", int queue_size_in=5, int max_buffer_size_in=1000);
    ~SimpleServer();
    SimpleServer(const SimpleServer&) = delete;
    SimpleServer& operator=(const SimpleServer&) = delete;

    int build();
    int serve(std::function<void(const std::string&)>);


private:
    int get_addr_info(const std::string&);
    std::unique_ptr<SocketManager> accept_connection();
    int recv_message(std::string& message, int con_fd);

    int max_buffer_size_;
    struct addrinfo* addr_info_;
    std::unique_ptr<SocketManager> socket_;

    std::string port_;
    int queue_size_;
    
};

inline SimpleServer::SimpleServer(const std::string& port_in, int queue_size_in, int max_buffer_size_in){
    port_ = port_in;
    queue_size_ = queue_size_in;
    max_buffer_size_ = max_buffer_size_in;
}

inline SimpleServer::~SimpleServer(){
    freeaddrinfo(addr_info_);
}

inline int SimpleServer::build(){
    // get address
    if (get_addr_info(port_) == -1) {
        return -1;
    }

    // init socket

    int fd_ = socket(addr_info_->ai_family, addr_info_->ai_socktype, addr_info_->ai_protocol);
    socket_ = std::make_unique<SocketManager>(fd_);
    if (socket_->get() == -1) {
        fprintf(stderr, "[SimpleServer::build] socket() error: %d\n", socket_->get());
        return -1;
    }

    // bind address
    int status_bind = bind(socket_->get(), addr_info_->ai_addr, addr_info_->ai_addrlen);
    if(status_bind == -1) {
        fprintf(stderr, "[SimpleServer::serve] bind() error: %d\n", status_bind);
        return -1;
    }

    return 0;
}

inline int SimpleServer::serve(std::function<void(const std::string&)> func) {
    // start listening on the address
    int status_listen = listen(socket_->get(), queue_size_);
    if(status_listen == -1) {
        fprintf(stderr, "[SimpleServer::serve] listen() error: %d\n", status_listen);
        return -1;
    }
    printf("[SimpleServer] listening start on %s\n", port_.c_str());

    // loop to accept connection and receive message
    std::string message;
    while(true) {
        std::unique_ptr<SocketManager> con_socket = accept_connection();
        if (con_socket->get() == -1) return -1;

        while(true) {
            int status = recv_message(message, con_socket->get());
            if (status == -1) {
                return -1;
            } else if (status == -2) {
                break;
            }
            func(message);
        }
    }

    return 0;
}

inline int SimpleServer::get_addr_info(const std::string& port) {
    // set getaddrinfo()
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status_get_addrinfo = getaddrinfo(NULL, port.c_str(), &hints, &addr_info_);
    if (status_get_addrinfo != 0) {
        fprintf(stderr, "[SimpleServer::get_addr_info] getaddrinfo() error: %s\n",
            gai_strerror(status_get_addrinfo));
        return -1;
    }
    return 0;
}

inline std::unique_ptr<SocketManager> SimpleServer::accept_connection(){
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    int connection_fd_ = accept(socket_->get(), (struct sockaddr*) &their_addr, &addr_size);
    std::unique_ptr<SocketManager> con_socket = std::make_unique<SocketManager>(connection_fd_);
    if (connection_fd_ == -1) {
        fprintf(stderr, "[SimpleServer::accept_connection] accept() error: %d\n", connection_fd_);
    }
    return con_socket;
}

inline int SimpleServer::recv_message(std::string& message, int con_fd) {
    char buffer[max_buffer_size_];
    int recv_status = recv(con_fd, (void*)buffer, max_buffer_size_, MSG_NOSIGNAL);
    if (recv_status == -1) {
        fprintf(stderr, "[SimpleServer::recv_message] recv() error: %d\n", recv_status);
        return -1;
    }
    else if (recv_status == 0) {
        printf("[SimpleServer::recv_message] peer closed\n");
        return -2;
    }
    else {
        printf("[SimpleServer] recv message with %d bytes\n", recv_status);
        message = std::string(buffer, recv_status);
        printf("[SimpleServer] recv message: %s\n", message.c_str());
    }
    return 0;
}

}