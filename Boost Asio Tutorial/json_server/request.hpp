

//
// request.hpp


#ifndef JSON_SERVER_REQUEST_HPP
#define JSON_SERVER_REQUEST_HPP

#include <string>
#include <vector>
#include "header.hpp"

//
// these two include files are for using json_spirit as header-only library
#include "json_spirit_reader_template.h"
#include "json_spirit_writer_template.h"

namespace json_based {
namespace server {

/// A request received from a client.
struct request
{
  size_t content_length;
  std::vector<header> headers;

  std::stringstream sstr;
  json_spirit::Value	_json_request;

  request();
};


} // namespace server
} // namespace json_based

#endif // JSON_SERVER_REQUEST_HPP
