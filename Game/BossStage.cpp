#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"
#include "Enemy3.h"
#include"GameCamera.h"
#include"BossClear.h"
#include"game.h"
#include"BossGameOver.h"
#include"TimerImage.h"
#include"sound/SoundEngine.h"

namespace
{
	const int hpPos = 3;

	//赤いハートの座標
	Vector3 m_RedHealthPos[hpPos] =
	{
		{-800.0f, 500.0f, 0.0f,},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f,}
	};
	//黒いハートの座標
	Vector3 m_BlackHealthPos[hpPos] =
	{
		{-800.0f, 500.0f, 0.0f},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f}
	};

	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
}
BossStage::BossStage()
{

}

BossStage::~BossStage()
{
	/*if (m_player->m_HP <= 0 || m_LimitTime <= 0)
	{
		DeleteGO(m_gameCamera);
		m_gameCamera = nullptr;
	}
	if (m_player)
	{
		DeleteGO(m_player);
		m_player = nullptr;
	}

	if (m_enemy3)
	{
		DeleteGO(m_enemy3);
		m_enemy3 = nullptr;
	}*/
}

bool BossStage::Start()
{

	g_soundEngine->ResistWaveFileBank(8, "Assets/BGM・SE/BossBGM.wav");

	//SoundSourceのオブジェクトを作成する。
	bgm = NewGO<SoundSource>(0);

	//WaveFileBankから登録されたwaveファイルのデータ（0番）を持ってくる。
	bgm->Init(8);

	//trueにすると、音がループする。
	bgm->Play(true);
	 m_player = NewGO<Player>(0, "player");

	 m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	 //m_player = FindGO<Player>("player");
	 if (m_player != nullptr)
	 {
		 Vector3 Pos = Vector3(0.0f, 0.0f, 0.0f);
		 m_player->SetPosition(Pos);

		 m_player->m_moveSpeed = Vector3::Zero;
		 m_player->m_isKnockBack = false;
		 m_player->m_knockBackTime = 0.0f;
		 //m_player->m_position = Pos;
	 }


	 //HPのUIをfor文で追加
	 for (int i = 0; i < 3; i++)
	 {

		 m_RedHeartRender[i].Init("Assets/Sprite/Heart.dds", 100.0f, 100.0f);
		 m_BlackHeartRender[i].Init("Assets/Sprite/BlackHeart3.dds", 100.0f, 100.0f);

	 }
	 m_enemy3 = NewGO<Enemy3>(0, "enemy3");

	m_modelRender.Init("Assets/Stage/BossStage2.tkm");
	m_modelRender.SetScale(SCALE);
	m_position = Vector3(0.0f, 0.0f, 0.0f);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}


void BossStage::Update()
{
	if (m_isClear)
	{
		return;
	}
	


	//ボスが倒されたらゲームクリアを生成
	if (m_enemy3 != nullptr && m_enemy3->IsDeathAnimationFinish)
	{
		OnGameClear();
		return;
	}

	//Hpが0、制限時間が0以下ならゲームオーバーを生成
	if (m_player->m_HP <= 0||m_LimitTime<=0)
	{
		RequestRestart();
		return;
		
	}
	HPDraw();

	TimerDraw();

	for (int i = 0; i < 3; i++)
	{
		m_RedHeartRender[i].SetPosition(m_RedHealthPos[i]);

		m_RedHeartRender[i].Update();
	}



	for (int i = 0; i < 3; i++)
	{
		m_BlackHeartRender[i].SetPosition(m_BlackHealthPos[i]);
		m_BlackHeartRender[i].Update();
	}
	/*if (m_player != nullptr)
	{
		wchar_t playertext[256];
		swprintf_s(playertext, 256, L"プレイヤーのポジションx: %.0f y: %.0f z: %.0f", m_player->m_position.x, m_player->m_position.y, m_player->m_position.z);
		m_playerPosFontRender.SetText(playertext);
		m_playerPosFontRender.SetPosition({ -200.0f,-100.0f,0.0f });
		m_playerPosFontRender.SetScale(1.0f);
		m_playerPosFontRender.SetColor(g_vec4White);
		m_modelRender.Update();
	}*/
	
}


void BossStage::HPDraw()
{
	hpFontRender.SetText(L"HP");
	//座標
	hpFontRender.SetPosition({ -950.0f,540.0f,0.0f });
	//文字の大きさ
	hpFontRender.SetScale(2.0f);
	//文字の色
	hpFontRender.SetColor(g_vec4White);
}


void BossStage::TimerDraw()
{

	//残り時間のテキスト
	int seconds = (int)m_LimitTime;
	m_LimitTime -= g_gameTime->GetFrameDeltaTime();
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"%03d", seconds);

	timerFontRender.SetText(timerText);
	//座標
	timerFontRender.SetPosition({ 800.0f,530.0f,0.0f });
	//文字の大きさ
	timerFontRender.SetScale(2.0f);
	//文字の色
	timerFontRender.SetColor(g_vec4White);

	
}



void BossStage::OnGameClear()
{
	m_isClear = true;

	// BGM停止
	if (bgm)
	{
		bgm->Stop();
	}

	if (m_player)
	{
		DeleteGO(m_player);
		m_player = nullptr;
	}

	if (m_enemy3)
	{
		DeleteGO(m_enemy3);
		m_enemy3 = nullptr;
	}

	if (m_gameCamera)
	{
		DeleteGO(m_gameCamera);
		m_gameCamera = nullptr;

	}

	// GAME CLEAR 表示
	NewGO<BossClear>(0, "bossclear");
	DeleteGO(this);
}




void BossStage::RequestRestart()
{

	if (bgm)
	{
		bgm->Stop();
	}
	// プレイヤー削除
	if (m_player)
	{
		DeleteGO(m_player);
		m_player = nullptr;
	}

	// ボス削除
	if (m_enemy3)
	{
		DeleteGO(m_enemy3);
		m_enemy3 = nullptr;
	}

	// カメラ削除
	if (m_gameCamera)
	{
		DeleteGO(m_gameCamera);
		m_gameCamera = nullptr;
	}
	NewGO<BossGameOver>(0, "bossgameover");
	// 自分を削除
	DeleteGO(this);
}
void BossStage::Render(RenderContext& rc)
{
	//m_playerPosFontRender.Draw(rc);

	m_modelRender.Draw(rc);


	timerFontRender.Draw(rc);

	hpFontRender.Draw(rc);


	int m_Health = m_player->m_HP;

	for (int i = 0; i < 3; i++)
	{
		//(例)/*m_Health = 2 のとき
		//i = 0 → 赤
		//i = 1 → 赤
		//i = 2 → 黒
		//i = 0　→ 0 < 2　→赤ハートを出す
		// i = 1→ 1 <  2　→赤ハートを出す 
		//i = 2 →2 < 2 →false→黒ハートを出す
		if (i < m_Health)
		{
			m_RedHeartRender[i].Draw(rc);
		}

		else
		{
			m_BlackHeartRender[i].Draw(rc);
		}
	}
}