#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <algorithm>

#include "M3DFW.h"

#include <GL\glew.h>
#include <SDL.h>

std::mutex cout_mutex;


void task1()
{
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Task 1 executed" << std::endl;
}

void task2()
{
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Task 2 executed" << std::endl;
}


void addTasks(m3dfw::TaskManager & t_manager, int rep)
{
	//12 Tasks, absolutly more than avaible threads

	for (int i = 0; i < rep; i++)
	{
		t_manager.assignTask(task1);
		t_manager.assignTask(task2);
	}
}


struct intstring
{
	intstring(const std::string & stri, int integ) : str(stri), i(integ) {}

	std::string str;
	int i;
};


class MRS1
	: public m3dfw::MessageReceiver, public m3dfw::MessageSender
{
public:

	MRS1(m3dfw::MessageManager & mm) : m3dfw::MessageSender(mm), m3dfw::MessageReceiver(mm) {}

	M3D_PROCESS_MSG(msg)
	{
		intstring data = msg.getData<intstring>();

		std::cout << data.str << std::endl << data.i << std::endl;
		
 		sendMessage<short>(1, 16);
	}
};

class MRS2
	: public m3dfw::MessageReceiver, public m3dfw::MessageSender
{
public:

	MRS2(m3dfw::MessageManager & mm) : m3dfw::MessageSender(mm), m3dfw::MessageReceiver(mm) {}

	void doit()
	{
		intstring is("wazna wiadomosc", 2137);
		sendMessage(0, is);
		bool didit = true;
	}

	M3D_PROCESS_MSG(msg)
	{
		short data = msg.getData<short>();

		std::cout << data << std::endl;
	}
};

