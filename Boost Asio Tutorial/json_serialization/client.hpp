
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include <boost/shared_ptr.hpp>

#include "stock.hpp"

namespace s11n_example {

	class client
	{
	public:
		/// Constructor starts the asynchronous connect operation.
		client(
			boost::asio::io_service& io_service,
			const std::string& host,
			const std::string& service,
			const std::string& symbol_file_name);

		/// Handle completion of a connect operation.
		void handle_connect(const boost::system::error_code& e);

		/// Handle completion of a read operation.
		void handle_read(const boost::system::error_code& e);

		/// Handle completion of a write operation.
		void handle_write(const boost::system::error_code& e, boost::shared_ptr<stock>&);


	private:
		/// Utility function to put together a request object
		/// to be sent to the server.
		boost::shared_ptr<stock> create_request_object(const std::string& );

		/// The connection to the server.
		boost::shared_ptr<connection> connection_;

		/// The data received from the server.
		std::vector<stock> stock_replies_;
		stock stock_reply_;

		/// The request to be sent to the server
		std::vector< boost::shared_ptr<stock> > stock_requests_;
		stock stock_request_ ;
		const std::string symbol_file_name_;
	};

} // namespace s11n_example
