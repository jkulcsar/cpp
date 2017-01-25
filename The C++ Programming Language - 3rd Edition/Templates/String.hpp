#pragma once

template<typename T>
class String
{
	struct Srep;
	Srep* rep;
public:
	String(void);
	String(const T*);
	String(const T&);
	T read(int i) const;
	virtual ~String(void);
};

template<typename T>
struct String<T>::Srep {
	T* s;	// pointer to elements
	int sz; // number of elements
	int n;	// reference count
	// ... others
};

template<typename T>
T String<T>::read(int i) const {
	return rep->s[i];
}

template<typename T>
String<T>::String() {
	rep = new Srep(0, T());
}
