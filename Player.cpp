#include "Player.h"


Player::Player()
{
	m_StoneList = NULL;
	m_iStoneCount = 0;
	m_iUndoCount = UNDO;
	m_iSubUndoCount = UNDO;
	m_bMapSetCheck = false;
}

void Player::LoadMemory(int Width, int Height)
{
	if (StoneReset())
		m_StoneList = new Position[(Width * Height) / 2];
}


void Player::ReplayDraw(int i)
{
	m_DrawManager.DrawPoint(StoneIcon, m_StoneList[i].StonePositionX, m_StoneList[i].StonePositionY);
}

void Player::LoadStone(int i, int X, int Y)
{
	m_StoneList[i].StonePositionX = X;
	m_StoneList[i].StonePositionY = Y;
}

void Player::Move(char ch, int width, int height)
{
	switch (ch)
	{
	case KEY_UP:
		if (Cursor.StonePositionY - 1 >= 0)
			Cursor.StonePositionY--;
		break;
	case KEY_DOWN:
		if (Cursor.StonePositionY + 1 < height)
			Cursor.StonePositionY++;
		break;
	case KEY_LEFT:
		if (Cursor.StonePositionX - 1 >= 0)
			Cursor.StonePositionX--;
		break;
	case KEY_RIGHT:
		if (Cursor.StonePositionX + 1 < width)
			Cursor.StonePositionX++;
		break;

	}
}

void Player::DrawCursor()
{
	m_DrawManager.DrawPoint(CursorIcon, Cursor.StonePositionX, Cursor.StonePositionY);
}

void Player::CursorSetting(int x, int y)
{
	Cursor.StonePositionX = x * 0.5;
	Cursor.StonePositionY = y * 0.5;
}

void Player::AddStone()
{
	if (StoneCheck(Cursor.StonePositionX, Cursor.StonePositionY) == false)
	{
		m_StoneList[m_iStoneCount].StonePositionX = Cursor.StonePositionX;
		m_StoneList[m_iStoneCount].StonePositionY = Cursor.StonePositionY;
		m_iStoneCount++;
		DrawStone(Cursor.StonePositionX, Cursor.StonePositionY);
	}
}

void Player::DrawStone(int x, int y)
{
	if (StoneCheck(x, y) == true)
		m_DrawManager.DrawPoint(StoneIcon, x, y);
}

bool Player::StoneCheck(int x, int y)
{
	for (int i = 0; i < m_iStoneCount; i++)
	{
		if (m_StoneList[i].StonePositionX == x && m_StoneList[i].StonePositionY == y)
			return  true;
	}
	return false;
}

bool Player::StoneReset()
{
	if (m_StoneList != NULL)//비지않았을때
	{
		if (m_bMapSetCheck == false)//맵 변경을 하지않았으면
			return false;
		else//맵크기 변경했으면
		{
			delete[] m_StoneList;
			m_StoneList = NULL;
			m_bMapSetCheck = false;
			return true;
		}
	}
	else//비었을때
		return true;
}

void Player::PlayerSetting(int Width, int Height)
{
	if (StoneReset())
		m_StoneList = new Position[(Width * Height) / 2];
	m_iStoneCount = 0;
	m_iUndoCount = m_iSubUndoCount;
}

int Player::WinStoneCount(int Width, int Height, int Cursor_x, int Cursor_y, int x, int y)
{
	int Count;

	for (Count = 0; (Cursor_x >= 0 && Cursor_x < Width) && (Cursor_y >= 0 && Cursor_y < Height);)
	{
		if (StoneCheck(Cursor_x, Cursor_y) == true)
		{
			Count++;
			Cursor_x += x;
			Cursor_y += y;
		}
		else
			break;
	}
	return Count;
}

void Player::OptionStoneDraw()
{
	for (int i = 0; i < m_iStoneCount; i++)
	{
		m_DrawManager.DrawPoint(StoneIcon, m_StoneList[i].StonePositionX, m_StoneList[i].StonePositionY);
	}
}

void Player::UndoStone(int Width, int Height)
{
	m_iStoneCount--;
	m_DrawManager.CursorErase(m_StoneList[m_iStoneCount].StonePositionX, m_StoneList[m_iStoneCount].StonePositionY, Width, Height);
}

void Player::UndoCursor(int Width, int Height)
{
	m_DrawManager.CursorErase(Cursor.StonePositionX, Cursor.StonePositionY, Width, Height);
}

bool Player::WinCheck(int Width, int Height)
{
	int Count = 0;
	//가로
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX + 1, Cursor.StonePositionY, 1, 0);
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX - 1, Cursor.StonePositionY, -1, 0);
	if (Count == WIN)
		return true;
	//세로
	Count = 0;
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX, Cursor.StonePositionY + 1, 0, 1);
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX, Cursor.StonePositionY - 1, 0, -1);
	if (Count == WIN)
		return true;
	//대각선왼쪽위오른쪽아래
	Count = 0;
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX + 1, Cursor.StonePositionY + 1, 1, 1);
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX - 1, Cursor.StonePositionY - 1, -1, -1);
	if (Count == WIN)
		return true;
	//대각선오른쪽위왼쪽아래
	Count = 0;
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX + 1, Cursor.StonePositionY - 1, 1, -1);
	Count += WinStoneCount(Width, Height, Cursor.StonePositionX - 1, Cursor.StonePositionY + 1, -1, +1);
	if (Count == WIN)
		return true;

	return false;
}

Player::~Player()
{
	if (m_StoneList != NULL)
		delete m_StoneList;
}