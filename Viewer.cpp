#include "Viewer.h"

PhaseObserver::PhaseObserver()
{
}

PhaseObserver::~PhaseObserver()
{

}

PhaseObserver::PhaseObserver(GameEngine* en)
{
	engine = en;
	engine->Attach(this);
}

void PhaseObserver::Update(int n)//send in some code to then call within update
							//either reinforce or attack, or foritfy
{
	display(n);
}

void PhaseObserver::display(int n) //This method accepts an int as argument and will determin what data
//to display, for example if the argument passed is 1, them displayReinforceInfo() will be called
//if 2 attackinfor() etc
{
}

void PhaseObserver::displayReinforceInfo()
{
}

void PhaseObserver::displayAttackInfo()
{
}

void PhaseObserver::displayFortifyInfo()
{
}
