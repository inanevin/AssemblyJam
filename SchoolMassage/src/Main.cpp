#include <iostream>
#include "Common/Utils.hpp"
#include "Graphics/Window.hpp"

int main(int argc, char** argv)
{
	SM::Window w;
	if (!w.Initialize(500, 500)) {
		SM::LOG("Window init failure :(");
		return 1;
	}

	while (true)
	{
		w.Update();
	}

	return 0;
}