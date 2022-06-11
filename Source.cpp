#include "Matrix.hpp"
int main()
{
	system("COLOR 0F");
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	ShowConsoleCursor(0);
	Matrix_Query();
	return 0;
}