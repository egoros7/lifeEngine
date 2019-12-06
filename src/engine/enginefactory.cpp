//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (��������� �����) ***
//				Copyright (C) 2018-2019
//
// ����������� ������:  https://github.com/zombihello/lifeEngine
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "enginefactory.h"
#include "concmd.h"
#include "convar.h"

// ------------------------------------------------------------------------------------ //
// ������� ������
// ------------------------------------------------------------------------------------ //
void* le::EngineFactory::Create( const char* NameInterface )
{
	if ( strcmp( NameInterface, CONCMD_INTERFACE_VERSION ) == 0 )				return new ConCmd();
	else if ( strcmp( NameInterface, CONVAR_INTERFACE_VERSION ) == 0 )			return new ConVar();

	return nullptr;
}

// ------------------------------------------------------------------------------------ //
// ������� ������
// ------------------------------------------------------------------------------------ //
void le::EngineFactory::Delete( const char* NameInterface, void* Object )
{
	if ( !Object ) return;
	delete Object;
}