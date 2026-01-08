#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
bool Title::Start()
{
	//画像を読み込む。
	spriteRender.Init("Assets/Sprite/Title3.dds", 1920.0f, 1080.0f);
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		NewGO<Game>(0, "game");
		g_soundEngine->ResistWaveFileBank(7, "Assets/BGM・SE/Start.wav");


		//SoundSourceのインスタンスを作成する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(7);

		//効果音はループさせないので、falseにする。
		se->Play(false);
		//音量を上げる。
		se->SetVolume(3.5f);
		DeleteGO(this);

	}
}


void Title::Render(RenderContext& rc)
{
	//画像を描画する。
	spriteRender.Draw(rc);
}