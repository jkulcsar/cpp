#pragma once

class EnemyTank: public EnemyTarget {
public:
	EnemyTank() { ++numTanks; }
	
	EnemyTank(const EnemyTank& rhs)
		: EnemyTarget(rhs)
	{ ++numTanks; }

	~EnemyTank() { --numTanks; }
	
	static size_t numberOfTanks()
	{ return numTanks; }
	
	virtual bool destroy() { return true; }
private:
	static size_t numTanks;         // object counter for tanks
};

// class statics must be defined outside the class;
// initialization is to 0 by default
size_t EnemyTank::numTanks;
