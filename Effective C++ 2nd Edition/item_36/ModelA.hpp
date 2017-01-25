#pragma once
#include "Airplane.hpp"

class ModelA :
	public Airplane
{
public:
	ModelA(void);
	virtual ~ModelA(void);
	virtual void fly(const Airport& destination);
};
