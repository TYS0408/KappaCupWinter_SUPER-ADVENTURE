#include "stdafx.h"
#include "AppearStage.h"
AppearStage::AppearStage()
{

}


AppearStage::~AppearStage()
{

}


bool AppearStage::Start()
{

	m_position = Vector3(0.0f, 3.0f, 350.0f);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Init("Assets/Stage/Kill_Stage.tkm");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
	return true;
}



void AppearStage::Update()
{

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void AppearStage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

