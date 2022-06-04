#pragma once
void Input();
void Output();
void Intro();
void Query();
const int Rand_Int();
class PBL
{
public:
	static int Input_Selection;
	static int Output_Selection;
	static int Matrix_Size;
	static constexpr const char *Input_Path = "MATRIX.IN";
	static constexpr const char *Output_Path = "MATRIX.OUT";
	static constexpr const char *Rand_Path = "MyMatrixRand.txt";
public:
	PBL() noexcept = default;
	~PBL() noexcept = default;
};