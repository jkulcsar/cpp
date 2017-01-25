
class dllist {
private:
	struct node {
		node* _prev;
		node* _next;
		int _value;
	public:
		node(int v = 0) : _prev(0), _next(0), _value(v) {}
	};

	node* _head;
	node* _tail;

	void insert_after(node*, node*);
	void insert_beginning(node*, node*);

public:
	void insert_end(int v);

	int get_next_forward();
	int get_next_reverse();

	void revert();

	dllist() : _head(0), _tail(0) {
		_head = _tail;
	}

	~dllist();
};


void dllist::insert_end(int v) {
	node* n = new node(v);
	if(n) {
		if(_tail == 0)
			insert_beginning(_head, n);
		else
			insert_after(_tail, n);
	}
}
void dllist::insert_after(node* n, node* new_node) {
	new_node->_prev = n;
	new_node->_next = n->_next;
	if(n->_next == 0) {
		_tail = new_node;
	}
	else {
		n->_next->_prev = new_node;
	}
	n->_next = new_node;
}

void dllist::revert() {
	//
	// revert a double-linked list? it's a trick question: just swap head and tail!
	node* n = _tail;
	_head = _tail;
	_tail = n;
}

dllist::~dllist() {
	while(_head != 0) {
		node* n = _head;
		_head = n->_next;
		_head->_prev = 0;
		delete n;
	}


}
