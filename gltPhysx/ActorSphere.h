#ifndef ActorSphere_H_
#define ActorSphere_H_

#include "gltPhysXActor.hpp"

class ActorSphere : public gltPhysXActor{
public:
	ActorSphere(NxScene* pScene, float radius, NxVec3 initialPosition);
	//~ActorSphere();

	void draw() const;
protected:
	void Create();

	float	_radius;		///Radius of Sphere
	NxVec3	_initPosition;	///Initial Position
};
inline ActorSphere::ActorSphere(NxScene* pScene, float radius, NxVec3 initialPosition)
	: gltPhysXActor(pScene), _radius(radius), _initPosition(initialPosition){
	Create();
}
//inline ActorSphere::~ActorSphere(){
//	this->~gltPhysXActor();
//}

#endif	//ActorSphere_H_