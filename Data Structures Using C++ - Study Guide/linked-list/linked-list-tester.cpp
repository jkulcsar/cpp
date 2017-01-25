#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//
// C-style implementation: using malloc/free ...
// but using C++ template class!
//

template<typename T>
class linked_list {
private:
	struct node {
		node* next_;
		T value_;
	};

	node* head_;

public:
	void insert_back(T value);
	void insert_front(T value);
	void remove(T value);
	T get_next();

	~linked_list();
	linked_list() : head_(0) {}
};

//template<typename T>
//linked_list<T>::node* linked_list<T>::cursor_ = 0;

template<typename T>
linked_list<T>::~linked_list() {
	node* curr_pos = head_;
	while( curr_pos != NULL ) {
		node* n = curr_pos;
		curr_pos = curr_pos->next_;
		if(n)
			free(n);
	}
}


template<typename T>
void linked_list<T>::insert_back(T value) {
	node* new_node = (node*) malloc( sizeof(node) );
	new_node->value_ = value;
	new_node->next_ = NULL;


	// grab the head
	// the list could also maintain a tail pointer;
	// with a tail pointer inserting at back would be a breeze
	node* curr_pos = head_;

	// move the current position to the end
	if( curr_pos != NULL)
		while( curr_pos->next_ != NULL )
			curr_pos = curr_pos->next_;
	

	if( curr_pos != NULL) {
		curr_pos->next_ = new_node;
	}
	else
		head_ = new_node;
}

template<typename T>
void linked_list<T>::remove(T value) {
	node* curr_pos;
	node* prev_pos;

	previous_pos = NULL;

	for(
		curr_pos = head_;
		curr_pos != NULL;
		prev_pos = curr_pos, curr_pos = curr_pos->next_ ) {
			if(curr_pos->value_ == value) { 
				if( prev_pos == NULL ) {
					// the node found is the head itself, so make the current node the head
					head_ = curr_pos->next_;
				}
				else {
					prev_pos->next_ = curr_pos->next;
				}
				free( curr_pos );

				return;
			}
		}
}

int main(int argc, char** argv) {
	linked_list<char> char_list;
	char_list.insert_back('a');


	return 0;
}

