//////////////////////////////////////////////////////////////////////////
//
//					*** lifeEngine ***
//				Copyright (C) 2018-2020
//
// Engine repository:  	https://github.com/BSOD-Games/lifeEngine
// Authors:				Egor Pogulyaka (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

#include "global.h"
#include "engine/resourcesystem.h"
#include "scriptsapi/common/luaimage.h"
#include "scriptsapi/studiorender/luamesh.h"
#include "scriptsapi/engine/lualevel.h"
#include "scriptsapi/engine/luaresourcesystem.h"

// ------------------------------------------------------------------------------------ //
// Register resource system in LUA
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::Register( lua_State* LuaVM )
{
	if ( !LuaVM )		return;

	// Registern input system
	luabridge::getGlobalNamespace( LuaVM ).
		beginClass<LUAResourceSystem>( "ResourceSystem" ).
		addStaticFunction( "LoadImage", &LUAResourceSystem::LoadImage ).
		addStaticFunction( "LoadMesh", &LUAResourceSystem::LoadMesh ).
		addStaticFunction( "LoadLevel", &LUAResourceSystem::LoadLevel ).
		addStaticFunction( "UnloadImage", &LUAResourceSystem::UnloadImage ).
		addStaticFunction( "UnloadMesh", &LUAResourceSystem::UnloadMesh ).
		addStaticFunction( "UnloadMeshes", &LUAResourceSystem::UnloadMeshes ).
		addStaticFunction( "UnloadLevel", &LUAResourceSystem::UnloadLevel ).
		addStaticFunction( "UnloadLevels", &LUAResourceSystem::UnloadLevels ).
		addStaticFunction( "UnloadAll", &LUAResourceSystem::UnloadAll ).
		addStaticFunction( "GetMesh", &LUAResourceSystem::GetMesh ).
		addStaticFunction( "GetLevel", &LUAResourceSystem::GetLevel ).
		endClass();
}

// ------------------------------------------------------------------------------------ //
// Load image
// ------------------------------------------------------------------------------------ //
le::LUAImage le::LUAResourceSystem::LoadImage( const char* Path, bool IsFlipVertical, bool IsSwitchRedAndBlueChannels )
{
	bool		isError = false;
	return g_resourceSystem->LoadImage( Path, isError, IsFlipVertical, IsSwitchRedAndBlueChannels );
}

// ------------------------------------------------------------------------------------ //
// Load mesh
// ------------------------------------------------------------------------------------ //
le::LUAMesh le::LUAResourceSystem::LoadMesh( const char* Name, const char* Path )
{
	return LUAMesh( g_resourceSystem->LoadMesh( Name, Path ) );
}

// ------------------------------------------------------------------------------------ //
// Load level
// ------------------------------------------------------------------------------------ //
le::LUALevel le::LUAResourceSystem::LoadLevel( const char* Name, const char* Path )
{	
	return LUALevel( g_resourceSystem->LoadLevel( Name, Path, ( IFactory* ) &LUALevel::GetEntityFactory() ) );
}

// ------------------------------------------------------------------------------------ //
// Unload image
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadImage( LUAImage& Image )
{
	g_resourceSystem->UnloadImage( ( le::Image& ) Image.GetHandle() );
}

// ------------------------------------------------------------------------------------ //
// Unload mesh
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadMesh( const char* Name )
{
	g_resourceSystem->UnloadMesh( Name );
}

// ------------------------------------------------------------------------------------ //
// Unload level
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadLevel( const char* Name )
{
	g_resourceSystem->UnloadLevel( Name );
}

// ------------------------------------------------------------------------------------ //
// Unload meshes
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadMeshes()
{
	g_resourceSystem->UnloadMeshes();
}

// ------------------------------------------------------------------------------------ //
// Unload levels
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadLevels()
{
	g_resourceSystem->UnloadLevels();
}

// ------------------------------------------------------------------------------------ //
// Unload all
// ------------------------------------------------------------------------------------ //
void le::LUAResourceSystem::UnloadAll()
{
	g_resourceSystem->UnloadAll();
}

// ------------------------------------------------------------------------------------ //
// Get mesh
// ------------------------------------------------------------------------------------ //
le::LUAMesh le::LUAResourceSystem::GetMesh( const char* Name )
{
	return LUAMesh( g_resourceSystem->GetMesh( Name ) );
}

// ------------------------------------------------------------------------------------ //
// Get level
// ------------------------------------------------------------------------------------ //
le::LUALevel le::LUAResourceSystem::GetLevel( const char* Name )
{
	return LUALevel( g_resourceSystem->GetLevel( Name ) );
}
