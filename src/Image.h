#ifndef IMAGE
#define IMAGE

#include <string>
#include <iostream>

class Image {
    std::string m_name;
public:
    Image(const std::string name) : m_name(name)
    {}

    const std::string getName() const {
        return m_name;
    }

    friend std::ostream& operator<<(std::ostream &os, const Image& obj) {
        os << obj.getName();
        return os;
    }

};

#endif