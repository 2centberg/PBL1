#include "Square_Matrix.h"
#include "Irreversible.h"
#include "Invalid_Matrix.h"
#include "PBL.h"
int main()
{	
	Square_Matrix<double> MT;
	try
	{
		Query();
		MT.Init();
	}
	catch (const Invalid_Matrix &ex)
	{
		std::cout << ex.what() << std::endl;
		return 0;
	}
	try
	{
		MT.Reverse();
		MT.Display();
	}
	catch (const Irreversible &ex)
	{
		std::cerr << "\t\t" << ex.what();
	}
	return 0;
}