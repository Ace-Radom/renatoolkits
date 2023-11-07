#include<iostream>

#define MAGIC_ENUM_RANGE_MAX 2048
// otherwise the magic_enum cannot iterate FStyle
#include"renatoolkits.h"

using namespace rena::rich;

int main(){
    rena::rich::rich_global_init();

    auto fc_entries = magic_enum::enum_entries<FColor>();
    for ( const auto& it : fc_entries )
    {
        std::cout << it.first << "This is Foreground " << it.second << style_reset << std::endl;
    }

    auto bc_entries = magic_enum::enum_entries<BColor>();
    for ( const auto& it : bc_entries )
    {
        std::cout << it.first << "This is Background " << it.second << style_reset << std::endl;
    }

#if RICH_COLOR_TYPE == RC_ANSI

    auto fs_entries = magic_enum::enum_entries<FStyle>();
    for ( const auto& it : fs_entries )
    {
        std::cout << it.first << "This is Style " << it.second << style_reset << std::endl;
    }

    for ( int i = 16 ; i < 256 ; i++ )
    {
        std::cout << EightBitColor( i , RICH_BACKGROUND_COLOR ) << " " << style_reset;
    }
    
    std::cout << std::endl;

    int r = 0 , g = 0 , b = 0;
    for ( r = 0 ; r < 256 ; r += 5 )
    {
        std::cout << TrueColor( r , g , b , RICH_BACKGROUND_COLOR ) << " " << style_reset;
    }
    for ( g = 0 ; g < 256 ; g += 5 , r -= 5 )
    {
        std::cout << TrueColor( r , g , b , RICH_BACKGROUND_COLOR ) << " " << style_reset;
    }
    for ( b = 0 ; b < 256 ; b += 5 , g -= 5 )
    {
        std::cout << TrueColor( r , g , b , RICH_BACKGROUND_COLOR ) << " " << style_reset;
    }

#endif

    return 0;
}