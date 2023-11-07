#pragma once

#ifndef _RICH_H_
#define _RICH_H_

#include<iostream>
#include<string>
#include<bitset>
#ifdef _WIN32
#include<Windows.h>
#endif

namespace rena {

    namespace rich {

#define RC_ANSI   0
#define RC_WINAPI 1
#ifdef _WIN32
#   ifdef RICH_USE_ANSI_COLOR_ONLY
#       define RICH_COLOR_TYPE RC_ANSI
#   else
#       define RICH_COLOR_TYPE RC_WINAPI
#   endif
#else
#   define RICH_COLOR_TYPE RC_ANSI
#endif

#if RICH_COLOR_TYPE == RC_WINAPI

        namespace win32u {
            extern CONSOLE_SCREEN_BUFFER_INFO _csbufinfo;
            extern HANDLE _WIN_STDOUT_HANDLE;

            void _get_console_screen_buffer_info();
            void _get_stdout_handle();

            extern WORD _original_color_attr;
            extern WORD _fgc; // foreground color
            extern WORD _bgc; // background color
        }; // namespace win32u

#endif // RICH_COLOR_TYPE == RC_WINAPI

        /**
         * @brief enum class FColor (Foreground Color)
        */
        enum class FColor : int {
            BLACK         = 30,
            RED           = 31,
            GREEN         = 32,
            YELLOW        = 33,
            BLUE          = 34,
            MAGENTA       = 35,
            CYAN          = 36,
            WHITE         = 37,
            GRAY          = 90,
            BRIGHTRED     = 91,
            BRIGHTGREEN   = 92,
            BRIGHTYELLOW  = 93,
            BRIGHTBLUE    = 94,
            BRIGHTMAGENTA = 95,
            BRIGHTCYAN    = 96,
            BRIGHTWHITE   = 97
        };

        /**
         * @brief enum class BColor (Background Color)
        */
        enum class BColor : int {
            BLACK         = 40,
            RED           = 41,
            GREEN         = 42,
            YELLOW        = 43,
            BLUE          = 44,
            MAGENTA       = 45,
            CYAN          = 46,
            WHITE         = 47,
            GRAY          = 100,
            BRIGHTRED     = 101,
            BRIGHTGREEN   = 102,
            BRIGHTYELLOW  = 103,
            BRIGHTBLUE    = 104,
            BRIGHTMAGENTA = 105,
            BRIGHTCYAN    = 106,
            BRIGHTWHITE   = 107
        };

        /**
         * @brief push one fontground color to ostream
        */
        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , FColor __fc );

        /**
         * @brief push one background color to otream
        */
        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , BColor __bc );

        /**
         * @brief reset all color style to default
         * 
         * @note Under Windows (and using WIN API) it will reset console text attr to the original attr got when calling renash_toolkit_global_init.
         *       Under Linux (or using ANSI under Windows) it pushes '\033[0m' to ostream.
        */
        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& style_reset( std::basic_ostream<_Elem,_Traits>& __os );

        /**
         * @brief clear one line's characters
        */
        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& clear_line( std::basic_ostream<_Elem,_Traits>& __os );

#pragma region RC_ANSI_ONLY

#if RICH_COLOR_TYPE == RC_ANSI

        /**
         * @brief enum class FStyle (Foreground text Style: bold, dim, itatic, underline)
         * 
         * @note if you're using Windows and undefined RICH_USE_ANSI_COLOR_ONLY in CMakeLists.txt, FStyle will not be available
        */
        enum class FStyle : int {
            BOLD   = 256,
            ITATIC = 512,
            DIM    = 1024,
            ULINE  = 2048 // underline
        };

        inline FColor operator|( FColor __fc , FStyle __ft ){ return static_cast<FColor>( static_cast<unsigned int>( __fc ) | static_cast<unsigned int>( __ft ) ); }
        inline FColor operator|( FStyle __ft , FColor __fc ){ return static_cast<FColor>( static_cast<unsigned int>( __fc ) | static_cast<unsigned int>( __ft ) ); }
        inline FStyle operator|( FStyle __ftl , FStyle __ftr ){ return static_cast<FStyle>( static_cast<unsigned int>( __ftl ) | static_cast<unsigned int>( __ftr ) ); }

        /**
         * @brief push one fontground style to ostream
        */
        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , FStyle __fs );

