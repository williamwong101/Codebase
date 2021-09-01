#include <future>
#include <stdio.h>
#include <memory>
#include <chrono>
#include <thread>
int main() {
    static int sum = 0;
    std::mutex mtx;
    auto fut = std::async( std::launch::async, 
        [&](int n){
            while(n > 0){
                std::lock_guard<std::mutex> lk(mtx);
                sum += n;
                printf(" + %d = %d\n", n, sum);
                n--;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }, 100);
    while(true) {
        std::lock_guard<std::mutex> lk(mtx);
        printf("main thread sum: %d\n", sum);
        if(sum > 3000) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    fut.wait();
    printf("=== main thread done ===\n");
    return 0;
}