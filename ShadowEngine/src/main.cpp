#include <iostream>
#include "ShadowAsset/AssetLoader.h"

// OpenGL headers
#include "glad/glad.h"
#include "GL/gl.h"

#include <SDL2/SDL.h>
#include <ShadowEntity/EntityRegistry.h>
#include <ShadowMap/ShadowMapRenderer.h>
#include "ShadowApplication.h"
#include "ShadowInput/ShadowAction.h"
#include "ShadowInput/Bindings/Binding2D.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "ShadowInput/Modifiers/ModifierRepeat.h"

int main(int argc, char* argv[]) {


	ShadowEntity::EntityRegistry registry;

	//registry.ListPreRegisteredEntitys();

	//AssetLoader loader;
	//ShadowWorld* w = loader.LoadWorld("Resources/Worlds/Default/overworld.txt");
	//w->SetActiveMap("default");
	//w->Update(ShadowMath::Vector2float(0, 0));
	//ShadowMapRenderer::RenderMap(*map);

	ShadowInput::ShadowAction<bool>("Test",
			new ShadowInput::KeyboardBinding("A")
		);

	


	ShadowApplication app;
	app.Init();
	app.Start();




	char s;
	std::cin >> s;

	return 0;
}
