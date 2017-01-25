#pragma once

// forward declarations
class Airport;

class Airplane
{
public:
	Airplane(void);
	virtual ~Airplane(void);

	virtual void fly(const Airport& destination) = 0;
};
