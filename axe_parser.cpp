#include <iostream>


#include "axe.h"

namespace axs = axe::shortcuts;
int main() {
    
    std::string input = "an_identifier = 10;";
    std::string name;
    size_t length(0);
    std::string value;
    
    auto rule_ident = axe::r_ident() >> name >> axe::e_length(length);
    
    
    auto rule = rule_ident > *axs::_s > "=" > *axs::_s > +axs::_d >> value > *axs::_s > ";";
    
    rule(input.begin(), input.end());
    std::cout << "parsed identifier: " <<  name << " is " << length << " characters long\n";
    std::cout << "value: " << value << "\n";
}
