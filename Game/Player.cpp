#include "stdafx.h"
#include "Player.h"
#include"GameOver.h"
#include"Game.h"
#include"Title.h"
#include "GoalPole.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
Player::Player()
{
	//アニメーションクリップを読み込む
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/Jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm",animationClips,enAnimationClip_Num,enModelUpAxisY);
	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{
	
}

bool Player:: Start()
{//ステージ開始時はここでプレイヤーの座標をリセット
	m_position = Vector3(0.0f, 0.0f, 0.0f);

	m_characterController.SetPosition(m_position);

	m_modelRender.SetPosition(m_position);

	m_goalPole = FindGO<GoalPole>("goalpole");
	m_respawn = m_position;
	return true;
}


void Player::Update()
{
	if (m_isKnockBack)
	{
		m_knockBackTime -= g_gameTime->GetFrameDeltaTime();

		//ノックバック移動
		m_position = m_characterController.Execute(
			m_moveSpeed,
			g_gameTime->GetFrameDeltaTime()
		);
		m_modelRender.SetPosition(m_position);


		if (m_knockBackTime <= 0.0f)
		{
			m_isKnockBack = false;
		}
		return;
	}


	//移動処理
	Move();
	//回転処理
	Rotation();
	//ステート管理
	ManageState();
    //アニメーション再生
	PlayAnimation();
	//更新処理
	m_modelRender.Update();

	//無敵時間処理
	if (InvincibleJuge)
	{
		//時間を減らす処理
		float dt = g_gameTime->GetFrameDeltaTime();

		InvincibleTime -= dt;

		//点滅タイマー
		m_blinkTimer += dt;
		if (m_blinkTimer >= m_blinkInterval)
		{
			m_blinkTimer -= m_blinkInterval;//0にしないようにする
			m_isVisible = !m_isVisible;//表示切替
		}

		//無敵時間が終わったら無敵を解除
		if (InvincibleTime <=0.0f)
		{
			InvincibleJuge = false;
			InvincibleTime = 0.0f;
			m_blinkTimer = 0.0f;
			m_isVisible = true;
		}
	}
	


	

	
	
}


//
//void Player::ResetStatus()
//{
//	m_HP = Max_HP;
//}
void Player::Move()
{
	//xzの入力量を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed. z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();//x軸の移動
	stickL.y = g_pad[0]->GetLStickYF();//y軸の移動
	//移動速度にスティックの入力量を取得
	m_moveSpeed.x += stickL.x * 120.0f;
	m_moveSpeed.z += stickL.y * 120.0f;

	//カメラの前方向と右ベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	//正規化
	right.y = 0.0f;
	forward.y = 0.0f;
	forward.Normalize();
	right.Normalize();


	
	//入力量を反映(TPS方式)
	Vector3 moveDir = forward * stickL.y * 120.0f + right * stickL.x * 120.0f;
	m_moveSpeed.x = moveDir.x;
	m_moveSpeed.z = moveDir.z;

	//左スティックの入力量と120.0fを乗算する
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//移動速度に上記で計算したベクトルを加算
	m_moveSpeed += right + forward;



	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;

		if (g_pad[0]->IsPress(enButtonB))
		{
			//ダッシュ処理
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 2.0f;

		}

		//普通のジャンプ処理
		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			if (g_pad[0]->IsTrigger(enButtonA))
			{
			//効果音
			g_soundEngine->ResistWaveFileBank(1, "Assets/BGM・SE/Jump.wav");

			//SoundSourceのインスタンスを作成する。
			SoundSource* se = NewGO<SoundSource>(0);

			se->Init(1);

			//効果音はループさせないので、falseにする。
			se->Play(false);

			//音量を上げる。
			se->SetVolume(3.5f);

				m_moveSpeed.y = 600.0f;
				//m_moveSpeed.y -= 4.0 * 2.0f;
			}
		}

		//垂直ジャンプ処理
		if (fabsf(m_moveSpeed.x) == 0.0f && fabsf(m_moveSpeed.z) == 0.0f)
		{
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//効果音
				g_soundEngine->ResistWaveFileBank(1, "Assets/BGM・SE/Jump.wav");

				//SoundSourceのインスタンスを作成する。
				SoundSource* se = NewGO<SoundSource>(0);

				se->Init(1);

				//効果音はループさせないので、falseにする。
				se->Play(false);

				//音量を上げる。
				se->SetVolume(3.5f);
				m_moveSpeed.y = 900.0f;
				//m_moveSpeed.y -= 6.0 * 2.0f;
			}

		}
	}
	else
	{
		//重力処理
		m_moveSpeed.y -= 8.0 * 3.0f;
	}
	//リスポーン処理
	if (m_position.y <= -1000.0f)
	{
		m_position = m_respawn;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
		m_HP--;
		////無敵時間処理
		InvincibleJuge = true;
		InvincibleTime = 3.0f;

		//無敵時間処理
		if (InvincibleJuge)
		{
			//時間を減らす処理
			float dt = g_gameTime->GetFrameDeltaTime();

			InvincibleTime -= dt;

			//点滅タイマー
			m_blinkTimer += dt;
			if (m_blinkTimer >= m_blinkInterval)
			{
				m_blinkTimer -= m_blinkInterval;//0にしないようにする
				m_isVisible = !m_isVisible;//表示切替
			}

			//無敵時間が終わったら無敵を解除
			if (InvincibleTime <= 0.0f)
			{
				InvincibleJuge = false;
				InvincibleTime = 0.0f;
				m_blinkTimer = 0.0f;
				m_isVisible = true;
			}
		}

		m_modelRender.SetPosition(m_position);
	}



	
	//プレイヤーを動くようにする。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_modelRender.SetPosition(m_position);

	//骨を発射する処理
	{
		if (g_pad[0]->IsTrigger(enButtonSelect))
		{
			ThrowBone();
		}
	}
}



