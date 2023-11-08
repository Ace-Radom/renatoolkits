#include"kbe.h"

#if defined( __linux__ ) || defined( __APPLE__ )

int rena::kbe::_kbhit(){
    struct termios old_attr , new_attr;
    tcgetattr( STDIN_FILENO , &old_attr );
    new_attr = old_attr;
    new_attr.c_lflag &= ~ICANON;
    tcsetattr( STDIN_FILENO , TCSANOW , &new_attr );
    setbuf( stdin , NULL );
    int bytes_waiting;
    ioctl( STDIN_FILENO , FIONREAD , &bytes_waiting );
    tcsetattr( STDIN_FILENO , TCSANOW , &old_attr );
    return bytes_waiting;
}

char rena::kbe::_getch(){
    struct termios old_attr , new_attr;
    tcgetattr( STDIN_FILENO , &old_attr );
    new_attr = old_attr;
    new_attr.c_lflag &= ~ICANON;
    tcsetattr( STDIN_FILENO , TCSANOW , &new_attr );
    char c;
    c = getchar();
    tcsetattr( STDIN_FILENO , TCSANOW , &old_attr );
    return c;
}

#endif // defined( __linux__ ) || defined( __APPLE__ )