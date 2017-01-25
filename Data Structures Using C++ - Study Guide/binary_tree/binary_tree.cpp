
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <queue>


class binary_tree {
private:
	struct node
	{
		node* _left;
		node* _right;
		int _value;

		node(int v = 0) : _left(0), _right(0), _value(v) {}
		bool add(int);
		void visit() {
			printf("%d\t", _value);
		}
	};
	
	node* _root;
public:
	binary_tree() : _root(0) {}
	~binary_tree();

	bool add(int value);
	void print();
};


bool binary_tree::node::add(int value) {
	if(value == _value)
		return false;
	else if(value < _value) {
		if(!_left) {
			_left = new node(value);
			return true;
		}
		else
			return _left->add(value);
	}
	else if(value > _value) {
		if(!_right) {
			_right = new node(value);
			return true;
		}
		else
			return _right->add(value);
	}
}

bool binary_tree::add(int value)
{
	if(!_root) {
		_root = new node(value);
		return true;
	}
	else
		return _root->add(value);
}


void binary_tree::print() {
	std::queue<binary_tree::node*> q;
	if(_root) {
		q.push(_root);
		while(q.size() > 0) {
			node* n = q.front();
			q.pop();
			if(n) {
				n->visit();
				if(n->_left)
					q.push(n->_left);
				if(n->_right)
					q.push(n->_right);
			}
		}
	}
}

binary_tree::~binary_tree() {
}

int main(int argc, char** argv)
{
	int range_max = 999;
	int range_min = 1;
	binary_tree tree;

	/* seed the random number generator */
	srand( (unsigned)time( NULL ) );

	/* add a few random integers to the tree */
	for(int i = 0; i < 5; i++) {
		int r = (int)((double)rand() / (RAND_MAX + 1) * (range_max - range_min)+ range_min);
		tree.add(r);
	}

	tree.print();

	return 0;
}
