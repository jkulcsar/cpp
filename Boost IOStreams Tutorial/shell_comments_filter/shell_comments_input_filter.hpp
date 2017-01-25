
#include <boost/iostreams/categories.hpp>	// input_filter_tag
#include <boost/iostreams/char_traits.hpp>	// EOF, WOULD_BLOCK
#include <boost/iostreams/operations.hpp>	// get, read, putback

//namespace io = boost::iostreams;
using namespace boost::iostreams;

class shell_comments_input_filter : public input_filter {
public:
	explicit shell_comments_input_filter(char comment_char = '#')
		: comment_char_(comment_char), skip_(false) {
	}

	//
	// attempt to produce one character of filtered data,
	// reading from src as necessary;
	// if successful, return the character;
	// otherwise return EOF to indicate end-of-stream or WOULD_BLOCK
	template <typename Source>
	int get(Source& src) {
		int c;
		while(true) {
            if ((c = boost::iostreams::get(src)) == EOF || c == WOULD_BLOCK)
                break;
            skip_ = c == comment_char_ ?
                true :
                c == '\n' ?
                    false :
                    skip_;
            if (!skip_)
                break;
        }
        return c;
	}

	template <typename Source>
	void close(Source&) {
		skip_ = false;
	}

private:
	char comment_char_;
	bool skip_;
};

