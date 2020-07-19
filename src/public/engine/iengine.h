//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef IENGINE_H
#define IENGINE_H

#include "common/types.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	struct Configurations;
	struct Version;
    struct GameInfo;
	class IConsoleSystem;
	class IStudioRender;
	class IWindow;
	class IFactory;
	class IResourceSystem;
	class IInputSystem;
    class IMaterialSystem;
    class IPhysicsSystem;
	class IScriptSystem;
	class IAudioSystem;

	//---------------------------------------------------------------------//

	class IEngine
	{
	public:
        virtual ~IEngine() {}
		virtual void					RunSimulation() = 0;
		virtual void					StopSimulation() = 0;		

		virtual bool					IsRunSimulation() const = 0;
		virtual bool					IsEditor() const = 0;
		virtual IConsoleSystem*			GetConsoleSystem() const = 0;
		virtual IStudioRender*			GetStudioRender() const = 0;
		virtual IResourceSystem*		GetResourceSystem() const = 0;
		virtual IInputSystem*			GetInputSystem() const = 0;
        virtual IMaterialSystem*		GetMaterialSystem() const = 0;
        virtual IPhysicsSystem*         GetPhysicsSystem() const = 0;
		virtual IScriptSystem*			GetScriptSystem() const = 0;
		virtual IAudioSystem*			GetAudioSystem() const = 0;
		virtual IWindow*				GetWindow() const = 0;
		virtual IFactory*				GetFactory() const = 0;
		virtual float					GetFixedTimeStep() const = 0;
        virtual const GameInfo&         GetGameInfo() const = 0;
		virtual Configurations			GetConfigurations() const = 0;
		virtual Version					GetVersion() const = 0;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !IENGINE_H
