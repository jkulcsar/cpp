
#include <memory>

//
// the support for installing a new new-handler can/should be factored out
// of the Widget class
//
template<typename T>
class NewHandlerSupport
{
public:
	static std::new_handler set_new_handler( std::new_handler p) throw();

	//
	// declare versions of operator new
	static void* operator new(std::size_t size) throw(std::bad_alloc);

private:
	static std::new_handler _currentHandler;

};