#define RICH_BACKGROUND_COLOR 0
#define RICH_FOREGROUND_COLOR 1


        /**
         * @brief Basic_EightBitColor Class: build a 8bit color ANSI code
        */
        class EightBitColor {
            public:
                enum class Grayscale : unsigned short {
                    Grayscale0  = 232,
                    Grayscale1  = 233,
                    Grayscale2  = 234,
                    Grayscale3  = 235,
                    Grayscale4  = 236,
                    Grayscale5  = 237,
                    Grayscale6  = 238,
                    Grayscale7  = 239,
                    Grayscale8  = 240,
                    Grayscale9  = 241,
                    Grayscale10 = 242,
                    Grayscale11 = 243,
                    Grayscale12 = 244,
                    Grayscale13 = 245,
                    Grayscale14 = 246,
                    Grayscale15 = 247,
                    Grayscale16 = 248,
                    Grayscale17 = 249,
                    Grayscale18 = 250,
                    Grayscale19 = 251,
                    Grayscale20 = 252,
                    Grayscale21 = 253,
                    Grayscale22 = 254,
                    Grayscale23 = 255
                }; // enum class Grayscale

            public:
                /**
                 * @brief build a 8bit color ANSI code with a single color-code (from 0 ~ 255)
                 * 
                 * @param __code single color-code (from 0 ~ 255)
                 * @param __fob fore- or background color (use RICH_BACKGROUND_COLOR or RICH_FOREGROUND_COLOR)
                */
                inline EightBitColor( unsigned short __code , bool __fob ){
                    this -> code = __code;
                    this -> fob = __fob;
                    return;
                }

                /**
                 * @brief build a 8bit color ANSI code with rgb
                 * 
                 * @param __r red (0 ~ 5)
                 * @param __g green (0 ~ 5)
                 * @param __b blue (0 ~ 5)
                 * @param __fob fore- or background color (use RICH_BACKGROUND_COLOR or RICH_FOREGROUND_COLOR)
                */
                inline EightBitColor( unsigned short __r , unsigned short __g , unsigned short __b , bool __fob ){
#define _MAX_5( x ) ( x <= 5 ? x : 5 )
                    this -> code = _MAX_5( __r ) * 36 + _MAX_5( __g ) * 6 + _MAX_5( __b ) + 16;
                    this -> fob = __fob;
#undef _MAX_5
                    return;
                }

                /**
                 * @brief build a 8bit color ANSI code for grayscale (232 ~ 255)
                 * 
                 * @param __g Grayscale (use defs under enum class rena::rich::EightBitColor::Grayscale)
                 * @param __fob fore- or background color (use RICH_BACKGROUND_COLOR or RICH_FOREGROUND_COLOR)
                */
                inline EightBitColor( Grayscale __g , bool __fob ){
                    this -> code = static_cast<unsigned short>( __g );
                    this -> fob = __fob;
                    return;
                }
                ~EightBitColor(){};

                template <class _Elem , class _Traits>
                inline void _dump_ANSI_code( std::basic_ostream<_Elem,_Traits>& __os ) const {
                    __os << "\033[" << ( this -> fob ? "38;5;" : "48;5;" ) << this -> code << "m";
                    return;
                }

            private:
                unsigned short code;
                bool fob; // foreground or background
        }; // class EightBitColor

        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const EightBitColor& __8bitc );

        class TrueColor {
            public:
                /**
                 * @brief build a 24bit true color ANSI code with rgb
                 * 
                 * @param __r red (0 ~ 255)
                 * @param __g green (0 ~ 255)
                 * @param __b blue (0 ~ 255)
                 * @param __fob fore- or background color (use RICH_BACKGROUND_COLOR or RICH_FOREGROUND_COLOR)
                */
                inline TrueColor( unsigned short __r , unsigned short __g , unsigned short __b , bool __fob ){
#define _MAX_255( x ) ( x <= 255 ? x : 255 )
                    this -> r = _MAX_255( __r );
                    this -> g = _MAX_255( __g );
                    this -> b = _MAX_255( __b );
                    this -> fob = __fob;
#undef _MAX_255
                }
                inline ~TrueColor(){};
                
                template <class _Elem , class _Traits>
                inline void _dump_ANSI_code( std::basic_ostream<_Elem,_Traits>& __os ) const {
                    __os << "\033[" << ( this -> fob ? "38;2;" : "48;2;" ) << this -> r << ";"
                                                                           << this -> g << ";"
                                                                           << this -> b << "m";
                    return;
                }

            private:
                unsigned short r;
                unsigned short g;
                unsigned short b;
                bool fob;
        }; // class TrueColor

        template <class _Elem , class _Traits>
        inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const TrueColor& __tc );

