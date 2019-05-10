/**
 * Class name: EnemyAI
 * Made by: Alex Kastanek
 * Date: May 10, 2019
 * Description: This is the aspect that is used by
 * 	the enemy entity. This aspect calculates the
 * 	transformation of the entity (position moving
 * 	towards the player and orientation facing the player).
 * 	It also shoots every shootInterval seconds.
 */

#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

#include "Aspect.h"

class Player;

class EnemyAI : public Aspect
{
public:
	EnemyAI (Entity381* ent);
	~EnemyAI ();

	void Tick (float dt);

	void SetPlayer(Player* player);

	Entity381* mEntity381 = nullptr;

private:

	Player* mPlayer;
};

#endif /* _ENEMY_AI_H_ */
