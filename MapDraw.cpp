#include "MapDraw.h"


MapDraw::MapDraw()
{

}

void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}


void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "¦£";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¤";
		}
		else if (y == Height - 1)
		{
			cout << "¦¦";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¥";
		}
		else
		{
			cout << "¦¢";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "¦¢";
		}
	}
	return;
}

void MapDraw::MainMapDraw(int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x == 0 && y == 0)
				cout << "¦£";
			else if (x == width - 1 && y == 0)
				cout << "¦¤";
			else if (x > 0 && x < width - 1 && y == 0)
				cout << "¦¨";
			else if (x == 0 && y > 0 && y < height - 1)
				cout << "¦§";
			else if (x == width - 1 && y > 0 && y < height - 1)
				cout << "¦©";
			else if (x > 0 && x < width - 1 && y == height - 1)
				cout << "¦ª";
			else if (x == 0 && y == height - 1)
				cout << "¦¦";
			else if (x == width - 1 && y == height - 1)
				cout << "¦¥";
			else
				cout << "¦«";
		}
		cout << endl;
	}
}

void MapDraw::CursorErase(int x, int y, int width, int height)
{
	gotoxy(x * 2, y);
	if (x == 0 && y == 0)
		cout << "¦£";
	else if (x == width - 1 && y == 0)
		cout << "¦¤";
	else if (x > 0 && x < width - 1 && y == 0)
		cout << "¦¨";
	else if (x == 0 && y > 0 && y < height - 1)
		cout << "¦§";
	else if (x == width - 1 && y > 0 && y < height - 1)
		cout << "¦©";
	else if (x > 0 && x < width - 1 && y == height - 1)
		cout << "¦ª";
	else if (x == 0 && y == height - 1)
		cout << "¦¦";
	else if (x == width - 1 && y == height - 1)
		cout << "¦¥";
	else
		cout << "¦«";
	return;
}

MapDraw::~MapDraw()
{
}