void Player::ThrowBone()
{


	//骨がない場合は投げれない
	Game* game = FindGO<Game>("game");
	//gameがnullptrならこの下の処理を中断
	if (!game)return;

	//持っている骨が0以下ならこの下の処理を中断
	if (game->m_haveBoneCount <= 0)
	{
		return;
	}

	//効果音再生
	g_soundEngine->ResistWaveFileBank(2, "Assets/BGM・SE/Throw.wav");

	//インスタンスの作成
	SoundSource* se = NewGO<SoundSource>(0);

	se->Init(2);

	//効果音はループさせない
	se->Play(false);

	//音量を上げる
	se->SetVolume(3.5f);

	//骨の数を減らす
	game->m_haveBoneCount--;

	//投げる骨の生成
	Display_Bone* bone = NewGO <Display_Bone>(0, "throw_bone");

	//プレイヤーの前方に飛ばす処理
	Vector3 pos = GetPos() + m_forward * 50.0f;
	pos.y += 50.0f;
	bone->SetPosition(pos);
	//12/1追加
	//投げる速度
	//Vector3 velocity = m_forward * 300.0f;
	
	
	bone->SetVelocity(m_forward * 300.0f);
	
}
void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変換
		m_rot.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rot);

		//プレイヤーの forward を更新する
		m_forward = Vector3::AxisZ;
		m_rot.Apply(m_forward);   // ← 回転を適用
	
		m_forward.Normalize();
	}
}



void Player::ManageState()
{
	if (m_characterController.IsOnGround() == false)
	{
		m_playerState = 2;
		return;
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ダッシュしていたら
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_playerState = 3;
		}

		else
		{
			//ダッシュしていなかったら
			m_playerState = 1;
		}
	}
	else
	{
		//何の入力もなかったら
		m_playerState = 0;
		
	}
		
}



void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;

	}
}


void Player::Render(RenderContext& rc)
{

	if (m_isVisible)
	{
		m_modelRender.Draw(rc);
	}
	
}
