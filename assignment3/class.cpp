#include "class.h"

man::man() : age(20), id(36) {}

man::man(const int new_age, const std::string new_name) : age(new_age), id(0), name(new_name) {}

int man::getAge() const {
    return age;
}

int man::getId() const {
    return id;
}

void man::setAge(const int new_age) {
    if (validate_age(new_age)) {
        this->age = new_age;
    }
}

bool man::validate_age(int new_age) const {
    return new_age >= 0;
}
