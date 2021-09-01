#include <unordered_map>
#include <string>
#include <stdio.h>
#include <memory>

class Base {
public:
    Base(std::string name) : name_(name) {}

    virtual void print_name() {
        printf("Base: %s\n", name_.c_str());
    }

protected:
    std::string name_;
};

#define DERIVED_CLASS(class_name)               \
    class Derived##class_name : public Base {   \
    public:                                     \
        Derived##class_name() : Base(#class_name) {};    \
        void print_name() override {            \
            printf("Derived: %s\n", name_.c_str());     \
        }                                       \
    }

DERIVED_CLASS(Class_0);
DERIVED_CLASS(Class_1);
DERIVED_CLASS(Class_2);


class Registry {
public:
    
    void register_class(std::string name, std::shared_ptr<Base> class_ptr) {
        registry_.emplace(name, class_ptr);
    }

    std::shared_ptr<Base> get_class(std::string class_name) {
        auto iter = registry_.find(class_name);
        if (iter != registry_.end()) {
            return iter->second;
        }
        else {
            return nullptr;
        }
    }

    // singleton
    static Registry& get_instance() {
        static Registry instance;
        return instance;
    }
    static void init() {
        get_instance();
    }

private:
    Registry() {}
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;
    
    std::unordered_map<std::string, std::shared_ptr<Base>> registry_;
};

#define REGISTER(class_name)                                            \
    Registry::get_instance()                                            \
        .register_class(#class_name, std::make_shared<Derived##class_name>())  \
