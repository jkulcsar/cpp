//
// reply.hpp


#ifndef JSON_SERVER_REPLY_HPP
#define JSON_SERVER_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

//
// these two include files are for using json_spirit as header-only library
#include "json_spirit_reader_template.h"
#include "json_spirit_writer_template.h"

namespace json_based {
namespace server {

/// A reply to be sent to a client.
struct reply
{
  /// The status of the reply.
  enum status_type
  {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  } status;

  /// The headers to be included in the reply.
  std::vector<header> headers;

  /// The content to be sent in the reply: the actual payload is one JSON object
  /// FIXME: for now, consider only one JSON object as payload;
  /// extend this to have multiple JSON objects in one message
  /// FIXME: on a second thought: it's OK to send just one JSON object;
  /// this is actually just a wrapper, containing a number of other JSON objects;
  /// can be simply an array of JSON objects in a top level JSON object
  json_spirit::Value	_json_reply;

  /// Convert the reply into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the reply object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> to_buffers();

  std::string _content;

  /// Get a stock reply.
  static reply stock_reply(status_type status);
};

} // namespace server
} // namespace json_based

#endif // JSON_SERVER_REPLY_HPP
