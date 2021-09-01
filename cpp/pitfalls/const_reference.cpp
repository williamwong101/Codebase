#include <iostream>
#include <memory>

class Widget {
private:
    int num;
public:
    Widget(int num_in):num(num_in){};
    void print_num() const {
        std::cout<<num<<"\n";
    }
};

void print_widget(const Widget& w){
    std::cout<<"const reference called:\n";
    w.print_num();
}
void print_widget(Widget&& w){
    std::cout<<"rvalue reference called:\n";
    w.print_num();
}

int main(){
    Widget tmp(5);
    print_widget(tmp);
    print_widget(std::move(tmp));
}