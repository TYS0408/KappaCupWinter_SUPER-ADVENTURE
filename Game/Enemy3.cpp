#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"
#include"Game.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"

namespace
{
	Vector3 SCALE = Vector3(4.0f, 3.7f, 4.0f);
}
Enemy3::Enemy3()
{
	//アニメーションクリップの読み込み
	animationClips[enAnimationClip_Idle].Load("Assets/Enemy_animData/Enemy3_Idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/Enemy_animData/Enemy3_Run.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Attack].Load("Assets/Enemy_animData/Enemy3_Attack.tka");
	animationClips[enAnimationClip_Attack].SetLoopFlag(true);
	animationClips[enAnimaitonClip_Dead].Load("Assets/Enemy_animData/Enemy3_Dead.tka");
	animationClips[enAnimaitonClip_Dead].SetLoopFlag(false);
	m_modelRender.Init("Assets/Stage/Boss.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ);
}

Enemy3::~Enemy3()
{

}

bool Enemy3::Start()
{
	m_player = FindGO<Player>("player");

	m_position = Vector3(0.0f, 0.0f, 400.0f);

	m_modelRender.SetPosition(m_position);

	m_rotation.SetRotationDegY(180.0f);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.SetScale(SCALE);

	m_characterController.Init(50.0f, 180.0f, m_position);

	m_BoxCollider.Create(m_BoxColliderScale);

	//頭のゴーストオブジェクト
	m_HeadGhostObj.CreateBox(
		nsK2EngineLow::Vector3(0.0f, 0.0f, 0.0f) + m_position,
		Quaternion::Identity,
		nsK2EngineLow::Vector3(m_HeadScale));

	//胴体のゴーストオブジェクト
	m_BodyGhostObj.CreateSphere(
		nsK2EngineLow::Vector3(0.0f, 0.0f, 0.0f) + m_position,
		Quaternion::Identity,
		75.0f);


	m_AttackGhostObj.CreateSphere(
		m_position,
		Quaternion::Identity,
		50.0f   // 攻撃範囲
	);

	// 最初は無効
	PhysicsWorld::GetInstance()->RemoveCollisionObject(
		m_AttackGhostObj.GetbtCollisionObject());
	m_modelRender.Update();
	return true;
}



void Enemy3::Update()
{
	if (m_isInvincible)
	{

		m_InvincibleTime -= g_gameTime->GetFrameDeltaTime();
		if (m_InvincibleTime <= 0.0f)
		{
			m_InvincibleTime = 0.0f;
			m_isInvincible = false;
		}



		m_blinkTimer += g_gameTime->GetFrameDeltaTime();

		const float BLINK_INTERVAL = 0.1f; // 0.1秒

		if (m_blinkTimer >= BLINK_INTERVAL)
		{
			m_blinkTimer = 0.0f;
			m_isBlinkVisible = !m_isBlinkVisible;
		}
	}
	else
	{
		// 無敵解除
		m_blinkTimer = 0.0f;
		m_isBlinkVisible = true;
	}

	
	//ボスが攻撃をする距離を計算
	Vector3 dif = m_player->GetPos() - m_position;
	//Y軸は考慮しない
	dif.y = 0.0f;
	m_playerDistance = dif.Length();


	//攻撃したらゴーストオブジェクトを消す
	if (enemy3State != 2 && m_isAttacking)
	{
		m_isAttacking = false;

		PhysicsWorld::GetInstance()->RemoveCollisionObject(
			m_AttackGhostObj.GetbtCollisionObject());
	}

	//プレイヤーを見つけたかどうか
	SearchPlayer();

	//ステート管理
	ManageState();

	//追跡処理
	Tracking();
	//移動処理
	Move();

	//ダメージ処理
	Damege(m_player);

	//アニメーション管理
	Enemy3Animation();

	//死亡処理
	Dead();

	m_modelRender.Update();
}



//void Enemy3::SetPosition(const Vector3& pos)
//{
//	m_position = pos;
//	m_modelRender.SetPosition(m_position);
//		
//}
//void Enemy3::Rotation()
//{
//	m_rotation.SetRotationDegY(180.0f);
//	m_modelRender.SetRotation(m_rotation);
//}


void Enemy3::Tracking()
{
	//攻撃中は移動しない
	if (enemy3State == 2)
	{
		m_moveSpeed = Vector3::Zero;
		return;
	}


	//初期化しておく
	m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

	if (!isSearchPlayer || !m_player)
	{
		return;
	}

	if (isSearchPlayer == true)
	{
		//プレイヤーの座標をエネミーに渡す
		Vector3 m_PlayerPos = m_player->GetPos();

		//プレイヤーの座標からエネミーの座標を引く
		Vector3 diff = m_PlayerPos - m_position;

		diff.y = 0.0f;

		//ベクトルの距離計算
		float distance = diff.Length();

		diff.Normalize();

		//追跡速度
		float TargetSpeed = 100.0f;
		//進行方向×速度 = 実際の移動ベクトル
		m_moveSpeed = diff * TargetSpeed;



		//キャラクターを移動させて、その結果の新しい位置をm_positionに代入
		m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
		m_modelRender.SetPosition(m_position);

		//ゴーストオブジェクトをセット
		m_HeadGhostObj.SetPosition(m_position + Vector3(0.0f, 280.0f, 0.0f));
		m_BodyGhostObj.SetPosition(m_position + Vector3(0.0f, 100.0f, 0.0f));
	}
}


void Enemy3::Move()
{
	if (fabsf(m_moveSpeed.x) >= 0.0001f || fabsf(m_moveSpeed.z >= 0.0001f))
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}
}


//Bulletの btCollisionWorld::ConvexResultCallback を継承。
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{

	bool isHit = false;//衝突フラグ
	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInwarldSpace)
	{
		//m_hitCollisionObject = ぶつかった相手のコライダー
		//getUserIndex() = ぶつかったコライダーの種類
		//enCollisionAttr_Ground = 地面や壁の属性ID
		//衝突した相手が “地面（または壁）” ではないなら無視する
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Ground)
		{
			return 0.0f;
		}
		//壁とぶつかったらtrueに
		isHit = true;
		return 0.0f;
	}
};

