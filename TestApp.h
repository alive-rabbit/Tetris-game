// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once
#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int mObj1XOld;
		int mObj1YOld;
		int mObj1X;
		int mObj1Y;

		int mObj2X;
		int mObj2Y;

		bool mDirection;

	public:
		TestApp();
		virtual void KeyPressed(const int& btnCode_1, const int& btnCode_2 = 0) override;
		virtual void UpdateF(const float& deltaTime) override;
		virtual void Clear_Full_Line() override; // логика очистки заполненной строки
		virtual int Is_Line_Full(const int& y); // проверка, является ли данная строка заполненной
		virtual void Push_Down_Pice_Of_Figures(const int& y); // опустить части фигуры после очистки заполненной строки
		virtual void Set_Score() override; // установить +100 очков после очистки строки

		template<class fig>
		void Print_Any_Figure(const int& x, const int& y, const int& number_of_figure, fig figure_texture, const int& count_of_shift);
		virtual void Print_Any_Figure(const int& x, const int& y, const int& number_of_figure, const int& count_of_shift);
		virtual void Clear_Last_Figure(const int& x, const int& y); // удалить старую фигуру после изменения на новую
		virtual void Clear_Any_Figure(const int& x, const int& y, const int& number_of_figure); // удалить указанную фигуру
};

struct Figure
{
	Figure(int x, int y, int type)
	{
		if (type == 1) // квадрат
		{
			fig = { x, y,
				x - 1, y,
				x, y - 1,
				x - 1, y - 1 };
		}
		else if (type == 2) // горизонтальный стик
		{
			fig = { x, y,
				x - 1, y,
				x - 2, y,
				x - 3, y };
		}
		else if (type == 3) // сдвинутый квадрат
		{
			fig = { x, y,
				x, y - 1,
				x - 1, y - 1,
				x - 1, y - 2 };
		}
		else if (type == 4) // T образный
		{
			fig = { x, y,
				x - 1, y,
				x - 1, y - 1,
				x - 2, y };
		}
		else if (type == 5) // L образный
		{
			fig = { x, y,
				x - 1, y,
				x - 2, y,
				x - 2, y - 1 };
		}
		else if (type == 6)// вертикальный стик
		{
			fig = { x, y,
				x, y - 1,
				x, y - 2,
				x, y - 3 };
		}
		else if (type == 7)	// 00
		{					//  00
			fig = { x, y,
				x - 1, y,
				x - 1, y - 1,
				x - 2, y - 1 };
		}
		else if (type == 8)	// 0
		{					// 00
			fig = { x, y,	// 0
				x + 1, y - 1,
				x, y - 1,
				x, y - 2 };
		}
		else if (type == 9) // 000
		{					//  0
			fig = { x, y,
				x + 1, y - 1,
				x, y - 1,
				x - 1, y - 1 };
		}
		else if (type == 10)	//  0
		{						// 00
			fig = { x, y,		//  0
				x, y - 1,
				x, y - 2,
				x - 1, y - 1 };
		}
		else if (type == 11)	// 00
		{						// 0
			fig = { x, y,		// 0
				x + 1, y - 2,
				x, y - 1,
				x, y - 2 };
		}
		else if (type == 12)	//   0
		{						// 000
			fig = { x, y,
				x, y - 1,
				x - 1, y,
				x - 2, y };
		}
		else if (type == 13)	// 0
		{						// 0
			fig = { x, y,		// 00
				x - 1, y,
				x - 1, y - 1,
				x - 1, y - 2 };
		}
	}

	std::vector<int> fig;
};
class Figures
{
public:
	Figures() : figure_number(rand() % 5), our_figure(figures.at(figure_number)){}
	wchar_t Get_Figure_Number()
	{
		return figure_number + 1;
	}
	wchar_t Get_Figure()
	{
		return our_figure;
	}
	template<class fig>
	void Show_Figure(fig figure);

private:
	const std::vector<wchar_t> figures = { '1', '2', '3', '4', '5'};
	int figure_number;
	const wchar_t our_figure;
};


//---------------------------------------------------------------

//	1:
//00
//00
//
//	2:
//0000
//
//	3: 
//0
//00
// 0
//
//	4:
// 0
//000
//
//	5:
//0
//000
//	6:
//0
//0
//0
//0
//
//	7:
//00
// 00
//
//	8:
//0
//00
//0
//
//	9:
//000
// 0
//
//	10:
//
// 0
//00
// 0
//
//	11:
//00
//0
//0
//
//	12:
//  0
//000
//
//	13:
//0
//0
//00