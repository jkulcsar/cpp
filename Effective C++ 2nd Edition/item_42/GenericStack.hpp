#pragma once

//
// GenericStack_v1 is used to illustrate the 'before' scenario;
// here: typesafe interface classes are using GenericStack_v1
// through has-a layering;
// GenericStack_v1 has push/pop/top public and nothig can stop
// a user to instantiate and use GenericStack directly, circumventing
// the typesafe version (IntStack and CatStack)
//
class GenericStack_v1 {
public:
	GenericStack_v1() : top(0) {}
	~GenericStack_v1() {
		while (top) {
			StackNode *toDie = top;       // get ptr to top node
			top = top->next;              // move to next node
			delete toDie;                 // delete former top node
		}
	}

	void push(void *object) {
		top = new StackNode(object, top);    // put new node at front of list
	}

	void * pop() {
		StackNode *topOfStack = top;    // remember top node
		top = top->next;
		void *data = topOfStack->data;      // remember node data
		delete topOfStack;
		return data;
	}

	bool empty() const { return top == 0; }

private:
	struct StackNode {
		void *data;                    // data at this node
		StackNode *next;               // next node in list
		StackNode(void *newData, StackNode *nextNode)
			: data(newData), next(nextNode) {}
	};
	StackNode *top;                          // top of stack
	GenericStack_v1(const GenericStack_v1& rhs);   // prevent copying and
	GenericStack_v1&                            // assignment (see
		operator=(const GenericStack_v1& rhs);    // Item 27)
};

class GenericStack {
protected:
	GenericStack() : top(0) {}
	~GenericStack() {
		while(top) {
			StackNode *toDie = top;
			top = top->next;
			delete toDie;
		}
	}

	void push(void *object) {
		top = new StackNode(object, top);
	}

	void * pop() {
		StackNode *topOfStack = top; // remember top of stack
		void *data = topOfStack->data; // remember pointer to payload (data)
		top = top->next; // move the top to the next
		delete topOfStack; // delete the top node
		return data;
	}

	bool empty() const { return top == 0; }
private:
	struct StackNode {
		void *data;                    // data at this node
		StackNode *next;               // next node in list
		StackNode(void *newData, StackNode *nextNode)
			: data(newData), next(nextNode) {}
	};
	StackNode *top;                          // top of stack
	GenericStack(const GenericStack& rhs);   // prevent copying and
	GenericStack&                            // assignment (see
		operator=(const GenericStack& rhs);  // Item 27)
};
