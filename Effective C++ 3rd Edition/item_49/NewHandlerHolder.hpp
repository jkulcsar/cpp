
#include <memory>

//
// to implement the operator new, we'll introduce a helper class
// as a resource-handling class

class NewHandlerHolder
{
public:
	// constructor: acquire current new-handler
	explicit NewHandlerHolder(std::new_handler nh) : _handler(nh) {}

	// destructor: release the current new-handler
	~NewHandlerHolder()
	{
		std::set_new_handler(_handler);
	}
private:
	std::new_handler _handler;

	//
	// prevent copying
	NewHandlerHolder( const NewHandlerHolder& );
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};
