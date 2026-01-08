#include "stdafx.h"
#include "Display_Bone.h"
#include "Player.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include "Game.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"



bool Display_Bone::Start()

{


	



	m_player = FindGO<Player>("player");

	m_game = FindGO<Game>("game");

	m_modelRender.Init("Assets/Stage/Bone.tkm");
	m_modelRender.SetScale(Vector3::One * 0.5f);

	return true;

}

void Display_Bone::SetPosition(const Vector3 pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position); // ModelRender が使える想定

}






//骨の取得処理
void Display_Bone::FoundBone()
{
	
	//if (m_isDeleted)return;

	if (m_player == nullptr|| m_game ==nullptr)
	{
		return;
	}

	if (m_isThrown)
	{
		return;
	}
	
	//地面についていた時だけ骨を拾うようにする。
	if (!m_player->GetCharacterController().IsOnGround())
	{

		
		return;
	}



	//骨の位置からプレイヤーへのベクトルを求める
	Vector3 diff = m_player->GetPos() - m_position;

	diff.y = 0.0f;

	//骨を取得する距離
	const float FoundBone =30.0f;



	//距離判定
	if (diff.Length() <= FoundBone)
	{
		//m_isPickedがfalseなら
		if (!m_isPicked)
		{
			m_isPicked = true;

			if (m_game)
			{
				g_soundEngine->ResistWaveFileBank(3, "Assets/BGM・SE/Found.wav");

				//SoundSourceのインスタンスを作成する。
				SoundSource* se = NewGO<SoundSource>(0);

				se->Init(3);

				//効果音はループさせないので、falseにする。
				se->Play(false);

				//音量を上げる。
				se->SetVolume(5.0f);
				//プレイヤーが骨を手に入れたことをゲームに通知
				m_game->OnGetBone();
				//落とした骨のオブジェクトを削除する
				DeleteGO(this);
			}

		}

		return;

	}

}



//当たり判定
void Display_Bone::CheakHitBone()
{
	if (!m_isThrown)
	{
		return;
	}
	if (m_game == nullptr)
	{
		return;
	}
	const float hitRange = 60.0f;

	auto enemies = m_game->GetEnemylist();

	for (auto obj : enemies)
	{
		if (obj == nullptr)
		{
			continue;
		}


		if (auto e1 = dynamic_cast<Enemy1*>(obj))
		{
			if (e1 ->IsDead)continue;
			Vector3 diff = e1->GetBodyPos() - m_position;
			diff.y = 0.0f;
			if (diff.Length() < hitRange)
			{
				e1->OnHitBone();
				m_isDead = true;
				
				return;//boneを消す
			}
	    }


		//Enemy2
		if (auto e2 = dynamic_cast<Enemy2*>(obj))
		{
			if (e2 ->IsDead)continue;
			Vector3 diff = e2->GetBodyPos2() - m_position;
			diff.y = 0.0f;

			if (diff.Length() < hitRange)
			{
				e2->OnHitBone2();
				m_isDead = true;
				return;
			}

		}
	}
}

//後で検索
void Display_Bone::SetVelocity(const Vector3& v)
{
	m_velocity = v;
	m_isThrown = true;
}




void Display_Bone::ThrowBone()
{
	//投げる処理
	//骨が投げられたら
	if (m_isThrown)
	{
		m_rotation.AddRotationDegY(20.0f);
		m_modelRender.SetRotation(m_rotation);
		m_position += m_velocity * g_gameTime->GetFrameDeltaTime();
		m_modelRender.SetPosition(m_position);

	
		//距離制限
		if (m_position.Length() > 4000.0f)
		{
			//投げた骨が4000以上なら削除する
			m_isDead = true;
			return;
		}
	}
}
void Display_Bone::Update()
{
	ThrowBone();

	FoundBone();

	CheakHitBone();


	//m_position += m_velocity * g_gameTime->GetFrameDeltaTime();
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);

}


void Display_Bone::Render(RenderContext& rc)

{

	m_modelRender.Draw(rc);

}
