#include "shpch.h"

#include <iostream>

// OpenGL headers
#include "glad/glad.h"
#include "GL/gl.h"

#include <SDL2/SDL.h>
#include <ShadowEntity/EntityRegistry.h>
#include "Core/ShadowApplication.h"

#include "ShadowScene/TestScene.h"

int main(int argc, char* argv[])
{
	ShadowEntity::EntityRegistry registry;
	

	ShadowEngine::ShadowApplication app;
	app.Init();
	app.Start();


	char s;
	std::cin >> s;

	return 0;
}
