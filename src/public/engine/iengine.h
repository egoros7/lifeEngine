//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (��������� �����) ***
//				Copyright (C) 2018-2019
//
// ����������� ������:  https://github.com/zombihello/lifeEngine
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef IENGINE_H
#define IENGINE_H

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	struct Configurations;
	struct Version;
	class IConsoleSystem;
	class IStudioRender;
	class IWindow;
	class IFactory;
	class IMaterialSystem;

	//---------------------------------------------------------------------//

	class IEngine
	{
	public:
		virtual bool					LoadConfig( const char* FilePath ) = 0;
		virtual bool					SaveConfig( const char* FilePath ) = 0;	
		virtual void					RunSimulation() = 0;
		virtual void					StopSimulation() = 0;		

		virtual void					SetConfig( const Configurations& Configurations ) = 0;

		virtual bool					IsRunSimulation() const = 0;
		virtual IConsoleSystem*			GetConsoleSystem() const = 0;
		virtual IStudioRender*			GetStudioRender() const = 0;
		virtual IMaterialSystem*		GetMaterialSystem() const = 0;
		virtual IWindow*				GetWindow() const = 0;
		virtual IFactory*				GetFactory() const = 0;
		virtual const Configurations&	GetConfigurations() const = 0;
		virtual const Version&			GetVersion() const = 0;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !IENGINE_H
