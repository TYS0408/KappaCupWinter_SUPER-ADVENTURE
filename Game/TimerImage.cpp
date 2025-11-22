#include "stdafx.h"
#include "TimerImage.h"


TimerImage::TimerImage()
{
	m_position = Vector3(750.0f, 490.0f, 0.0f);
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Init("Assets/Sprite/Image.dds",130.0f,130.0f);
}

TimerImage::~TimerImage()
{

}

bool TimerImage::Start()
{
	
	return true;
}

void TimerImage::Update()
{



	m_spriteRender.Update();
}


void TimerImage::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}