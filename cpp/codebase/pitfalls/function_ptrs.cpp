#include <iostream>
#include <functional>
#include <stdio.h>

using func_t = bool (*)(int);
using function_t = std::function<bool(int)>;

void call_func(int num, func_t function) {
    auto ret = function(num);
    std::cout<<"[function_ptr called] call result: " << ret << std::endl;
}

void call_function(int num, function_t function) {
    auto ret = function(num);
    std::cout<<"[std::function called] call result: " << ret << std::endl;
}

bool print_cmp_10(int num) {
    printf("[print_cmp_10]: %d\n", num);
    return num >= 10;
}

bool print_cmp_5(int num) {
    printf("[print_cmp_5]: %d\n", num);
    return num >= 5;
}

int main(){

    call_func(5, print_cmp_10);
    call_func(5, &print_cmp_5);
    func_t print_cmp_1 = [](int num){
        printf("[print_cmp_1]: %d\n", num);
        return num >= 1;
    };
    call_func(5, print_cmp_1);

    std::cout<<"==========\n";

    call_function(5, print_cmp_10);
    call_function(5, &print_cmp_5);
    call_function(5, print_cmp_1);
    function_t print_cmp_100 = [](int num){
        printf("[print_cmp_100]: %d\n", num);
        return num >= 100;
    };
    call_function(5, print_cmp_100);
}