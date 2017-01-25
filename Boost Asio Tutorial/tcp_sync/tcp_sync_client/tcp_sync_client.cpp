//
// Boost Asio TCP Synchronous example
//

#include "client.h"

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <iostream>


int main( int argc, char** argv )
{
  try
  {
	std::cout << "Synchronous TCP asio CLIENT " << std::endl;

    boost::asio::io_service io_service;
    client c( io_service );
    c.connect( argc, argv );

    // Read ACK from Host
    message ms;
    ms.read( c.socket() );
    std::cout << " client# Received message from Host: "<< ms << std::endl;

    for(int n=0; n<5;++n)
    {
    	// Send some DATA stuff to Host
    	std::cout << " client# Send " << n << "/5 MS_DATA to Host. " << std::endl;
    	message ms_d( message::MS_DATA);
    	ms_d.setData(n);
    	ms_d.send( c.socket() );

    	boost::posix_time::millisec t(1200);
    	boost::this_thread::sleep( t );
    }

    // Send END to Host
    std::cout << " client# Send MS_END to Host. " << std::endl;
    message ms_e( message::MS_END);
    ms_e.send( c.socket() );

  }
  catch (std::runtime_error& e)  {
    std::cerr << "Client Exception: " << e.what() << "\n";
  }
  catch (std::exception& e)  {
      std::cerr << "Client Exception: " << e.what() << "\n";
    }
  return 0;
}

