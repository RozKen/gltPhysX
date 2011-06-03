#include "ActorSphere.h"
#include <GL/glut.h>

void ActorSphere::Create(){

	NxActorDesc			actorDesc;		///actor Descriptor with Collection of Shapes.
	NxBodyDesc			bodyDesc;		///Body Physical Descriptor
	NxSphereShapeDesc	sphereDesc;		///Sphere Shape Descriptor

	//�f�t�H���g�l�ŏ����� (�N���A)
	actorDesc.setToDefault();
	bodyDesc.setToDefault();
	sphereDesc.setToDefault();
	//bodyDesc.angularDamping = 0.5f;	//�]���薀�C�W��

	sphereDesc.radius = _radius;									//���̔��a���w��
	actorDesc.shapes.pushBack(&sphereDesc);	//�����A�N�^�[�ɒǉ�
	actorDesc.body = &bodyDesc;	//���I�����w��
	actorDesc.density = 1.0f;//7874.0f;		//���x7874 kg/m^3 : �S�̖��x
	actorDesc.globalPose.t = _initPosition;	//Scene��̈ʒu
	//Set userData to NULL if you are not doing anyting with it.
	_pActor = _pScene->createActor( actorDesc );
	return;
}

void ActorSphere::draw() const{
	float glMat[16];
	glPushMatrix();
	{
		_pActor->getGlobalPose().getColumnMajor44(glMat);
		glMultMatrixf(glMat);
		glutSolidSphere(_radius, 16, 8);
	}
	glPopMatrix();
	return;
}