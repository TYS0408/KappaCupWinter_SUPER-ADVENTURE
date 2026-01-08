#pragma once
#include"sound/SoundEngine.h"
class BossClear :public IGameObject
{
public:
	BossClear();

	~BossClear();

	//bool Start();
	void Update();

	void Render(RenderContext& rc);
	SoundSource* bgm;
	//メンバ変数
	bool isDeleteRequest = false;//削除要求フラグ
private:
	SpriteRender m_BossClearSpriteRender;//スプライトレンダー

};

