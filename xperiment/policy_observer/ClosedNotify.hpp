#pragma once

template< typename Subject >
class ClosedNotify : Subject {
public:
	ClosedNotify() : _closed(false) {
	}

	typedef typename Subject::Event Event;
	typedef typename Subject::Observer Observer;
	typedef typename Subject::ObserverID ObserverID;

	bool Attach(ObserverID id, Event e) {
		if(_closed)
			throw logic_error("");
		return Subject::Attach(id,e);
	}

	virtual bool Detach(ObserverID id, Event e) {
		if(_closed)
			throw logic_error("");
		return Subject::Detach(id, e);
	}

	virtual bool Detach(ObserverID id) {
		if(_closed)
			throw logic_error("");
		return Subject::Detach(id);
	}

	virtual void NotifyAll(Event e) {
		if(_closed)
			throw logic_error("");

		_closed = true;

		struct Local {
			~Local() { *_b = false; }
			bool *_b;
		} local = { &_closed } ;
		
		Subject::NotifyAll(e);
	}

private:
	bool _closed;
};
