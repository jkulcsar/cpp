//  Copyright Joel de Guzman 2002-2004. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>


char const* greeting()
{
   return "hello, world";
}

struct World
{
	World(std::string msg) : msg(msg) {
	}
	void set(std::string msg) {
		this->msg = msg;
	}
	std::string greet() {
		return msg;
	}
	std::string msg;
};

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def("greeting", greeting);

	class_<World>("World", init<std::string>())
		.def("greetworld", &World::greet)
		.def("setgreeting", &World::set)
	;
}

