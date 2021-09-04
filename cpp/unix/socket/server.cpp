#include "server.h" 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./server -p [port]\n");
        return -1;
    }
    else if (std::string(argv[1]) != "-p") {
        printf("Usage: ./server -p [port]\n");
        return -1;
    }
    else {
        cb::SimpleServer server(argv[2], 5);
        server.build();
        server.serve([](const std::string& msg){
            printf("Echo message: %s\n", msg.c_str());
        });
    }
    return 0;
}