//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2020
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "engine/lifeengine.h"
#include "physics/physicssystem.h"
#include "engine/iengine.h"
#include "engine/iconsolesystem.h"

LIFEENGINE_PHYSICSSYSTEM_API( le::PhysicsSystem );

// ------------------------------------------------------------------------------------ //
// Initialize physics system
// ------------------------------------------------------------------------------------ //
bool le::PhysicsSystem::Initialize( le::IEngine* Engine )
{
    return true;
}

// ------------------------------------------------------------------------------------ //
// Update physics system
// ------------------------------------------------------------------------------------ //
void le::PhysicsSystem::Update()
{

}

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
le::PhysicsSystem::PhysicsSystem()
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
le::PhysicsSystem::~PhysicsSystem()
{}

// ------------------------------------------------------------------------------------ //
// Get factory
// ------------------------------------------------------------------------------------ //
le::IFactory* le::PhysicsSystem::GetFactory() const
{
    return ( IFactory* ) &factory;
}
