
//
// item 50: understanding when it makes sense to replace new and delete
//
// (1) to detect usage errors:
// Failure to delete memory conjured up by new leads to memory leaks. Using 
// more than one delete on newed memory yields undefined behavior.
// If operator new keeps a list of allocated addresses and operator delete 
// removes addresses from the list, it's easy to detect such usage errors. 
// Similarly, a variety of programming mistakes can lead to data overruns 
// (writing beyond the end of an allocated block) and underruns 
// (writing prior to the beginning of an allocated block).
// Custom operator news can overallocate blocks so there's room to put known
// byte patterns ("signatures") before and after the memory made available
// to clients. operator delete can check to see if the signatures are still
// intact. If they're not, an overrun or underrun occurred sometime during 
// the life of the allocated block, and operator delete can log that fact, 
// along with the value of the offending pointer
//
// (2) to improve efficiency
// The versions of operator new and operator delete that ship with compilers
// are designed for general-purpose use. They have to be acceptable for 
// long-running programs (e.g., web servers), but they also have to be 
// acceptable for programs that execute for less than a second. They have 
// to handle series of requests for large blocks of memory, small blocks, 
// and mixtures of the two. They have to accommodate allocation patterns 
// ranging from the dynamic allocation of a few blocks that exist for the 
// duration of the program to constant allocation and deallocation of a 
// large number of short-lived objects. They have to worry about
// heap fragmentation, a process that, if unchecked, eventually leads 
// to the inability to satisfy requests for large blocks of memory, 
// even when ample free memory is distributed across many small blocks.
//
// (3) to collect usage statistics
// Before heading down the path of writing custom news and deletes, 
// it's prudent to gather information about how your software uses its 
// dynamic memory.
// What is the distribution of allocated block sizes?
// What is the distribution of their lifetimes?
// Do they tend to be allocated and deallocated in FIFO 
// ("first in, first out") order, LIFO ("last in, first out") order, 
// or something closer to random order? Do the usage patterns change 
// over time, e.g., does your software have different allocation/deallocation
// patterns in different stages of execution? What is the maximum amount 
// of dynamically allocated memory in use at any one time 
// (i.e., its "high water mark")?
// Custom versions of operator new and operator delete make it easy to 
// collect this kind of information.

#include <memory>

static const int signature = 0xDEADBEEF;
typedef unsigned char byte;

//
// the following code has several flaws, see comments!
void* operator new(std::size_t size) throw(std::bad_alloc)
{
	using namespace std;

	//
	// increase size of memory request so that two
	// signatures also fit inside
	size_t real_size = size + 2 * sizeof(int);

	//
	// call malloc to get the actual memory allocated
	void* pmem = malloc(real_size);
	if( !pmem )
		throw bad_alloc();

	//
	// write signature into first and last parts of the
	// memory just allocated
	*(static_cast<int*>(pmem)) = signature;
	*(reinterpret_cast<int*>(static_cast<byte*>(pmem) + real_size - sizeof(int))) = signature;

	//
	// return a pointer to the memory just past the first signature
	return static_cast<byte*>(pmem) + sizeof(int);
}


int main(int argc, char** argv)
{
	return 0;
}
