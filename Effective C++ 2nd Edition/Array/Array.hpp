template<typename T>
class Array
{
 public:
    Array(unsigned arraySize):
        data(0), size(arraySize)
    {
        if(size > 0)
            data = new T[size];
    }

		Array(const Array& rhs) : data(0), size(rhs.size)
	{
		if(rhs.size > 0)
		{
			data = new T[size];
			// don't just copy the value of the pointer
			// must copy all elements of the array pointed to (deep copy)
			for(unsigned i=0; i<size; i++)
				data[i] = rhs.data[i];
		}
	}
    ~Array()
    {
        if(data)
			delete[] data;
    }

	Array& operator=(const Array& rhs)
	{
		// check for self-assignement
		if( this == &rhs )
			return *this;

		// check if there's any data; if yes, delete
		if(data)
		{
			delete[] data;
			data = 0;
		}

		// deep copy
		size = rhs.size;
		if(size)
		{
			data = new T[size];
			for(unsigned i=0; i<size; ++i)
				data[i] = rhs.data[i];
		}

		return *this;
	}


    void setValue(unsigned index, const T& value)
    {
        if(index < size)
            data[index] = value;
    }

    T getValue(unsigned index) const
    {
        if(index < size)
            return data[index];
        else
            return T();
    }

 private:
    T* data;
    unsigned size;
};

//3: Reference counting
//Often it would be nice to be able to pass data structures like this one by value and 
//to assign them around but modifying the copies is never done and thus it would be a 
//huge waste of time and memory if the data was needlessly copied every time.
//In other words, sometimes it would be very useful if the Array class acted like a 
//reference to the data instead of being the data itself. This way just this reference 
//is copied around and not the data, and when the last reference to the data goes 
//out of scope, the data is deleted. 
//
//(One practical situation where this may be the desired behaviour is when you create 
//a big std::vector<Array> and then use std::sort() to sort its contents. 
//The arrays will be copied around inside the vector many times, but none of the copies 
//are modified and the deep-copy solution would thus be very inefficient.) 
//
//This can be implemented by adding a reference counter to the class. This way the data 
//is never copied (even though the instances of the class are) but there's still no risk 
//of memory leaks nor double deletions nor accessing deleted memory. 
//One has to simply remember that if a copy is modified, all the other copies are "modified" 
//too (because they all point to the same data). 
//
//Implementing reference counting is not unambiguous, and there are many ways of doing it 
//efficiently depending on the class, but if you are interested in seeing a generic solution 
//applied to this case, here's the code. 
//


//template<typename T>
//class Array
//{
// public:
//    Array(unsigned arraySize):
//        data(0), size(arraySize), refCount(new long unsigned)
//    {
//        if(size > 0)
//            data = new T[size];
//        *refCount = 1;
//    }
//
//    ~Array()
//    {
//        decRefCount();
//    }
//
//    Array(const Array& cpy):
//        data(cpy.data), size(cpy.size), refCount(cpy.refCount)
//    {
//        ++(*refCount);
//    }
//
//    const Array& operator=(const Array& cpy)
//    {
//        // Check for assignment onto itself:
//        if(data == cpy.data) return *this;
//
//        decRefCount();
//
//        data = cpy.data;
//        size = cpy.size;
//        refCount = cpy.refCount;
//        ++(*refCount);
//
//        return *this;
//    }
//
//    void setValue(unsigned index, const T& value)
//    {
//        if(index < size)
//            data[index] = value;
//    }
//
//    T getValue(unsigned index) const
//    {
//        if(index < size)
//            return data[index];
//        else
//            return T();
//    }
//
//
// private:
//    T* data;
//    unsigned size;
//    unsigned long* refCount;
//
//    void decRefCount()
//    {
//        --(*refCount);
//        if(*refCount == 0)
//        {
//            if(data) { delete[] data; data = 0; }
//            delete refCount; refCount = 0;
//        }
//    }
//};
//



//4: Copy-on-write
//The copy-on-write technique is a kind of lazy evaluation algorithm: Instead of copying the 
//data right away, the class copies it only if and when needed (in other words, when an attempt
//to modify a copy is performed). It's basically just an extension to the reference counting 
//technique: If there's more than one reference to an existing data and one of the references 
//tries to modify it, it first makes a copy of the data for itself before the modification. 
//
//This way it is possible to copy and assign the array as much as you like without any actual 
//data copying happening, yet if a copy is modified, it will not modify all the other instances 
//of the data, but instead a deep copy will be done for that copy first. In other words, it will
//externally work exactly in the same way as the deep copying solution, but copying and 
//assigning will be much more efficient. 
//
//Adding copy-on-write functionality to the reference counting solution above is very trivial. 
//You can see the code here. (The only modifications are in the setValue() function and the 
//addition of a new function at the end of the class.) 
//

//template<typename T>
//class Array
//{
// public:
//    Array(unsigned arraySize):
//        data(0), size(arraySize), refCount(new long unsigned)
//    {
//        if(size > 0)
//            data = new T[size];
//        *refCount = 1;
//    }
//
//    ~Array()
//    {
//        decRefCount();
//    }
//
//    Array(const Array& cpy):
//        data(cpy.data), size(cpy.size), refCount(cpy.refCount)
//    {
//        ++(*refCount);
//    }
//
//    const Array& operator=(const Array& cpy)
//    {
//        // Check for assignment onto itself:
//        if(data == cpy.data) return *this;
//
//        decRefCount();
//
//        data = cpy.data;
//        size = cpy.size;
//        refCount = cpy.refCount;
//        ++(*refCount);
//
//        return *this;
//    }
//
//    void setValue(unsigned index, const T& value)
//    {
//        copyOnWrite();
//        if(index < size)
//            data[index] = value;
//    }
//
//    T getValue(unsigned index) const
//    {
//        if(index < size)
//            return data[index];
//        else
//            return T();
//    }
//
//
// private:
//    T* data;
//    unsigned size;
//    unsigned long* refCount;
//
//    void decRefCount()
//    {
//        --(*refCount);
//        if(*refCount == 0)
//        {
//            if(data) { delete[] data; data = 0; }
//            delete refCount; refCount = 0;
//        }
//    }
//
//    void copyOnWrite()
//    {
//        if(*refCount > 1 && size > 0)
//        {
//            --(*refCount);
//            refCount = new unsigned long;
//            *refCount = 1;
//
//            T* oldData = data;
//            data = new T[size];
//            for(unsigned i = 0; i < size; ++i)
//                data[i] = oldData[i];
//        }
//    }
//};
//
