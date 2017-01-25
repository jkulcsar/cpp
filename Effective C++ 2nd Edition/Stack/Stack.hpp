#pragma once

#include <vector> 
#include <stdexcept> 

template <typename T> 
class Stack { 
  private: 
    std::vector<T> elems;     // elements 

  public: 
    void push(T const&);      // push element 
    T pop();                  // pop element 
    T top() const;            // return top element 
    bool empty() const {      // return whether the stack is empty 
        return elems.empty(); 
    } 
}; 

template <typename T> 
void Stack<T>::push (T const& elem) 
{ 
    elems.push_back(elem);    // append copy of passed elem 
} 

template <typename T> 
T Stack<T>::pop () 
{ 
    if (elems.empty()) { 
        throw std::out_of_range("Stack<>::pop(): empty stack"); 
    } 
    T elem = elems.back();    // save copy of last element 
    elems.pop_back();         // remove last element 
    return elem;              // return copy of saved element 
} 

template <typename T> 
T Stack<T>::top () const 
{ 
    if (elems.empty()) { 
        throw std::out_of_range("Stack<>::top(): empty stack"); 
    } 
	return elems.back();      // return copy of last element 
} 
