//#include <cstdlib>
////#include <unistd.h>
//#include "log4cpp/Category.hh"
//#include "log4cpp/CategoryStream.hh"
//#include "log4cpp/PropertyConfigurator.hh"
//
//void grandChild ()
//{
//    log4cpp::Category& grandChild = 
//        log4cpp::Category::getInstance ("com.rbccm.arch.child.grandChild");
//	grandChild << log4cpp::Priority::INFO << "Hello from grandChild" << log4cpp::CategoryStream::ENDLINE;
//
////	log4cpp::AppenderSet appenderSet = grandChild.getAllAppenders();
//}
//
//void child ()
//{
//    log4cpp::Category& child = 
//        log4cpp::Category::getInstance ("com.rbccm.arch.child");
//	
//
//	char buffer[256];
////	message.reserve(100);
//	std::string test_string("test_string");
//	int nHexa = 1000;
//	sprintf( buffer, "testing printf with %s and %lX ", test_string.c_str(), nHexa);
//	std::string message(buffer);
//
//	
//	child << log4cpp::Priority::NOTICE << buffer << log4cpp::CategoryStream::ENDLINE;
//
//	sprintf( buffer, "a" );
//	child << log4cpp::Priority::NOTICE << buffer << log4cpp::CategoryStream::ENDLINE;
//
//    child << log4cpp::Priority::NOTICE << "Hello from child"<< log4cpp::CategoryStream::ENDLINE;
////	::Sleep(1000);
//    child << log4cpp::Priority::WARN << "Hello World! 0"<< log4cpp::CategoryStream::ENDLINE;
////	::Sleep(1000);
//    child << log4cpp::Priority::WARN << "Hello World! 1"<< log4cpp::CategoryStream::ENDLINE;
//    child << log4cpp::Priority::WARN << "Hello World! 2"<< log4cpp::CategoryStream::ENDLINE;
////	::Sleep(1000);
//    child << log4cpp::Priority::WARN << "Hello World! 3"<< log4cpp::CategoryStream::ENDLINE;
////	::Sleep(1000);
//    child << log4cpp::Priority::WARN << "Hello World! 4"<< log4cpp::CategoryStream::ENDLINE;
//  
//	grandChild ();
//}
//
//
//int main (int argc, char **argv) 
//{
//    log4cpp::PropertyConfigurator::configure ("log4cpp.properties");
//    log4cpp::Category& root = log4cpp::Category::getRoot();
//   
//    root << log4cpp::Priority::WARN << "Hello World! 0"<< log4cpp::CategoryStream::ENDLINE;
//    //root << log4cpp::Priority::WARN << "Hello World! 1";
//    //root << log4cpp::Priority::WARN << "Hello World! 2";
//    //root << log4cpp::Priority::WARN << "Hello World! 3";
//    //root << log4cpp::Priority::WARN << "Hello World! 4";
//    //root << log4cpp::Priority::WARN << "Hello World! 5";
//    child();
//    log4cpp::Category::shutdown();
//    exit (EXIT_SUCCESS);
//}
//
// testConfig.cpp : Derived from testPattern.cpp.
//

#include <log4cpp/Portability.hh>

#ifdef WIN32
#include <windows.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <cstdlib>

#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/PropertyConfigurator.hh>

double calcPi()
{
    double denominator = 3.0;
    double retVal = 4.0;
    long i;
    for (i = 0; i < 50000000l; i++)
    {
        retVal = retVal - (4.0 / denominator);
        denominator += 2.0;
        retVal = retVal + (4.0 /denominator);
        denominator += 2.0;
    }
    return retVal;
}

int main(int argc, char* argv[])
{
    try {
        /* looking for the init file in $srcdir is a requirement of
           automake's distcheck target.
        */
        char* srcdir = std::getenv("srcdir");
        std::string initFileName;
        if (srcdir == NULL) {
            initFileName = "./testConfig.log4cpp.properties";
        }
        else {
            initFileName = std::string(srcdir) + "/testConfig.log4cpp.properties";
        }
        log4cpp::PropertyConfigurator::configure(initFileName);
    } catch(log4cpp::ConfigureFailure& f) {
        std::cout << "Configure Problem " << f.what() << std::endl;
        return -1;
    }

    log4cpp::Category& root = log4cpp::Category::getRoot();

    log4cpp::Category& sub1 = 
        log4cpp::Category::getInstance(std::string("sub1"));

    log4cpp::Category& sub2 = 
        log4cpp::Category::getInstance(std::string("sub1.sub2"));

    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

    calcPi();

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");

    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

#ifdef WIN32
    Sleep(3000);
#else
    sleep(3);
#endif

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    sub2.error("%s %s %d", "test", "vform", 123);
    sub2.warnStream() << "streamed warn";

    sub2 << log4cpp::Priority::WARN << "warn2.." << "..warn3..value=" << 0 << "..warn4";

    log4cpp::Category::shutdown();

    return 0;
}

