#include <string>

class man {
private:
    int age;
    int id;

    bool validate_age(int new_age) const;

public:
    std::string name;

    man();
    man(const int new_age, const std::string new_name);
    int getAge() const;
    int getId() const;
    void setAge(const int new_age);
};