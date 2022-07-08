#include "Matrix.hpp"
#include <random>
Matrix::Matrix() : Number_Of_Col{0}, Number_Of_Row{0}, Container{0} {}
Matrix::Matrix(const int &Number_Of_Row, const int &Number_Of_Col) 
	: Number_Of_Col{Number_Of_Col}, Number_Of_Row{Number_Of_Row}
{
	if (Number_Of_Col * Number_Of_Row > 10000)
	{
		throw Too_Large_Matrix();
	}
	try
	{
		Container = new double * [Number_Of_Row];
		for (int &&i{0}; i < Number_Of_Row; ++i)
		{
			Container[i] = new double[Number_Of_Col];
		}
	}
	catch (...)
	{
		throw Out_Of_Memory();
	}
}
Matrix::Matrix(const int &Number_Of_Row, const int &Number_Of_Col, const bool &&Is_Identity_Matrix) 
	: Number_Of_Col{Number_Of_Col}, Number_Of_Row{Number_Of_Row}
{
	if (Number_Of_Row * Number_Of_Col > 10000)
	{
		throw Too_Large_Matrix();
	}
	try
	{
		Container = new double * [Number_Of_Row];
		if (Is_Identity_Matrix)
		{
			for (int &&i{0}; i < Number_Of_Row; ++i)
			{
				Container[i] = new double[Number_Of_Col];
				for (int &&j{0}; j < Number_Of_Col; ++j)
				{
					Container[i][j] = 0;
				}
				Container[i][i] = 1;
			}
		}
		else
		{
			for (int &&i{0}; i < Number_Of_Row; ++i)
			{
				Container[i] = new double[Number_Of_Col];
			}
		}
	}
	catch (...)
	{
		throw Out_Of_Memory();
	}
}
Matrix::~Matrix() noexcept
{
	if (Container)
	{
		for (int &&i{0}; i < Number_Of_Row; ++i)
		{
			delete[] Container[i];
		}
		delete[] Container;
		Container = 0;
	}
	Number_Of_Col = 0;
	Number_Of_Row = 0;
}
bool isEmty(std::string str)
{
	for (int &&i{0}; i < str.length(); ++i)
	{
		if (isdigit(str[i]))
		{
			return 0;
		}
	}
	return 1;
}
void Matrix::Init()
{
	this->~Matrix();
	if (PBL::Input_Selection == 1)
	{
		std::fstream INPUT_STREAM;
		INPUT_STREAM.open(PBL::Input_Path, std::ios::in);
		std::string element;
		Queue<std::string> Q;
		while (std::getline(INPUT_STREAM, element))
		{
			if (isEmty(element))
			{
				continue;
			}
			Q.Push(element);
		}
		INPUT_STREAM.close();
		if (Q.Size() == 0)
		{
			throw Invalid_Matrix();
		}
		std::stringstream sstream;
		sstream.str(Q.Top());
		int &&i{0}, &&j{0};
		while (sstream >> element)
		{
			++j;
		}

		this->operator=(Matrix(Q.Size(), j));
		while (Q.Size())
		{
			j = 0;
			sstream.clear();
			sstream.str(Q.Top());
			Q.Pop();
			while (sstream >> element)
			{
				if (j == Number_Of_Col)
				{
					throw Invalid_Matrix();
				}
				try
				{
					Container[i][j] = stod(element);
					++j;
				}
				catch (...)
				{
					throw Invalid_Matrix();
				}
			}
			if (j != Number_Of_Col)
			{
				throw Invalid_Matrix();
			}
			++i;
		}
		INPUT_STREAM.close();
	}
	else
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::fstream Rand_Stream(PBL::Rand_Path, std::ios::out);
		int seed = PBL::Row_Size * PBL::Col_Size;
		this->operator=(Matrix(PBL::Row_Size, PBL::Col_Size));
		std::fstream RAND_STREAM;
		RAND_STREAM.open(PBL::Rand_Path, std::ios::out);
		RAND_STREAM.clear();
		for (int &&i{0}; i < Number_Of_Row; ++i)
		{
			for (int &&j{0}; j < Number_Of_Col; ++j)
			{
				Container[i][j] = static_cast<int>(gen() % (2 * seed + 1)) - seed;
				RAND_STREAM << std::setw(5) << Container[i][j] << ' ';
			}
			RAND_STREAM << '\n';
		}
		RAND_STREAM.close();
	}
}
void Matrix::Display() noexcept
{
	if (PBL::Output_Selection == 1)
	{
		std::fstream OUTPUT_STREAM;
		OUTPUT_STREAM.open(PBL::Output_Path, std::ios::out);
		for (int &&i{0}; i < Number_Of_Row; ++i)
		{
			for (int &&j{0}; j < Number_Of_Col; ++j)
			{
				OUTPUT_STREAM << std::setprecision(3) << std::fixed << std::setw(12) << Container[i][j] << ' ';
			}
			OUTPUT_STREAM << std::endl;
		}
		OUTPUT_STREAM.close();
	}
	else
	{
		for (int &&i{0}; i < Number_Of_Row; ++i)
		{

			for (int &&j{0}; j < Number_Of_Col; ++j)
			{
				std::cout << std::setw(12) << Container[i][j];
			}
			std::cout << std::endl;
		}
	}
}
void Matrix::Swap_Row(const int &Row_Index)
{
	for (int i{Row_Index + 1}; i < Number_Of_Row; ++i)
	{
		if (Container[i][Row_Index] != 0)
		{
			std::swap(Container[i], Container[Row_Index]);
			return;
		}
	}
	throw 0;
}
void Matrix::Reverse()
{
	if (Number_Of_Col != Number_Of_Row)
	{
		throw NonSquare_Matrix();
	}
	double Anchor_Point{0};
	Matrix Unit_Matrix(Number_Of_Row, Number_Of_Col, 1);
	for (int &&Row_Index{0}; Row_Index < Number_Of_Row; ++Row_Index)
	{
		if (Container[Row_Index][Row_Index] == 0)
		{
			try
			{
				this->Swap_Row(Row_Index);
			}
			catch (...)
			{
				throw Irreversible();
			}
		}
		Anchor_Point = Container[Row_Index][Row_Index];
		for (int &&Col_Index{0}; Col_Index < Number_Of_Col; ++Col_Index)
		{
			if (Col_Index <= Row_Index)
			{
				Unit_Matrix.Container[Row_Index][Col_Index] /= Anchor_Point;
			}
			else
			{
				Container[Row_Index][Col_Index] /= Anchor_Point;
			}
		}
		Container[Row_Index][Row_Index] = 1;

		for (int &&Another_Row{0}; Another_Row < Number_Of_Row; ++Another_Row)
		{
			if (Another_Row != Row_Index)
			{
				Anchor_Point = -Container[Another_Row][Row_Index];
				for (int &&Col_Index{0}; Col_Index < Number_Of_Col; ++Col_Index)
				{
					if (Col_Index <= Row_Index)
					{
						Unit_Matrix.Container[Another_Row][Col_Index] 
							+= Anchor_Point * Unit_Matrix.Container[Row_Index][Col_Index];
					}
					else
					{
						Container[Another_Row][Col_Index] 
							+= Anchor_Point * Container[Row_Index][Col_Index];
					}
				}
				Container[Another_Row][Row_Index] = 0;
			}

		}
	}
	this->~Matrix();
	this->Container = Unit_Matrix.Container;
	this->Number_Of_Row = this->Number_Of_Col = Unit_Matrix.Number_Of_Row;
	Unit_Matrix.Container = 0;
}
double Matrix::Determinant()
{
	if (Number_Of_Col != Number_Of_Row)
	{
		throw NonSquare_Matrix();
	}
	double ans{1};
	this->Triangular();
	for (int &&i{0}; i < Number_Of_Row; ++i)
	{
		ans = ans * Container[i][i];
		if (ans == 0)
		{
			return ans;
		}
	}
	return ans;
}
void Matrix::Transpose()
{
	Matrix Temp;
	Temp.Number_Of_Col = Number_Of_Row;
	Temp.Number_Of_Row = Number_Of_Col;
	Temp.Container = new double *[Temp.Number_Of_Row];
	for (int &&i{0}; i < Temp.Number_Of_Row; ++i)
	{
		Temp.Container[i] = new double[Temp.Number_Of_Col];
		for (int &&j{0}; j < Temp.Number_Of_Col; ++j)
		{
			Temp.Container[i][j] = Container[j][i];
		}
	}
	this->~Matrix();
	Container = Temp.Container;
	Number_Of_Row = Temp.Number_Of_Row;
	Number_Of_Col = Temp.Number_Of_Col;
	Temp.Container = 0;
}
int Matrix::Rank()
{
	int &&ans{0};
	this->Triangular();
	for (int &&i{0}; i < min(Number_Of_Col, Number_Of_Row); ++i)
	{
		if (Container[i][i] != 0)
		{
			++ans;
			continue;
		}
		int j{i + 1};
		for (; j < Number_Of_Col; ++j)
		{
			if (Container[i][j] != 0)
			{
				++ans;
				break;
			}
		}
		if (j == Number_Of_Col)
		{
			break;
		}
	}
	return ans;
}
void Matrix::Triangular()
{
	double Anchor_Point{0};
	for (int &&Row_Index{0}; Row_Index < min(Number_Of_Row, Number_Of_Col); ++Row_Index)
	{
		int j{Row_Index};
		while (j < Number_Of_Col && Container[Row_Index][j] == 0)
		{
			bool &&flag{0};
			for (int i{Row_Index + 1}; i < Number_Of_Row; ++i)
			{
				if (Container[i][j] != 0)
				{
					std::swap(Container[i], Container[Row_Index]);
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				break;
			}
			++j;
			if (j == Number_Of_Col)
			{
				return;
			}
		}
		for (int j{Row_Index + 1}; j < Number_Of_Row; ++j)
		{
			if (Container[j][Row_Index] == 0)
			{
				continue;
			}
			Anchor_Point = -Container[j][Row_Index] / Container[Row_Index][Row_Index];
			for (int k{Row_Index + 1}; k < Number_Of_Col; ++k)
			{
				Container[j][k] += Container[Row_Index][k] * Anchor_Point;
			}
			Container[j][Row_Index] = 0;
		}
	}
}
Matrix &Matrix::operator=(Matrix &&rhs) noexcept
{
	this->Container = rhs.Container;
	this->Number_Of_Row = rhs.Number_Of_Row;
	this->Number_Of_Col = rhs.Number_Of_Col;
	rhs.Container = 0;
	return *this;
}