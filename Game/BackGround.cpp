#include "stdafx.h"
#include "BackGround.h"


namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
}
BackGround::BackGround()
{
	
    //‰ŠúƒŠƒX
	m_modelRender.Init("Assets/Stage/Stage_First.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());


	//“–‚½‚è”»’è•`‰æ
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}


void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
	
