#include "Square_Matrix.h"
int main()
{
	system("COLOR 0F");
	Intro();
	system("pause");
	Square_Matrix<double> MT;
	try
	{
		Query();
		MT.Init();
		MT.Reverse();
		Output();
		MT.Display();
	}
	catch (const Invalid_Matrix &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (const Out_Of_Memory &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (const NonSquare_Matrix &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (const Irreversible &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (const Too_Large_Matrix &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}