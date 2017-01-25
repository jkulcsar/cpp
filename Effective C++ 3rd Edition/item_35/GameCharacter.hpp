
#include <functional>

//////////////////////////////////////////////////////////////////////////////
// classic implementation, with virtual function interface,
// also providing a default implementation (best parctice, see item 34)
//
class GameCharacter {
public:

	///
	// return the character's health rating;
	// derived classes may redefine this
	virtual int healthValue() const {
		// provide a default implementation
		// since healthValue() is not pure virtual
		return 0;
	}

	/// ... other members here
};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// NVI = non-virtual interface idiom
// this is an implementation of the Template Pattern (has nothing to do with C++ templates)
// via the NVI idiom:
// virtual functions should always be private; have non-virtual functions in the interface
// call the private virtual functions
//
class GameCharacterNVI {
public:

	//
	// since healthValue() is non-virtual, this should not be redefined
	// by derived classes
	int healthValue() const {
		// ... do some 'before' stuff
		int retVal = doHealthValue();
		// ... do some 'after' stuff
		return retVal;
	}

private:
	//
	// derived classes may re-define this!
	virtual int doHealthValue() const {
		// ... default algorithm to calculate health
		return 0;
	}
};

class EvilBadGuyNVI : public GameCharacterNVI {
public:
	// ... specific for evil bad guys
private:
	// re-define the inherited virtual function(s)
	virtual int doHealthValue() const {
		// ... algorithm for evil bad guys
		return 100;
	}
};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Strategy Pattern via function pointers
// using suffix 'SPvFP' to differentiate from other implementations

class GameCharacterSPvFP;

// function for the default health calculation
int defaultHealthCalc(const GameCharacterSPvFP& gc);

class GameCharacterSPvFP {
public:
	typedef int (*HealthCalcFunc)(const GameCharacterSPvFP&);

	explicit GameCharacterSPvFP(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc_(hcf) {
	}

	int healthValue() const {
		return healthFunc_(*this);
	}

private:
	HealthCalcFunc healthFunc_;
};

//
// using the Strategy Pattern via function pointers:
// (1) different instances of the same class character type can have
// different health calculation algorithm
//
// (2) Health calculation algorithms can be changed at runtime
//
// (3) DISADVANTAGE: since the health calculation algorithms are external
// to the class, they don't have access to the private members of the
// class which may mean difficult if not impossible implementations
// here: defaultHealthCalc or loseHealthQuickly can not access the non-public
// members of EvilBadGuySPvFP
//
class EvilBadGuySPvFP : public GameCharacterSPvFP {
public:
	explicit EvilBadGuySPvFP(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacterSPvFP(hcf) {
	}

	// ... other
};

// health calculation functions, different behavior

int loseHealthQuickly(const GameCharacterSPvFP&) { 
	// do health calculation here
	return 5;
}
int loseHealthSlowly(const GameCharacterSPvFP&) {
	// do health calculation here
	return 5;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// The Strategy Pattern via tr1::function
// using suffix 'SPvTR1F' to differentiate from other implementations
//
class GameCharacterSPvTR1F;

// function for the default health calculation
int defaultHealthCalcSPvTR1F(const GameCharacterSPvTR1F& gc);

class GameCharacterSPvTR1F {
public:
	//
	// HealthCalcFunc is any callable entity
	typedef std::tr1::function<int (const GameCharacterSPvTR1F&)> HealthCalcFunc;

	explicit GameCharacterSPvTR1F(HealthCalcFunc hcf = defaultHealthCalcSPvTR1F)
		: healthFunc_(hcf) {
	}

	int healthValue() const {
		return healthFunc_(*this);
	}

	// ... other members here
private:
	HealthCalcFunc healthFunc_;
};

//
// much more options in specifying health calculation functions/algorithms:
// NOTE: Unlike with ordinary pointers to functions, the return type and the arguments 
// of the target function may differ from those of func so long as there is an 
// implicit conversion between those types.
//
// (1) - simple health calculation function - note non-int return type is OK!
short calcHealthSPvTR1F(const GameCharacterSPvTR1F&) {
	return 0;
}

// (2) class for health calculation function objects
struct HealthCalculator {
	int operator()(const GameCharacterSPvTR1F&) const {
		return 0;
	}
};

// (3) health calculation mem function - note non-int return type is OK!
class GameLevel {
public:
	float health(const GameCharacterSPvTR1F&) const {
		return 0.0;
	}
};

//
// //////
class EvilBadGuySPvTR1F : public GameCharacterSPvTR1F {
public:
	explicit EvilBadGuySPvTR1F(HealthCalcFunc hcf = defaultHealthCalcSPvTR1F)
		: GameCharacterSPvTR1F(hcf) {
	}

	// ... other
};

//
// another character type
class EyeCandyCharacterSPvTR1F : public GameCharacterSPvTR1F {
public:
	explicit EyeCandyCharacterSPvTR1F(HealthCalcFunc hcf = defaultHealthCalcSPvTR1F)
		: GameCharacterSPvTR1F(hcf) {
	}

	// ... other
};

//////////////////////////////////////////////////////////////////////////////