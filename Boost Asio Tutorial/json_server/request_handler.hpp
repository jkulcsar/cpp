//
// request_handler.hpp


#ifndef JSON_SERVER_REQUEST_HANDLER_HPP
#define JSON_SERVER_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace json_based {
namespace server {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler
  : private boost::noncopyable
{
public:
  
  explicit request_handler();

  /// Handle a request and produce a reply.
  void handle_request(const request& req, reply& rep);

private:

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace server
} // namespace json_based

#endif // JSON_SERVER_REQUEST_HANDLER_HPP
