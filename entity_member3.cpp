#include <iostream>

#include "entity.h"
#include "entity_member3.h"

member_type3::member_type3() {
    v_.push_back(666);
}
void member_type3::test() {
    std::cout << v_.front() << "\n";
}
void member_type2::test() {
    std::cout << y << " " << z << "\n";
}
