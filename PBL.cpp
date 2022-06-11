#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <cwchar>
#include "Matrix.hpp"
constexpr double &&lower_bound = -1;
constexpr double &&upper_bound = 1;
int PBL::Input_Selection = 1;
int PBL::Output_Selection = 2;
int PBL::Row_Size = 0;
int PBL::Col_Size = 0;
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
int &&colour = 1;
void ShowConsoleCursor(bool showFlag)
{
	//HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void Intro()
{
	std::fstream INTRO("intro.txt", std::ios::in);
	std::string line;
	while (std::getline(INTRO, line))
	{
		SetConsoleTextAttribute(hConsole, colour++);
		std::cout << line << '\n';
		if (colour == 16)
		{
			colour = 1;
		}
	}
}
void Outro()
{
	colour = 6;
	std::fstream INTRO("outro.txt", std::ios::in);
	std::string line;
	while (std::getline(INTRO, line))
	{
		SetConsoleTextAttribute(hConsole, colour++);
		std::cout << line << '\n';
		if (colour == 16)
		{
			colour = 1;
		}
	}
	char ch = _getch();
	system("pause");
}
int str_to_int(const std::string &str)
{
	if (str.length() == 0 || str == "0")
	{
		throw Invalid_Input();
	}
	int ans{0};
	for (const char &ch : str)
	{
		if (ch < '0' || ch > '9')
		{
			throw Invalid_Input();
		}
		ans = ans * 10 + ch - '0';
		if (ans > 10000)
		{
			throw Too_Large_Matrix();
		}
	}
	return ans;
}
void Input()
{
	std::string selection;
	
	while (true)
	{
		try
		{
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << "============================================\n";
			SetConsoleTextAttribute(hConsole, 6);
			std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
			std::cout << "2.Tao ma tran ngau nhien" << std::endl;
			std::cout << "Lua chon : ";
			getline(std::cin, selection);
			if (selection != "1" && selection != "2")
			{
				throw Invalid_Input();
			}
			break;
		}
		catch (const Invalid_Input &ex)
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cerr << ex.what() << std::endl;
		}
	}
	PBL::Input_Selection = selection[0] - '0';
	if (PBL::Input_Selection == 2)
	{
		while (true)
		{
			while (true)
			{
				SetConsoleTextAttribute(hConsole, 6);
				std::cout << "Nhap so hang cua ma tran : ";
				std::getline(std::cin, selection);
				try
				{
					PBL::Row_Size = str_to_int(selection);
					break;
				}
				catch (const Invalid_Input &ex)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cerr << ex.what() << std::endl;
					SetConsoleTextAttribute(hConsole, 11);
					std::cout << "============================================\n";
					SetConsoleTextAttribute(hConsole, 6);
					std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
					std::cout << "2.Tao ma tran ngau nhien" << std::endl;
					std::cout << "Lua chon : 2" << std::endl;
				}
				catch (const Too_Large_Matrix &ex)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cerr << ex.what() << std::endl;
					SetConsoleTextAttribute(hConsole, 11);
					std::cout << "============================================\n";
					SetConsoleTextAttribute(hConsole, 6);
					std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
					std::cout << "2.Tao ma tran ngau nhien" << std::endl;
					std::cout << "Lua chon : 2" << std::endl;
				}
			};
			while (true)
			{
				SetConsoleTextAttribute(hConsole, 6);
				std::cout << "Nhap so cot cua ma tran : ";
				std::getline(std::cin, selection);
				try
				{
					PBL::Col_Size = str_to_int(selection);
					break;
				}
				catch (const Invalid_Input &ex)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cerr << ex.what() << std::endl;
					SetConsoleTextAttribute(hConsole, 11);
					std::cout << "============================================\n";
					SetConsoleTextAttribute(hConsole, 6);
					std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
					std::cout << "2.Tao ma tran ngau nhien" << std::endl;
					std::cout << "Lua chon : 2" << std::endl;
					std::cout << "Nhap so cot cua ma tran : " << PBL::Row_Size << std::endl;
				}
				catch (const Too_Large_Matrix &ex)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cerr << ex.what() << std::endl;
					SetConsoleTextAttribute(hConsole, 11);
					std::cout << "============================================\n";
					SetConsoleTextAttribute(hConsole, 6);
					std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
					std::cout << "2.Tao ma tran ngau nhien" << std::endl;
					std::cout << "Lua chon : 2" << std::endl;
					std::cout << "Nhap so cot cua ma tran : " << PBL::Row_Size << std::endl;
				}
			}
			if (PBL::Row_Size + PBL::Row_Size > 10000 || PBL::Row_Size * PBL::Row_Size > 10000)
			{
				SetConsoleTextAttribute(hConsole, 12);
				std::cerr << Too_Large_Matrix().what() << std::endl;
				SetConsoleTextAttribute(hConsole, 11);
				std::cout << "============================================\n";
				SetConsoleTextAttribute(hConsole, 6);
				std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
				std::cout << "2.Tao ma tran ngau nhien" << std::endl;
				std::cout << "Lua chon : 2" << std::endl;
				continue;
			}
			else
			{
				break;
			}
		}
	}
};
void Output()
{
	std::string selection;
	std::cout << std::noshowpos;

	while (true)
	{
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "============================================\n";
		SetConsoleTextAttribute(hConsole, 6);
		std::cout << "1.Xuat ma tran nghich dao ra file MATRIX.OUT" << std::endl;
		std::cout << "2.Xuat ma tran nghich dao ra man hinh" << std::endl;
		std::cout << "Lua chon : ";
		try
		{
			getline(std::cin, selection);
			if (selection != "1" && selection != "2")
			{
				throw Invalid_Input();
			}
			break;
		}
		catch (const Invalid_Input &ex)
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cerr << ex.what() << std::endl;
		}
	};
	
	PBL::Output_Selection = selection[0] - '0';
}
int Menu()
{
	Queue<std::string> Q;
	std::fstream Menu_Stream;
	Menu_Stream.open(PBL::Menu_Path, std::ios::in);
	std::string line;
	while (std::getline(Menu_Stream, line))
	{
		Q.Push(line);
	}
	Menu_Stream.close();
	while (true)
	{
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "============================================\n";
		SetConsoleTextAttribute(hConsole, 6);
		Q.Display();
		std::cout << "Lua chon : ";
		std::getline(std::cin, line);
		try
		{
			int ans = str_to_int(line);
			if (1 <= ans && ans <= 8)
			{
				return ans;
			}
			else
			{
				throw Invalid_Input();
			}
		}
		catch (const Invalid_Input &ex)
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cerr << ex.what() << std::endl;
		}
	}
}
void Reverse()
{
	Input();
	Matrix MT;
	try
	{
		MT.Init();
		MT.Reverse();
	}
	catch (const Invalid_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Out_Of_Memory &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const NonSquare_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Irreversible &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Too_Large_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	Output();
	MT.Display();
}
void Determinant()
{
	Input();
	Matrix MT;
	try
	{
		MT.Init();
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Dinh thuc cua ma tran : " << MT.Determinant() << std::endl;
	}
	catch (const Invalid_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Out_Of_Memory &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const NonSquare_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
}
void Transpose()
{
	Input();
	Matrix MT;
	try
	{
		MT.Init();
	}
	catch (const Invalid_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Out_Of_Memory &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}

	MT.Transpose();
	Output();
	MT.Display();
}
void Rank()
{
	Input();
	Matrix MT;
	try
	{
		MT.Init();
	}
	catch (const Invalid_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Out_Of_Memory &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "Hang cua ma tran : " << MT.Rank() << std::endl;
}
void Triangular()
{
	Input();
	Matrix MT;
	try
	{
		MT.Init();
	}
	catch (const Invalid_Matrix &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	catch (const Out_Of_Memory &ex)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << ex.what() << std::endl;
		return;
	}
	MT.Triangular();
	Output();
	MT.Display();
}
void Matrix_Query()
{
	Intro();
	char ch = _getch();
	system("cls");
	while (true)
	{
		int selection = Menu();
		switch (selection)
		{
			case 1:
				Reverse();
				break;
			case 2:
				Determinant();
				break;
			case 3:
				Transpose();
				break;
			case 4:
				Rank();
				break;
			case 5:
				Triangular();
				break;
			case 6:
				system("cls");
				Outro();
				return;
		}
	}
};