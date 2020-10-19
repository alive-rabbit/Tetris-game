// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"

int X_START = 8, Y_START = 4;
wchar_t our_figure = L'0'; // переменная фигуры
wchar_t pice_of_figure = L'O'; // переменная, которая обозначает часть фигуры

TestApp::TestApp() : Parent(24, 24)
{
	mDirection = true;
	mObj1XOld = mObj1X = X_START;
	mObj1YOld = mObj1Y = Y_START;
	mObj2X = 2;
	mObj2Y = 12;
}

void TestApp::UpdateF(const float& deltaTime)
{
	Figure f_next{ mObj1X, mObj1Y, number_of_now_figure };
	Figure f_last{ mObj1XOld, mObj1YOld, number_of_now_figure };
	Clear_Last_Figure(mObj1XOld, mObj1YOld);
	Print_Any_Figure(mObj1X, mObj1Y, number_of_now_figure, our_figure, 0);

	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;

}
void TestApp::KeyPressed(const int& btnCode_1, const int& btnCode_2) // назначение клавиш
{
	if (btnCode_1 == 0) // необходимо для постоянного сдвига фигуры вниз
		mObj1Y++;
	else if (btnCode_2 == 80) // arrow down
	{
		while (GetChar(mObj1X, mObj1Y + 1) != pice_of_figure)
		{
			if (GetChar(mObj1X, mObj1Y + 1) == L'#')
			{
				break;
			}
			mObj1Y++;
		}
	}
	else if (btnCode_2 == 75) // arrow left
		mObj1X--;
	else if (btnCode_2 == 77) // arrow right
		mObj1X++;
	else if (btnCode_1 == 27) // ESCAPE
	{
		system("cls");
		HWND myConsole = GetConsoleWindow(); //window handle
		PostMessage(myConsole, WM_CLOSE, 0, 0);
	}
	else if (btnCode_1 == 32) // ESCAPE
	{
		if (number_of_now_figure == 2) 
		{ 
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 6; 
		}
		else if (number_of_now_figure == 6)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 2;
		}
		else if (number_of_now_figure == 3)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 7;
		}
		else if (number_of_now_figure == 7)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 3;
		}
		else if (number_of_now_figure == 4)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 8;
		}
		else if (number_of_now_figure == 8)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 9;
		}
		else if (number_of_now_figure == 9)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 10;
		}
		else if (number_of_now_figure == 10)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 4;
		}
		else if (number_of_now_figure == 5)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 11;
		}
		else if (number_of_now_figure == 11)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 12;
		}
		else if (number_of_now_figure == 12)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 13;
		}
		else if (number_of_now_figure == 13)
		{
			Clear_Last_Figure(mObj1X, mObj1Y);
			number_of_now_figure = 5;
		}
	}

	// проверка ограничителей

	int left_bordet = Y_SIZE - 8, down_bordet = X_SIZE - 4;
	Figure temp_fig{ mObj1X, mObj1Y, number_of_now_figure };

	if (temp_fig.fig[6] < 1) // ограничение передвижения
		mObj1X += 1;
	if (temp_fig.fig[2] >= left_bordet) // ограничение передвижения
		mObj1X--;
	else if (mObj1X >= left_bordet)
		mObj1X = left_bordet - 1;
	else if (mObj1Y < 1) // ограничение передвижения
		mObj1Y = 1; 

	for(int i = 0; i < 7; i += 2)
	{
		if (GetChar(temp_fig.fig[i], temp_fig.fig[i + 1]) == L'#' || GetChar(temp_fig.fig[i], temp_fig.fig[i + 1]) == pice_of_figure)
		{
			if (mObj1Y <= 5)// mObj1YOld)
			{
				system("cls");
				HWND myConsole = GetConsoleWindow(); //window handle
				PostMessage(myConsole, WM_CLOSE, 0, 0);
			}
			Clear_Last_Figure(mObj1XOld, mObj1YOld);
			Clear_Last_Figure(mObj1XOld, mObj1YOld);
			Print_Any_Figure(mObj1X, mObj1Y, number_of_now_figure, -1); // зарисовка фигуры, когда она опустилась вниз
			mObj1XOld = mObj1X = X_START;
			mObj1YOld = mObj1Y = Y_START;
			Figures _fig; // создание следующей фигуры
			number_of_now_figure = number_of_next_figure; // присвоение нынешней фигуре (что теперь будет новой) номер следующей фигуры
			number_of_next_figure = _fig.Get_Figure_Number(); 
			Clear_Any_Figure(21, 3, number_of_now_figure);
			Print_Any_Figure(21, 3, number_of_next_figure, 0);
			//SetChar(20, 3, _fig.Get_Figure()); // место следующей фигуры
			break;
		}
	}
}

void TestApp::Clear_Full_Line()
{
	for (int y = 1; y < 20; y++)
	{
		if (Is_Line_Full(y) == 15) // y - высота заполненной строки
		{
			for (int x = 1; x < 16; x++)
			{
				SetChar(x, y, L'.');
			}
			Push_Down_Pice_Of_Figures(y);
			Set_Score();
		}
	}
}

int TestApp::Is_Line_Full(const int& y)
{
	int count_pice_of_figures_in_line = 0;
	for (int x = 1; x < 16; x++)
	{
		if (GetChar(x, y) == pice_of_figure)
		{
			count_pice_of_figures_in_line++;
		}
	}
	return count_pice_of_figures_in_line;
}

void TestApp::Push_Down_Pice_Of_Figures(const int& c_y)
{
	for (int y = c_y - 1; y > 1; y--)
	{
		for (int x = 1; x < 16; x++)
		{
			SetChar(x, y + 1, GetChar(x, y));
		}
	}
}

void TestApp::Set_Score()
{
	score_int += 100;
	std::string score_str = to_string(score_int);
	int i = 9;
	for (auto k : score_str)
	{
		SetChar(i, 22, k);
		i++;
	}
}

template<class fig>
void TestApp::Print_Any_Figure(const int& x, const int& y, const int& number_of_figure, fig figure = pice_of_figure, const int& count_of_shift = 0)
{
	Figure temp_fig{ x, y, number_of_figure };
	for (int j = 0; j < 7; j += 2)
	{
		SetChar(temp_fig.fig[j], temp_fig.fig[j + 1] + count_of_shift, figure); // зарисовка фигуры, когда она опустилась вниз
	}

}
void TestApp::Print_Any_Figure(const int& x, const int& y, const int& number_of_figure, const int& count_of_shift = 0)
{
	Figure temp_fig{ x, y, number_of_figure };
	for (int j = 0; j < 7; j += 2)
	{
		SetChar(temp_fig.fig[j], temp_fig.fig[j + 1] + count_of_shift, pice_of_figure); // зарисовка фигуры, когда она опустилась вниз
	}

}
void TestApp::Clear_Last_Figure(const int& x, const int& y) // удалить старую фигуру после изменения на новую
{
	Figure temp_fig_back{ x, y, number_of_now_figure };
	for (int j = 0; j < 7; j += 2)
	{
		SetChar(temp_fig_back.fig[j], temp_fig_back.fig[j + 1], L'.'); // зарисовка фигуры, когда она опустилась вниз
	}
}
void TestApp::Clear_Any_Figure(const int& x, const int& y, const int& number_of_figure) // удалить указанную фигуру
{
	Figure temp_fig_back{ x, y, number_of_figure };
	for (int j = 0; j < 7; j += 2)
	{
		SetChar(temp_fig_back.fig[j], temp_fig_back.fig[j + 1], L' '); // зарисовка фигуры, когда она опустилась вниз
	}
}
