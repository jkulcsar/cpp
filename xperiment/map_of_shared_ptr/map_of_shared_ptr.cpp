
#include <map>
#include <string>

#include <boost/shared_ptr.hpp>


class client {
};

		
typedef boost::shared_ptr<client> client_ptr;
typedef std::map< char, client_ptr >  _partitions_to_client_map_type;
	


int main( int argc, char** argv ) {
	client_ptr a_client(new client());
		
	_partitions_to_client_map_type _partitions_to_client_map;

	const std::string str_start("0");
	const std::string str_end("Z");

	char start_char = str_start.at(0);
	char end_char = str_end.at(0);
	for( char c = start_char; c < end_char; ++c ) {
		std::pair<char, client_ptr> p = std::make_pair(c , a_client);
		//_partitions_to_client_map.insert( std::make_pair(c, client) );
		_partitions_to_client_map.insert( p );
	}

	return 0;
}
