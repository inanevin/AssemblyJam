#include <iostream>
#include "Graphics/Window.hpp"

int main(int argc, char** argv)
{
	SM::Window w;
	if (!w.Initialize(500, 500)) {
		std::cout << "WINDOW INIT FAILLLL";
		return 1;
	} else {
		std::cout << "WINDOW INIT OK!!";
	}

	while (true)
	{
		w.Update();
	}

	return 0;
}