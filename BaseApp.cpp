// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>

#define MY_PERFORMENCE_COUNTER

#include "PerformanceCounter.h"

BaseApp::BaseApp(const int& xSize, const int& ySize) : X_SIZE(xSize), Y_SIZE(ySize)
{
	SMALL_RECT windowSize = { 0, 0, X_SIZE, Y_SIZE };
	COORD windowBufSize = { X_SIZE + 1, Y_SIZE + 1 };

	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	if (!SetConsoleScreenBufferSize(mConsole, windowBufSize))
	{
		std::cerr << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}
	if (!SetConsoleWindowInfo(mConsole, TRUE, &windowSize))
	{
		std::cerr << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);


	mChiBuffer = (CHAR_INFO*)malloc((X_SIZE + 1) * (Y_SIZE + 1) * sizeof(CHAR_INFO));

	mDwBufferSize.X = X_SIZE + 1;
	mDwBufferSize.Y = Y_SIZE + 1;		// размер буфера данных

	mDwBufferCoord.X = 0;
	mDwBufferCoord.Y = 0;				// координаты ячейки

	mLpWriteRegion.Left = 0;
	mLpWriteRegion.Top = 0;
	mLpWriteRegion.Right = X_SIZE + 1;
	mLpWriteRegion.Bottom = Y_SIZE + 1;	// прямоугольник для чтения


	for (int x = 0; x < X_SIZE + 1; x++) // рисуем область (левел)
	{
		for (int y = 0; y < Y_SIZE + 1; y++)
		{
			wchar_t symbol_for_map = L'▓';
			SetChar(x, y, L'.');
			if ((x > 15 && x < X_SIZE) || (y > 20 && y < Y_SIZE))
			{
				SetChar(x, y, L' ');
			}
			SetChar(x, 0, symbol_for_map);
			SetChar(x, Y_SIZE, symbol_for_map);
			SetChar(x, Y_SIZE - 4, symbol_for_map);
			if (x < X_SIZE - 8) { SetChar(x, Y_SIZE - 4, L'#'); }
			SetChar(0, y, symbol_for_map);
			SetChar(X_SIZE, y, symbol_for_map);
			if (y < Y_SIZE - 4)
			{
				SetChar(X_SIZE - 8, y, symbol_for_map);
			}
		}
	}
	SetChar(21, 3, L'0'); // зарисовка фигуры, когда она опустилась вниз
	SetChar(20, 3, L'0');
	SetChar(21, 2, L'0');
	SetChar(20, 2, L'0');
	int i = 2;
	for (auto k : "Score: 0")
	{
		SetChar(i, 22, k);
		i++;
	}

}

BaseApp::~BaseApp()
{
	free(mChiBuffer);
}

void BaseApp::SetChar(const int& x, const int& y, const wchar_t& c)
{
	mChiBuffer[x + (X_SIZE+1)*y].Char.UnicodeChar = c;
	mChiBuffer[x + (X_SIZE+1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
}

wchar_t BaseApp::GetChar(const int& x, const int& y)
{
	return mChiBuffer[x + (X_SIZE+1)*y].Char.AsciiChar;
}

void BaseApp::Render()
{
	if (!WriteConsoleOutput(mConsole, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion)) 
	{
		std::cerr << "WriteConsoleOutput failed - " << '\n' << GetLastError();
	}
}

void BaseApp::Run()
{
	CStopwatch timer;
	int sum = 0;
	int counter = 0;

	int deltaTime = 0;
	while (1)
	{
		timer.Start();
		if (kbhit())
		{
			int first_symbol = getch(), second_symbol = 0;
			if (first_symbol == 224)
			{
				KeyPressed(first_symbol, getch());
			}
			else
			{
				KeyPressed(first_symbol);
			}
			if (!FlushConsoleInputBuffer(mConsoleIn))
				std::cerr << "FlushConsoleInputBuffer failed with error " << GetLastError();
		}
		KeyPressed(0);
		UpdateF((float)deltaTime / 1000.0f); // отвечает за прорисовку движения частиц
		Render(); // отрисовка
		Clear_Full_Line();
		float t = 1 + score_int / 1000.;
		Sleep(300/t); // FPS

		while (1)
		{
			deltaTime = timer.Now();
			if (deltaTime > 20)
				break;
		}

		sum += deltaTime;
		counter++;
		if (sum >= 1000)
		{
			TCHAR  szbuff[255];
			StringCchPrintf(szbuff, 255, TEXT("FPS: %d"), counter);
			SetConsoleTitle(szbuff);

			counter = 0;
			sum = 0;
		}
	}
}