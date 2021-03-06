/*
 * UnitAI.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: alex
 */

#include "UnitAI.h"

UnitAI::UnitAI(Entity381* ent) : Aspect(ent)
{

}

UnitAI::~UnitAI()
{

}

void UnitAI::Tick(float dt)
{
	if (!commands.empty() && !commands.front()->done())
	{
		commands.front()->tick(dt);
	}
	else if (!commands.empty() && commands.front()->done())
	{
		commands.pop();
	}
}

void UnitAI::SetCommand(Command *c)
{
	while (!commands.empty())
	{
		commands.pop();
	}

	commands.push(c);
}

void UnitAI::AddCommand(Command *c)
{
	commands.push(c);
}



