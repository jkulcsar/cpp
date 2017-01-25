
#include <boost/iostreams/concepts.hpp>    // output_filter
#include <boost/iostreams/operations.hpp>  // put

using namespace boost::iostreams;

class shell_comments_output_filter : public output_filter {
public:
    explicit shell_comments_output_filter(char comment_char = '#')
        : comment_char_(comment_char), skip_(false) {
	}

	//
	// the member function put() first examines the given character c
	// and updates skip_;
	// next, unless skip_ is true, it attempts to write c.

    template<typename Sink>
    bool put(Sink& dest, int c) {
        skip_ = c == comment_char_ ?
            true :
            c == '\n' ?
                false :
                skip_;

        if (skip_)
            return true;

        return iostreams::put(dest, c);
    }

	//
	// the member function close() simply clears the skip_ flag so that
	// the Filter will be ready to be used again.

    template<typename Source>
    void close(Source&) {
		skip_ = false;
	}

private:
    char comment_char_;
    bool skip_;
};
