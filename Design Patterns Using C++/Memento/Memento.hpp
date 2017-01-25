
//
// A memento is an object that stores a snapshot of the internal state of another 
// object—the memento's originator. The undo mechanism will request a memento from 
// the originator when it needs to checkpoint the originator's state.
// The originator initializes the memento with information that characterizes its 
// current state. Only the originator can store and retrieve information from the 
// memento—the memento is "opaque" to other objects.
//
// Implementation considerations:
// (1) Language support. Mementos have two interfaces: a wide one for originators 
// and a narrow one for other objects.
// Ideally the implementation language will support two levels of static protection.
// C++ lets you do this by making the Originator a friend of Memento and making
// Memento's wide interface private. Only the narrow interface should be 
// declared public.
//

#ifndef MEMENTO_HPP_
#define MEMENTO_HPP_


class Originator;
class State;

class Memento {
public:
	// narrow public interface
	~Memento();
private:
	// private members accessible only to Originator
	friend class Originator;
	Memento();

	void SetState(State*);
	State* GetState();
	// ...
};

#endif