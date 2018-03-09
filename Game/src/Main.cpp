#include <iostream>
#include <map>

#include <Core/Systems/Core.h>
#include <Test/MathTest.h>
#include <Resources/Scene.h>

#include "Scenes/DemoScene.h"
#include "Scenes/PBRScene.h"
#include "Scenes/TestScene.h"

int main(void)
{

#ifdef _DEBUG
	// Tests
	MathTest::startTest();
#else
	FreeConsole();
#endif

	// Create Scenes
	std::map<std::string, Scene*> sceneMap;
	sceneMap["Realistic Rendering"] = new TestScene();
	sceneMap["Material Test"] = new PBRScene();
	sceneMap["Demo Scene"] = new DemoScene();

	// Create and initialize the RenderProject
	Core core;
	core.init(sceneMap, "Realistic Rendering");
	core.run();
	core.destroy();

#ifdef _DEBUG
	std::cout << "press ENTER to quit" << std::endl;
	std::cin.ignore();
#endif

	return 0;
}