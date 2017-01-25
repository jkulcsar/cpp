
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

#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace io = boost::iostreams;


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: daytime_client <host>" << std::endl;
      return 1;
    }

    tcp::iostream tcp_stream(argv[1], "daytime");

	//
	// setup a gzip decompressor stream
	// and copy the output of this stream into a file
	io::filtering_streambuf<io::input> in_gzip;
	in_gzip.push(io::gzip_decompressor());
	in_gzip.push(tcp_stream);
	std::ostringstream ostr;
	io::copy(in_gzip, ostr);
	std::cout << ostr.str() << std::endl;


    //std::string line;
    //std::getline(tcp_stream, line);
    //std::cout << line << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
