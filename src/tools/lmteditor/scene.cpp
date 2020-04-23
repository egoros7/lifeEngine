//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2020
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "scene.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
Scene::Scene() :
	camera( nullptr )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
Scene::~Scene()
{
	Clear();
}

// ------------------------------------------------------------------------------------ //
// Render
// ------------------------------------------------------------------------------------ //
void Scene::Render()
{
	if ( !studioRender ) return;

	studioRender->BeginScene( camera );
	studioRender->EndScene();
}

// ------------------------------------------------------------------------------------ //
// Set camera
// ------------------------------------------------------------------------------------ //
void Scene::SetCamera( le::ICamera* Camera )
{
	if ( camera == Camera ) return;
	if ( camera )
	{
		if ( camera->GetCountReferences() <= 1 )
			camera->Release();
		else
			camera->DecrementReference();
	}

	camera = Camera;
}

// ------------------------------------------------------------------------------------ //
// Clear scene
// ------------------------------------------------------------------------------------ //
void Scene::Clear()
{
	if ( camera )
	{
		if ( camera->GetCountReferences() <= 1 )
			camera->Release();
		else
			camera->DecrementReference();
	}
}