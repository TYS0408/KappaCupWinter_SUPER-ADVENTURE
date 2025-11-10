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
	m_StagePos = Vector3(650.0f, 300.0f, 1750.0f);
	m_StagemodelRender.SetPosition(m_StagePos);
	m_StagemodelRender.Update();
	m_StagephysicsStaticObject.CreateFromModel(m_StagemodelRender.GetModel(), m_StagemodelRender.GetModel().GetWorldMatrix());

	//クリボー&ノコノコステージ
	m_Stage2modelRender.Init("Assets/Stage/Stage_Object_floor2.tkm");
	m_Stage2modelRender.SetScale(SCALE);
	m_Stage2Pos = Vector3(-650.0f, 300.0f, 1750.0f);
	m_Stage2modelRender.SetPosition(m_Stage2Pos);
	m_Stage2modelRender.Update();
	m_Stage2physicsStaticObject.CreateFromModel(m_Stage2modelRender.GetModel(), m_Stage2modelRender.GetModel().GetWorldMatrix());

	//橋のオブジェクト
	m_BrigemodelRender.Init("Assets/Stage/Stage_Object_Brige.tkm");
	m_BrigemodelRender.SetScale(SCALE);
	m_BrigePos = Vector3(0.0f, 180.0f, 1900.0f);
	m_BrigemodelRender.SetPosition(m_BrigePos);
	m_BrigemodelRender.Update();
	m_BrigephysicsStaticObject.CreateFromModel(m_BrigemodelRender.GetModel(), m_BrigemodelRender.GetModel().GetWorldMatrix());
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
	m_Stage2modelRender.Draw(rc);
	m_BrigemodelRender.Draw(rc);
}
