#include <iostream>
#include "Common/Utils.hpp"
#include "Graphics/Window.hpp"

int main(int argc, char** argv)
{
	using namespace SM;

	Window w;
	if (!w.Initialize()) {
		LOG("Window init failure :(");

		return 1;
	}

	auto v = ReadFile("Resources/map.txt");
	LOG("DEBUG map text file size: %u", v.size());

	while (true)
	{
		w.Update();
	}

	return 0;
}