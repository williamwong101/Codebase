#include <iostream>

class Singleton {
private:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton& sing_in) = delete;
    Singleton& operator=(const Singleton& sing_in) = delete;
    
    std::string name_;
public:
    static Singleton& instance() {
        static Singleton instance_;
        return instance_;
    }
    static void init() {
        instance();
    }
    std::string& get_name(){
        return name_;
    }
    void set_name(const std::string& name_in) {
        name_ = name_in;
    }
};


void foo () {
    // just another function
    Singleton::instance().set_name("Sing once in foo");
    std::cout << "name: " << Singleton::instance().get_name() << std::endl;
}

int main() {
    Singleton::init();
    Singleton::instance().set_name("Sing");
    std::cout << "name before foo: " << Singleton::instance().get_name() << std::endl;

    // cannot create new 
    // Singleton new_sing;
    // new_sing.set_name("new_Sing");
    foo();
    std::cout << "name after foo: " << Singleton::instance().get_name() << std::endl;
}
