#pragma once
class Game;
class GameOver : public IGameObject
{
public:
	GameOver();

	~GameOver();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;

	bool isDeleteRequested = false;//削除要求フラグ

	Game* m_game = nullptr;
};

