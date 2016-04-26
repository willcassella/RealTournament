// Projectile.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/RealTournament/Projectile.h"
#include "../include/RealTournament/Player.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(real_tournament::Projectile)
.Field("damage", &Projectile::damage);

namespace real_tournament
{
	///////////////////
	///   Methods   ///

	void Projectile::on_initialize()
	{
		this->Base::on_initialize();
		this->velocity = { 0.1f, 0, 0 };
		this->get_world().bind_event("update", *this, &Projectile::on_update);
	}

	void Projectile::on_collision(Entity& collidee)
	{
		if (auto player = Cast<Player>(collidee))
		{
			player->health -= this->damage;
		}
	}

	void Projectile::on_update(float dt)
	{
		if (life < 0)
		{
			this->destroy();
		}
		else
		{
			life -= dt;
			this->set_world_location(this->get_world_location() + velocity);
		}
	}
}
