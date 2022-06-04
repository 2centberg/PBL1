#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include "Invalid_Input.h"
#include "Invalid_Matrix.h"
#include "NonSquare_Matrix.h"
#include "pbl.h"
constexpr double &&lower_bound = -1;
constexpr double &&upper_bound = 1;
int PBL::Input_Selection = 1;
int PBL::Output_Selection = 2;
int PBL::Matrix_Size = 0;
void Intro()
{
	std::fstream INTRO("intro.txt", std::ios::in);
	std::string line;
	while (std::getline(INTRO, line))
	{
		std::cout << line << '\n';
	}
	return;
}

void Input()
{
	std::string selection;
	while (true)
	{
		try
		{
			system("cls");
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
			std::cerr << ex.what() << std::endl;
			system("pause");
			continue;
		}
	}
	PBL::Input_Selection = selection[0] - '0';
	return;
};

void Output()
{
	std::string selection;
	std::cout << std::noshowpos;
	while (true)
	{
		try
		{
			system("CLS");
			std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
			std::cout << "2.Tao ma tran ngau nhien" << std::endl;
			std::cout << "Lua chon : " << PBL::Input_Selection << std::endl;
			if (PBL::Input_Selection == 2)
			{
				std::cout << "Nhap cap cua ma tran : " << PBL::Matrix_Size << std::endl;
			}
			std::cout << "1.Xuat ma tran nghich dao ra file MATRIX.OUT" << std::endl;
			std::cout << "2.Xuat ma tran nghich dao ra man hinh" << std::endl;
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
			std::cerr << ex.what() << std::endl;
			system("pause");
		}
	};
	std::cout << std::endl;
	PBL::Output_Selection = selection[0] - '0';
}

void Rand_Matrix(const int &Size)
{
	//std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	//std::random_device rand_dev;
	//std::mt19937 rand_engine(rand_dev());
	//std::fstream Rand_Stream(PBL::Rand_Path, std::ios::out);
	//Rand_Stream << std::showpos;
	//for (int i{0}; i < Size; i++)
	//{
	//	for (int j{0}; j < Size; j++)
	//	{
	//		Rand_Stream << std::setw(12) << unif(rand_engine) << ' ';
	//	}
	//	Rand_Stream << '\n';
	//}
	//Rand_Stream.close();
}

const int Rand_Int()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::fstream Rand_Stream(PBL::Rand_Path, std::ios::out);
	int t = PBL::Matrix_Size * PBL::Matrix_Size;
	return static_cast<int>(gen() % (t+1)) - t/2;
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
	}
	return ans;
}

void Query()
{
	Input();
	if (PBL::Input_Selection == 2) // Rand_Matrix
	{
		std::string selection;
		while (true)
		{
			system("CLS");
			std::cout << "1.Doc ma tran tu file MATRIX.IN" << std::endl;
			std::cout << "2.Tao ma tran ngau nhien" << std::endl;
			std::cout << "Lua chon : 2" << std::endl;
			std::cout << "Nhap cap cua ma tran : ";
			std::getline(std::cin, selection);
			try
			{
				PBL::Matrix_Size = str_to_int(selection);
				break;
			}
			catch (const Invalid_Input &ex)
			{
				std::cerr << ex.what() << std::endl;
				system("pause");
			}
		};
		Rand_Matrix(PBL::Matrix_Size);
	}
	//Output();
};