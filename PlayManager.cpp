#include "PlayManager.h"



PlayManager::PlayManager()
{
	m_iMapWidth = WIDTH;
	m_iMapHeight = HEIGHT;
	m_iTurnCount = 1;
	m_bGamePlayCheck = false;
}

void PlayManager::LoadPlayerSetting(TEAM team, string CursorIcon, string StoneIcon)
{
	m_PlayerList[team].CursorIconSetting(CursorIcon);
	m_PlayerList[team].StoneIconSetting(StoneIcon);
	m_PlayerList[team].CursorSetting(m_iMapWidth, m_iMapHeight);
}

void PlayManager::WantSave()
{
	int select;

	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
	m_DrawManager.DrawMidText("저장하시겠습니까 ?", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("1.현재 게임 저장", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("2.저장 없이 종료", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.gotoxy(m_iMapWidth, m_iMapHeight * 0.7);
	cin >> select;

	switch (select)
	{
	case 1:
		m_iTurnCount--;
		Save();
		break;
	case 2:
		break;
	}

}
void PlayManager::Save()
{
	ofstream save;
	int Black = 0;
	int White = 0;

	save.open("LastGame.txt");
	if (save.is_open())
	{
		save << m_iMapWidth << " " << m_iMapHeight << endl;
		save << m_iTurnCount << endl;
		save << m_PlayerList[BLACK].GetStoneCount() << " " << m_PlayerList[WHITE].GetStoneCount() << endl;
		save << m_PlayerList[BLACK].GetName() << " " << m_PlayerList[WHITE].GetName() << endl;
		save << m_PlayerList[BLACK].GetIcon() << " " << m_PlayerList[WHITE].GetIcon() << endl;
		save << m_PlayerList[BLACK].GetCursorIcon() << " " << m_PlayerList[WHITE].GetCursorIcon() << endl;
		for (int i = 1; i <= m_iTurnCount; i++)
		{
			if (i % 2 == 1)
			{
				save << m_PlayerList[BLACK].GetStonePosition(Black).StonePositionX << " " << m_PlayerList[BLACK].GetStonePosition(Black).StonePositionY << endl;
				Black++;
			}
			else
			{
				save << m_PlayerList[WHITE].GetStonePosition(White).StonePositionX << " " << m_PlayerList[WHITE].GetStonePosition(White).StonePositionY << endl;
				White++;
			}

		}
		save.close();
	}
}

void PlayManager::Load()
{
	ifstream Load;
	string Name;
	string Icon;
	string Cursor;
	int Turn;
	int X;
	int Y;
	int StoneCount;
	int MapWidth;
	int MapHeight;

	m_PlayerList[BLACK].LoadMemory(m_iMapWidth, m_iMapHeight);
	m_PlayerList[WHITE].LoadMemory(m_iMapWidth, m_iMapHeight);

	Load.open("LastGame.txt");

	if (Load.is_open())
	{
		Load >> MapWidth;
		m_iMapWidth = MapWidth;
		Load >> MapHeight;
		m_iMapHeight = MapHeight;
		Load >> Turn;
		m_iTurnCount = Turn;
		Load >> StoneCount;
		m_PlayerList[BLACK].SetStoneCount(StoneCount);
		Load >> StoneCount;
		m_PlayerList[WHITE].SetStoneCount(StoneCount);
		Load >> Name;
		m_PlayerList[BLACK].NameSetting(Name);
		Load >> Name;
		m_PlayerList[WHITE].NameSetting(Name);
		Load >> Icon;
		m_PlayerList[BLACK].StoneIconSetting(Icon);
		Load >> Icon;
		m_PlayerList[WHITE].StoneIconSetting(Icon);
		Load >> Cursor;
		m_PlayerList[BLACK].CursorIconSetting(Cursor);
		Load >> Cursor;
		m_PlayerList[WHITE].CursorIconSetting(Cursor);

		for (int i = 0, m_iTurnCount = 1; m_iTurnCount <= Turn; m_iTurnCount++)
		{
			Load >> X >> Y;
			if (m_iTurnCount % 2 == 1)
				m_PlayerList[BLACK].LoadStone(i, X, Y);
			else
				m_PlayerList[WHITE].LoadStone(i++, X, Y);

		}
		Load.close();
	}
}

void PlayManager::Replay()
{
	char buf[256];

	system("cls");

	Load();

	sprintf(buf, "mode con: lines=%d cols=%d", m_iMapHeight + 5, (m_iMapWidth * 2) + 1);
	system(buf);
	m_DrawManager.MainMapDraw(m_iMapWidth, m_iMapHeight);

	for (int i = 0, _Turn = 1; _Turn <= m_iTurnCount; _Turn++)
	{
		Sleep(1000);
		if (_Turn % 2 == 1)
		{
			m_PlayerList[BLACK].ReplayDraw(i);
			m_DrawManager.DrawMidText(m_PlayerList[BLACK].GetName(), m_iMapWidth, m_iMapHeight + 1);
		}
		else
		{
			m_PlayerList[WHITE].ReplayDraw(i);
			m_DrawManager.DrawMidText(m_PlayerList[WHITE].GetName(), m_iMapWidth, m_iMapHeight + 1);
			i++;
		}
	}
	m_DrawManager.DrawMidText("리플레이를 종료하시려면 아무키나 누르세요.", m_iMapWidth*0.01, m_iMapHeight + 1);
	getch();
}


void PlayManager::MainMenu()
{
	bool GameExit = true;
	int select;
	char buf[256];

	sprintf(buf, "mode con: lines=%d cols=%d", m_iMapHeight + 5, (m_iMapWidth * 2) + 1);
	system(buf);
	while (GameExit)
	{
		system("cls");
		m_DrawManager.MainMapDraw(m_iMapWidth, m_iMapHeight);
		MenuDraw();
		cin >> select;
		switch (select)
		{
		case MAINMENU_GAMESTART:
			m_bGamePlayCheck = true;
			m_iTurnCount = 1;
			Game();
			break;
		case MAINMENU_REPLAY:
			Replay();
			break;
		case MAINMENU_OPTIONSETTING:
			OptionSetting();
			break;
		case MAINMENU_EXIT:
			GameExit = false;
			break;
		}
	}
}

void PlayManager::MenuDraw()
{
	m_DrawManager.DrawMidText(" ★ 오 목 ★", m_iMapWidth, m_iMapHeight * 0.2);
	m_DrawManager.DrawMidText("1.게임 시작", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.리플레이", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("3.옵션 설정", m_iMapWidth, m_iMapHeight * 0.5);
	m_DrawManager.DrawMidText("4.게임 종료", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.BoxDraw(m_iMapWidth / 2, m_iMapHeight * 0.7, m_iMapWidth * 0.5, 3);
	m_DrawManager.gotoxy(m_iMapWidth, m_iMapHeight * 0.7 + 1);
}

void PlayManager::OptionMenuDraw()
{
	m_DrawManager.DrawMidText("= Option =", m_iMapWidth, m_iMapHeight * 0.2);
	m_DrawManager.DrawMidText("1.Map Size Set", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.Cursor Custom", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("3.Stone Custom", m_iMapWidth, m_iMapHeight * 0.5);
	m_DrawManager.DrawMidText("4.Undo Count Set", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.DrawMidText("5.Return", m_iMapWidth, m_iMapHeight * 0.7);
	m_DrawManager.DrawMidText("입력 : ", m_iMapWidth, m_iMapHeight * 0.8);
}

void PlayManager::MapSizeSetting()
{
	int Width;
	int Height;
	char buf[256];

	if (m_bGamePlayCheck == false)
	{
		system("cls");
		m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
		m_DrawManager.DrawMidText("Width : ", m_iMapWidth, m_iMapHeight * 0.4);
		cin >> Width;
		m_DrawManager.DrawMidText("Height : ", m_iMapWidth, m_iMapHeight * 0.6);
		cin >> Height;
		if (Width >= 20 && Width <= 90 && Height >= 20 && Height <= 45)
		{
			m_iMapWidth = Width;
			m_iMapHeight = Height;
			sprintf(buf, "mode con: lines=%d cols=%d", m_iMapHeight + 5, (m_iMapWidth * 2) + 1);
			system(buf);
			m_PlayerList[BLACK].MapSetCheck();
			m_PlayerList[WHITE].MapSetCheck();
			return;
		}
		else
		{
			system("cls");
			m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
			m_DrawManager.DrawMidText("변경 불가능", m_iMapWidth, m_iMapHeight * 0.4);
			m_DrawManager.DrawMidText("(가로 : 20 ~ 90, 세로 : 20 ~ 45)", m_iMapWidth, m_iMapHeight * 0.5);
			getch();
		}
	}
	else
	{
		system("cls");
		m_DrawManager.DrawMidText("접근 불가능", m_iMapWidth, m_iMapHeight * 0.4);
		m_DrawManager.DrawMidText("(Game Play중)", m_iMapWidth, m_iMapHeight * 0.5);
		getch();
	}
}
void PlayManager::CursorMenu()
{
	m_DrawManager.DrawMidText("= Set Cursor =", m_iMapWidth, m_iMapHeight * 0.2);
	m_DrawManager.DrawMidText("1.○,●", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.♡,♥", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("3.☞,☜", m_iMapWidth, m_iMapHeight * 0.5);
	m_DrawManager.DrawMidText("4.①,②", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.DrawMidText("5.Return", m_iMapWidth, m_iMapHeight * 0.7);
	m_DrawManager.DrawMidText("입력 : ", m_iMapWidth, m_iMapHeight * 0.8);
}

void PlayManager::CursorSetting()
{
	int Select;

	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
	CursorMenu();
	cin >> Select;

	switch (Select)
	{
	case 1:
		m_PlayerList[WHITE].CursorIconSetting("●");
		m_PlayerList[BLACK].CursorIconSetting("○");
		break;
	case 2:
		m_PlayerList[WHITE].CursorIconSetting("♥");
		m_PlayerList[BLACK].CursorIconSetting("♡");
		break;
	case 3:
		m_PlayerList[WHITE].CursorIconSetting("☜");
		m_PlayerList[BLACK].CursorIconSetting("☞");
		break;
	case 4:
		m_PlayerList[WHITE].CursorIconSetting("②");
		m_PlayerList[BLACK].CursorIconSetting("①");
		break;
	case 5:
		return;
	}
}
void PlayManager::StoneMenu()
{
	m_DrawManager.DrawMidText("= Set Stone =", m_iMapWidth, m_iMapHeight * 0.2);
	m_DrawManager.DrawMidText("1.○,●", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.♡,♥", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("3.☏,☎", m_iMapWidth, m_iMapHeight * 0.5);
	m_DrawManager.DrawMidText("4.①,②", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.DrawMidText("5.Return", m_iMapWidth, m_iMapHeight * 0.7);
	m_DrawManager.DrawMidText("입력 : ", m_iMapWidth, m_iMapHeight * 0.8);
}

void PlayManager::StoneSetting()
{
	int Select;

	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
	StoneMenu();
	cin >> Select;

	switch (Select)
	{
	case 1:
		m_PlayerList[WHITE].StoneIconSetting("●");
		m_PlayerList[BLACK].StoneIconSetting("○");
		break;
	case 2:
		m_PlayerList[WHITE].StoneIconSetting("♥");
		m_PlayerList[BLACK].StoneIconSetting("♡");
		break;
	case 3:
		m_PlayerList[WHITE].StoneIconSetting("☎");
		m_PlayerList[BLACK].StoneIconSetting("☏");
		break;
	case 4:
		m_PlayerList[WHITE].StoneIconSetting("②");
		m_PlayerList[BLACK].StoneIconSetting("①");
		break;
	case 5:
		return;
	}
}

void PlayManager::UndoMenu()
{
	m_DrawManager.DrawMidText("= Set Undo =", m_iMapWidth, m_iMapHeight * 0.2);
	m_DrawManager.DrawMidText("1.Set Undo Count", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.Undo Off", m_iMapWidth, m_iMapHeight * 0.4);
	m_DrawManager.DrawMidText("3.Return", m_iMapWidth, m_iMapHeight * 0.5);
	m_DrawManager.DrawMidText("입력 : ", m_iMapWidth, m_iMapHeight * 0.6);
}

void PlayManager::UndoSetting()
{
	int Select;

	while (1)
	{
		if (m_bGamePlayCheck == false)
		{
			system("cls");
			m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
			UndoMenu();
			cin >> Select;
			switch (Select)
			{
			case 1:
				while (1)
				{
					system("cls");
					m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
					m_DrawManager.DrawMidText("무르기 횟수 입력(최대 10회) : ", m_iMapWidth, m_iMapHeight * 0.5);
					cin >> Select;
					if (Select < 0 || Select > 10)
					{
						m_DrawManager.DrawMidText("범위가 맞지 않습니다(0 ~ 10)", m_iMapWidth, m_iMapHeight * 0.6);
						getch();
					}
					else
						break;
				}
				m_PlayerList[BLACK].UndoSetting(Select);
				m_PlayerList[WHITE].UndoSetting(Select);
				break;
			case 2:
				system("cls");
				m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
				m_DrawManager.DrawMidText("무르기 Off", m_iMapWidth, m_iMapHeight * 0.5);
				m_PlayerList[BLACK].UndoSetting(0);
				m_PlayerList[WHITE].UndoSetting(0);
				getch();
				break;
			case 3:
				return;
			}
		}
		else
		{
			system("cls");
			m_DrawManager.DrawMidText("접근 불가능", m_iMapWidth, m_iMapHeight * 0.4);
			m_DrawManager.DrawMidText("(Game Play중)", m_iMapWidth, m_iMapHeight * 0.5);
			getch();
			break;
		}
	}
}

void PlayManager::OptionSetting()
{
	int select;
	bool OptionSetting = true;

	while (OptionSetting)
	{
		system("cls");
		m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);
		OptionMenuDraw();
		cin >> select;
		switch (select)
		{
		case OPTIONMENU_MAPSIZESETTING:
			MapSizeSetting();
			break;
		case OPTIONMENU_CURSORCUSTOM:
			CursorSetting();
			break;
		case OPTIONMENU_STONECUSTOM:
			StoneSetting();
			break;
		case OPTIONMENU_UNDOCOUNTSET:
			UndoSetting();
			break;
		case OPTIONMENU_RETURN:
			OptionSetting = false;
			break;
		}
	}
}

void PlayManager::Game()
{
	int Select;
	bool LoadCheck = false;
	char buf[256];

	sprintf(buf, "mode con: lines=%d cols=%d", m_iMapHeight + 5, (m_iMapWidth * 2) + 1);
	system(buf);

	system("cls");
	m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);

	m_DrawManager.DrawMidText("1.새로하기", m_iMapWidth, m_iMapHeight * 0.3);
	m_DrawManager.DrawMidText("2.불러오기", m_iMapWidth, m_iMapHeight * 0.6);
	m_DrawManager.gotoxy(m_iMapWidth, m_iMapHeight * 0.8);
	cin >> Select;

	switch (Select)
	{
	case LOADMENU_NEWGAME:
		system("cls");
		m_DrawManager.BoxDraw(0, 0, m_iMapWidth, m_iMapHeight);

		NameSetting("P1 이름", BLACK, m_iMapWidth, m_iMapHeight * 0.3);
		NameSetting("P2 이름", WHITE, m_iMapWidth, m_iMapHeight * 0.5);


		PlayerSetting(BLACK, "○", "○");
		PlayerSetting(WHITE, "●", "●");
		break;

	case LOADMENU_LOADGAME:
		LoadCheck = true;
		Load();
		LoadPlayerSetting(BLACK, m_PlayerList[BLACK].GetCursorIcon(), m_PlayerList[BLACK].GetIcon());
		LoadPlayerSetting(WHITE, m_PlayerList[WHITE].GetCursorIcon(), m_PlayerList[WHITE].GetIcon());
		break;
	}

	system("cls");
	sprintf(buf, "mode con: lines=%d cols=%d", m_iMapHeight + 5, (m_iMapWidth * 2) + 1);
	system(buf);
	m_DrawManager.MainMapDraw(m_iMapWidth, m_iMapHeight);
	InGameState();

	if (LoadCheck)
	{
		for (int i = 0, _Turn = 1; _Turn <= m_iTurnCount; _Turn++)
		{
			if (_Turn % 2 == 1)
			{
				m_PlayerList[BLACK].ReplayDraw(i);
				//m_DrawManager.DrawMidText(m_PlayerList[BLACK].GetName(), m_iMapWidth, m_iMapHeight + 1);
			}
			else
			{
				m_PlayerList[WHITE].ReplayDraw(i);
				//m_DrawManager.DrawMidText(m_PlayerList[WHITE].GetName(), m_iMapWidth, m_iMapHeight + 1);
				i++;
			}
		}
		m_iTurnCount++;
	}

	while (m_bGamePlayCheck)
	{
		InGameState();
		m_PlayerList[m_iTurnCount % 2].DrawCursor();
		_Move();
	}
}

void PlayManager::_Move()
{
	char ch;
	Position Cursor;

	switch (ch = getch())
	{
	case KEY_UP:
	case KEY_DOWN:
	case KEY_LEFT:
	case KEY_RIGHT:
		DrawPoint();
		m_PlayerList[m_iTurnCount % 2].Move(ch, m_iMapWidth, m_iMapHeight);
		break;
	case KEY_ESC:
		WantSave();
		m_bGamePlayCheck = false;
		break;
	case KEY_ENTER:
		Cursor = m_PlayerList[m_iTurnCount % 2].GetCursorPosition();
		if (m_PlayerList[BLACK].StoneCheck(Cursor.StonePositionX, Cursor.StonePositionY) == true || m_PlayerList[WHITE].StoneCheck(Cursor.StonePositionX, Cursor.StonePositionY) == true)
			break;
		else
		{
			m_PlayerList[m_iTurnCount % 2].AddStone();
			if (m_PlayerList[m_iTurnCount % 2].WinCheck(m_iMapWidth, m_iMapHeight))
			{
				m_bGamePlayCheck = false;
				m_DrawManager.DrawMidText(m_PlayerList[m_iTurnCount % 2].GetName() + "팀 승리!!", m_iMapWidth, m_iMapHeight * 0.5);
				getch();
				Save();
			}
			m_iTurnCount++;
		}
		break;
	case KEY_UNDO:
		if (m_PlayerList[m_iTurnCount % 2].GetUndoCount() > 0)
		{
			m_PlayerList[m_iTurnCount % 2].UndoCursor(m_iMapWidth, m_iMapHeight);
			m_PlayerList[m_iTurnCount % 2].UndoCountDown();
			m_iTurnCount--;
			m_PlayerList[m_iTurnCount % 2].UndoStone(m_iMapWidth, m_iMapHeight);
		}
		break;
	case KEY_OPTION:
		OptionSetting();
		system("cls");
		m_DrawManager.MainMapDraw(m_iMapWidth, m_iMapHeight);
		InGameState();
		m_PlayerList[WHITE].OptionStoneDraw();
		m_PlayerList[BLACK].OptionStoneDraw();
	}
}

void PlayManager::DrawPoint()
{
	m_DrawManager.CursorErase(m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionX, m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionY, m_iMapWidth, m_iMapHeight);
	m_PlayerList[BLACK].DrawStone(m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionX, m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionY);
	m_PlayerList[WHITE].DrawStone(m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionX, m_PlayerList[m_iTurnCount % 2].GetCursorPosition().StonePositionY);
}

void PlayManager::NameSetting(string str, TEAM team, int x, int y)
{
	m_DrawManager.DrawMidText(str, x, y);
	m_DrawManager.DrawMidText("입력 : ", x, y + 1);
	m_PlayerList[team].SetName();
}

void PlayManager::PlayerSetting(TEAM team, string CursorIcon, string StoneIcon)
{
	m_PlayerList[team].CursorIconSetting(CursorIcon);
	m_PlayerList[team].StoneIconSetting(StoneIcon);
	m_PlayerList[team].CursorSetting(m_iMapWidth, m_iMapHeight);
	m_PlayerList[team].PlayerSetting(m_iMapWidth, m_iMapHeight);
}

void PlayManager::InGameState()
{
	string name;
	string str;
	int UndoCount;

	string TurnStr;

	name = m_PlayerList[m_iTurnCount % 2].GetName();
	UndoCount = m_PlayerList[m_iTurnCount % 2].GetUndoCount();

	str = "Player Name : " + name + "	무르기 : " + to_string(UndoCount);

	TurnStr = " Turn : " + to_string(m_iTurnCount);

	m_DrawManager.DrawMidText("====조작키====", m_iMapWidth, m_iMapHeight);
	m_DrawManager.DrawMidText("이동:A,S,W,D 돌놓기 : ENTER", m_iMapWidth, m_iMapHeight + 1);
	m_DrawManager.DrawMidText("무르기 : N 옵션 : P 종료 : ESC", m_iMapWidth, m_iMapHeight + 2);
	m_DrawManager.DrawMidText(str, m_iMapWidth, m_iMapHeight + 3);
	m_DrawManager.DrawMidText(TurnStr, m_iMapWidth, m_iMapHeight + 4);
}

PlayManager::~PlayManager()
{
}
