#pragma once
class TimerImage :public IGameObject
{
public:

	TimerImage();

	~TimerImage();

	bool Start();

	void Update();

	void Render(RenderContext & rc);


private:

	SpriteRender m_spriteRender;
	Vector3 m_position;
};

