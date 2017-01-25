#pragma once

template <typename E>
class BaseSubject {
public:
	typedef E Event;
	struct Observer {
			virtual void Update(Event) = 0;
			virtual ~Observer();
	};

	typedef Observer*	ObserverID;

	enum {
		attachKillsAllIters = 1,
		detachKillsCurrentIter = 1,
		detachKillsAllIters = 1
	};

	virtual bool Attach(ObserverID, Event) = 0;
	virtual bool Detach(ObserverID, Event) = 0;
	virtual void Detach(ObserverID) = 0;
	virtual void NotifyAll(Event) = 0;

	virtual ~BaseSubject() {}

	Observer* ID2Observer(ObserverID id) {
		return id;
	}
};
