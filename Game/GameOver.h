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

	bool isDeleteRequest = false;//íœ—v‹ƒtƒ‰ƒO

	Game* m_game = nullptr;
};

