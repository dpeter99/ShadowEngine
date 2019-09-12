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
	std::unique_ptr<ShadowScene> a = std::make_unique<ShadowScene>();

	ShadowScene* i = new TestScene();

	a.reset(i);


	ShadowEntity::EntityRegistry registry;
	

	ShadowApplication app;
	app.Init();
	app.Start();


	char s;
	std::cin >> s;

	return 0;
}
