#pragma once
class BossStage;
class BossGameOver: public IGameObject
{
public:
	BossGameOver();

	~BossGameOver();

	bool Start();

	void Update();


	
	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;

	bool isDeleteRequest = false;//削除要求フラグ

	BossStage* m_bossStage = nullptr;
};

