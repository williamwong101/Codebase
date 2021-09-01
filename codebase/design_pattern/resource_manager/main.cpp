#include "resource_manager.h" 
#include <string>
#include <unordered_map>

// template<typename K, typename V>
// using MemCache = std::unordered_map<K, V>;

int main() {

    // ResourceManager<MemCache<std::string, int64_t>> resource_manager;
    ResourceManager<int> int_rm;
    std::cout << "[init] construct value: "<< *int_rm.get() 
        << " address: " << int_rm.get() << std::endl;

    int* int_ptr = int_rm.get();
    *int_ptr = 5;
    std::cout << "[init] construct value: "<< *int_rm.get() 
        << " address: " << int_rm.get() << std::endl;

    ResourceManager<int> int_rm_copy(int_rm);
    std::cout << "[copy] construct value: "<< *int_rm_copy.get() 
        << " address: " << int_rm_copy.get() << std::endl;
    
    ResourceManager<int> int_rm_copy1;
    int_rm_copy1 = int_rm;
    std::cout << "[copy] assigned value: "<< *int_rm_copy1.get() 
        << " address: " << int_rm_copy1.get() << std::endl;
    
    ResourceManager<int> int_rm_copy2(std::move(int_rm_copy1));
    std::cout << "[move] construct value: "<< *int_rm_copy2.get() 
        << " address: " << int_rm_copy2.get() << std::endl;

    ResourceManager<int> int_rm_copy3;
    int_rm_copy3 = std::move(int_rm_copy2);
    std::cout << "[move] assigned value: "<< *int_rm_copy3.get() 
        << " address: " << int_rm_copy3.get() << std::endl;
}