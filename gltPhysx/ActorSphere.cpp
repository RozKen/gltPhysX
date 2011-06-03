#include "ActorSphere.h"
#include <GL/glut.h>

void ActorSphere::Create(){

	NxActorDesc			actorDesc;		///actor Descriptor with Collection of Shapes.
	NxBodyDesc			bodyDesc;		///Body Physical Descriptor
	NxSphereShapeDesc	sphereDesc;		///Sphere Shape Descriptor

	//デフォルト値で初期化 (クリア)
	actorDesc.setToDefault();
	bodyDesc.setToDefault();
	sphereDesc.setToDefault();
	//bodyDesc.angularDamping = 0.5f;	//転がり摩擦係数

	sphereDesc.radius = _radius;									//球の半径を指定
	actorDesc.shapes.pushBack(&sphereDesc);	//球をアクターに追加
	actorDesc.body = &bodyDesc;	//動的情報を指定
	actorDesc.density = 1.0f;//7874.0f;		//密度7874 kg/m^3 : 鉄の密度
	actorDesc.globalPose.t = _initPosition;	//Scene上の位置
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