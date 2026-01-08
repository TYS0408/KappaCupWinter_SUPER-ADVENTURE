#include "stdafx.h"
#include "BackGround.h"


namespace
{
	Vector3 SCALE = Vector3(3.0f, 4.0f, 3.0f);
}
BackGround::BackGround()
{
	
    //初期リス
	m_modelRender.Init("Assets/Stage/Stage.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//当たり判定描画
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}


void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
	
