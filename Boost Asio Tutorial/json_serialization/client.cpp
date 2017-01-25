//
// client.cpp
#include <fstream>
#include "client.hpp"


namespace s11n_example {

  /// Constructor starts the asynchronous connect operation.
  client::client(
	  boost::asio::io_service& io_service,
      const std::string& host,
	  const std::string& service,
	  const std::string& symbol_file_name) 
	  :
  symbol_file_name_(symbol_file_name)
  {
	  connection_ = boost::shared_ptr<connection>(new connection(io_service));

    // Resolve the host name into an IP address.
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
      resolver.resolve(query);

    // Start an asynchronous connect operation.
	boost::asio::async_connect(connection_->socket(), endpoint_iterator,
        boost::bind(&client::handle_connect, this,
          boost::asio::placeholders::error));
  }

  /// Handle completion of a connect operation.
  void client::handle_connect(const boost::system::error_code& e)
  {
	std::cout << "client::handle_connect()" << std::endl;

    if (!e)
    {
      // Successfully established connection.

		// Read the file of symbols and send requests to the server
		std::ifstream file;
		try	{
			file.open(symbol_file_name_.c_str(), std::ios::in | std::ios::binary);
			std::string s;
			while(file >> s)
				stock_requests_.push_back( create_request_object(s) );
			file.close();

			for( size_t i = 0; i < stock_requests_.size(); ++i )
			{
			  // Write a request object to the server
				connection_->async_write((*stock_requests_.at(i)),
					boost::bind(&client::handle_write, this,
					boost::asio::placeholders::error, stock_requests_.at(i) ));
			}
			std::cout << "\tsize_of_stock_requests_: " << stock_requests_.size() << std::endl;
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}


	  // Start operation to read.
      // The connection::async_read() function will automatically
      // decode the data that is read from the underlying socket.
		// here: it could read a vector of stock objects in one shot;
		// optimize for this;
      //connection_->async_read(stocks_,
      //    boost::bind(&client::handle_read, this,
      //      boost::asio::placeholders::error));
		// current implementation is item-by-item only
      
		connection_->async_read(stock_reply_,
          boost::bind(&client::handle_read, this,
            boost::asio::placeholders::error));
    }
    else
    {
      // An error occurred. Log it and return. Since we are not starting a new
      // operation the io_service will run out of work to do and the client will
      // exit.
      std::cout << e.message() << std::endl;
    }
  }

 /// Handle completion of a write operation.

 void client::handle_write(const boost::system::error_code& e, boost::shared_ptr<stock>& s)
 {
    std::cout << "client::handle_write()" << std::endl;

	std::cout << s->_json_value_as_string << std::endl;

	//
	// delete the item, not needed anymore
	s.reset();

    if (!e)
    {
		//
		// essentially, do nothing for now if write was successful
		std::cout << "client::handle_write() - no error" << std::endl;
    }
    else
    {
      // An error occurred.
      std::cout << e.message() << std::endl;
	  
    }

	std::cout << "leaving client::handle_write()" << std::endl;
 }


 /// Handle completion of a read operation.
  void client::handle_read(const boost::system::error_code& e)
  {
	std::cout << "client::handle_read()" << std::endl;

    if (!e)
    {
		// Print out the data that was received.
		try {
			// FIXME:
			// the next two lines are very useful for debugging
			//std::cout << "The JSON value as string: " << std::endl;
			//std::cout << stock_reply_._json_value_as_string << std::endl;

			//
			// now turn the JSON value-as-string into a JSON value
			std::cout << "reading json" << std::endl;
			std::stringstream sstr( stock_reply_._json_value_as_string );
			json_spirit::read_stream_or_throw( sstr, stock_reply_._json_value );
			std::cout << "done reading json" << std::endl;

			//
			// now show the JSON value
			json_spirit::write_stream( json_spirit::Value(stock_reply_._json_value), std::cout, json_spirit::pretty_print);
			std::cout << std::endl;
			std::cout << std::endl;
		}
		catch(json_spirit::Error_position ep) {
			std::cout << ep.reason_ << " - " 
				<< " line: " << ep.line_ 
				<< " column: " << ep.column_ 
				<< std::endl;
		}
    }
    else
    {
      // An error occurred.
      std::cout << e.message() << std::endl;
	  
	  // reset pointer to themself, destroying current object
	  connection_.reset();
    }

    // Since we are not starting a new operation the io_service will run out of
    // work to do and the client will exit.
	// FIXED: keep the client connected by starting another async read
	//
	// check first if connection is still open, server may have closed it;
	// this verification may need improvement!
	//
	if( connection_ )
	{
		connection_->async_read(stock_reply_,
			boost::bind(&client::handle_read, this,
			boost::asio::placeholders::error)
			);
	}
  }

  boost::shared_ptr<stock> client::create_request_object(const std::string& item_name)
  {
	  std::cout << "in create_request_object()" << std::endl;

	  boost::shared_ptr<stock> req( new stock() );

	  // Create a simple request object, as JSON, to be sent to the server.
	  json_spirit::Object obj;
	  obj.push_back( json_spirit::Pair( "item_name", item_name ) );
	  obj.push_back( json_spirit::Pair( "data_model", "marketprice" ) );
	  obj.push_back( json_spirit::Pair( "data_flow", "streaming" ) );
	  req->_json_value = obj;

	  //
	  // done with setting-up JSON value,
	  // FIXME: now serialize it as string (could this be called inside of serialize,
	  // just before copied into the archive?
	  std::ostringstream osstr;
	  json_spirit::write_stream( json_spirit::Value(req->_json_value), osstr/*, json_spirit::pretty_print*/);

	  // is a call to str() of stringstream sstr necessary?
	  // sstr is initialized with the std::string already...
	  req->_json_value_as_string = osstr.str();

	  std::cout << "leaving create_request_object()" << std::endl;
	  return req;

  }

} // namespace s11n_example


int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 4)
    {
      std::cout << "Usage: client <host> <port> <symbol file name>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;
    s11n_example::client client(io_service, argv[1], argv[2], argv[3]);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
