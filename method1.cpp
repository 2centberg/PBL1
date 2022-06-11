#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <string>
using namespace std;
constexpr char In_File[15] = "MATRIX.IN"  ;
constexpr char Out_File[15] = "MATRIX.OUT" ;
constexpr char Rand_File[15] = "MATRIX.RAND";
void Create_Matrix ( double** Matrix,
					 double** Unit_Matrix, 
					 const size_t& Size );
void Print_Matrix ( double** Matrix,
					const size_t& Size );
bool Reverse ( double** Matrix,
			   double** Unit_Matrix, 
			   const size_t& Size );
size_t Find ( double** Matrix,
			  const size_t& Size,
			  const size_t& Row );
void Swap_Row ( double** Matrix,
				const size_t& Size,
				const size_t& Row_1,
				const size_t& Row_2 );
double Rand_Range ( const double& Lower_Bound,
					const double& Upper_Bound );
size_t  Input ();
size_t  Output ();
int main()
{
	system("CLS");
	size_t Inp = Input();
	double** Matrix{ 0 };
	double** Unit_Matrix{ 0 };
	size_t Size, Invertible;
	if (Inp == 1)
	{
		// Doc ma tran tu file MATRIX.IN
		fstream Fptr(In_File, ios::in);
		Fptr >> Size;
		// allocate
		Matrix = new double* [Size];
		Unit_Matrix = new double* [Size];
		for (size_t Row = 0; Row < Size; Row++)
		{
			Matrix[Row] = new double[Size];
			Unit_Matrix[Row] = new double[Size];
		}
		// initialization
		for (size_t Row = 0; Row < Size; Row++)
		{
			for (size_t Col = 0; Col < Size; Col++)
			{
				Fptr >> Matrix[Row][Col];
				Unit_Matrix[Row][Col] = 0;
			}
			Unit_Matrix[Row][Row] = 1;
		}
		// reverse
		Invertible = Reverse(Matrix, Unit_Matrix, Size);
		Fptr.close();
	}
	else //Tao ma tran ngau nhien, ghi ma tran vao file MATRIX.RAND
	{
		printf("\n\t\tNhap cap cua ma tran : ");
		cin >> Size;
		// allocate
		Matrix = new double* [Size];
		Unit_Matrix = new double* [Size];
		for (size_t Row = 0; Row < Size; Row++)
		{
			Matrix[Row] = new double[Size];
			Unit_Matrix[Row] = new double[Size];
		}
		// create random matrix
		Create_Matrix(Matrix, Unit_Matrix, Size);
		// reverse
		Invertible = Reverse(Matrix, Unit_Matrix, Size);
	}

	size_t Out = Output();
	if (Out == 1) // Ghi ma tran nghich dao ra file MATRIX.OUT
	{
		FILE* Fptr = fopen(Out_File, "w");
		if (Invertible == 0)
		{
			fprintf(Fptr, "\n\tMa tran khong kha nghich");
		}
		else
		{
			for (size_t Row = 0; Row < Size; Row++)
			{
				for (size_t Col = 0; Col < Size; Col++)
				{
					fprintf(Fptr, "%+-1.6lf\t", Unit_Matrix[Row][Col]);
				}
				fputc('\n', Fptr);
			}
		}
		fclose(Fptr);
	}
	else
	{
		if (Invertible == 0)
		{
			perror("\tMa tran khong kha nghich");
		}

		else
		{
			Print_Matrix(Unit_Matrix, Size);
		}
	}
	// delete 
	for (size_t i = 0; i < Size; i++)
	{
		delete[] Matrix[i];
		delete[] Unit_Matrix[i];
	}

	delete Matrix;
	Matrix = 0;
	delete Unit_Matrix;
	Unit_Matrix = 0;
	return 0;
}
void Print_Matrix ( double** Matrix,
					const size_t& Size )
{
	for (size_t i = 0; i < Size; i++)
	{
		printf("\t\t");
		for (size_t j = 0; j < Size; j++)
		{
			printf("%+-1.3lf\t", Matrix[i][j]);
		}
		printf("\n");
	}
	return;
}
void Create_Matrix ( double** Matrix,
					 double** Unit_Matrix,
					 const size_t& Size )
{
	srand(time(NULL));
	// ghi ma tran tao ngau nhien vao file MATRIX.RAND
	FILE* Fptr = fopen(Rand_File, "w");
	fprintf(Fptr, "%ld\n", Size);
	cout << "Loading : ";
	int m=Size*Size;
	
	for (size_t i = 0; i < Size; i++)
	{
		int n=i*Size;
		for (size_t j = 0; j < Size; j++)
		{
			for (int k = 0; k < 3; k++) {
            	{
            		cout << static_cast<int> ((n+j)*100.0/m) << '%';
            		sleep(0.5);
				}
        }
        cout << "\b\b\b   \b\b\b\b\b\b\b";
			Matrix[i][j] = Rand_Range(-Rand_Range(-rand()%1000, rand()%1000), 
										Rand_Range(-rand()%1000, rand()%1000));
			Unit_Matrix[i][j] = 0;
			fprintf(Fptr, "%+-lf\t", Matrix[i][j]);
		}
		Unit_Matrix[i][i] = 1;
		fputc('\n', Fptr);
	}
	fclose(Fptr);
	return;
}
bool Reverse ( double** Matrix,
			   double** Unit_Matrix,
			   const size_t& Size )
{
	double Anchor_Point;
	for (size_t Row_Index = 0; Row_Index < Size; Row_Index++)
	{
		Anchor_Point = Matrix[Row_Index][Row_Index];
		if (Anchor_Point == 0)
		{
			size_t Find_Row_Below = Find(Matrix, Size, Row_Index);
			if (Find_Row_Below != -1)
			{
				Swap_Row(Matrix, Size, Row_Index, Find_Row_Below);
				Swap_Row(Unit_Matrix, Size, Row_Index, Find_Row_Below);
			}
			else
			{
				return 0;
			}
			Anchor_Point = Matrix[Row_Index][Row_Index];
		}
		for (size_t Col_index = 0; Col_index < Size; Col_index++)
		{
			Matrix[Row_Index][Col_index] 	  /= Anchor_Point;
			Unit_Matrix[Row_Index][Col_index] /= Anchor_Point;
		}

		for (size_t Another_Row = 0; Another_Row < Size; Another_Row++)
		{
			if (Another_Row == Row_Index)
			{
				continue;
			}
			Anchor_Point = -Matrix[Another_Row][Row_Index];
			for (size_t Col_index = 0; Col_index < Size; Col_index++)
			{
				Matrix[Another_Row][Col_index] 		+= Anchor_Point * Matrix[Row_Index][Col_index];
				Unit_Matrix[Another_Row][Col_index] += Anchor_Point * Unit_Matrix[Row_Index][Col_index];
			}
		}
	}
	return 1;
}
size_t Find ( double** Matrix,
			  const size_t& Size, 
			  const size_t& Row )
{
	for (size_t Next_Row = Row + 1; Next_Row < Size; Next_Row++)
	{
		if (Matrix[Next_Row][Row] != 0)
		{
			return Next_Row;
		}
	}
	return -1;
}
void Swap_Row ( double** Matrix,
				const size_t& Size,
				const size_t& Row_1,
				const size_t& Row_2 )
{
	swap(Matrix[Row_1], Matrix[Row_2]);
}
double Rand_Range ( const double& Lower_Bound,
					 const double& Upper_Bound )
{
	return Lower_Bound + (Upper_Bound - Lower_Bound) * ((double)rand()) / 0x7fff;
}
size_t Input ()
{
	size_t Selection;
	printf("\n\n\t\t1.Doc ma tran tu file MATRIX.IN");
	printf("\n\t\t2.Tao ma tran ngau nhien");
	printf("\n\t\tLua chon : ");
	cin >> Selection;
	return Selection;
}
size_t Output ()
{
	size_t Selection;
	printf("\n\t\t1.Xuat ma tran nghich dao ra file MATRIX.OUT");
	printf("\n\t\t2.Xuat ma tran nghich dao ra man hinh");
	printf("\n\t\tLua chon : ");
	cin >> Selection;
	return Selection;
}
