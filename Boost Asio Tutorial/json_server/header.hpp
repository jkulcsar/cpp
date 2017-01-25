//
// header.hpp


#ifndef JSON_SERVER_HEADER_HPP
#define JSON_SERVER_HEADER_HPP

#include <string>

namespace json_based {
namespace server {

struct header
{
  std::string name;
  std::string value;
};

} // namespace server
} // namespace json_based

#endif // JSON_SERVER_HEADER_HPP
