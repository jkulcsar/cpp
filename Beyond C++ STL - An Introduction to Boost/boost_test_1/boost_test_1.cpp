#include <stdexcept>
#include <exception>
#include <boost/test/included/prg_exec_monitor.hpp> 

int foo() { throw std::exception( "big trouble" ); }

int cpp_main( int, char* [] ) // note the name
{
    foo();

    return 0;
}
