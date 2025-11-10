#include "stdafx.h"
#include "Enemy1.h"
#include"Player.h"



Enemy1::Enemy1()
{
	//アニメーションクリップを読み込む
	animationClips[enAnimationClip_Idle].Load("Assets/Enemy_animData/Enemy_Idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/Enemy_animData/Enemy_Walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_modelRender.Init("Assets/Stage/Enemy1_Model.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ);
}

Enemy1::~Enemy1()
{

}


bool Enemy1::Start()
{
	//エネミーの初期位置
	m_position = Vector3(0.0f, 0.0f, 300.0f);
	m_modelRender.SetPosition(m_position);
	//エネミーの大きさ
	m_modelRender.SetScale(Vector3::One* 2.0f);

	m_player = FindGO<Player>("player");
	//当たり判定
	m_characterController.Init(50.0f, 0.0f, m_position);

	//スフィアコライダーを初期化
	m_sphereCollider.Create(1.0f);
	
	return true;
}


void Enemy1::Update()
{
	//回転
	Rotation();
	//プレイヤーを見つけたかどうか
	SearchPlayer();
	//移動
	Move();
	//追跡処理
	TracKing();
	//ステート管理
	ManageState();
    //アニメーション管理
	Enemy1Animation();
	
	m_modelRender.Update();
}


void Enemy1::Rotation()
{
	//1フレームに２度ずつY軸回転を
	m_rotation.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_rotation);
	
}


void Enemy1::TracKing()	
{
	//初期化
	m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
	if (m_player == nullptr)
	{
		return;
	}

	//追跡開始距離
	//const float StartTarget = 300.0f;//const = 定数にする。

	if (m_isSearchPlayer == true)
	{
		//プレイヤーの座標をエネミーに渡す。
		Vector3 m_PlayerPos = m_player->GetPos();

		//プレイヤーの座標からエネミーの座標を引く。
		Vector3 diff = m_PlayerPos - m_position;

		//これがないとプレイヤーが上にいても追いかけてくる
		diff.y = 0.0f;
		//ベクトルの距離計算
		float distance = diff.Length();

		//ベクトルを正規化
		diff.Normalize();

		//追跡速度
		float TargetSpeed = 100.0f;

		//moveSpeedにどの方向でどんな速さで進むかを代入させる。
		// 「進行方向 × 速度」＝ 実際の移動ベクトル
		m_moveSpeed = diff * TargetSpeed;

		//キャラクターを移動させて、その結果の新しい位置をm_positionに代入。
		m_position = m_characterController.Execute(m_moveSpeed,1.0f /60.0f);
		m_modelRender.SetPosition(m_position);

	}

}

void Enemy1:: Move()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変換
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}

	if (m_isSearchPlayer == true)
	{
		Vector3 diff = m_player->GetPos() - m_position;
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

void Enemy1::SearchPlayer()
{
	m_isSearchPlayer = false;

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	Vector3 playerPos = m_player->GetPos();
	Vector3 diff = playerPos - m_position;

	//追跡可能距離
	const float CHASEDISTANCE = 300.0f;
	float distance = diff.Length();
	if (distance >= CHASEDISTANCE)
	{
		return;
	}
	diff.Normalize();
	float angle = acosf(diff.Dot(m_forward));//Dot = 内積
	//プレイヤーが視界内になかったら。
	if (Math::PI * 0.2f <= fabsf(angle))
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
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
	//壁と衝突
	if (callback.isHit == true)
	{
		//プレイヤーは見つかっていない
		return;
	}

	//壁と衝突していない
	//プレイヤー見つけたフラグをtrueに
	m_isSearchPlayer = true;
}



void Enemy1::ManageState()
{
	if (m_isSearchPlayer == true)
	{
		m_enemy1State = 1;
	}
	else
	{
		m_enemy1State = 0;
	}

}

void Enemy1::Enemy1Animation()
{
	switch (m_enemy1State)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}
void Enemy1::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	if (m_isSearchPlayer == false)
	{
		m_fontRender.SetText(L"見つかっていない・・");
	}

	if (m_isSearchPlayer == true)
	{
		m_fontRender.SetText(L"見つかった！");
	}

	m_fontRender.Draw(rc);
}