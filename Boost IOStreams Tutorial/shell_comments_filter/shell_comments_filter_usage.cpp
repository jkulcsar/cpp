
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include "shell_comments_stdio_filter.hpp"
#include "shell_comments_input_filter.hpp"
#include "shell_comments_output_filter.hpp"

namespace io = boost::iostreams;

int main(int argc, char** argv) {

	io::filtering_istreambuf in;
	in.push(shell_comments_input_filter());
	in.push(file_source("./scripts/cmptree.sh"));

	while(char c = get(in))
		std::cout << c;

	return 0;
}
