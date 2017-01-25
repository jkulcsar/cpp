
class Memento;
class State;

class Originator {
public:
	Memento* CreateMemento();
	void SetMemento(const Memento*);
	// ...
private:
	State* state_;
};
