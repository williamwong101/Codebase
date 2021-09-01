#include <iostream>
#include <memory>

class Base {
private:
    int num;
public:
    Base(int num_in): num(num_in){};
    int& get_num(){
        return num;
    }
};

class Derived: public Base {
private:
    int version;
public: 
    Derived(int ver_in, int num_in): Base(num_in), version(ver_in) {};
    int& get_version() {
        return version;
    }
};

void change_num(Base& base, int target) {
    base.get_num() = target;
}

int main() {
    Derived d(1,10);
    Base& d_base_r = d; // d_base_r refers to Base subobject in Derived
    std::cout<<"Base reference to derived: " << "num: " << d_base_r.get_num() << std::endl;
    std::cout<<"Derived: " << d.get_version() <<" num: " << d.get_num() << std::endl;
    change_num(d_base_r, 5);
    std::cout<<"Base reference to derived: " << "num: " << d_base_r.get_num() << std::endl;
    std::cout<<"Derived: " << d.get_version() <<" num: " << d.get_num() << std::endl;
    change_num(d, 1);
    std::cout<<"Base reference to derived: "  << "num: " << d_base_r.get_num() << std::endl;
    std::cout<<"Derived: " << d.get_version() <<" num: " << d.get_num() << std::endl;


    int i1 = 2;
    // int&& i2 = i1;
    double&& i3 = i1;
}
