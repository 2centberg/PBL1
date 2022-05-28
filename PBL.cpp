#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
#include <conio.h>
#include "Invalid_Input.h"
#include "Invalid_Matrix.h"
#include "pbl.h"
constexpr double &&lower_bound = -1;
constexpr double &&upper_bound = 1;
void Title()
{
	std::cout << "\n\t\t**************************************************";
	std::cout << "\n\t\t*                                                *";
	std::cout << "\n\t\t*            Do an lap trinh tinh toan           *";
	std::cout << "\n\t\t*      Ten de tai : Tinh ma tran nghich dao      *";
	std::cout << "\n\t\t*                                                *";
	std::cout << "\n\t\t**************************************************";
	return;
}

int Input()
{
	std::string selection;
	while (true)
	{
		//std::cin.ignore();
		try
		{
			system("CLS");
			Title();
			std::cout << "\n\n\t\t1.Doc ma tran tu file MATRIX.IN";
			std::cout << "\n\t\t2.Tao ma tran ngau nhien";
			std::cout << "\n\t\tLua chon : ";
			getline(std::cin, selection);
			if (selection != "1" && selection != "2")
			{
				throw Invalid_Input();
			}
			break;
		}
		catch (const Invalid_Input &ex)
		{
			std::cerr << "\n\t\t" << ex.what() << std::endl << "\t\t";
			system("pause");
		}
	} 
	return Input_Selection = selection[0] - '0';
}

int Output()
{
	std::string selection;
	while (true)
	{
		//fflush(stdin);
		try
		{
			system("CLS");
			Title();
			std::cout << "\n\n\t\t" << "1.Doc ma tran tu file MATRIX.IN";
			std::cout << "\n\t\t" << "2.Tao ma tran ngau nhien";
			std::cout << "\n\t\t" << "Lua chon : " << Input_Selection;
			if (Input_Selection == 2)
			{
				std::cout << "\n\n\t\t" << "Nhap cap cua ma tran : " << Matrix_Size;
			}
			std::cout << "\n\n\t\t" << "1.Xuat ma tran nghich dao ra file MATRIX.OUT";
			std::cout << "\n\t\t" << "2.Xuat ma tran nghich dao ra man hinh";
			std::cout << "\n\t\tLua chon : ";
			getline(std::cin, selection);
			if (selection != "1" && selection != "2")
			{
				throw Invalid_Input();
			}
			break;
		}
		catch (const Invalid_Input &ex)
		{
			std::cerr << "\n\t\t" << ex.what() << std::endl << "\t\t";
			system("pause");
		}
	};
	std::cout << std::endl;
	return Output_Selection = selection[0] - '0';
}

inline int str_to_int(std::string selection)
{
	int ans{0};
	for (const char &c : selection)
	{
		if (c >= '0' && c <= '9')
		{
			ans = ans * 10 + c - '0';
		}
		else
		{
			throw Invalid_Matrix();
		}
	}
	return ans;
}

void rand_matrix(const int &Size)
{
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	std::fstream Rand_Stream(Rand_Path, std::ios::out);
	for (int i{0}; i < Size; i++)
	{
		for (int j{0}; j < Size; j++)
		{
			Rand_Stream << unif(rand_engine) << ' ';
		}
		Rand_Stream << '\n';
	}
	Rand_Stream.close();
	return;
}

void Query()
{
	Input();
	if (Input_Selection == 2)
	{
		std::string selection;
		while(true)
		{
			system("CLS");
			Title();
			std::cout << "\n\n\t\t";
			std::cout << "1.Doc ma tran tu file MATRIX.IN" << "\n\t\t";
			std::cout << "2.Tao ma tran ngau nhien" << "\n\t\t";
			std::cout << "Lua chon : 2" << "\n\n\t\t";
			std::cout << "Nhap cap cua ma tran : ";
			getline(std::cin, selection);
			try
			{
				Matrix_Size = str_to_int(selection);
				break;
			}
			catch (const Invalid_Matrix &ex)
			{
				std::cerr << "\t\t" << ex.what() << std::endl << "\t\t";
				system("pause");
			}
		}
	}
	Output();
}

bool is_double(std::string element)
{
	int count_dot{0};
	for (int i = 0; i < element.size(); i++)
	{
		if (element[i] == '-' || element[i] == '+')
		{
			if (i != 0)
			{
				return 0;
			}
		}
		if (element[i] == '.')
		{
			count_dot ++;
			if (count_dot > 1)
			{
				return 0;
			}
			continue;
		}
		if (element[i] > '9' || element[i] < '0')
		{
			return 0;
		}
	}
	return 1;
}

int valid_matrix()
{
	std::fstream input_file(Input_Path, std::ios::in);
	std::string element;
	int count{0};
	while (input_file >> element)
	{
		count++;
		if (!is_double(element))
			return 0;
	}
	int Size{(int)sqrt(count)};
	if (Size * Size == count) //kiem tra so phan tu co phai la so chinh phuong khong
	{
		return Size;
	}
	return 0;
}

void Find_Matrix_Size()
{
	if (Input_Selection == 1)
	{
		Matrix_Size = valid_matrix();
	}
	else
	{
		rand_matrix(Matrix_Size);
	}
}

const int &Get_Input_Selection()
{
	return Input_Selection;
}

const int &Get_Output_Selection()
{
	return Output_Selection;
}

const int &Get_Matrix_size()
{
	return Matrix_Size;
}

const char *Get_Input_Path()
{
	return Input_Path;
}
const char *Get_Output_Path()
{
	return Output_Path;
}
const char *Get_Rand_Path()
{
	return Rand_Path;
}