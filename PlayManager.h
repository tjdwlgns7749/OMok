#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Player.h"

enum MAINMENU
{
	MAINMENU_GAMESTART = 1,
	MAINMENU_REPLAY,
	MAINMENU_OPTIONSETTING,
	MAINMENU_EXIT
};

enum OPTIONMENU
{
	OPTIONMENU_MAPSIZESETTING = 1,
	OPTIONMENU_CURSORCUSTOM,
	OPTIONMENU_STONECUSTOM,
	OPTIONMENU_UNDOCOUNTSET,
	OPTIONMENU_RETURN
};

enum LOADMENU
{
	LOADMENU_NEWGAME = 1,
	LOADMENU_LOADGAME
};

enum TEAM
{
	WHITE = 0,
	BLACK
};

#define WIDTH 20
#define HEIGHT 20

class PlayManager
{
private:
	int m_iMapHeight;
	int m_iMapWidth;
	int m_iTurnCount;
	bool m_bGamePlayCheck;
	MapDraw m_DrawManager;
	Player m_PlayerList[MAXPEOPLE];
public:
	void MainMenu();
	void MenuDraw();
	void OptionMenuDraw();
	void OptionSetting();
	void InGameState();
	void PlayerSetting(TEAM team, string CursorIcon, string StoneIcon);
	void Game();
	void _Move();
	void NameSetting(string str, TEAM team, int x, int y);
	void DrawPoint();
	void MapSizeSetting();
	void CursorSetting();
	void CursorMenu();
	void StoneSetting();
	void StoneMenu();
	void UndoSetting();
	void UndoMenu();
	void Save();
	void Load();
	void WantSave();
	void Replay();
	void LoadPlayerSetting(TEAM team, string CursorIcon, string StoneIcon);



	PlayManager();
	~PlayManager();
};

