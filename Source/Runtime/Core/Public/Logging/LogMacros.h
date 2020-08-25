// Copyright BSOD-Games, All Rights Reserved.
// Authors: Egor Pogulyaka (zombiHello)

#ifndef LOGMACROS_H
#define LOGMACROS_H

#include "Misc/CoreDefines.h"
#include "Logging/Logger.h"

// If debug configuration - allow print debug info to logs
#ifdef LIFEENGINE_DEBUG
	#define LIFEENGINE_LOG_DEBUG( Category, Message, ... )			le::Logger::GetInstance()->Logf( le::LT_Debug, Category, Message, __VA_ARGS__ )
#else
	#define LIFEENGINE_LOG_DEBUG( Category, Message, ... )
#endif // LIFEENGINE_DEBUG

// Macros for print info, warning and errors to logs
#define LIFEENGINE_LOG_INFO( Category, Message, ... )				le::Logger::GetInstance()->Logf( le::LT_Info, Category, Message, __VA_ARGS__ )
#define LIFEENGINE_LOG_WARNING( Category, Message, ... )			le::Logger::GetInstance()->Logf( le::LT_Warning, Category, Message, __VA_ARGS__ )
#define LIFEENGINE_LOG_ERROR( Category, Message, ... )				le::Logger::GetInstance()->Logf( le::LT_Error, Category, Message, __VA_ARGS__ )

// Macros for print fatal error in log and stop engine
#define LIFEENGINE_LOG_FAIL( Category, Message, ... ) \
{ \
	le::Logger::GetInstance()->Logf( le::LT_Fail, Category, "Fatal error in file [" __FILE__ "] on line %i", __LINE__ ); \
	le::Logger::GetInstance()->Logf( le::LT_Fail, Category, Message, __VA_ARGS__ ); \
	PLATFORM_BREAK(); \
}

#endif // !LOGMACROS_H
