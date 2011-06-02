#include "gltPhysX.hpp"
#include "gltPhysXActor.hpp"
#include "ActorGroundPlane.h"	//Ç≈Ç´ÇÍÇŒÇ±Ç±Ç…íuÇ´ÇΩÇ≠Ç»Ç¢Åc

void gltPhysX::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);		//îwåiêFÇê›íË

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//Render All Objects
	for( int i = 0;i < _actors.size(); i++){
		_actors[i]->draw();
	}
	//Render Ground Plane
	//if(_isShowGroundPlane){
	//	
	//}
}

void gltPhysX::OnTick()
{
	//begin Loop{
	/*if (!mousePressed() && !_isSimulate){
		_viewMatrix = matrixRotate(Vector1,0.2)*_viewMatrix;
	}*/
	if(_isSimulate){
		_pScene->simulate(1.0f/(float)_fps);
	}
	//Write Calculation

	//Render the scene
	postRedisplay();

	if(_isSimulate){
		_pScene->flushStream();
		_pScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	//} //end Loop
}

void gltPhysX::OnKeyboard(unsigned char key, int x, int y)
{
	bool draw = true;

	gltPhysXActor* newActor = NULL;
	//GltShape *newShape = NULL;
	switch (key){
	case '1':					//Press '1'
		//newShape = new GlutSphere(false);
		break;
	case '2':					//Press '2'
		//newShape = new GlutCube(false);
		break;
	case '0':					//Press '0'
		_actors.clear();	//Clear All Objects
		break;
	case 'f':
		newActor = new ActorGroundPlane(_pScene);
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
	if (newActor)
	{
		_actors.push_back(newActor);
	}
	
	//Cnofigure Each Object;
	GltShape* tmp;
	for(int i = 0; i < _actors.size(); i++){
		tmp = _actors[i];
		tmp->color() = green;
		//tmp->solid() = true;
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
		_pPhysicsSDK->release();	//Release PhysicsSDK Object
	}
	
	if(!_actors.empty()){
		_actors.clear();		//Release Shape Array
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