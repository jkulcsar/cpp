//
// stock.hpp

#ifndef SERIALIZATION_STOCK_HPP
#define SERIALIZATION_STOCK_HPP

#include <string>

//
// these two include files are for using json_spirit as header-only library
#include "json_spirit_reader_template.h"
#include "json_spirit_writer_template.h"

namespace s11n_example {

	/// Structure to hold information about a single stock.
	struct stock
	{
		stock() {
			std::cout << "stock constructor" << std::endl;
		}

		~stock() {
			std::cout << "stock dtor" << std::endl;
		}

		json_spirit::Value	_json_value;
		std::string _json_value_as_string;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & _json_value_as_string;
		}
	};

} // namespace s11n_example

#endif // SERIALIZATION_STOCK_HPP
