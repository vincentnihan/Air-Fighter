#include <Book/Application.hpp>

#include <stdexcept>
#include <iostream>


bool mouseCtrlEnabled;

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
