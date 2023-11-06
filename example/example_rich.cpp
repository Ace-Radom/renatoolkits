#include<iostream>

#include"renatoolkits.h"

int main(){
    rena::rich::rich_global_init();

    auto fc_entries = magic_enum::enum_entries<rena::rich::FColor>();
    for ( const auto& it : fc_entries )
    {
        std::cout << it.first << "This is " << it.second << rena::rich::style_reset << std::endl;
    }

    return 0;
}