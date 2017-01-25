//Concrete types are not intended to display polymorphic behavior (see §2.5.5, §12.2.6).
//If you don’t like some detail of a concrete type, you build a new one with the desired behavior.

//A type with virtual functions is called a
//polymorphic type. To get polymorphic behavior in C++, the member functions called must be v i r t
//u a l and objects must be manipulated through pointers or references. When manipulating an object
//directly (rather than through a pointer or reference), its exact type is known by the compilation so
//that runtime polymorphism is not needed.