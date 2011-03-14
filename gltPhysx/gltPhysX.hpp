/***********************************************
 * gltPhysX.hpp
 * @author - Kenichi Yorozu
 * @email - rozken@gmail.com
 * @website - http://rozken.homelinux.net/
 * @description - This is an Physics-Based Simulation Circumstance
 * by using PhysX and OpenGL Toolkit.
 * @STATUS - Just Integrated OpenGL Toolkit and PhysX.
 * However initialization and termination are the only implemented PhysX features.
 * @TODO - For visual and physical object integration, I have to create
 * new Shape class inheriting GltShape.
 * @descrition - This Project is Creating a Object-Oriented Physics-Based
 * Simulation Circumstance using Nvidia PhysX with OpenGL Toolkit (GLT).
 * @notice - Sourcefiles on this repository is provided as-is and no guarentee 
 * or warrenty is provided for any damage that may arise from using it. 
 * This code is free for your own use, the only thing I ask is a small 
 * credit somewhere for my work. An e-mail saying you found it useful 
 * would also be much appreciated by myself.
 ***********************************************/
#ifndef __GLTPHYSX_HPP__ //Avoiding Corruption of Including
#define __GLTPHYSX_HPP__

#include <glutm/winexam.h>		//OpenGL Window
#include <glutm/shape.h>			//GLUT Geometric Object Classes
#include <glt/light.h>					//Enable Light Source
#include <NxPhysics.h>				//PhysX
#include <glt/rgb.h>					//use color name e.g. blue red
#include <iostream>					//use console/file inputs/outputs
#include <vector>						//use dynamic array

using namespace std;

class GltShape;

class gltPhysX : public GlutWindowExaminer
{
public:
	gltPhysX(		
		int width                = widthDefault, 
		int height               = heightDefault,
		int x                    = xDefault, 
		int y                    = yDefault,
		int fps					= 60,
		bool isSimulate		= true
	);
   ~gltPhysX();

   void OnOpen();
   void OnClose();
   void OnDisplay();
   void OnTick();
   void OnKeyboard(unsigned char key, int x, int y);

protected:
	bool InitNx();						//Initialize PhysX
	bool InitNxScene();				//Initialize PhysX Scene
	void CleanUpNx();				//Terminate PhysX
	void myGLInit();					//Initialize OpenGL

	//auto_ptr<GltShape>  _shape;
	//Shape List
	vector<GltShape*> _shape;

	//Viewport Ground
	bool _isShowGroundPlane;	//Flag to switch Ground Plane Display ON/OFF
	int _yGround;			//Ground Level y
	int _numGridLine;			//Half Number of Grid Lines
	float _scaleGridLine;		//Scale of Grid Lines

	int		_fps;							//frame per second : Simulation Time
	bool	_isSimulate;				//Flag to switch Simulation ON/OFF
	NxPhysicsSDK* _pPhysicsSDK;	//PhysX
	NxScene* _pScene;			//PhysX Scene
	NxVec3 _DefaultGravity;	//Gravity
};

gltPhysX::gltPhysX(int width,int height,int x,int y, int fps, bool isSimulate)
: GlutWindowExaminer("gltPhysX",width,height,x,y),_fps(fps)
	,_isSimulate(isSimulate),_DefaultGravity(0, -9.8, 0),_yGround(0)
	,_numGridLine(10),_scaleGridLine(0.2f),_isShowGroundPlane(true)
{
	InitNx();
	InitNxScene();
	//myGLInit();			//ここに置くと"light0.set()"がエラーになる．なぜだか．
}

gltPhysX::~gltPhysX()
{
	CleanUpNx();
}

void
gltPhysX::OnOpen()
{
	_viewMatrix = matrixRotate(Vector1,60.0)*_viewMatrix;
	
	myGLInit();
	
	OnKeyboard('1',0,0);	// Select sphere to start with
	setTick(1000/_fps);		// 60fps maximum
}

void
gltPhysX::OnClose()
{
}

