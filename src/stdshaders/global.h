//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GLOBAL_H
#define GLOBAL_H

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class IFactory;
	extern IFactory*			g_studioRenderFactory;

	//---------------------------------------------------------------------//

	class IConsoleSystem;
	extern IConsoleSystem*		g_consoleSystem;

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !GLOBAL_H

