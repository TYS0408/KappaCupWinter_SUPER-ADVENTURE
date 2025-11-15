#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
GameClear::GameClear()
{
	m_gameClearSpriteRender.Init("Assets/Suprite/GameClear.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトルのオブジェクトを作る
		NewGO<Title>(0, "Title");
		isDeleteRequested = true;
	}
	//削除リクエストが来ている場合に、このオブジェクト自身を削除する
	if (isDeleteRequested == true)//このオブジェクトが削除を要求されたかどうか」を判定し、削除を実行する処理
	{
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_gameClearSpriteRender.Draw(rc);
}