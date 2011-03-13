//#include <glutm/main.h>
#include <glutm/winexam.h>
#include <glutm/glut.h>
#include <glutm/shape.h>
#include <glt/light.h>					//Enable Light
#include <NxPhysics.h>				//PhysX
//#include <glt/fontasci.h>
#include <glt/rgb.h>

//#include <node/shape.h>
//#include <node/text.h>

//#include <fonts/fonts.h>

#include <memory>
#include <iostream>

using namespace std;

class GltShape;

class myPhysX : public GlutWindowExaminer
{
public:
	myPhysX(		
		int width                = widthDefault, 
		int height               = heightDefault,
		int x                    = xDefault, 
		int y                    = yDefault,
		int fps					= 60,
		bool isSimulate		= true
	);
   ~myPhysX();

   void OnOpen();
   void OnClose();
   void OnDisplay();
   void OnTick();
   void OnKeyboard(unsigned char key, int x, int y);

protected:
	bool InitNx();						//Initialize PhysX
	bool InitNxScene();				//Initialize PhysX Scene
	void CleanUpNx();				//Terminate PhysX
	void myGLInit();			//Initialize OpenGL

	auto_ptr<GltShape>  _shape;
	int		_fps;							//frame per second : Simulation Time
	bool	_isSimulate;				//Flag to switch Simulation ON/OFF
	NxPhysicsSDK* _pPhysicsSDK;	//PhysX
	NxScene* _pScene;			//PhysX Scene
	NxVec3 _DefaultGravity;	//Gravity
};

myPhysX::myPhysX(int width,int height,int x,int y, int fps, bool isSimulate)
: GlutWindowExaminer("myPhysX",width,height,x,y),_fps(fps)
	,_isSimulate(isSimulate),_DefaultGravity(0, -9.8, 0)
{
	InitNx();
	InitNxScene();
	//myGLInit();			//ここに置くと"light0.set()"がエラーになる．なぜだか．
}

myPhysX::~myPhysX()
{
	CleanUpNx();
}

void
myPhysX::OnOpen()
{
	_viewMatrix = matrixRotate(Vector1,60.0)*_viewMatrix;
	
	myGLInit();
	
	OnKeyboard('1',0,0);	// Select sphere to start with
	setTick(1000/_fps);		// 60fps maximum
}

void
myPhysX::OnClose()
{
}

void myPhysX::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2, 0.2, 0.2, 1.0);		//背景色を設定

	if (_shape.get()){
		_shape->draw();
	}
}

void myPhysX::OnTick()
{
	if (!mousePressed()){
		_viewMatrix = matrixRotate(Vector1,0.2)*_viewMatrix;
	}
	if(_isSimulate){
		_pScene->simulate(1.0f/(float)_fps);
	}

	postRedisplay();
	if(_isSimulate){
		_pScene->flushStream();
		_pScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
}

void myPhysX::OnKeyboard(unsigned char key, int x, int y)
{
	GlutWindowExaminer::OnKeyboard(key,x,y);

	GltShape *newShape = NULL;

	switch (key)
	{
	case '1':					//'1'
		newShape = new GlutSphere(false);
		break;
	case 27:				//'ESC'
		exit(0);				//Terminate Program
		break;
	case 32:
		_isSimulate = !_isSimulate;	//Switch Simulation Flag State
		break;
	default:
		break;
	}

	if (newShape)
	{
		// gcc doesn't allow:  _shape = auto_ptr<GltShape>(newShape)
		auto_ptr<GltShape> tmp(newShape);
		_shape = tmp;
	}

	_shape->color() = green;
	_shape->solid() = false;

	postRedisplay();
}

bool myPhysX::InitNx()
{
	bool initialized = false;
#ifdef _DEBUG
	std::cout << "Physics SDK Loading Version: " << NX_PHYSICS_SDK_VERSION << std::endl;
#endif //_DEBUG
	_pPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	if (_pPhysicsSDK != NULL){
		_pPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect("localhost", 5425);
#ifdef _DEBUG
		std::cout << "PhysX Initialized" << std::endl;
#endif //_DEBUG
		initialized = true;
	}else{
		std::cout<<"Initialize Error: Cannot Create Physics SDK"<<std::endl;
	}
	return initialized;
}
	/**
	 *	InitScene() : Initialize Scene
	 * @return bool - whether Scene Initialization has done or not.
	 * @description - Initialize Scene.
	 */
bool myPhysX::InitNxScene(){
	bool sceneInit = false;
	//Create Scene Descripter
	NxSceneDesc sceneDesc;
	sceneDesc.gravity = _DefaultGravity;
	//Create Real Scene
	_pScene = _pPhysicsSDK->createScene(sceneDesc);
	if (_pScene != NULL){
#ifdef _DEBUG
		std::cout << "Scene Initialized" << std::endl;
#endif //_DEBUG
		sceneInit = true;
	}
	return sceneInit;
}
	/**
	 *	CleanUpNx() : Clean Up PhysX Objects
	 *	@description - Clean Up Memory.
	 */
void myPhysX::CleanUpNx(){
	if(_pPhysicsSDK != NULL){
		if( _pScene != NULL ){
			_pPhysicsSDK->releaseScene(*_pScene);
			_pScene = NULL;	//Release Scene Object
		}
		NxReleasePhysicsSDK( _pPhysicsSDK );
		_pPhysicsSDK = NULL;	//Release PhysicsSDK Object
	}
#ifdef _DEBUG
		std::cout << "Clean Up Ended." << std::endl;
#endif //_DEBUG
}
	/**
	 * myGLInit() : Initialize OpenGL
	 * @description - Initialize OpenGL
	 */
void myPhysX::myGLInit(){
	// Setup default render states
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	//glEnable(GL_NORMALIZE);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DITHER);
	//glCullFace(GL_BACK);
	//glClearDepth(1.0);
	//glDepthRange(0.0,1.0);
	//glLoadIdentity();

	//// Setup lighting
	GltLight light0(GL_LIGHT0);
	light0.ambient()  = blue;
	light0.specular() = green;
	light0.specular() = GltColor(0.5f, 0.5f, 0.5f, 0.2f);
	light0.position() = Vector(1.5f, 4.0f, 8.0f);
	light0.enabled() = true;
	light0.set();
	// Setup lighting
#ifdef _DEBUG
	cout << "OpenGL Initialized" << endl;
#endif //_DEBUG
	return;
}

bool GlutMain(const std::vector<std::string> &arg)
{
	GlutWindow *main = new myPhysX(640,480,100,100);
	main->open();
	cout << "===Viewport Navigation (Maya Style)===" <<endl;
	cout << "Rotate: Right Drag" << endl;
	cout << "Move: Cener Drag" << endl;
	cout << "Zoom: Right and Center Drag" << endl;
	cout << "===Simulation Navigation===" << endl;
	cout << "Simulation ON/OFF: Space Key" << endl;
	return true;
}