#pragma once
#include "Square_Matrix.h"
void Title();
int Input();
int Output();
void Query();
void Find_Matrix_Size();
static int Input_Selection = 1;
static int Output_Selection = 1;
static int Matrix_Size = 0;
static constexpr const char *Input_Path = "MATRIX.IN";
static constexpr const char *Output_Path = "MATRIX.OUT";
static constexpr const char *Rand_Path = "MATRIX.RAND";
const int &Get_Input_Selection();
const int &Get_Output_Selection();
const int &Get_Matrix_size();
const char *Get_Input_Path();
const char *Get_Output_Path();
const char *Get_Rand_Path();