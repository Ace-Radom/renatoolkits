#include"rich.h"

#if RICH_COLOR_TYPE == RC_WINAPI

CONSOLE_SCREEN_BUFFER_INFO rena::rich::win32u::_csbufinfo;
HANDLE rena::rich::win32u::_WIN_STDOUT_HANDLE = nullptr;

void rena::rich::win32u::_get_console_screen_buffer_info(){
    GetConsoleScreenBufferInfo( _WIN_STDOUT_HANDLE , &_csbufinfo );
    return;
}

void rena::rich::win32u::_get_stdout_handle(){
    _WIN_STDOUT_HANDLE = GetStdHandle( STD_OUTPUT_HANDLE );
    return;
}

WORD rena::rich::win32u::_original_color_attr = 0;
WORD rena::rich::win32u::_fgc = 0;
WORD rena::rich::win32u::_bgc = 0;

#endif // RICH_COLOR_TYPE == RC_WINAPI


void rena::rich::rich_global_init(){
#if RICH_COLOR_TYPE == RC_WINAPI
    win32u::_get_stdout_handle();
    win32u::_get_console_screen_buffer_info();
    win32u::_original_color_attr = win32u::_csbufinfo.wAttributes;
#endif
    return;
}
