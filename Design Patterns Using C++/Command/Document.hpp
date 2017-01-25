#ifndef DOCUMENT_HPP_
#define DOCUMENT_HPP_

class Document {
private:
	const char* _name;
public:
	Document(const char* n) : _name(n) {
	}

	void Open() {
		//
		// open this document
	}
	void Paste() {
		//
		// paste into this document
	}
};

#endif

