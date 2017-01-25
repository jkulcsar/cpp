//
// Item 11: Prevent exceptions from leaving destructors.
//
// We thus find ourselves with two good reasons for keeping exceptions from 
// propagating out of destructors.
// First, it prevents terminate() from being called during the stack-unwinding 
// part of exception propagation. 
// Second, it helps ensure that destructors always accomplish everything they 
// are supposed to accomplish. Each argument is convincing in its own right, 
// but together, the case is ironclad. 

int main( int argc, char ** argv)
{
	return 0;
}

