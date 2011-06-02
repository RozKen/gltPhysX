#ifndef ActorGoundPlane_H_
#define ActorGoundPlane_H_

#include "gltPhysXActor.hpp"

class ActorGroundPlane : public gltPhysXActor{
public:
	ActorGroundPlane(NxScene* pScene);
	//~ActorGroundPlane();

	void draw() const;
protected:
	void Create();

	int		_yGround;			//Ground Level y
	int		_numGridLine;		//Half Number of Grid Lines
	float	_scaleGridLine;		//Scale of Grid Lines
};
inline ActorGroundPlane::ActorGroundPlane(NxScene* pScene)
	: gltPhysXActor(pScene), _yGround(0), _numGridLine(10), _scaleGridLine(0.2f){
}
//inline ActorGroundPlane::~ActorGroundPlane(){
//	this->~gltPhysXActor();
//}

#endif	//ActorGoundPlane_H_