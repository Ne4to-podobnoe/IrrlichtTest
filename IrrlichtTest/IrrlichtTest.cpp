#include <iostream>
#include <irrlicht.h>
#include <windows.h>
#include <sstream>

# pragma comment(lib, "winmm.lib")



#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{

    IrrlichtDevice* device = createDevice(
    video::EDT_DIRECT3D9,
    dimension2d<u32>(640, 480), 
    32,    
    false, 
    false, 
    false, 
    0);

    device->setWindowCaption(L"Test");

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

	IGUIStaticText* FPSText = guienv->addStaticText(
		L"", rect<s32>(10, 10, 260, 22));

	IAnimatedMesh* mesh = smgr->getMesh("media/classd.b3d");
	if (!mesh) {
		device->drop();
		return 0;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setCurrentFrame(2);
		node->setAnimationSpeed(0);
	}

	smgr->addCameraSceneNode(0, vector3df(0, 80, -40), vector3df(0, 5, 0));

	int framescount = 0;
	DWORD time = timeGetTime()+1000;
	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();

		framescount++;

		if (time < timeGetTime()) { 
			std::ostringstream localstr;
			localstr << "FPS: " << framescount;
			FPSText->setText(stringw(localstr.str().c_str()).c_str());

			framescount = 0;
			time = timeGetTime() + 1000;
		}
	}

	device->drop();
    return 0;
}