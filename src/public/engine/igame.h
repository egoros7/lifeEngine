//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (��������� �����) ***
//				Copyright (C) 2018-2019
//
// ����������� ������:  https://github.com/zombihello/lifeEngine
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef IGAME_H
#define IGAME_H

#include "common/types.h"
#include "engine/iappsystem.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	struct Event;
	class IEngine;

	//---------------------------------------------------------------------//

	class IGame
	{
	public:
		virtual bool				Initialize( IEngine* Engine ) = 0;
		virtual void				Update( UInt32_t DeltaTime ) = 0;
		virtual void				OnEvent( const Event& Event ) = 0;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !IGAME_H

