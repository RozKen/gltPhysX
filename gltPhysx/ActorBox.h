#ifndef ActorBox_H_
#define ActorBox_H_

#include "gltPhysXActor.hpp"

class ActorBox : public gltPhysXActor{
public:
	ActorBox(NxScene* pScene, NxVec3 initialPosition, NxVec3 dimensions);
	//~ActorBox();

	void draw() const;
protected:
	void Create();

	NxVec3	_dimensions;			///Dimensions of Box (w, d, h)
	NxVec3	_initPosition;		///Initial Position

};
inline ActorBox::ActorBox(NxScene* pScene, NxVec3 initialPosition, NxVec3 dimensions)
	: gltPhysXActor(pScene), _initPosition(initialPosition), _dimensions(dimensions){
	Create();
}
//inline ActorBox::~ActorBox(){
//	this->~gltPhysXActor();
//}

#endif	//ActorBox_H_