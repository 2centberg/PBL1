#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
constexpr char In_File[10] = "MATRIX.IN";
constexpr char Out_File[11] = "MATRIX.OUT";
constexpr char Rand_File[12] = "MATRIX.RAND";
void Create_Matrix(double **Matrix,
				   const size_t &Size);
void Print_Matrix(double **Matrix,
				  const size_t &Size);
double **Reverse(double **Matrix,
				 const size_t &Size);
size_t Find(double **Matrix,
			const size_t &Size,
			const size_t &Row);
void Swap_Row(double **Matrix,
			  const size_t &Size,
			  const size_t &Row_1,
			  const size_t &Row_2);
double Rand_Range(const double &Lower_Bound,
				  const double &Upper_Bound);
size_t Input();
size_t Output();
double Det(double **Matrix,
		   const size_t &Size);
size_t Sub_Matrix(double **Matrix,
				  const size_t &Size,
				  const size_t &Row,
				  const size_t &Col);
double Det_Of_Sub_Matrix(double **Matrix,
						 const size_t &Size,
						 const size_t &Row,
						 const size_t &Col);
//driver code
int main()
{
	size_t Inp = Input();
	size_t Size;
	double **Matrix{0};
	double **Reverse_Matrix{0};
	if (Inp == 1) // Doc ma tran tu file MATRIX.IN
	{
		fstream Fptr(In_File, ios::in);
		Fptr >> Size; // lay kich thuong ma tran
		Matrix = new double *[Size];

		for (size_t Row = 0; Row < Size; Row++)
		{
			Matrix[Row] = new double[Size];
			for (size_t Col = 0; Col < Size; Col++)
			{
				Fptr >> Matrix[Row][Col];
			}
		}

		Reverse_Matrix = Reverse(Matrix, Size);
		Fptr.close();
	}
	else
	{
		printf("\nNhap cap cua ma tran : ");
		cin >> Size;
		Matrix = new double *[Size];
		for (size_t Row = 0; Row < Size; Row++)
		{
			Matrix[Row] = new double[Size];
		}
		Create_Matrix(Matrix, Size);
		Print_Matrix(Matrix, Size);
		Reverse_Matrix = Reverse(Matrix, Size);
	}
	size_t Out = Output();
	if (Out == 1) // Ghi ma tran nghich dao ra file MATRIX.OUT
	{
		FILE *Fptr = fopen("MATRIX.OUT", "w");
		if (Reverse_Matrix == 0)
		{
			fprintf(Fptr, "\n\tMa tran khong kha nghich");
		}

		else
		{
			for (size_t Row = 0; Row < Size; Row++)
			{
				for (size_t Col = 0; Col < Size; Col++)
				{
					fprintf(Fptr, "%+-1.3lf\t", Reverse_Matrix[Row][Col]);
				}
				fputc('\n', Fptr);
			}
		}
		fclose(Fptr);
	}
	else
	{
		if (Reverse_Matrix == 0)
		{
			perror("Ma tran khong kha nghich");
		}
		else
		{
			Print_Matrix(Reverse_Matrix, Size);
		}
	}
	for (size_t Row = 0; Row < Size; Row++)
	{
		delete[] Matrix[Row];
	}
	delete Matrix;
	Matrix = 0;
	if (Reverse_Matrix)
	{
		for (size_t Row = 0; Row < Size; Row++)
		{
			delete[] Reverse_Matrix[Row];
		}
		delete Reverse_Matrix;
		Reverse_Matrix = 0;
	}
	return 0;
}
void Print_Matrix(double **Matrix,
				  const size_t &Size)
{
	for (size_t Row = 0; Row < Size; Row++)
	{
		printf("");
		for (size_t Col = 0; Col < Size; Col++)
		{
			printf("%+-1.3lf  ", Matrix[Row][Col]);
		}
		printf("\n");
	}
	return;
}
void Create_Matrix(double **Matrix,
				   const size_t &Size)
{
	srand(time(NULL));
	// ghi ma tran tao ngau nhien vao file MATRIX.RAND
	FILE *_fptr = fopen("MATRIX.RAND", "w");
	fprintf(_fptr, "%d\n", Size);
	for (size_t Row = 0; Row < Size; Row++)
	{
		for (size_t Col = 0; Col < Size; Col++)
		{
			// Matrix[Row][Col] = Rand_Range(-Rand_Range(-rand()%10, rand()%10), 
			// 								Rand_Range(-rand()%10, rand()%10));
			Matrix[Row][Col] = Rand_Range(-1, 1);
			fprintf(_fptr, "%+-+1.6lf ", Matrix[Row][Col]);
		}
		fputc('\n', _fptr);
	}
	fclose(_fptr);
	return;
}
double Det(double **Matrix,
		   const size_t &Size)
{
	double **_temp_matrix = new double *[Size];
	for (size_t i = 0; i < Size; i++)
	{
		_temp_matrix[i] = new double[Size];
	}
	for (size_t i = 0; i < Size; i++)
	{
		for (size_t j = 0; j < Size; j++)
		{
			_temp_matrix[i][j] = Matrix[i][j];
		}
	}
	double _anchor_point;
	for (size_t Row = 0; Row < Size - 1; Row++)
	{
		if (_temp_matrix[Row][Row] == 0)
		{
			if (Find(_temp_matrix, Size, Row) == 0)
				return 0;
		}
		for (size_t _next_rows = Row + 1; _next_rows < Size; _next_rows++)
		{
			_anchor_point = _temp_matrix[_next_rows][Row];
			for (size_t Col = Row + 1; Col < Size; Col++)
			{
				_temp_matrix[_next_rows][Col] += _temp_matrix[Row][Col] * -_anchor_point / _temp_matrix[Row][Row];
			}
			_temp_matrix[_next_rows][Row] = 0;
		}
	}
	double Ans = 1.0;
	for (size_t i = 0; i < Size; i++)
	{
		Ans = Ans * _temp_matrix[i][i];
	}

	for (size_t i = 0; i < Size; i++)
	{
		delete _temp_matrix[i];
	}
	delete _temp_matrix;
	return Ans;
}
size_t Sub_Matrix(double **Matrix,
				  const size_t &Size,
				  const size_t &Row,
				  const size_t &Col)
{
	size_t Count = 0;
	double Temp;
	if (Row != Size - 1)
	{
		for (size_t j = 0; j < Size; j++)
		{
			Temp = Matrix[Row][j];
			Matrix[Row][j] = Matrix[Size - 1][j];
			Matrix[Size - 1][j] = Temp;
		}
		if (Row != Size - 2)
		{
			Count++;
		}
	}
	if (Col != Size - 1)
	{
		for (size_t i = 0; i < Size; i++)
		{
			Temp = Matrix[i][Col];
			Matrix[i][Col] = Matrix[i][Size - 1];
			Matrix[i][Size - 1] = Temp;
		}
		if (Col != Size - 2)
		{
			Count++;
		}
	}
	return Count;
}
double Det_Of_Sub_Matrix(double **Matrix,
						 const size_t &Size,
						 const size_t &Row,
						 const size_t &Col)
{

	size_t Count = Sub_Matrix(Matrix, Size, Row, Col);
	double Ans = Det(Matrix, Size - 1);
	Sub_Matrix(Matrix, Size, Row, Col);
	return (Count == 1) ? -Ans : Ans;
}
double **Reverse(double **Matrix,
				 const size_t &Size)
{
	double DET = Det(Matrix, Size);
	if (DET == 0)
	{
		return 0;
	}
	if (Size == 1)
	{
		double **Reverse_Matrix = new double *;
		Reverse_Matrix[0] = new double;
		Reverse_Matrix[0][0] = 1 / DET;
		return Reverse_Matrix;
	}
	double **Reverse_Matrix{new double *[Size]};
	for (size_t i = 0; i < Size; i++)
	{
		Reverse_Matrix[i] = new double[Size];
	}
	for (size_t i = 0; i < Size; i++)
	{
		for (size_t j = 0; j < Size; j++)
		{
			Reverse_Matrix[i][j] = Det_Of_Sub_Matrix(Matrix, Size, j, i) / DET;
			if ((i + j) & 1)
			{
				Reverse_Matrix[i][j] *= -1;
			}
		}
	}
	return Reverse_Matrix;
}
size_t Find(double **Matrix,
			const size_t &Size,
			const size_t &Row)
{
	for (size_t Next_Row = Row + 1; Next_Row < Size; Next_Row++)
	{
		if (Matrix[Next_Row][Row] != 0)
		{
			Swap_Row(Matrix, Size, Row, Next_Row);
			return 1;
		}
	}
	return 0;
}
void Swap_Row(double **Matrix,
			  const size_t &Size,
			  const size_t &Row_1,
			  const size_t &Row_2)
{
	double Temp;
	for (size_t Col = 0; Col < Size; Col++)
	{
		Temp = Matrix[Row_1][Col];
		Matrix[Row_1][Col] = Matrix[Row_2][Col];
		Matrix[Row_2][Col] = Temp;
	}
	return;
}
double Rand_Range(const double &Lower_Bound,
				  const double &Upper_Bound)
{
	return Lower_Bound + (Upper_Bound - Lower_Bound) * ((double)rand()) / 0x7fff;
}
size_t Input()
{
	size_t Selection;
	printf("1.Doc ma tran tu file MATRIX.IN");
	printf("\n2.Tao ma tran ngau nhien");
	printf("\nLua chon : ");
	cin >> Selection;
	return Selection;
}
size_t Output()
{
	size_t Selection;
	printf("\n1.Xuat ma tran nghich dao ra file MATRIX.OUT");
	printf("\n2.Xuat ma tran nghich dao ra man hinh");
	printf("\nLua chon : ");
	cin >> Selection;
	return Selection;
}
3
1 2 3
4 5 7
7 8 10