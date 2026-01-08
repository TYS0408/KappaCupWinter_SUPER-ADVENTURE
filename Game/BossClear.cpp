#include "stdafx.h"
#include "BossClear.h"
#include"BossStage.h"
#include"Title.h"
#include"sound/SoundEngine.h"
BossClear::BossClear()
{
	m_BossClearSpriteRender.Init("Assets/Sprite/BossClear.dds",1920.0f,1080.0f);
	
}

BossClear::~BossClear()
{

}


void BossClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		BossStage* bossStage = FindGO<BossStage>("bossstage");
		if (bossStage)
		{
			DeleteGO(bossStage);
		}
		
		//g_soundEngine->ResistWaveFileBank(9, "Assets/BGM・SE/GameClear.wav");


		//ボスクリア画面を出すとタイトルに移行
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}


void BossClear::Render(RenderContext& rc)
{
	m_BossClearSpriteRender.Draw(rc);
}
