#include "stdafx.h"
#include "BackGround.h"


namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
	Vector3 FLOORSCALE = Vector3(20.0f, 4.0f, 3.0f);
}
BackGround::BackGround()
{
	
    //初期リス
	m_modelRender.Init("Assets/Stage/Demo_Stage.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//クリボーステージ
	m_DemoStagemodelRender.Init("Assets/Stage/Demo_Stage2.tkm");
	m_DemoStagemodelRender.SetScale(SCALE);
	m_DemoPos = Vector3(0.0f, 180.0f, 870.0f);
	m_DemoStagemodelRender.SetPosition(m_DemoPos);
	m_DemoStagemodelRender.Update();
	m_DemophysicsStaticObject.CreateFromModel(m_DemoStagemodelRender.GetModel(),m_DemoStagemodelRender.GetModel().GetWorldMatrix());

	//ノコノコステージ
	m_StagemodelRender.Init("Assets/Stage/Stage_Object_floor2.tkm");
	m_StagemodelRender.SetScale(SCALE);
	m_StagePos = Vector3(400.0f, 300.0f, 1750.0f);
	m_StagemodelRender.SetPosition(m_StagePos);
	m_StagemodelRender.Update();
	m_StagephysicsStaticObject.CreateFromModel(m_StagemodelRender.GetModel(), m_StagemodelRender.GetModel().GetWorldMatrix());

	//当たり判定描画
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}


void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_DemoStagemodelRender.Draw(rc);
	m_StagemodelRender.Draw(rc);
}
