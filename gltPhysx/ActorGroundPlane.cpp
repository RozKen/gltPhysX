#include "ActorGroundPlane.h"

void ActorGroundPlane::Create(){

	NxActorDesc	actorDesc;			///actor Descriptor with Collection of Shapes.
	NxPlaneShapeDesc	planeDesc;	///Plane Shape Descriptor
	
	//•½–Ê•û’ö®: ax + by + cz + d = 0;
	planeDesc.normal = NxVec3(0, 1, 0);		//–Ê‚Ì–@ü‚ÍY²(ª)•ûŒü
	planeDesc.d = 0.0f;								//Y = 0.0f‚É–Ê‚ğì‚é

	actorDesc.shapes.pushBack( &planeDesc );	//Actor‚ÉPlane‚ğ“o˜^

	//NxScene Creates Actor and Returns a Pointer.
	_pActor = _pScene->createActor( actorDesc);
	_pActor->userData = NULL;		//PhysXã‚ÌActor‚Æ(ƒQ[ƒ€‚È‚Ç‚Ì)ƒf[ƒ^ã‚ÌActor‚ğŒ‹‚Ñ‚Â‚¯‚é
		
	//Set the parameters for the Default Material
	//Physics‚Ì"Material"‚Æ‚Í–Ú‚ÉŒ©‚¦‚é•\–ÊŞ¿‚Å‚Í‚È‚­C•¨‘Ì‚Ì•¨—Šw“I“Á’¥‚ğ•\‚·
	NxMaterial* defaultMaterial = _pScene->getMaterialFromIndex( 0 );
	defaultMaterial->setRestitution( 0.3f );			//”½”­ŒW”
	defaultMaterial->setStaticFriction( 0.5f );		//Ã~–€CŒW”
	defaultMaterial->setDynamicFriction( 0.5f );	//“®–€CŒW”
}

void ActorGroundPlane::draw() const{
	glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		for(int i=-_numGridLine;i<=_numGridLine;i++) {
			//Lines Parallel to Z Axis
			glVertex3f(i*_scaleGridLine, (GLfloat)_yGround, -_numGridLine * _scaleGridLine);
			glVertex3f(i*_scaleGridLine, (GLfloat)_yGround, _numGridLine * _scaleGridLine);
			//Lines Prallel to X Axis
			glVertex3f(_numGridLine * _scaleGridLine, (GLfloat)_yGround, i*_scaleGridLine);
			glVertex3f(-_numGridLine * _scaleGridLine, (GLfloat)_yGround, i*_scaleGridLine);
		}
	glEnd();
	glEnable(GL_LIGHTING);
}