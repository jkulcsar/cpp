//
// server.cpp

#include <cstdlib>
#include "server.hpp"

namespace s11n_example {

	/// Constructor opens the acceptor and starts waiting for the first incoming
	/// connection.
	server::server(
		boost::asio::io_service& io_service,
		unsigned short port,
		concurrent_queue<boost::shared_ptr<stock> >& q)
		: acceptor_(io_service,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		timer_( io_service, boost::posix_time::millisec(1000)),
		timer_started_(false),
		stock_data_queue_(q)
	{

		// seed the random number generator
		srand( (unsigned)time( NULL ) );

		// Start an accept operation for a new connection.
		connection_ptr new_conn(new connection(acceptor_.get_io_service()));

		acceptor_.async_accept(new_conn->socket(),
			boost::bind(&server::handle_accept, this,
			boost::asio::placeholders::error, new_conn));
	}

		void server::consume_data()
	{
		while(true)
		{
			boost::shared_ptr<stock> s;
			stock_data_queue_.wait_and_pop(s);
			write(s);
		}
	}

	/// Handle completion of a accept operation.
	void server::handle_accept(const boost::system::error_code& e, connection_ptr conn)
	{
		std::cout << "in server::handle_accept()" << std::endl;
		if (!e)
		{
			data_consumer_thread_ = boost::thread( boost::bind(&server::consume_data, this) );

			// Successfully accepted a new connection.
			// Send the list of stocks to the
			// client. The connection::async_write() function will automatically
			// serialize the data structure for us.
			////conn->async_write(stocks_,
			////    boost::bind(&server::handle_write, this,
			////      boost::asio::placeholders::error, conn));
			
			//client_connections_.push_back( conn );
			connection_manager_.start( conn );

			//
			// so the server can read incoming requests!
			conn->async_read(stock_request_,
				boost::bind(&server::handle_read, this,
				boost::asio::placeholders::error, conn));
		}

		// Start an accept operation for a new connection.
		connection_ptr new_conn(new connection(acceptor_.get_io_service()));
		acceptor_.async_accept(new_conn->socket(),
			boost::bind(&server::handle_accept, this,
			boost::asio::placeholders::error, new_conn));

		if( !timer_started_ ) {
			//
			// on completion of accepting a new client,
			// just setup another timeout
			timer_.expires_at(timer_.expires_at() + boost::posix_time::milliseconds(1000));
			timer_.async_wait(boost::bind(&server::handle_timer_tick, this));
			timer_started_ = true;
		}
	}


	/// Handle completion of a read operation.
	void server::handle_read(const boost::system::error_code& e, connection_ptr conn)
	{
		std::cout << "in server::handle_read()" << std::endl;
		if (!e)
		{
				try {
					std::cout << "The JSON value as string: " << std::endl;
					std::cout << stock_request_._json_value_as_string << std::endl;

					//
					// now turn the JSON value-as-string into a JSON value
					std::stringstream sstr( stock_request_._json_value_as_string );
					json_spirit::read_stream_or_throw( sstr, stock_request_._json_value );

					//
					// now show the JSON value
					json_spirit::write_stream( json_spirit::Value(stock_request_._json_value), std::cout, json_spirit::pretty_print);
					std::cout << std::endl;
					std::cout << std::endl;

					//
					// extract requested item name and properties
					const json_spirit::Object& obj = stock_request_._json_value.get_obj();
					for( json_spirit::Object::size_type i = 0; i != obj.size(); ++i )
					{
						const json_spirit::Pair& pair = obj[i];

						const std::string& name  = pair.name_;
						const json_spirit::Value&  value = pair.value_;

						json_spirit::Value_type vType = pair.value_.type();

						if( (name == "item_name") && !(vType == json_spirit::Value_type::null_type) )
						{
							if( request_table_.find(value.get_str()) != request_table_.end() )
							{
								std::list<boost::weak_ptr<connection> > conn_list = request_table_[value.get_str()];
								conn_list.push_back( boost::weak_ptr<connection>(conn));
							}
							else
							{
								std::list<boost::weak_ptr<connection> > conn_list;
								conn_list.push_back(boost::weak_ptr<connection>(conn));
								request_table_.insert( std::make_pair( value.get_str(), conn_list ) );

								//
								// purely helper for the random data generator:
								// if it's a new item request, add it to the simplified table
								// so the random data generator can pick one randomly, based on
								// it's index in the vector
								vec_of_req_items_.push_back( value.get_str() );
							}

							// 
							// this is the equivalent of subscribing to the item
							// requested by the client, sending the subscription to
							// another source service;
							// here: it does not apply; the create_payload_data() function
							// will look at the request_table and randomly choose a few symbols,
							// generate data for these
//							broker_.subscribe(value.get_str(), listener_);
						}
					}
				}
				catch(json_spirit::Error_position ep) {
					std::cerr << ep.reason_ << " - " 
						<< " line: " << ep.line_ 
						<< " column: " << ep.column_ 
						<< std::endl;
				}

			//
			// keep the server reading incoming requests
			conn->async_read(stock_request_,
				boost::bind(&server::handle_read, this,
				boost::asio::placeholders::error, conn));
		}
		else
		{
			// An error occurred.
			std::cerr << e.message() << std::endl;

			// if error reading from client,
			// reset pointer to themself, destroying current object
			connection_manager_.stop(conn);
			//	  conn.reset();
		}
	}

	/// Handle completion of a write operation.
	void server::handle_write(const boost::system::error_code& e, connection_ptr conn, boost::shared_ptr<stock>& s)
	{
		std::cout << "in server::handle_write()" << std::endl;
		if(!e)
		{
			//
			// decrement the counter on the shared_ptr; by this point it should be destroyed
			s.reset();

			//// Nothing to do. The socket will be closed automatically when the last
			//// reference to the connection object goes away.
			//
			// FIXED: for the existing connection, as long as it's valid, keep:
			// - generating data
			// - writing it on the client connection
			// - reset the async wait timer
			if( conn )
			{
				// FIXME:
				// this is a great model to call handle_write on itself
				// to pull data from a concurrent queue, item by item
				// and write out
				// the handle_timer would be the notifier call,
				// when data is added to the concurrent queue
				//
				//stocks_.pop_front();

				//bool write_in_progress = !stocks_.empty();
				//if (!write_in_progress)
				//{
				//	conn->async_write(stocks_.front(),
				//		boost::bind(&server::handle_write, this,
				//		boost::asio::placeholders::error, *conn));
				//}
				//
			}
		}
		else
		{
			connection_manager_.stop(conn);
			//
			// FIXME:
			// now verify all items that were requested through this connection;
			// if this was the last connection associated with an item,
			// remove the item from the request_table
			//...
			//
			//
			//client_connections_.remove(conn);
			//		  conn.reset();
		}
	}

	void server::handle_stop()
	{
	  // The server is stopped by cancelling all outstanding asynchronous
	  // operations. Once all operations have finished the io_service::run() call
	  // will exit.
	  acceptor_.close();
	  connection_manager_.stop_all();
	  data_consumer_thread_.join();
	}

	void server::handle_timer_tick()
	{
		std::cout << "in handle_timer_tick()" << std::endl;
		std::cout << "\tsize of data array: " << stocks_.size() << std::endl;
		
		create_payload_data();

		// setup another timeout
		timer_.expires_at(timer_.expires_at() + boost::posix_time::milliseconds(1000));
		timer_.async_wait(boost::bind(&server::handle_timer_tick, this));

		
//		bool write_in_progress = !stocks_.empty();
//	    if (!write_in_progress)
//		{
			//
			// iterate through all open connections
			// and write the payload data to each
		    // FIXED: no need to write in the timer handler
		// the consume_data thread will write as soon as data is
		// pushed on the queue
			//std::list<connection_ptr>::const_iterator citer_conn = client_connections_.begin();
			//while( citer_conn != client_connections_.end() )
			//{

			//	(*citer_conn)->async_write(stocks_,
			//		boost::bind(&server::handle_write, this,
			//		boost::asio::placeholders::error, *citer_conn));

			//	++citer_conn;
			//}
//		}

//		reset_payload_data();
	}

	void server::create_payload_data()
	{
		std::cout << "in create_payload_data()" << std::endl;
		// Create the data to be sent to each client.

		size_t number_of_items_requested = request_table_.size();
		if( !number_of_items_requested )
			return;

		size_t number_of_items_to_generate = (double)rand() / (RAND_MAX + 1) * number_of_items_requested;

		
		for( size_t i = 0; i < number_of_items_to_generate; i++ )
		{
			int rnd_idx = (double)rand() / (RAND_MAX + 1) * vec_of_req_items_.size();
			request_table_type::key_type item_name = vec_of_req_items_[rnd_idx];

			boost::shared_ptr<stock> s(new stock());

			json_spirit::Object obj;

			obj.push_back( json_spirit::Pair( "item_name", item_name ) );

			size_t numberOfFields = (double)rand() / (RAND_MAX + 1) * 20;
			for( size_t field_idx = 0; field_idx < numberOfFields; ++field_idx ) {
				const std::string field_name = "field_name_" + boost::lexical_cast<std::string>(field_idx);
				obj.push_back( json_spirit::Pair( field_name, boost::lexical_cast<std::string>(field_idx) ) );
			}

			s->_json_value = obj;

			//
			// done with setting-up JSON value,
			// FIXME: now serialize it as string (could this be called inside of serialize,
			// just before copied into the archive?
			std::ostringstream osstr;
			json_spirit::write_stream( json_spirit::Value(s->_json_value), osstr/*, json_spirit::pretty_print*/);

			// is a call to str() of stringstream sstr necessary?
			// sstr is initialized with the std::string already...
			s->_json_value_as_string = osstr.str();

			stock_data_queue_.push(s);
			//stocks_.push_back(s);
		}
	}

	void server::reset_payload_data()
	{
		std::cout << "in reset_payload_data()" << std::endl;
		stocks_.clear();
	}


	void server::write(const boost::shared_ptr<stock>& s)
	{
		const json_spirit::Object& obj = s->_json_value.get_obj();
		for( json_spirit::Object::size_type i = 0; i != obj.size(); ++i )
		{
			const json_spirit::Pair& pair = obj[i];

			const std::string& name  = pair.name_;
			const json_spirit::Value&  value = pair.value_;

			json_spirit::Value_type vType = pair.value_.type();

			if( (name == "item_name") && !(vType == json_spirit::Value_type::null_type) )
			{
				if( request_table_.find(value.get_str()) != request_table_.end() )
				{
					std::list<boost::weak_ptr<connection> > conn_list = request_table_.at(value.get_str());
					std::list<boost::weak_ptr<connection> >::iterator iter_conn = conn_list.begin();
					while( iter_conn != conn_list.end() )
					{
						if( boost::shared_ptr<connection> sp_conn = iter_conn->lock() )
						{
							sp_conn->async_write(*s,
								boost::bind(&server::handle_write, this,
								boost::asio::placeholders::error, sp_conn, s));
						}
						++iter_conn;
					}
				}
				else
				{
					//
					// no connection listening to this item; unsolicited?
				}
			}
		}
	}

} // namespace s11n_example



int main(int argc, char* argv[])
{
	try
	{
		// Check command line arguments.
		if (argc != 2)
		{
			std::cerr << "Usage: server <port>" << std::endl;
			return 1;
		}
		unsigned short port = boost::lexical_cast<unsigned short>(argv[1]);

		boost::asio::io_service io_service;
		concurrent_queue< boost::shared_ptr<s11n_example::stock> > the_stock_data_queue;
		s11n_example::server server(io_service, port, the_stock_data_queue);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

