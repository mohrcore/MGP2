#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include <vector>
#include <cstdlib>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <M3D.h>
#include <M3D_gui.h>

#include "IMP_Asset.h"

#define FOV 1.22f
#define Z_NEAR 0.1f
#define Z_FAR 100.0f

int display_w = 1024;
int display_h = 720;

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window * mainwindow = SDL_CreateWindow("MobTweaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_w, display_h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext _gl_context = SDL_GL_CreateContext(mainwindow);

	glewInit();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Enable double buffer

	glClearColor(1.0, 1.0, 1.0, 1.0);

	SDL_Event _ev;
	
	bool _quit = false;

	TextureBank _tbank;

	//std::vector<Vertex> vd;
	//vd.resize(4);
	//
	//vd[0].pos = Vec3f(0.0f, 0.0f, 0.0f);
	//vd[1].pos = Vec3f(256.0f, 0.0f, 0.0f);
	//vd[2].pos = Vec3f(256.0f, 256.0f, 0.0f);
	//vd[3].pos = Vec3f(0.0f, 256.0f, 0.0f);
	////vd[0].col = Color(255, 0, 0, 255);
	////vd[1].col = Color(0, 255, 0, 255);
	////vd[2].col = Color(0, 0, 255, 255);
	////vd[3].col = Color(255, 0, 0, 255);
	//vd[0].uv = Vec2f(0.0f, 0.0f);
	//vd[1].uv = Vec2f(1.0f, 0.0f);
	//vd[2].uv = Vec2f(1.0f, 1.0f);
	//vd[3].uv = Vec2f(0.0f, 1.0f);
	//
	//std::vector<GLuint> vd_i = { 0, 3, 1, 1, 3, 2 };
	//
	//std::vector<Texture> t1;
	//t1.resize(1);
	//t1[0].loadFromFile("resources/textures/test1.png", DIFFUSE_MAP);
	//
	//Mesh m1;
	//
	//m1.loadRawData(vd, vd_i, t1);
	//m1.uploadData();

	StaticShader_PPL ss1;
	ss1.vertSource("resources/shaders/static_ppl.vert");
	ss1.fragSource("resources/shaders/static_ppl.frag");
	ss1.compile();
	ss1.bindAttribute(0, "vertexPosition");
	ss1.bindAttribute(1, "uv_coord");
	ss1.bindAttribute(2, "normal_v");
	ss1.link();

	StaticShader ss_gui;
	ss_gui.vertSource("resources/shaders/static.vert");
	ss_gui.fragSource("resources/shaders/static.frag");
	ss_gui.compile();
	ss_gui.bindAttribute(0, "vertexPosition");
	ss_gui.bindAttribute(1, "uv_coord");
	ss_gui.link();


	BinaryInput _bi;

	Camera cam1(_bi);
	cam1.setPosition(Vec3f(0.0f, 0.0f, 0.0f));
	cam1.setAngle(Vec3f(0.0f, 0.0f, 0.0f));

	Camera gui_cam(_bi);
	gui_cam.setPosition(Vec3f(0.0f, 0.0f, 0.0f));
	gui_cam.setAngle(Vec3f(0.0f, 0.0f, 0.0f));

	Renderer renderer;
	//renderer.setProjectionMatrix(/*FOV, Z_NEAR, Z_FAR, (float)display_w / (float)display_h*/ display_w, display_h);
	renderer.setProjectionMatrix(FOV, Z_NEAR, Z_FAR, (float)display_w / (float)display_h); //3D mode
	renderer.setActiveCamera(cam1);

	Renderer gui_renderer;
	gui_renderer.setProjectionMatrix(display_w, display_h); //2D pixel-perfect mode
	gui_renderer.setActiveCamera(gui_cam);

	std::string imp_path;

	std::cout << "Enter model path: ";
	//std::cin >> imp_path;
	imp_path = "resources/models/cubepanel.obj"; //PH

	IMP_Asset ia;

	ia.import(imp_path, _tbank);

	EntityM em = ia.getEntityM();
	em.position = Vec3f(0.0f, 0.0f, -10.0f);
	em.scale = Vec3f(0.1f, 0.1f, 0.1f);
	em.uploadData();

	LightSource light1;
	light1.position = Vec3f(-1.0f, 1.0f, 10.0f);

	ss1.bind();
	ss1.setLightning(light1);
	ss1.unbind();

	Sprite sprite1(_tbank);
	sprite1.loadTextureFromFile("resources/textures/test1.png");
	sprite1.setPosition(Vec2f(8, 8));
	sprite1.setDimensions(Vec2f(128, 128));
	sprite1.setCropRect(Rect2d(4.0f, 4.0f, 32.0f, 64.0f));

	Sprite sprite2(_tbank);
	sprite2.loadTextureFromFile("resources/textures/test2.png");
	sprite2.setPosition(Vec2f(138, 8));
	sprite2.setDimensions(Vec2f(256, 256));
	sprite2.setRepeats(Vec2f(128, 128));

	Font f1(_tbank);
	f1.loadFromFile("resources/fonts/Simplex_IV50_DF.fnt");

	Clock c1;

	while (!_quit) //  <-------------------------------------------------------------------------------------------------------------------------------------------------Main loop
	{
		while (SDL_PollEvent(&_ev))
		{
			switch (_ev.type)
			{
			case SDL_QUIT:

				_quit = true;
				break;
			}
		}

		em.rotation = Vec3f(sin(c1.getTime()), c1.getTime(), 0.0f);

		cam1.update();
		gui_cam.update();

		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//renderer.RenderMesh(m1, ss1);

		renderer.renderEntityM(em, ss1);

		gui_renderer.renderSprite(sprite1, ss_gui);
		gui_renderer.renderSprite(sprite2, ss_gui);

		SDL_GL_SwapWindow(mainwindow);

	}

	SDL_DestroyWindow(mainwindow);

	SDL_Quit();
	IMG_Quit();

	return 0;
}