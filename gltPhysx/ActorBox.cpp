#include "ActorBox.h"
#include <GL/glut.h>

/*
 Create a Box Actor
 Dynamic Actor: Rigid Bodies
 */
void ActorBox::Create(){
	//Create a Body Descriptor
	NxBodyDesc bodyDesc;					//Box—p Body Descriptor
	bodyDesc.angularDamping = 0.5f;	//‰ñ“]Œ¸ŠŒW”????
	//bodyDesc.linearVelocity = NxVec3 (-30, -10, -10); //‰Šú‘¬“x‚ÍXŽ²•ûŒü‚É1
		
	//The Actor Descriptor
	NxActorDesc actorDesc;
	actorDesc.body = &bodyDesc;
		
	//Box Shape Descriptor
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = _dimensions;	//20.0 x 20.0 x 20.0‚Ì’¼•û‘Ì
	actorDesc.shapes.pushBack( &boxDesc );	//Actor‚ÉBody‚ð“o˜^
	actorDesc.density = 1.0f;	//–§“x1.0
	actorDesc.globalPose.t = _initPosition;		//‰ŠúˆÊ’u(10.0, 10.0, 10.0)
		
	//Set userData to NULL if you are not doing anyting with it.
	_pActor = _pScene->createActor( actorDesc );
	_pActor->userData = (void *)size_t((int)2);
	return;
}

void ActorBox::draw() const{
	float glMat[16];
	glPushMatrix();
	{
		_pActor->getGlobalPose().getColumnMajor44(glMat);
		glMultMatrixf(glMat);
		glutSolidCube( _dimensions.x * 2.0 );
	}
	glPopMatrix();
	return;
}