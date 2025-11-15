#pragma once
class Title :public IGameObject
{
public:
	Title() {};
	~Title() {};

	bool Start();
	void Update();
	//描画関数
	void Render(RenderContext& rc);
	//スプライトレンダー。
	SpriteRender spriteRender;

};

