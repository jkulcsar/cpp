//
// request_parser.cpp

#include "request_parser.hpp"
#include "request.hpp"

#include <boost/lexical_cast.hpp>

namespace json_based {
namespace server {

request_parser::request_parser()
  : state_(header_line_start)
{
}

void request_parser::reset()
{
  state_ = header_line_start;
}

boost::tribool request_parser::consume(request& req, char input)
{
  switch (state_)
  {
  case header_line_start:
    if (input == '\r')
    {
      state_ = expecting_newline_3;
      return boost::indeterminate;
    }
    else if (!req.headers.empty() && (input == ' ' || input == '\t'))
    {
      state_ = header_lws;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.push_back(header());
      req.headers.back().name.push_back(input);
      state_ = header_name;
      return boost::indeterminate;
    }
  case header_lws:
    if (input == '\r')
    {
      state_ = expecting_newline_2;
      return boost::indeterminate;
    }
    else if (input == ' ' || input == '\t')
    {
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      state_ = header_value;
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case header_name:
    if (input == ':')
    {
      state_ = space_before_header_value;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.back().name.push_back(input);
      return boost::indeterminate;
    }
  case space_before_header_value:
    if (input == ' ')
    {
      state_ = header_value;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case header_value:
    if (input == '\r')
    {
      state_ = expecting_newline_2;
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case expecting_newline_2:
    if (input == '\n')
    {
      state_ = header_line_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case expecting_newline_3:
    if (input == '\n')
	{
		state_ = reading_json_object;

		//
		// all headers are read by now
		// we need the content length extracted
		std::vector<header>::const_iterator citer = req.headers.begin();
		for( citer = req.headers.begin(); citer < req.headers.end(); ++citer )
		{
			if((*citer).name.find("Content-Length") != std::string::npos)
			{
				// FIXME: add a try/catch here for lexical_cast failure
				req.content_length = boost::lexical_cast<size_t>( (*citer).value );
			}
		}
		content_length = req.content_length;

		return boost::indeterminate;
	}
	else
	{
		return false;
	}
  case reading_json_object:
	  if(req.content_length)
		  {
			// copy this input char into the stringstream that represents the json object
			// FIXME: very inefficient to copy char-by-char
			req.sstr.put(input);

			// decrement the local counter for reading the content
			content_length--;

			if(!content_length) {
				// done with reading content/actual payload
				// attempt to create a JSON object from the captured content
				try {
					json_spirit::read_stream_or_throw( req.sstr, req._json_request );
				}
				catch(json_spirit::Error_position ep) {
					std::cout << ep.reason_ << std::endl;
				}
				return true;
			}
			else
				return boost::indeterminate;

	  }
	  else
	  {
		  return false;
	  }

  default:
    return false;
  }
}

bool request_parser::is_char(int c)
{
  return c >= 0 && c <= 127;
}

bool request_parser::is_ctl(int c)
{
  return (c >= 0 && c <= 31) || (c == 127);
}

bool request_parser::is_tspecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
    return true;
  default:
    return false;
  }
}

bool request_parser::is_digit(int c)
{
  return c >= '0' && c <= '9';
}

} // namespace server
} // namespace json_based
