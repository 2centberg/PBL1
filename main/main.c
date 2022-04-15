#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void _calc();
void _create_matrix(double **_matrix, const int _size);
void _print_matrix(double **_matrix, const int _size);
int  _reverse(double **_matrix, const int _size);
int  _find(double **_matrix, const int _size, const int _row);
void _swap_row(double **_matrix, const int _size, const int _row, const int _next_row);
double _rand_range(double _lower_bound, double _upper_bound);
int  _input();
int  _output();
void _check(int _inp, int _out);
int main()
{
	_calc();
	return 0;
}
void _calc()
{
	int _inp = 0, _out = 0;
	double** _matrix;
	int _size, _invertible;
	if (_input() == 1) // Doc ma tran tu file MATRAN.IN
	{
		FILE* _fptr = fopen("D:\\PBL1\\main\\MATRAN.IN", "r");
		fscanf(_fptr, "%d", &_size);
		_matrix = (double**)malloc(_size * sizeof(double*));
		for (int _row = 0; _row < _size; _row++)
			_matrix[_row] = (double*)malloc(2 * _size * sizeof(double));
		
		for (int _row = 0; _row < _size; _row++)
		{
			for (int _col = 0; _col < _size; _col++)
			{
				fscanf(_fptr, "%lf", &_matrix[_row][_col]);
				_matrix[_row][_col + _size] = 0;
			}
			_matrix[_row][_row + _size] = 1;
		}
		_invertible = _reverse(_matrix, _size);
		fclose(_fptr);
	}
	else // Tao ma tran ngau nhien, ghi ma tran vao file MATRAN.RAND
	{
		_inp = 1;
		printf("\n\tNhap cap cua ma tran : ");
		scanf("%d", &_size);
		_matrix = (double**)malloc(_size * sizeof(double*));
		for (int _row = 0; _row < _size; _row++)
			_matrix[_row] = (double*)malloc(2 * _size * sizeof(double));
		
		_create_matrix(_matrix, _size);
		_invertible = _reverse(_matrix, _size);
	}
	
	if (_output() == 1) // Ghi ma tran nghich dao ra file MATRAN.OUT
	{
		FILE* _fptr = fopen("D:\\PBL1\\main\\MATRAN.OUT", "w");
		if (_invertible == 0)
			fprintf(_fptr, "\n\tMa tran khong kha nghich");
			
		else 
		{
			for (int _row = 0; _row < _size; _row++)
			{
				for (int _col = _size; _col < 2*_size; _col++)
					fprintf(_fptr, "%lf\t", _matrix[_row][_col]);
					
				fputc('\n', _fptr);
			}
		}
		fclose(_fptr);
	}
	else 
	{
		_out = 1;
		if (_invertible == 0)
			printf("\tMa tran khong kha nghich");
			
		else
			_print_matrix(_matrix, _size);
	}
	for(int _row = 0; _row < _size; _row++)
		free(_matrix[_row]);
		
	free(_matrix);
	if (_invertible == 1)
		_check(_inp, _out);
	return;
}
void _print_matrix (double **_matrix, const int _size)
{
	FILE* _fptr = fopen("D:\\PBL1\\main\\MATRAN.OUT2", "w");
	for (int _row = 0; _row < _size; _row++)
	{
		for(int _col = _size; _col < 2*_size; _col++)
		{
			printf("%+-1.3lf  ", _matrix[_row][_col]);
			fprintf(_fptr, "%+-1.3lf  ", _matrix[_row][_col]);
		}
		printf("\n");
		fputc('\n', _fptr);
	}
	fclose(_fptr);
	return;
}
void _create_matrix(double **_matrix, const int _size)
{
	srand(time(NULL));
	double _lower_bound, _upper_bound;
	{
		printf("\tNhap gia tri nho nhat cua cac phan tu : "); 
			scanf("%lf", &_lower_bound);
		printf("\tNhap gia tri lon nhat cua cac phan tu : "); 
			scanf("%lf", &_upper_bound);
	}
	// ghi ma tran tao ngau nhien vao file MATRAN.RAND
	FILE* _fptr = fopen("D:\\PBL1\\main\\MATRAN.RAND", "w");
	fprintf(_fptr, "%d\n", _size);
	for (int _row = 0; _row < _size; _row++)
	{
		for(int _col = 0; _col < _size; _col++)
		{
			_matrix[_row][_col] = _rand_range(_lower_bound, _upper_bound);
			_matrix[_row][_col + _size] = 0;
			fprintf(_fptr, "%lf ", _matrix[_row][_col]);
		}
		_matrix[_row][_row + _size] = 1;
		fputc('\n', _fptr);
	}
	fclose(_fptr);
	return;
}
int _reverse(double** _matrix, const int _size)
{
	double _anchor_point;
	for (int _row = 0; _row < _size; _row++)
	{
		_anchor_point = _matrix[_row][_row];
		if (_anchor_point == 0)
		{
			if (_find(_matrix, _size, _row) == 0)
				return 0;
				
			_anchor_point = _matrix[_row][_row];
		}
		for (int _col = 0; _col < 2 * _size; _col++)
			_matrix[_row][_col] /= _anchor_point;
			
		for (int _another_row = 0; _another_row < _size ; _another_row++)
		{
			if (_another_row == _row) 
				continue;
				
			_anchor_point = -_matrix[_another_row][_row];
			for(int _col = 0; _col < 2*_size; _col++)
				_matrix[_another_row][_col] += _anchor_point*_matrix[_row][_col];
		}
	}
	return 1;
}
int _find (double **_matrix, const int _size, const int _row)
{
	for (int _next_row = _row + 1; _next_row < _size; _next_row++)
	{
		if (_matrix[_next_row][_row] != 0)
		{
			_swap_row(_matrix, _size, _row, _next_row);
			return 1;
		}
	}
	return 0;
}
void _swap_row (double **_matrix, const int _size, const int _row, const int _next_row)
{
	for (int _col = 0; _col < 2 * _size; _col++)
	{
		double _temp = _matrix[_row][_col];
		_matrix[_row][_col] = _matrix[_next_row][_col];
		_matrix[_next_row][_col] = _temp;
	}
	return;
}
double _rand_range(double _lower_bound, double _upper_bound)
{
	return _lower_bound + (_upper_bound - _lower_bound) * ((double)rand()) / 0x7fff;
}
int _input()
{
	int _selection;
	printf("\t\tChuong trinh tim ma tran ngich dao");
	do
	{
		printf("\n\t1.Doc ma tran tu file");
		printf("\n\t2.Tao ma tran ngau nhien");
		printf("\n\tLua chon : ");
		scanf("%d", &_selection);
	} while (_selection != 1 && _selection != 2);
	return _selection;
}
int _output()
{
	int _selection;
	do
	{
		printf("\n\t1.Xuat ma tran ra file");
		printf("\n\t2.Xuat ma tran ra man hinh");
		printf("\n\tLua chon : "); 
		scanf("%d", &_selection);
	} while (_selection != 1 && _selection != 2);
	return _selection;
}
void _check(int _inp, int _out)
{
	FILE* _fptr_1;
	FILE* _fptr_2;
	
	if (_inp == 0)
		_fptr_1 = fopen("D:\\PBL1\\main\\MATRAN.IN", "r");
	else
		_fptr_1 = fopen("D:\\PBL1\\main\\MATRAN.RAND", "r");
	if (_out == 0)
		_fptr_2 = fopen("D:\\PBL1\\main\\MATRAN.OUT", "r");
	else
		_fptr_2 = fopen("D:\\PBL1\\main\\MATRAN.OUT2", "r");
	
	int _size;
	fscanf(_fptr_1, "%d", &_size);
	double** _matrix_1, ** _matrix_2;
	_matrix_1 = (double**)malloc((_size) * sizeof(double*));
	_matrix_2 = (double**)malloc((_size) * sizeof(double*));
	for (int i = 0; i < _size; i++)
	{
		_matrix_1[i] = (double*)malloc((_size) * sizeof(double*));
		_matrix_2[i] = (double*)malloc((_size) * sizeof(double*));
    }
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
        {
			fscanf(_fptr_1, "%lf", &_matrix_1[i][j]);
			fscanf(_fptr_2, "%lf", &_matrix_2[i][j]);
        }
	}
	fclose(_fptr_1);
	fclose(_fptr_2);
	
	FILE* _product = fopen("D:\\PBL1\\Main\\MATRAN.TICH", "w");
	double _temp;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
        {
			_temp = 0;
			for (int k = 0; k < _size; k++)
			{
				_temp = _temp + _matrix_1[i][k] * _matrix_2[k][j];
			}
			fprintf(_product, "%+-1.3lf\t", _temp);
		}
		fputc('\n', _product);
	}
	fclose(_product);
	return;
}