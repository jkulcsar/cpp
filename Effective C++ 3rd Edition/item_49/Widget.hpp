
#include <memory>
#include "NewHandlerSupport.hpp"

class Widget
{
public:
	static std::new_handler set_new_handler( std::new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);

private:
	static std::new_handler _currentHandler;
};

//
// Using the Curiously Recurring Template Pattern (CRTP) aka "Do It For Me" tehnique:
// EnhanncedWidget derives from a template class (NewHandlerSupport) which takes as a
// type parameter EnhancedWidget itself.
//
class EnhancedWidget : public NewHandlerSupport<EnhancedWidget>
{
};
