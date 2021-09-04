#include "client.h"
#include <cstdio>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: ./client -h [to_host] -p [to_port]\n");
        return -1;
    } else if (std::string(argv[1]) != "-h" || std::string(argv[3]) != "-p") {
        fprintf(stderr, "Usage: ./client -h [to_host] -p [to_port]\n");
        return -1;
    } else {
        cb::SimpleClient client(argv[2], argv[4]);
        if (client.build() == -1) {
            return -1;
        }
        while (true) {
            std::cout << "Message to send >>";
            std::string message;
            std::cin >> message;
            if (client.send_message(message) == -1) {
                std::cout << "==Message send failed==\n";
            }
        }
    }
}