#undef _TO_PCHAR_OR_PWCHAR
#undef _TO_STR_OR_WSTR

#endif // RICH_COLOR_TYPE == RC_ANSI

#pragma endregion RC_ANSI_ONLY

        void rich_global_init();

    }; // namespace rich

}; // namespace rena

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::operator<<( std::basic_ostream<_Elem,_Traits>& __os , rena::rich::FColor __fc ){

#if RICH_COLOR_TYPE == RC_WINAPI

    // when using win api to set color, foreground text style will not be available

    switch ( __fc ) {
        case FColor::BLACK:         win32u::_fgc = 0x0000; break;
        case FColor::RED:           win32u::_fgc = 0x0004; break;
        case FColor::GREEN:         win32u::_fgc = 0x0002; break;
        case FColor::YELLOW:        win32u::_fgc = 0x0006; break;
        case FColor::BLUE:          win32u::_fgc = 0x0001; break;
        case FColor::MAGENTA:       win32u::_fgc = 0x0005; break;
        case FColor::CYAN:          win32u::_fgc = 0x0003; break;
        case FColor::WHITE:         win32u::_fgc = 0x0007; break;
        case FColor::GRAY:          win32u::_fgc = 0x0008; break;
        case FColor::BRIGHTRED:     win32u::_fgc = 0x000C; break;
        case FColor::BRIGHTGREEN:   win32u::_fgc = 0x000A; break;
        case FColor::BRIGHTYELLOW:  win32u::_fgc = 0x000E; break;
        case FColor::BRIGHTBLUE:    win32u::_fgc = 0x0009; break;
        case FColor::BRIGHTMAGENTA: win32u::_fgc = 0x000D; break;
        case FColor::BRIGHTCYAN:    win32u::_fgc = 0x000B; break;
        case FColor::BRIGHTWHITE:   win32u::_fgc = 0x000F; break;
        default: return __os;
    };

    SetConsoleTextAttribute( win32u::_WIN_STDOUT_HANDLE , win32u::_fgc | win32u::_bgc );

#else // using WIN API

    unsigned int chandle = static_cast<unsigned int>( __fc );
    unsigned int cpart = std::bitset<8>( chandle ).to_ulong(); // color part
    __os << "\033[" << cpart;

    if ( chandle & static_cast<unsigned int>( rena::rich::FStyle::BOLD   ) ) __os << ";1";
    if ( chandle & static_cast<unsigned int>( rena::rich::FStyle::DIM    ) ) __os << ";2";
    if ( chandle & static_cast<unsigned int>( rena::rich::FStyle::ITATIC ) ) __os << ";3";
    if ( chandle & static_cast<unsigned int>( rena::rich::FStyle::ULINE  ) ) __os << ";4";
    // has FStyle

    __os << "m" << std::flush;

#endif // using ANSI

    return __os;
}

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::operator<<( std::basic_ostream<_Elem,_Traits>& __os , rena::rich::BColor __bc ){

#if RICH_COLOR_TYPE == RC_WINAPI

    switch ( __bc ) {
        case BColor::BLACK:         win32u::_bgc = 0x0000; break;
        case BColor::RED:           win32u::_bgc = 0x0040; break;
        case BColor::GREEN:         win32u::_bgc = 0x0020; break;
        case BColor::YELLOW:        win32u::_bgc = 0x0060; break;
        case BColor::BLUE:          win32u::_bgc = 0x0010; break;
        case BColor::MAGENTA:       win32u::_bgc = 0x0050; break;
        case BColor::CYAN:          win32u::_bgc = 0x0030; break;
        case BColor::WHITE:         win32u::_bgc = 0x0070; break;
        case BColor::GRAY:          win32u::_bgc = 0x0080; break;
        case BColor::BRIGHTRED:     win32u::_bgc = 0x00C0; break;
        case BColor::BRIGHTGREEN:   win32u::_bgc = 0x00A0; break;
        case BColor::BRIGHTYELLOW:  win32u::_bgc = 0x00E0; break;
        case BColor::BRIGHTBLUE:    win32u::_bgc = 0x0090; break;
        case BColor::BRIGHTMAGENTA: win32u::_bgc = 0x00D0; break;
        case BColor::BRIGHTCYAN:    win32u::_bgc = 0x00B0; break;
        case BColor::BRIGHTWHITE:   win32u::_bgc = 0x00F0; break;
        default: return __os;
    };

    SetConsoleTextAttribute( win32u::_WIN_STDOUT_HANDLE , win32u::_fgc | win32u::_bgc );

#else // using WIN API

    unsigned int chandle = static_cast<unsigned int>( __bc );
    unsigned int cpart = std::bitset<8>( chandle ).to_ulong(); // color part
    __os << "\033[" << cpart << "m" << std::flush;

#endif // using ANSI

    return __os;
}

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::style_reset( std::basic_ostream<_Elem,_Traits>& __os ){

#if RICH_COLOR_TYPE == RC_WINAPI
    win32u::_fgc = 0;
    win32u::_bgc = 0;
    SetConsoleTextAttribute( win32u::_WIN_STDOUT_HANDLE , win32u::_original_color_attr );
#else // using WIN API
    __os << "\033[0m" << std::flush;
#endif // using ANSI

    return __os;
}

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::clear_line( std::basic_ostream<_Elem,_Traits>& __os ){

#if RICH_COLOR_TYPE == RC_WINAPI
    win32u::_get_console_screen_buffer_info();
    COORD cp; // cursor position
    cp.X = 0;
    cp.Y = win32u::_csbufinfo.dwCursorPosition.Y;
    SetConsoleCursorPosition( win32u::_WIN_STDOUT_HANDLE , cp );
    DWORD cw; // chars written
    FillConsoleOutputCharacter( win32u::_WIN_STDOUT_HANDLE , ' ' , win32u::_csbufinfo.dwSize.X , cp , &cw );
    SetConsoleCursorPosition( win32u::_WIN_STDOUT_HANDLE , cp );
#else
    __os << "\033[2K\r" << std::flush;
#endif

    return __os;
}