int main(int argc, char* argv[])
{
	std::cout << "Unpause, when profiling tools are ready" << std::endl;
	system("pause");

	SDL_Init(SDL_INIT_EVERYTHING);

	const float res_x = 1920;
	const float res_y = 1080;

	SDL_Window * win = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)res_x, (int)res_y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL/* | SDL_WINDOW_FULLSCREEN*/);
	SDL_GLContext gl_context = SDL_GL_CreateContext(win);

	if (!m3dfw::init())
		m3dfw::fatalError("Failed to initialize GLEW");

	//glewExperimental = GL_TRUE;
	//GLenum glew_isucc = glewInit();

	//std::string err = (char *)glewGetErrorString(glew_isucc);

	//if(glew_isucc != GLEW_OK)
	//	m3dfw::fatalError("Failed to initialize GLEW: " + err);

	const unsigned int th_no = std::thread::hardware_concurrency();

	m3dfw::TaskManager t_manager(th_no - 1);

	m3dfw::Clock cl1;

	addTasks(t_manager, 6);

	t_manager.waitTillFinished();

	m3dfw::MessageManager mm;
	
	MRS1 mrs1(mm);
	MRS2 mrs2(mm);
	mrs1.subscribe(0);
	mrs2.subscribe(1);

	//mm.subscribe(&mrs1, 0);
	//mm.subscribe(&mrs2, 1);

	mrs2.doit();

	mm.sendMessages();
	//mm.sendMessages();

	std::cout << "Time elapsed: " << cl1.getTime() << "s" << std::endl;

	m3dfw::GameDLib gdlib;

	//gdlib.loadLibrary("TestGameDLib.dll");

	//void(*func1)() = (void(*)())gdlib.getFunctionByName("function1");
	//void(*func2)() = (void(*)())gdlib.getFunctionByName("function2");

	//func1();
	//func2();

	m3dfw::GLSLProgramParseInfo ppi1;

	bool kupa;

	if (ppi1.parse("resources/shaders/static_ppl.vert", m3dfw::GLSLParseMode::ParseIn | m3dfw::GLSLParseMode::ParseUniform))
	{
		kupa = true;
	}

	kupa = true;

	std::cout << "CL size: " << m3dfw::HardwareInfo::getInstance().getCPUCacheLineSize() << std::endl;

	GLenum error = glGetError();

	m3dfw::ResourceManager rm;
	m3dfw::ResourceLoader rloader(rm);

	m3dfw::ShaderManager sm1;

	m3dfw::ShID coolshader = sm1.loadProgram("resources/shaders/static_ppl.vert", "resources/shaders/static_ppl.frag", "<unknown>");

	m3dfw::GLSLProgram & prog = sm1.getProgram(coolshader);

	error = glGetError();

	m3dfw::loadMaterialResourcesFromMDPFile("tm3.mdp", rloader, sm1);
	auto testmodel1 = rloader.importGfxModel3d("tm3.mob", "tm3");

	error = glGetError();

	m3dfw::GfxObject object1(testmodel1);

	m3dfw::O3DRendererGL renderer(sm1);
	renderer.setProjectionMatrix(0.8f, 0.01f, 10000.0f, res_x / res_y);

	m3dfw::Camera3d camera1(m3dfw::Vec3f(0, 0, 0), m3dfw::Vec3f(0, 0, 0));

	//sm1.compileFromSourceFile("resources/shaders/static_ppl.vert", "resources/shaders/static_ppl.frag", "static_ppl");
	//sm1.compileFromSourceFile("resources/shaders/static.vert", "resources/shaders/static.frag", "static");
	//m3dfw::ShCK shader_key_static_ppl = sm1.getShaderCompatibilityKey("static_ppl");
	//m3dfw::ShCK shader_key_static = sm1.getShaderCompatibilityKey("static");

	//std::cout << "Shader \"static\" SCK: " << shader_key_static << std::endl;

	//m3dfw::List<int> & mylist = m3dfw::CustomAllocList<int, m3dfw::StaticPoolAllocator>(); // Nice <3<3<3

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(0);

	object1.position = m3dfw::Vec3f(0, 0, 100);

	m3dfw::Clock c1;

	//std::vector<m3dfw::GfxBasicLight> lights;
	//lights.resize(2);
	m3dfw::GfxBasicLight light1, light2;
	light1.position = m3dfw::Vec3f(0, 100, 10);
	light1.color = m3dfw::Vec3f(1.0, 0.0, 0.5);
	light2.position = m3dfw::Vec3f(0, -100, 100);
	light2.color = m3dfw::Vec3f(0.0, 1.0, 0.5);

	m3dfw::List<m3dfw::GfxBasicLight> lights;
	lights.push(light1);
	lights.push(light2);

	SDL_Event sdl_event;

	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&sdl_event))
		{
			switch (sdl_event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				switch (sdl_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
				break;
			}
		}

		int mousepos_x, mousepos_y;
		Uint32 mouse_state = SDL_GetMouseState(&mousepos_x, &mousepos_y);
		m3dfw::Vec2f mouse_pos((float)mousepos_x, (float)mousepos_y);

		double time = c1.getTime();

		//lights[0].position = m3dfw::Vec3f(1.0f, std::sin(time / 2.0f) * 1.0f, 0.0f);

		object1.rotation = m3dfw::Vec3f((float)time / 2.0f, (float)time, (float)time / 3.0f);
		camera1.angle = m3dfw::Vec3f(mouse_pos.y / res_y - 0.5f, mouse_pos.x / res_x - 0.5f, 0.0f) * 3.0f;

		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(object1, camera1, lights);
		//renderer.renderTestQuadMat(*testmodel1->materials[0]);

		//error = glGetError();

		SDL_GL_SwapWindow(win);
	}

	m3dfw::DynamicStackAllocator alloc1(256);

	std::string * str_arr = alloc1.alloc<std::string>(20);


	//GL errors on clearup!!!
	rm.clearAllResources();

	SDL_DestroyWindow(win);
	SDL_GL_DeleteContext(gl_context);

	system("pause");

	return 0;
}