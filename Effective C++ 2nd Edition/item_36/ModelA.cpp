#include "ModelA.hpp"

ModelA::ModelA(void)
{
}

ModelA::~ModelA(void)
{
}

void ModelA::fly(const Airport& destination) {
	// call default first
	Airplane::fly(destination);
	//
	// sequence specific to ModelA
	//
}