void gltPhysX::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3, 0.3, 0.3, 1.0);		//背景色を設定

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//Render All Objects
	for( int i = 0;i < _shape.size(); i++){
		_shape[i]->draw();
	}
	//Render Ground Plane
	if(_isShowGroundPlane){
		glBegin(GL_LINES);
			for(int i=-_numGridLine;i<=_numGridLine;i++) {
				//Lines Parallel to Z Axis
				glVertex3f(i*_scaleGridLine, _yGround, -_numGridLine * _scaleGridLine);
				glVertex3f(i*_scaleGridLine, _yGround, _numGridLine * _scaleGridLine);
				//Lines Prallel to X Axis
				glVertex3f(_numGridLine * _scaleGridLine, _yGround, i*_scaleGridLine);
				glVertex3f(-_numGridLine * _scaleGridLine, _yGround, i*_scaleGridLine);
			}
		glEnd();
	}
}

void gltPhysX::OnTick()
{
	if (!mousePressed() && !_isSimulate){
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

void gltPhysX::OnKeyboard(unsigned char key, int x, int y)
{
	bool draw = true;

	GltShape *newShape = NULL;
	switch (key){
	case '1':					//Press '1'
		newShape = new GlutSphere(false);
		break;
	case '2':					//Press '2'
		newShape = new GlutCube(false);
		break;
	case '0':					//Press '0'
		_shape.clear();	//Clear All Objects
		break;
	case 'g':					//Press 'g'
		_isShowGroundPlane = !_isShowGroundPlane;	//Switch Display Flag State
		break;
	case 27:				//Press 'ESC'
		exit(0);				//Terminate Program
		break;
	case 32:				//Press Space Key
		_isSimulate = !_isSimulate;	//Switch Simulation Flag State
		break;
	default:
		GlutWindow::OnKeyboard(key, x, y);
		draw = false;
		break;
	}
	
	//Add Objects to Shape Array
	if (newShape)
	{
		_shape.push_back(newShape);
	}
	
	//Cnfigure Each Object;
	GltShape* tmp;
	for(int i = 0; i < _shape.size(); i++){
		tmp = _shape[i];
		tmp->color() = green;
		//tmp->solid() = false;
	}

	if(draw){
		_viewMatrixInverse = _viewMatrix.inverse();
		postRedisplay();
		OnOrient(_viewMatrix,_viewMatrixInverse);
	}
}
	/**
	 *	InitNx() : Initialize PhysX
	 *	@return bool - whether Physics SDK Initialization has done or not.
	 */
bool gltPhysX::InitNx()
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
bool gltPhysX::InitNxScene(){
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
void gltPhysX::CleanUpNx(){
	if(_pPhysicsSDK != NULL){
		if( _pScene != NULL ){
			_pPhysicsSDK->releaseScene(*_pScene);
			_pScene = NULL;	//Release Scene Object
		}
		NxReleasePhysicsSDK( _pPhysicsSDK );
		_pPhysicsSDK = NULL;	//Release PhysicsSDK Object
	}
	
	if(!_shape.empty()){
		_shape.clear();		//Release Shape Array
	}
#ifdef _DEBUG
		std::cout << "Clean Up Ended." << std::endl;
#endif //_DEBUG
}
	/**
	 * myGLInit() : Initialize OpenGL
	 * @description - Initialize OpenGL
	 */
void gltPhysX::myGLInit(){
	// Setup default render states
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

	// Setup Lighting
	GltLight light0(GL_LIGHT0);
	light0.ambient()  = blue;
	light0.specular() = green;
	light0.specular() = GltColor(0.5f, 0.5f, 0.5f, 0.2f);
	light0.position() = Vector(1.5f, 4.0f, 8.0f);
	light0.enabled() = true;
	light0.set();

#ifdef _DEBUG
	cout << "OpenGL Initialized" << endl;
#endif //_DEBUG
	return;
}

#endif //__GLTPHYSX__ //Avoiding Corruption of Including
