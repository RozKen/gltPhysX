/***********************************************
gltPhysXActor.hpp
@author - Kenichi Yorozu
@email - rozken@gmail.com
@website - http://rozken.homelinux.net/
@description - This class provides Physical Actor for gltPhysX with PhysX
@STATUS - first commit
@TODO - 
@project_descrition - This Project is Creating a Object-Oriented Physics-Based
Simulation Circumstance using Nvidia PhysX with OpenGL Toolkit (GLT).
@notice - Sourcefiles on this repository is provided as-is and no guarentee 
or warrenty is provided for any damage that may arise from using it. 
This code is free for your own use, the only thing I ask is a small 
credit somewhere for my work. An e-mail saying you found it useful 
would also be much appreciated by myself.
@License - GNU Lesser General Public Lisense (GLT require this Lisense)
 ***********************************************/
#ifndef __gltPhysXActor_hpp__
#define __gltPhysXActor_hpp__

#include <NxPhysics.h>
#include <node/shape.h>

class gltPhysXActor;
typedef ReferenceCountPtr<gltPhysXActor>	gltPhysXActorPtr;

class gltPhysXActor : public GltShape {
public:
	gltPhysXActor(NxScene* pScene);
	virtual ~gltPhysXActor();

	virtual void draw() const = 0;

protected:
	virtual void Create() = 0;
	bool			_isStatic;		//Is this Object Static (true) / Dynamic (false) ?
	NxActor*		_pActor;		//Ponter to Actor
	NxVec3			_position;		//Initial Position of the Object

	NxScene*		_pScene;		//Pointer to the Scene
};

inline gltPhysXActor::gltPhysXActor(NxScene* pScene)
	: _pScene(pScene), _isStatic(true), _position(NxVec3(0, 5, 0)){
}

inline gltPhysXActor::~gltPhysXActor(){
}

#endif //__gltPhysXActor_hpp__