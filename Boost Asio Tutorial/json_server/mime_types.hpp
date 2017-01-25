//
// mime_types.hpp


#ifndef JSON_SERVER_MIME_TYPES_HPP
#define JSON_SERVER_MIME_TYPES_HPP

#include <string>

namespace json_based {
namespace server {
namespace mime_types {

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

} // namespace mime_types
} // namespace server
} // namespace json_based

#endif // JSON_SERVER_MIME_TYPES_HPP
