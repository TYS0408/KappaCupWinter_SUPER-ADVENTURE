#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include"Enemy1.h"
#include"Title.h"
#include"GameClear.h"
#include"GameOver.h"
#include"Enemy2.h"
#include"AppearStage.h"
#include"nature/SkyCube.h"
#include"TimerImage.h"
#include"graphics/RenderingEngine.h"

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
		{-800.0f, 500.0f, 0.0f,},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f,}
	};

}
Game::Game()
{
	
}


Game::~Game()
{
	//背景を削除
	if (m_backGround != nullptr)
	{
		
		DeleteGO(m_backGround);
		m_backGround = nullptr;
	}
	//プレイヤーを削除
	if (m_player != nullptr)
	{
		
		DeleteGO(m_player);
		m_player = nullptr;
	}
	
	//ゲームカメラを削除
	if (m_gameCamera != nullptr)
	{
		
		DeleteGO(m_gameCamera);
		m_gameCamera = nullptr;
	}
	

	//これは C++ では配列名 = 配列の先頭アドレス
	//しかし nullptr と比較しても絶対に true にも false にもならない
    //つまり 常に true 扱い
    //if (m_enemy != nullptr)  // ← 配列なので絶対に nullptr にならない！
	//これは 無意味。
	

	//エネミー１を削除
	for (int i = 0; i < 3; i++)
	{
		if (m_enemy[i] != nullptr)
		{
			DeleteGO(m_enemy[i]);
			m_enemy[i] = nullptr;
		}
	}

	//エネミー２を削除
	
		for (int j = 0; j < 3; j++)
		{
			if (m_enemy2[j] != nullptr)
			{
				DeleteGO(m_enemy2[j]);
				m_enemy2[j] = nullptr;
			}

	}
	
	if (m_timerImage != nullptr)
	{
		DeleteGO(m_timerImage);
		m_timerImage = nullptr;
    }

	if (m_appearStage != nullptr)
	{
		DeleteGO(m_appearStage);
		m_appearStage = nullptr;
	}
	
	
	

}


bool Game::Start()
{
	////ポイントライトを作成
	//auto* pointLight = g_sceneLight->NewPointLight();
	//pointLight->SetPosition(Vector3(5.0f, 55.0f, 0.0f));
	//pointLight->SetColor(0.1f, 0.1f, 10.0f);
	//pointLight->SetRange(100.0f);
	//pointLight->SetAffectPowParam(1.0f);
	//pointLight->Update();



	

	//HPのUIをfor文で追加
	for (int i = 0; i < 3; i++)
	{

		m_RedHeartRender[i].Init("Assets/Sprite/Heart.dds", 100.0f, 100.0f);
		m_BlackHeartRender[i].Init("Assets/Sprite/BlackHeart3.dds", 100.0f, 100.0f);

	}
	

	InitSky();

	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0, "backGround");
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_timerImage = NewGO<TimerImage>(0, "timerimage");


	

	//m_timerImage = NewGO<TimerImage>(0, "timerimage");
	//これはm_enemyをm_enemy自身の値で初期化しようとしている
	/*{
		m_enemy[0],
		m_enemy[1],
		m_enemy[2],
	};*/
	//エネミー１をfor文で追加
	for (int i = 0; i < 3; i++)
	{
		m_enemy[i] = NewGO<Enemy1>(0, "enemy1");
	}

	//エネミーの初期位置を設定する
	m_enemy[0]->SetPosition(Vector3(0.0f, 0.0f, 500.0f));
	m_enemy[1]->SetPosition(Vector3(200.0f, 0.0f, 400.0f));
	m_enemy[2]->SetPosition(Vector3(-200.0f, 0.0f, 200.0f));
		


	//エネミー２をfor文で追加

	for (int j = 0; j < 3; j++)
	{
		m_enemy2[j] = NewGO<Enemy2>(0, "enemy2");
	}

//エネミー２の初期座標を設定
	m_enemy2[0]->SetPosition(Vector3(0.0f, 250.0f, 1000.0f));
	m_enemy2[1]->SetPosition(Vector3(200.0f, 250.0f,1000.0f));
	m_enemy2[2]->SetPosition(Vector3(-200.0f, 250.0f, 1000.0f));

	return true;
}

void Game::Update()
{
	TimerDraw();

	//キルカウントが3以上ならステージを出現させる
	if (m_killCount >= 3 && m_appearStage ==nullptr)
	{
	    m_appearStage = NewGO<AppearStage>(0, "appearstage");
	}

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

	if (IsCreateBone == true)
	{
		m_BoneModelRender.Init("Assets/Stage/Bone.tkm");
	}

	//HPが0になったらゲームオーバーにする
	if (m_player->m_HP <= 0)
	{
		if (m_gameOver == nullptr)
		{
			m_gameOver = NewGO<GameOver>(0, "gameover");
		}
		m_isEnd = true;
	}

	if (m_isEnd)
	{
		DeleteGO(this);
		return;
	}
	
}

void Game::TimerDraw()
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

	if (m_LimitTime <= 0.0f)
	{
		m_gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);

	}
}



void Game::InitSky()
{
	DeleteGO(m_skycube);
	m_skycube = NewGO<SkyCube>(0, "skycube");
	m_skycube->SetLuminance(1.0f);//明るさ設定
	m_skycube->SetType((EnSkyCubeType)m_SkyCubeType);//スカイキューブのタイプ設定
	g_renderingEngine->SetAmbientByIBLTexture(m_skycube->GetTextureFilePath(), 1.0f);
	//環境光の計算のためのIBLテクスチャをセット
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::Render(RenderContext& rc)
{
	timerFontRender.Draw(rc);
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

	/*if (m_Health <= 0)
	{
		m_gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}*/
}
