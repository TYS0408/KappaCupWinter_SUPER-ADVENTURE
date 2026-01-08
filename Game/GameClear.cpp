#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include"BossStage.h"
#include"Game.h"

GameClear::GameClear()
{
	m_gameClearSpriteRender.Init("Assets/Sprite/GameClear.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}




void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		Game* game = FindGO<Game>("game");
		if (game)
		{
			DeleteGO(game);
		}
		//ゲームクリアするとBossStage作る
		NewGO<BossStage>(0, "bossStage");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_gameClearSpriteRender.Draw(rc);
}