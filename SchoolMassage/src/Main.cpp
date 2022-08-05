#include <iostream>
#include "Common/Utils.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/Backend.hpp"

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

	Backend::Initialize();

	while (true)
	{
		w.Update();
	}

	Backend::Terminate();

	return 0;
}