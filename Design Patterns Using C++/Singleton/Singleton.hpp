
#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

class Singleton {
private:
	static Singleton* pInstance_;
protected:
	Singleton() {}
public:
	static Singleton* Instance() {
		if(pInstance_ == 0)
			pInstance_ = new Singleton();

		return pInstance_;
	}

	~Singleton() {
		if(pInstance_)
			delete pInstance_;
	}
};

Singleton* Singleton::pInstance_ = 0;

#endif