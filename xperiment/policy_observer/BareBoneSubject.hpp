#pragma once

#include <vector>

using namespace std;

template <typename E>
class BareBoneSubject {
public:
	typedef typename BaseSubject<E>::Event Event;
	typedef typename BaseSubject<E>::Observer Observer;
	typedef typename BaseSubject<E>::ObserverID ObserverID;

	bool Attach(ObserverID id, Event e) {
		value_type v(e, id);
	}

private:
	typedef pair<Event, ObserverID> value_type;
	typedef vector<value_type> container;

	container _data;

protected:
	typedef typename container::iterator iterator;
	iterator begin(Event) { 
		return _data.begin(); 
	}

	iterator end(Event) {
		return _data.end();
	}
};