void Enemy3::SearchPlayer()
{
	isSearchPlayer = false;

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	Vector3 playerPos = m_player->GetPos();
	Vector3 diff = playerPos - m_position;

	//追跡可能距離
	const float CHASEDISSTANCE = 700.0f;
	float Distance = diff.Length();

	if (Distance >= CHASEDISSTANCE)
	{
		return;
	}
	diff.Normalize();
	//Dot = 内積
	float angle = acosf(diff.Dot(m_forward));
	//プレイヤーが視界内なら
	if (Math::PI * 0.5f <= fabsf(angle))
	{
		return;
	}
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//始点はエネミーの座標
	start.setOrigin(btVector3(m_position.x, m_position.y + 70.0f, m_position.z));
	//終点はプレイヤーの座標
	end.setOrigin(btVector3(playerPos.x, playerPos.y + 70.0f, playerPos.z));

	SweepResultWall callback;
	//コライダーを始点から終点まで動かして衝突するか調べる
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_BoxCollider.GetBody(), start, end, callback);
	//壁と衝突
	if (callback.isHit == true)
	{
		//プレイヤーは見つかっていない
		return;
	}

	//壁と衝突していない
	//プレイヤー見つけたフラグをtrueに
	isSearchPlayer = true;

}

void Enemy3::Damege(Player* player)
{

	if (m_isInvincible)
	{
		return;
	}

	if (player == nullptr)
	{
		return;
	}

	if (BossHP <= 0)
	{
		IsDead = true;
	}

	PhysicsWorld::GetInstance()->ContactTest(player->GetCharacterController(), [&](const btCollisionObject& contactObject)
		{

			
			//接触相手が頭のゴーストオブジェクトなら
			if (m_HeadGhostObj.IsSelf(contactObject))
			{

				if (m_isInvincible)
				{
					return;
				}

				//効果音
				g_soundEngine->ResistWaveFileBank(4, "Assets/BGM・SE/Stomp.wav");

				//SoundSourceのインスタンスを作成する。
				SoundSource* se = NewGO<SoundSource>(0);

				se->Init(4);
				//効果音はループさせないので、falseにする。
				se->Play(false);

				//音量を上げる。
				se->SetVolume(3.5f);
				player->m_moveSpeed.y = 500.0f;
				BossHP--;

			//無敵開始
				m_isInvincible = true;
				m_InvincibleTime = 5.0f;
				
			}


			//接触相手が敵の胴体(ゴースト)かどうかを判定する関数			
			if (m_BodyGhostObj.IsSelf(contactObject))
			{
				if (player->m_HP > 0 and player->InvincibleJuge == false)
				{

					g_soundEngine->ResistWaveFileBank(6, "Assets/BGM・SE/Damage.wav");

					//SoundSourceのインスタンスを作成する。
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(6);

					//効果音はループさせないので、falseにする。
					se->Play(false);

					//音量を上げる。
					se->SetVolume(3.5f);



					player->m_HP--;
					//無敵時間処理
					player->InvincibleJuge = true;
					player->InvincibleTime = 3.0f;

				}
			}



			if (m_isAttacking && m_AttackGhostObj.IsSelf(contactObject))
			{
				if (player->InvincibleJuge == false)
				{

					g_soundEngine->ResistWaveFileBank(6, "Assets/BGM・SE/Damage.wav");

					//SoundSourceのインスタンスを作成する。
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(6);

					//効果音はループさせないので、falseにする。
					se->Play(false);

					//音量を上げる。
					se->SetVolume(3.5f);
					player->m_HP--;

					player->InvincibleJuge = true;
					player->InvincibleTime = 3.0f;

					//ノックバック処理
					Vector3 knockDir = player->GetPos() - m_position;
					knockDir.y = 0.0f;
					knockDir.Normalize();

					const float KNOCKBACK_POWER = 400.0f;

					player->m_moveSpeed = knockDir * KNOCKBACK_POWER;
					player->m_moveSpeed.y = 200.0f;//少し浮かせたい場合


					player->m_isKnockBack = true;
					player->m_knockBackTime = 0.3f;
						
				}
			}
		}
	);
}

