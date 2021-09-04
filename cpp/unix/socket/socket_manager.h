#include <sys/types.h>         
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

namespace cb {

class SocketManager {
public:
    SocketManager() {
        fd_ = -1;
    }
    explicit SocketManager(int socket_fd) {
        fd_ = socket_fd;
    }
    SocketManager(SocketManager&& rhs) {
        fd_ = rhs.fd_;
        rhs.fd_ = -1;
    }
    ~SocketManager() {
        if(fd_ != -1) close(fd_);
    }
    int get() {
        return fd_;
    }
    SocketManager(const SocketManager&) = delete;
    SocketManager& operator=(const SocketManager&) = delete;
private:
    int fd_;
};

}