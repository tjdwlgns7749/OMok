#pragma once
#include "Mecro.h"
#include "MapDraw.h"


#define UNDO 5
#define WIN 4

struct Position
{
	int StonePositionX;
	int StonePositionY;
};

class Player
{
private:
	MapDraw m_DrawManager;
	Position Cursor;
	Position* m_StoneList;
	string m_PlayerName;
	int m_iUndoCount;
	string CursorIcon;
	int m_iStoneCount;
	string StoneIcon;
	int m_iSubUndoCount;
	bool m_bMapSetCheck;

public:
	Player();
	~Player();
	void Move(char ch, int width, int height);
	void DrawCursor();
	void CursorSetting(int x, int y);
	void AddStone();
	void PlayerSetting(int Width, int Height);
	void DrawStone(int x, int y);
	bool StoneCheck(int x, int y);
	bool WinCheck(int Width, int Height);
	int WinStoneCount(int Width, int Height, int Cursor_x, int Cursor_y, int x, int y);
	void UndoCursor(int Width, int Height);
	void UndoStone(int Width, int Height);
	void OptionStoneDraw();
	bool StoneReset();
	void LoadStone(int i, int X, int Y);
	void ReplayDraw(int i);
	void LoadMemory(int Width, int Height);

	inline string GetName() { return m_PlayerName; };
	inline int GetUndoCount() { return m_iUndoCount; };
	inline void SetName() { cin >> m_PlayerName; };
	inline void showName() { cout << m_PlayerName; };
	inline void CursorIconSetting(string icon) { CursorIcon = icon; };
	inline void StoneIconSetting(string icon) { StoneIcon = icon; };
	inline Position GetCursorPosition() { return Cursor; };
	inline void UndoCountDown() { m_iUndoCount--; };
	inline void UndoSetting(int UndoCount) { m_iUndoCount = UndoCount; m_iSubUndoCount = UndoCount; };
	inline void MapSetCheck() { m_bMapSetCheck = true; };
	inline string GetIcon() { return StoneIcon; };
	inline string GetCursorIcon() { return CursorIcon; };
	inline Position GetStonePosition(int Count) { return m_StoneList[Count]; };
	inline void NameSetting(string name) { m_PlayerName = name; };
	inline int GetStoneCount() { return m_iStoneCount; };
	inline void SetStoneCount(int StoneCount) { m_iStoneCount = StoneCount; };

};

