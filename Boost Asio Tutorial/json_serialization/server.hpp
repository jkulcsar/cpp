
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <list>
#include <queue>
#include "connection.hpp" // Must come before boost/serialization headers.
#include "connection_manager.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/weak_ptr.hpp>
#include "stock.hpp"
#include "concurrent_queue.hpp"

namespace s11n_example {

	// FIXME:
	// this is a push-only server; once a client connection has been established,
	// the server will only write, unaware if in the meantime the client closed
	// the connection
	//
	// two solutions:
	// (1) wrap each client connection in a session for state management
	// (2) server should always fire up an async_read and check on error
	//		if there's an error, means that client connection is no longer valid
	//

	/// Serves stock quote information to any client that connects to it.
	class server
	{
	public:
		/// Constructor opens the acceptor and starts waiting for the first incoming
		/// connection.
		server(
			boost::asio::io_service& io_service,
			unsigned short port,
			concurrent_queue<boost::shared_ptr<stock> >& data_queue);

		/// Handle completion of a accept operation.
		void handle_accept(const boost::system::error_code& e, connection_ptr conn);


		/// Handle completion of a read operation.
		void handle_read(const boost::system::error_code& e, connection_ptr conn);

		/// Handle completion of a write operation.
		void handle_write(const boost::system::error_code& e, connection_ptr conn, boost::shared_ptr<stock>& s);

		/// Handle a request to stop the server.
		void handle_stop();

		void handle_timer_tick();
		void create_payload_data();
		void reset_payload_data();
		void write(const boost::shared_ptr<stock>& );
		void consume_data();

	private:
		/// The acceptor object used to accept incoming socket connections.
		boost::asio::ip::tcp::acceptor acceptor_;

		/// The data to be sent to each client.
		std::vector<stock> stocks_;

		/// The connection manager which owns all live connections.
		connection_manager connection_manager_;
		//std::list<connection_ptr> client_connections_;

		stock stock_request_;

		boost::asio::deadline_timer timer_;
		bool timer_started_;

		concurrent_queue<boost::shared_ptr<stock> >& stock_data_queue_;

		//
		// server maintains a routing table of requested items - to - client connections
		// multiple client connections may 'subscribe' interest to the same item-by-name
		// so keep a list of client connections associated with the requested item
		//
		typedef std::map< std::string, std::list<boost::weak_ptr<connection> > > request_table_type;
		request_table_type request_table_;

		//
		// this is purely a helper data structure:
		// in order to randomly choose an item from the request map
		// we need to keep an indexed list of these items
		std::vector<request_table_type::key_type> vec_of_req_items_; 

		//data_consumer data_consumer_;
		boost::thread data_consumer_thread_;

		static const size_t MAX_NUMBER_OF_STOCKS = 5;
	};
} // namespace s11n_example
