#pragma once

class EnemyTarget
{
public:
	EnemyTarget() { ++numTargets; }
	EnemyTarget(const EnemyTarget&) { ++numTargets; }
	~EnemyTarget() { --numTargets; }
	static size_t numberOfTargets()
	{ return numTargets; }
	
	// returns success of
	// attempt to destroy
	// EnemyTarget object
	virtual bool destroy()	{ return true; }
		
private:
	static size_t numTargets;               // object counter
};

// class statics must be defined outside the class;
// initialization is to 0 by default
size_t EnemyTarget::numTargets;

