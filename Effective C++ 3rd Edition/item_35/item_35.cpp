
//
// item 35: Consider alternatives to virtual functions
//

#include <iostream>
#include <memory>
#include <functional>
#include "GameCharacter.hpp"

using namespace std;

int main(int argc, char** argv) {

	//
	// test-drive the classic implementation
	auto_ptr<GameCharacter> gc(new GameCharacter());
	int gc_health = gc->healthValue();

	//
	// objects created by classes inheriting from non-virtual interface idiom
	// classes can not call the re-defined private virtual functions directly,
	// only the public interface which will call the 'right' virtual function
	//
	// unable to call directly but CAN (and should) re-define private virtual 
	// functions: this is NOT a contradiction!
	// re-defining specifies HOW something is to be done
	// calling specifies WHEN something is to be done
	//
	auto_ptr<EvilBadGuyNVI> ebgNVI(new EvilBadGuyNVI());
	// ebgNVI->doHealthValue();   // can't call private virtual directly
	int ebgNVI_health = ebgNVI->healthValue();

	//
	// using the Strategy Pattern via function pointers:
	// (1) different instances of the same class character type can have
	// different health calculation algorithm:
	EvilBadGuySPvFP ebgSPvFP1(loseHealthQuickly);
	ebgSPvFP1.healthValue();
	EvilBadGuySPvFP ebgSPvFP2(loseHealthSlowly);
	ebgSPvFP2.healthValue();

	//
	// using Strategy Pattern via tr1::function
	// case (1): using simple function
	EvilBadGuySPvTR1F ebg100(calcHealthSPvTR1F);
	ebg100.healthValue();

	// case (2): using function object
	HealthCalculator hc;
	EyeCandyCharacterSPvTR1F ecc100(hc);
	ecc100.healthValue();

	// case (3): using mem function and binding
	GameLevel currentLevel;
	EvilBadGuySPvTR1F ebg101(
		std::tr1::bind(&GameLevel::health, currentLevel, std::tr1::placeholders::_1)
		);
	ebg101.healthValue();

	return 0;
}