void Enemy3::Dead()
{
	if (IsDead == true)
	{
		//エネミーが死んだらゴーストオブジェクト(頭)を削除
		PhysicsWorld::GetInstance()->RemoveCollisionObject(m_HeadGhostObj.GetbtCollisionObject());

		//ゴーストオブジェクト(胴体)を削除
		PhysicsWorld::GetInstance()->RemoveCollisionObject(m_BodyGhostObj.GetbtCollisionObject());



		//死んだときのアニメーションを一度だけ再生
		if (DeathAnimation == false)
		{
			DeathAnimation = true;

			m_modelRender.PlayAnimation(enAnimaitonClip_Dead);

		}



		if (!m_modelRender.IsPlayingAnimation())
		{
			IsDeathAnimationFinish = true;

			//DeleteGO(this);
			//return;
		}
	}
}


void Enemy3::ManageState()
{

	//プレイヤーを見つけていない
	if (isSearchPlayer == false)
	{
		enemy3State = 0;
		return;
	}


	const float ATTACK_DISTANCE = 150.0f;

	if (m_playerDistance <= ATTACK_DISTANCE)
	{
		enemy3State = 2;

	}
	else
	{
		enemy3State = 1;
	}

}

void Enemy3::Enemy3Animation()
{
	if (IsDead)
	{
		return;
	}

	switch (enemy3State)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;

	case 2:

		if (!m_isAttacking)
		{
			m_isAttacking = true;


			// 攻撃判定を前方に出す
			m_AttackGhostObj.SetPosition(
				m_position + m_forward * 80.0f + Vector3(0.0f, 100.0f, 0.0f));

			PhysicsWorld::GetInstance()->AddCollisionObject(
				m_AttackGhostObj.GetbtCollisionObject());
		}
		m_modelRender.PlayAnimation(enAnimationClip_Attack);
		break;
	}
}


void Enemy3::Render(RenderContext& rc)
{

	if (!m_isBlinkVisible)
	{
		return;
	}
	m_modelRender.Draw(rc);
}