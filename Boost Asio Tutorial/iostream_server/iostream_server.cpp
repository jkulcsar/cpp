
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/operations.hpp> // get, EOF, WOULD_BLOCK

#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    
//#include <boost/thread/lock_types.hpp>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace io = boost::iostreams;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp::endpoint endpoint(tcp::v4(), 13);
		tcp::acceptor acceptor(io_service, endpoint);

		for (;;)
		{
			tcp::iostream tcp_stream;
			acceptor.accept(*tcp_stream.rdbuf());

			io::filtering_ostream out_gzip;
			out_gzip.push(io::gzip_compressor());
			out_gzip.push(tcp_stream);

			out_gzip << make_daytime_string() /*<< EOF*/<< std::endl;
			for( std::size_t i = 0; i<100; ++i )
				out_gzip << i << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
