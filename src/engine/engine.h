//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "common/configurations.h"
#include "common/version.h"
#include "common/gameinfo.h"
#include "engine/lifeengine.h"
#include "engine/iengineinternal.h"
#include "engine/consolesystem.h"
#include "engine/resourcesystem.h"
#include "engine/window.h"
#include "engine/enginefactory.h"
#include "engine/inputsystem.h"
#include "engine/materialsystem.h"
#include "engine/scriptsystem.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class IStudioRenderInternal;
    class IPhysicsSystemInternal;
	class IAudioSystemInternal;
	class IConCmd;
	class IConVar;

	//---------------------------------------------------------------------//

	struct StudioRenderDescriptor
	{
		void*								handle;
		LE_CreateStudioRenderFn_t			LE_CreateStudioRender;
		LE_DeleteStudioRenderFn_t			LE_DeleteStudioRender;
		LE_SetCriticalErrorFn_t				LE_SetCriticalError;
	};

	//---------------------------------------------------------------------//

    struct PhysicsSystemDescriptor
    {
        void*								handle;
        LE_CreatePhysicsSystemFn_t			LE_CreatePhysicsSystem;
        LE_DeletePhysicsSystemFn_t			LE_DeletePhysicsSystem;
        LE_SetCriticalErrorFn_t				LE_SetCriticalError;
    };

    //---------------------------------------------------------------------//

	struct AudioSystemDescriptor
	{
		void*								handle;
		LE_CreateAudioSystemFn_t			LE_CreateAudioSystem;
		LE_DeleteAudioSystemFn_t			LE_DeleteAudioSystem;
		LE_SetCriticalErrorFn_t				LE_SetCriticalError;
	};

	//---------------------------------------------------------------------//

	struct GameDescriptor
	{
		void*								handle;
		LE_CreateGameFn_t					LE_CreateGame;
		LE_DeleteGameFn_t					LE_DeleteGame;
		LE_SetCriticalErrorFn_t				LE_SetCriticalError;
	};

	//---------------------------------------------------------------------//

	class Engine : public IEngineInternal
	{
	public:

		friend void					ChangeCallback_WindowResize( IConVar* ConVar );
		friend void					ChangeCallback_WindowFullscreen( IConVar* ConVar );
		friend void					ChangeCallback_EnableVSinc( IConVar* ConVar );

		// IEngine	
		virtual void					RunSimulation();
		virtual void					StopSimulation();		

		virtual bool					IsRunSimulation() const;
		virtual IConsoleSystem*			GetConsoleSystem() const;
		virtual IStudioRender*			GetStudioRender() const;
		virtual IResourceSystem*		GetResourceSystem() const;
		virtual IInputSystem*			GetInputSystem() const;
        virtual IMaterialSystem*		GetMaterialSystem() const;
        virtual IPhysicsSystem*         GetPhysicsSystem() const;
		virtual IScriptSystem*			GetScriptSystem() const;
		virtual IWindow*				GetWindow() const;
		virtual IFactory*				GetFactory() const;
		virtual float					GetDeltaTime() const;
		virtual float					GetFixedTimeStep() const;
        virtual const GameInfo&         GetGameInfo() const;
		virtual const Version&			GetVersion() const;
		virtual Configurations			GetConfigurations() const;

		// IEngineInternal
		virtual bool					Initialize( const char* EngineDirectory, const char* LogFile = "console.log" );
		virtual bool					LoadGame( const char* DirGame, UInt32_t CountArguments = 0, const char** Arguments = nullptr );
		virtual void					UnloadGame();

		virtual const char*				GetEngineDirectory() const;

		// Engine
		Engine();
		~Engine();

	private:
		bool							LoadModule_StudioRender( const char* PathDLL );
		void							UnloadModule_StudioRender();
        bool							LoadModule_PhysicsSystem( const char* PathDLL );
        void							UnloadModule_PhysicsSystem();
		bool							LoadModule_AudioSystem( const char* PathDLL );
		void							UnloadModule_AudioSystem();
		bool							LoadGameInfo( const char* GameDir );
		bool							LoadModule_Game( const char* PathDLL, UInt32_t CountArguments, const char** Arguments  );
		void							UnloadModule_Game();

		bool							isInitialized;
		bool							isRunSimulation;
		float							deltaTime;

		IConCmd*						cmd_Exit;
		IConCmd*						cmd_Version;
		IConVar*						cvar_windowWidth;
		IConVar*						cvar_windowHeight;
		IConVar*						cvar_windowFullscreen;
		IConVar*						cvar_mouseSensitivity;
		IConVar*						cvar_rvsinc;
		IConVar*						cvar_phyDebug;

		IStudioRenderInternal*			studioRender;
		StudioRenderDescriptor			studioRenderDescriptor;

        IPhysicsSystemInternal*         physicSystem;
        PhysicsSystemDescriptor         physicSystemDescriptor;

		IAudioSystemInternal*			audioSystem;
		AudioSystemDescriptor			audioSystemDescriptor;

		IGame*							game;
		GameDescriptor					gameDescriptor;

		CriticalErrorCallbackFn_t		criticalError;
		ConsoleSystem					consoleSystem;
		ResourceSystem					resourceSystem;
		InputSystem						inputSystem;
		MaterialSystem					materialSystem;
		ScriptSystem					scriptSystem;
		Window							window;
		EngineFactory					engineFactory;
		GameInfo						gameInfo;
		std::string						engineDirectory;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !ENGINE_H
