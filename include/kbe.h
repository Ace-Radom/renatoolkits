// KeyBoard Events Header

#pragma once

#ifndef _KBE_H_
#define _KBE_H_

#ifdef WIN32
#include<conio.h>
#define kbhit _kbhit
#define getch _getch
#else // __linux__ || __APPLE__
#include<cstdio>
#include<termios.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/ioctl.h>
#define kbhit rena::kbe::_kbhit
#define getch rena::kbe::_getch
#endif

#if defined( __linux__ ) || defined( __APPLE__ )

namespace rena {

    namespace kbe {

        /**
         * @brief Check the console for a recent keystroke
         * 
         * @return A nonzero value if a key has been pressed. Otherwise, it returns 0.
        */
        int _kbhit();

        /**
         * @brief Read a single character from the console without echoing the character.
         * 
         * @return Returns the character read.
        */
        char _getch();
        
    }; // namespace kbe

}; // namespace rena

#endif // defined( __linux__ ) || defined( __APPLE__ )

#endif