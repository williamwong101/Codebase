#include "thread_pool.h"
#include <stdio.h>
#include <memory>

int main() {
    ThreadPool thread_pool(600);

    std::vector<std::function<void()>> func_list;
    for(int i = 0; i < 100; i++){
        auto func_print = [i](){
            for(int j = i; j >= 0; j--){
                printf("[thread %d] printing %d\n", i, j);
            }
        };
        func_list.emplace_back(std::move(func_print));
    }

    thread_pool.concurrent_run(func_list);
    thread_pool.stop();
    return 0;
}