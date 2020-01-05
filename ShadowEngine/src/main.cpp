#include "shpch.h"

#include <iostream>

// OpenGL headers
#include "glad/glad.h"
//#include "GL/gl.h"

//#include <SDL2/SDL.h>
#include <EntitySystem/EntityRegistry.h>
#include "Core/ShadowApplication.h"

#include "ShadowScene/TestScene.h"

#include "EntitySystem/Entities/Camera.h"

int main(int argc, char* argv[])
{
	ShadowEngine::EntitySystem::EntityRegistry registry;

	

	ShadowEngine::ShadowApplication app;
	app.Init();
	app.Start();


	char s;
	std::cin >> s;

	return 0;
}
