#pragma once
void Matrix_Query();
void ShowConsoleCursor(bool showFlag);
void Remove_Scrollbars();
#include <Windows.h>
class PBL
{
public:
	static HANDLE  hConsole;
	static int &&colour;
	static int Input_Selection;
	static int Output_Selection;
	static int Row_Size;
	static int Col_Size;
	static constexpr const char *Input_Path = "MATRIX.IN";
	static constexpr const char *Output_Path = "MATRIX.OUT";
	static constexpr const char *Rand_Path = "MATRIX.RAND";
	static constexpr const char *Menu_Path = "MENU.TXT";
public:
	PBL() noexcept = default;
	~PBL() = default;
};

