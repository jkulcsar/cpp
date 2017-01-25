#pragma once

class Widget {
public:
	Widget(int size) { 
		// should use 'size' here
	}
	Widget(const Widget& rhs) {}
	~Widget() {}
	Widget& operator=(const Widget& rhs) {}
	void doThis() {}
	int showThat() const {
		return 0;
	}
};