#if RICH_COLOR_TYPE == RC_ANSI

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::operator<<( std::basic_ostream<_Elem,_Traits>& __os , FStyle __fs ){
    bool one_pushed = false;
    unsigned int shandle = static_cast<unsigned int>( __fs );
    __os << "\033[";

#define FSTYLE_ANSI_PUSH( os , code ) {     \
        if ( !one_pushed )                  \
        {                                   \
            one_pushed = true;              \
            os << #code;                    \
        }                                   \
        else                                \
        {                                   \
            os << ";" << #code;             \
        }                                   \
    }

    if ( shandle & static_cast<unsigned int>( rena::rich::FStyle::BOLD   ) ) FSTYLE_ANSI_PUSH( __os , 1 );
    if ( shandle & static_cast<unsigned int>( rena::rich::FStyle::DIM    ) ) FSTYLE_ANSI_PUSH( __os , 2 );
    if ( shandle & static_cast<unsigned int>( rena::rich::FStyle::ITATIC ) ) FSTYLE_ANSI_PUSH( __os , 3 );
    if ( shandle & static_cast<unsigned int>( rena::rich::FStyle::ULINE  ) ) FSTYLE_ANSI_PUSH( __os , 4 );

#undef FSTYLE_ANSI_PUSH

    __os << "m" << std::flush;
    return __os;
}

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::operator<<( std::basic_ostream<_Elem,_Traits>& __os , const rena::rich::EightBitColor& __8bitc ){
    __8bitc._dump_ANSI_code( __os );
    __os << std::flush;
    return __os;
}

template <class _Elem , class _Traits>
std::basic_ostream<_Elem,_Traits>& rena::rich::operator<<( std::basic_ostream<_Elem,_Traits>& __os , const rena::rich::TrueColor& __tc ){
    __tc._dump_ANSI_code( __os );
    __os << std::flush;
    return __os;
}

#endif // RICH_COLOR_TYPE == RC_ANSI

#endif