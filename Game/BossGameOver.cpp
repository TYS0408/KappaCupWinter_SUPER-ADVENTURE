#include "stdafx.h"
#include "BossGameOver.h"
#include"BossStage.h"

BossGameOver::BossGameOver()
{

}

BossGameOver::~BossGameOver()
{

}

bool BossGameOver::Start()
{
	//画像読み込み
	m_spriteRender.Init("Assets/Sprite/GameOver2.dds", 1920.0f, 1080.0f);
	return true;
}

void BossGameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		////ボスステージをを削除
		//BossStage* bossStage = FindGO<BossStage>("bossstage");
		//if (bossStage)
		//{
		//	bossStage->RequestRestart();
		//}

		//新しいボスステージを生成
		NewGO<BossStage>(0, "bossstage");
		DeleteGO(this);
	}

	////削除リクエストが来ている場合に、このオブジェクト自身を削除する
	//if (isDeleteRequest == true)
	//{
	//	DeleteGO(this);
	//	return;
	//}
}




void BossGameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}