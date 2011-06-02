/***********************************************
gltPhysX.hpp
@author - Kenichi Yorozu
@email - rozken@gmail.com
@website - http://rozken.homelinux.net/
@description - This is an Physics-Based Simulation Circumstance
by using PhysX and OpenGL Toolkit.
@STATUS - Just Integrated OpenGL Toolkit and PhysX.
However initialization and termination are the only implemented PhysX features.
@TODO - For visual and physical object integration, I have to create
new Shape class inheriting GltShape.
@project_descrition - This Project is Creating a Object-Oriented Physics-Based
Simulation Circumstance using Nvidia PhysX with OpenGL Toolkit (GLT).
@notice - Sourcefiles on this repository is provided as-is and no guarentee 
or warrenty is provided for any damage that may arise from using it. 
This code is free for your own use, the only thing I ask is a small 
credit somewhere for my work. An e-mail saying you found it useful 
would also be much appreciated by myself.
@License - GNU Lesser General Public Lisense (GLT require this Lisense)
 ***********************************************/
#ifndef __gltPhysX_hpp__ //Avoiding Corruption of Including
#define __gltPhysX_hpp__

#include <glutm/winexam.h>		//OpenGL Window
#include <glutm/shape.h>		//GLUT Geometric Object Classes
#include <glt/light.h>			//Enable Light Source
#include <NxPhysics.h>			//PhysX
#include <glt/rgb.h>			//use color name e.g. blue red
#include <iostream>				//use console/file inputs/outputs
#include <vector>				//use dynamic array

using namespace std;

class gltPhysXActor;

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
	//vector<GltShape*> _shape;
	vector<gltPhysXActor*> _actors;

	//Viewport Ground
	bool _isShowGroundPlane;	//Flag to switch Ground Plane Display ON/OFF
	

	int		_fps;				//frame per second : Simulation Time
	bool	_isSimulate;		//Flag to switch Simulation ON/OFF
	NxPhysicsSDK* _pPhysicsSDK;	//PhysX
	NxScene* _pScene;			//PhysX Scene
	NxVec3 _DefaultGravity;		//Gravity
};

inline gltPhysX::gltPhysX(int width,int height,int x,int y, int fps, bool isSimulate)
: GlutWindowExaminer("gltPhysX",width,height,x,y),_fps(fps)
	,_isSimulate(isSimulate),_DefaultGravity(0, -9.8, 0),_isShowGroundPlane(true)
{
	InitNx();
	InitNxScene();
	//myGLInit();			//ここに置くと"light0.set()"がエラーになる．なぜだか．
}

inline gltPhysX::~gltPhysX()
{
	CleanUpNx();
}

inline void
gltPhysX::OnOpen()
{
	_viewMatrix = matrixRotate(VectorY, 60.0)*matrixRotate(VectorX,-30.0)*_viewMatrix;
	
	myGLInit();
	
	//OnKeyboard('1',0,0);	// Select sphere to start with
	setTick(1000/_fps);		// 60fps maximum
}

inline void
gltPhysX::OnClose()
{
}

#endif //__GLTPHYSX__ //Avoiding Corruption of Including
