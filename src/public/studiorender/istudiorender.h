//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef ISTUDIORENDER_H
#define ISTUDIORENDER_H

#include "common/types.h"
#include "engine/lifeengine.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class IFactory;
	class ICamera;
	class IMesh;
	struct StudioRenderViewport;

	//---------------------------------------------------------------------//

	class IStudioRender
	{
	public:
		virtual void							BeginScene( ICamera* Camera ) = 0;
		virtual void							SubmitMesh( IMesh* Mesh, const Matrix4x4_t& Transformation ) = 0;
		virtual void							EndScene() = 0;
				
		virtual void							SetVerticalSyncEnabled( bool IsEnabled = true ) = 0;
		virtual void							SetViewport( const StudioRenderViewport& Viewport ) = 0;

		virtual IFactory*						GetFactory() const = 0;
		virtual const StudioRenderViewport&		GetViewport() const = 0;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !ISTUDIORENDER_H
