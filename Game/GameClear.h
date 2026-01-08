#pragma once
class GameClear :public IGameObject
{
public:
	GameClear();

	~GameClear();

	//bool Start();
	void Update();

	void Render(RenderContext& rc);
		//メンバ変数
	bool isDeleteRequested = false;//削除要求フラグ
	private:
		SpriteRender m_gameClearSpriteRender;//スプライトレンダー
		
	
};

