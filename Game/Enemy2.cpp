#include "stdafx.h"
#include "Enemy2.h"

Enemy2::Enemy2()
{
	//大きさ調整
	m_modelRender.SetScale(Vector3::One * 2.0f);

	//スフィアコライダーを初期化
	m_sphereColider.Create(1.0f);

	m_modelRender.Init("Assets/Stage/Enemy2_Model.tkm");
	
}

Enemy2::~Enemy2()
{

}

bool Enemy2:: Start()
{
	return true;
}


void Enemy2::Update()
{
	m_modelRender.Update();
}


void Enemy2::Render(RenderContext & rc)
{ 
	m_modelRender.Draw(rc);
}