#include"renatoolkits.h"

int main( int argc , char** argv ){
    rena::cmdline::parser cmdparser;
    cmdparser.add<std::string>( "host" , 'h' , "host name" , true , "" );
    cmdparser.add<int>( "port" , 'p' , "port number" , false , 80 , rena::cmdline::range( 1 , 65535 ) );
    cmdparser.add<std::string>( "type" , 't' , "protocol type" , false , "http" , rena::cmdline::oneof<std::string>( "http" , "https" , "ssh" , "ftp" ) );
    cmdparser.add( "gzip" , '\0' , "gzip when transfer" );
    cmdparser.parse_check( argc , argv );
    std::cout << cmdparser.get<std::string>( "type" ) << "://"
              << cmdparser.get<std::string>( "host" ) << ":"
              << cmdparser.get<int>( "port" ) << std::endl;
    if ( cmdparser.exist( "gzip" ) )
        std::cout << "gzip" << std::endl;
    return 0;            
}