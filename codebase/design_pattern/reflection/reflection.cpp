#include "reflection.h"

int main() {
    Registry::init();
    REGISTER(Class_0);
    REGISTER(Class_1);
    REGISTER(Class_2);

    auto derived_0 = Registry::get_instance().get_class("Class_0");
    derived_0->print_name();

    auto derived_1 = Registry::get_instance().get_class("Class_1");
    derived_1->print_name();

    return 0;
}