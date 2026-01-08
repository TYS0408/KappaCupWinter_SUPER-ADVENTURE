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
	//èâä˙íl
	m_position = Vector3(0.0f, -50.0f, 440.0f);
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

