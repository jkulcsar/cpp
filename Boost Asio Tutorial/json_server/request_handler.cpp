//
// request_handler.cpp

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace json_based {
namespace server {

request_handler::request_handler()

{
}

void request_handler::handle_request(const request& req, reply& rep)
{
	// Handle the payload coming in the request
	// here: it's a json object which may be parsed/interpreted here

	//
	// let's take a look at it
	json_spirit::write_stream( json_spirit::Value(req._json_request), std::cout, json_spirit::pretty_print);

	json_spirit::Object obj;
//	rep._json_reply.clear();

	obj = req._json_request.get_obj();

	for( size_t i = 0; i < 10; i++ ) {
		const std::string field_name = "field_name_" + boost::lexical_cast<std::string>(i);
		obj.push_back( json_spirit::Pair( field_name, boost::lexical_cast<std::string>(i) ) );
	}

//	rep._json_reply.push_back( obj );
	rep._json_reply = obj;

	//
	// extract data from the json object
  // Fill out the reply to be sent to the client.
  rep.status = reply::ok;

   std::stringstream sstr;
  json_spirit::write_stream( json_spirit::Value(rep._json_reply), sstr, json_spirit::pretty_print);

  rep._content.clear();
  rep._content = sstr.str();

  rep.headers.push_back(header());
  rep.headers.back().name = "Content-Length";
  rep.headers.back().value = boost::lexical_cast<std::string>(rep._content.size());
  
  rep.headers.push_back(header());
  rep.headers.back().name = "Content-Type";
  rep.headers.back().value = mime_types::extension_to_type("json");
  
  rep.headers.push_back(header());
  rep.headers.back().name = "Status";
  rep.headers.back().value = rep.status;

  


// /* std::size_t last_slash_pos = request_path.find_last_of("/");
//  std::size_t last_dot_pos = request_path.find_last_of(".");
//  std::string extension;
//  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
//  {
//    extension = request_path.substr(last_dot_pos + 1);
//  }
//*/

  //
  // send a stock reply on error/unable to interpret request
  // e.g. service or item name are not recognized or serviced at this time

//  if (!is)
  //{
  //  rep = reply::stock_reply(reply::not_found);
  //  return;
  //}
}

bool request_handler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server
} // namespace json_based
