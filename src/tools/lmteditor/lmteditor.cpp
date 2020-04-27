//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2020
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <qapplication.h>
#include <qfile.h>
#include <qtextstream.h>
#include <fstream>
#include <qmessagebox.h>
#include <sstream>
#include <qdebug.h>

#include "engine/iconsolesystem.h"
#include "engineapi.h"
#include "window_selectgame.h"
#include "window_editor.h"

#define GOLD_DATE					43572			// Apr 18 2020 (start coding lmteditor)
#define LMTEDITOR_VERSION_MAJOR		0
#define LMTEDITOR_VERSION_MINOR		1
#define LMTEDITOR_VERSION_PATCH		0

// ------------------------------------------------------------------------------------ //
// Compute build number
// ------------------------------------------------------------------------------------ //
int Application_ComputeBuildNumber( int GoldDate )
{
	const char* date = __DATE__;

	const char* month[ 12 ] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	const char		month_days[ 12 ] =
	{ 31,    28,    31,    30,    31,    30,    31,    31,    30,    31,    30,    31 };

	int				buildNumber = 0;
	int				months = 0;
	int				days = 0;
	int				years = 0;

	for ( months = 0; months < 11; ++months )
	{
		if ( strncmp( &date[ 0 ], month[ months ], 3 ) == 0 )
			break;

		days += month_days[ months ];
	}

	days += atoi( &date[ 4 ] ) - 1;
	years = atoi( &date[ 7 ] ) - 1900;

	buildNumber = days + static_cast< int >( ( years - 1 ) * 365.25f );

	if ( ( years % 4 == 0 ) && months > 1 )
		++buildNumber;

	buildNumber -= GoldDate;
	return buildNumber;
}

// ------------------------------------------------------------------------------------ //
// Application critical error
// ------------------------------------------------------------------------------------ //
void Application_CriticalError( const char* Message )
{
	std::ofstream			fileLog( "lmteditor.log", std::ios::app );
	
	QMessageBox::critical( nullptr, "Error lmtedit", Message );
	fileLog << "\nCritical error: " << Message;
	exit( 1 );
}

// ------------------------------------------------------------------------------------ //
// Print message in logs
// ------------------------------------------------------------------------------------ //
void Application_MessageOutput( QtMsgType Type, const QMessageLogContext &Context, const QString &Message )
{
	static le::IConsoleSystem*			consoleSystem = nullptr;
	if ( !consoleSystem )				consoleSystem = EngineAPI::GetInstance()->GetConsoleSystem();

	switch ( Type )
	{
	case QtDebugMsg:
		consoleSystem->PrintInfo( Message.toLocal8Bit().data() );
		break;

	case QtInfoMsg:
		consoleSystem->PrintInfo( Message.toLocal8Bit().data() );
		break;

	case QtWarningMsg:
		consoleSystem->PrintWarning( Message.toLocal8Bit().data() );
		break;

	case QtCriticalMsg:
		consoleSystem->PrintError( Message.toLocal8Bit().data() );
		break;

	case QtFatalMsg:
		consoleSystem->PrintError( Message.toLocal8Bit().data() );
		exit( 1 );
		break;
	}

}

// ------------------------------------------------------------------------------------ //
// Main function
// ------------------------------------------------------------------------------------ //
int main( int argc, char** argv )
{
	QApplication			application( argc, argv );
	EngineAPI*				engineAPI = new EngineAPI();

	// Loading engine
	if ( !engineAPI->Load() )
	{
		Application_CriticalError( engineAPI->GetErrorString().toLocal8Bit().data() );
		return 1;
	}

    qInstallMessageHandler( Application_MessageOutput  );
	{
		std::stringstream				strStream;
		strStream << "LMTEditor " << LMTEDITOR_VERSION_MAJOR << "." << LMTEDITOR_VERSION_MINOR << "." << LMTEDITOR_VERSION_PATCH << " (build " << Application_ComputeBuildNumber( GOLD_DATE ) << ")";
		qDebug() << strStream.str().c_str();

		strStream.str( "" );
		strStream << "Qt version: " << qVersion();
		qDebug() << strStream.str().c_str();
	}

	// Loading style
	/*{
		QFile			file( "styles/dark/style.css" );
		if ( file.exists() )
		{
			file.open( QFile::ReadOnly | QFile::Text );
			QTextStream			textStream( &file );
			application.setStyleSheet( textStream.readAll() );
		}
	}*/

	// Selecting game for work
	{
		Window_SelectGame						window_SelectGame;
		Window_SelectGame::RESULT_TYPE			result = ( Window_SelectGame::RESULT_TYPE ) window_SelectGame.exec();
		if ( result == Window_SelectGame::RT_CANCEL )
			return 0;
	}

	// Start editor
	Window_Editor				window_Editor;
	window_Editor.show();
	return application.exec();
}
