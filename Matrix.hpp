#pragma once

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

#include "PBL.hpp"
#include "Queue.hpp"
#include "Irreversible.hpp"
#include "Out_Of_Memory.hpp"
#include "Invalid_Input.hpp"
#include "Invalid_Matrix.hpp"
#include "NonSquare_Matrix.hpp"
#include "Too_Large_Matrix.hpp"

class Matrix
{
protected:
	int Number_Of_Row;
	int Number_Of_Col;
	double **Container;
public:
	Matrix();
	Matrix(const int &Number_Of_Row, const int &Number_Of_Col);
	Matrix(const int &Number_Of_Row, const int &Number_Of_Col, const bool &&Is_Identity_Matrix);
	~Matrix() noexcept;
	void Init();
	void Display() noexcept;
	void Swap_Row(const int &Row_Index);
	void Reverse();
	double Determinant();
	void Transpose();
	int Rank();
	void Triangular();
	Matrix &operator=(Matrix &&rhs) noexcept;
};