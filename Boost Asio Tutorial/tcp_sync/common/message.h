//
//
//

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <boost/asio.hpp>

#include <iostream>
#include <cstring>

struct msdata_ack {
	int a1;

	friend std::ostream& operator<<(std::ostream& os, msdata_ack const & d ) {
		return os << "a1=" << d.a1;
	}
};

struct msdata_data {
	int d1;
	char d2[64];
	double d3;

	friend std::ostream& operator<<(std::ostream& os, msdata_data const & d ) {
		return os << "d1=" << d.d1 << ", d2=" << d.d2 << ", d3=" << d.d3;
	}
};

struct msdata_end {
	int e1;
	int e2;

	friend std::ostream& operator<<(std::ostream& os, msdata_end const & d ) {
		return os << "e1=" << d.e1 << ", e2=" << d.e2;
	}
};

struct msheader {
	int id;
	int length;
	msheader() : id(0), length(0){ }

	friend std::ostream& operator<<(std::ostream& os, msheader const & h ) {
		os << "header{ id= " << h.id << ", length= " << h.length << " }";
		return os;
	}
};

union msbody {
	msdata_ack ms_ack;
	msdata_data ms_data;
	msdata_end ms_end;
	msbody() {
		memset(this, 0, sizeof(*this) );
	}
};

struct message {
	enum mstype { MS_ACK = 11,
				  MS_DATA = 22,
				  MS_END = 99 };

	msheader header;
	msbody body;

	message() {	}

	message( mstype mt ) {
		switch( mt ) {
			case MS_ACK : header.length = sizeof( msdata_ack ); break;
			case MS_DATA : header.length = sizeof( msdata_data );break;
			case MS_END : header.length = sizeof( msdata_end ); break;
			default: header.length = sizeof( msbody );
		}

		header.id = static_cast< int >( mt );
		header.length += sizeof(msheader);
	}

	void setData( int n ) {
		body.ms_data.d1 = n;
		char t[] = "\'Here some text\'";
		memcpy( body.ms_data.d2, t, sizeof(t) );
		body.ms_data.d3 = n*n;
	}

	void send( boost::asio::ip::tcp::socket& s ) const {
		try {
			boost::asio::write( s, boost::asio::buffer( this, header.length));
		}
		catch( std::exception e ) {
			throw std::runtime_error("message send error | " + std::string( e.what() ) );
		}
	}

	void read( boost::asio::ip::tcp::socket& s ) {
		try {
			// Read header
			size_t lh = boost::asio::read( s, boost::asio::buffer( &header, sizeof(header)));

			// Read body
			boost::asio::read( s, boost::asio::buffer( &body, header.length - lh ));
		}
		catch( std::exception e ) {
			throw std::runtime_error( "message read error | " + std::string( e.what() ) );
		}
	}


	friend std::ostream& operator<<(std::ostream& os, message const & ms ) {
		os << ms.header << "   body{ ";
		switch( ms.header.id ) {
			case MS_ACK : os << ms.body.ms_ack; break;
			case MS_DATA : os << ms.body.ms_data; break;
			case MS_END : os << ms.body.ms_end; break;
		}
		os << " } " << std::endl;
		return os;
	}
};

#endif
