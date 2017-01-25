#include "EnemyTarget.hpp"
#include "EnemyTank.hpp"

///
/// Item 14: Make sure base classes have virtual destructors
/// More accurately:
/// Polymorphic base classes should have virtual destructors;
/// if a class has any virtual functions it also must have a 
/// virtual destructor.
/// Classes not designed to be base classes (or not designed 
/// to be used polymorphically) should NOT have a virtual destructor
/// Advice:
/// STL containers (vector, list, set, etc) do not have virtual
/// destructors --> do not inherit from these!
/// 
int main(int argc, char** argv[])
{
	EnemyTarget* targetPtr = new EnemyTank();

	///
	/// the derived part of EnemyTank is never deleted,
	/// (partially destroyed)
	/// C++ specifies that this leads to undefined behavior
	if(targetPtr)
		delete targetPtr;

	return 0;
}