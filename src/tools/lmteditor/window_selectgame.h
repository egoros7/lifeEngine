//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2020
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_SELECTGAME_H
#define WINDOW_SELECTGAME_H

#include <QDialog>

//---------------------------------------------------------------------//

namespace Ui
{
	class Window_SelectGame;
}

//---------------------------------------------------------------------//

class Window_SelectGame : public QDialog
{
	Q_OBJECT

public:
	// Window_SelectGame
	Window_SelectGame( QWidget* Parent = nullptr );
	~Window_SelectGame();

private slots:
	void				on_pushButton_editGames_clicked();

private:
	Ui::Window_SelectGame*			ui;
};

//---------------------------------------------------------------------//

#endif // WINDOW_SELECTGAME_H
