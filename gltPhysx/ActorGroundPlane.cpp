#include "ActorGroundPlane.h"

void ActorGroundPlane::Create(){

	NxActorDesc	actorDesc;			///actor Descriptor with Collection of Shapes.
	NxPlaneShapeDesc	planeDesc;	///Plane Shape Descriptor
	
	//���ʕ�����: ax + by + cz + d = 0;
	planeDesc.normal = NxVec3(0, 1, 0);		//�ʂ̖@����Y��(��)����
	planeDesc.d = 0.0f;								//Y = 0.0f�ɖʂ����

	actorDesc.shapes.pushBack( &planeDesc );	//Actor��Plane��o�^

	//NxScene Creates Actor and Returns a Pointer.
	_pActor = _pScene->createActor( actorDesc);
	_pActor->userData = NULL;		//PhysX���Actor��(�Q�[���Ȃǂ�)�f�[�^���Actor�����т���
		
	//Set the parameters for the Default Material
	//Physics��"Material"�Ƃ͖ڂɌ�����\�ʍގ��ł͂Ȃ��C���̂̕����w�I������\��
	NxMaterial* defaultMaterial = _pScene->getMaterialFromIndex( 0 );
	defaultMaterial->setRestitution( 0.3f );			//�����W��
	defaultMaterial->setStaticFriction( 0.5f );		//�Î~���C�W��
	defaultMaterial->setDynamicFriction( 0.5f );	//�����C�W��
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