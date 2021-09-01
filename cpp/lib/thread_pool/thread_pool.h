#pragma once
#include <algorithm>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

class ThreadPool {
public:
    explicit ThreadPool(size_t pool_size=500);
    void concurrent_run(const std::vector<std::function<void()>>&);
    void stop();
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
private:
    std::future<void> enqueue(const std::function<void()>&);
    std::vector<std::thread> threads_pool_;
    std::queue<std::function<void()>> waiting_queue_;
    std::mutex queue_mtx_;
    std::condition_variable queue_cv_;
    bool stop_;
};


inline ThreadPool::ThreadPool(size_t pool_size): stop_(false) {
    threads_pool_.reserve(pool_size);
    std::function<void()> wrapper_ = [this](){
        while(true) {
            std::function<void()> next_task_;

            {
                std::unique_lock<std::mutex> lock_(queue_mtx_);
                queue_cv_.wait(lock_, [&](){
                    return !waiting_queue_.empty() || stop_;
                });

                if(stop_) {
                    printf("stopping\n");
                    break;
                }

                next_task_ = waiting_queue_.front();
                waiting_queue_.pop();
            }

            next_task_();
        }
    };
    for(size_t i = 0; i < pool_size; i++) {
        threads_pool_.emplace_back(wrapper_);
    }
}

inline ThreadPool::~ThreadPool(){
    stop();
    for(auto& thread: threads_pool_) {
        thread.join();
    }
}

inline void ThreadPool::concurrent_run(const std::vector<std::function<void ()>>& function_list) {
    std::vector<std::future<void>> futures;
    for(auto& func: function_list) {
        futures.push_back(enqueue(func));
    }
    for(auto& future: futures){
        future.get();
    }
}

inline void ThreadPool::stop(){
    std::unique_lock<std::mutex> stop_lock_(queue_mtx_);
    stop_ = true;
    queue_cv_.notify_all();
}

inline std::future<void> ThreadPool::enqueue(const std::function<void()>& func) {
    std::shared_ptr<std::promise<void>> task_ = std::make_shared<std::promise<void>>();
    std::future<void> task_future_ = task_->get_future();
    std::function<void()> wrapped_func = [task_, &func] () mutable {
        func();
        task_->set_value();
    };
    std::unique_lock<std::mutex> lock_(queue_mtx_);
    waiting_queue_.push(wrapped_func);
    lock_.unlock();
    queue_cv_.notify_one();
    return task_future_;
}