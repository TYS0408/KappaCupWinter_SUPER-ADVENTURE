#pragma once
class Player;
class Enemy3 :public IGameObject
{
public:
	Enemy3();
	~Enemy3();

	bool Start();

	void Update();


	void Tracking();

	void Move();

	void Rotation();

	void SearchPlayer();

	void Damege(Player* player);//ダメージを受ける関数

	void ManageState();

	void Enemy3Animation();

	void Dead();

	const Vector3& GetPos()
	{
		return m_position;
	}

	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	void Render(RenderContext& rc);

	int BossHP = 3;

	bool m_isDead = false;//倒したらゲームクリアを生成するためのフラグ

	bool IsDeathAnimationFinish = false;//死亡アニメーションが終わったらゲームクリアにする
private:
	ModelRender m_modelRender;

	Vector3 m_position;

	Vector3 m_moveSpeed;

	Vector3 m_BoxColliderScale = Vector3(100.0f, 400.0f, 100.0f);

	Vector3 m_forward;

	Quaternion m_rotation;

	BoxCollider m_BoxCollider;

	CharacterController  m_characterController;

	Player* m_player = nullptr;


	//頭のゴーストオブジェクト
	PhysicsGhostObject m_HeadGhostObj;

	Vector3 m_HeadScale = Vector3(50.0f, 50.0f, 50.0f);
	//胴体のゴーストオブジェクト
	PhysicsGhostObject m_BodyGhostObj;
	//攻撃時のゴーストオブジェクト
	PhysicsGhostObject m_AttackGhostObj;

	bool m_isAttacking = false;

	//無敵時間処理
	bool m_isInvincible = false;

	float m_InvincibleTime = 0.0f;


	bool  m_isBlinkVisible = true;

	float m_blinkTimer = 0.0f;

	static constexpr float INVINCIBLE_DURATION = 2.0f;



	
	bool isSearchPlayer = false;//プレイヤーを見つけたか、見つけていないか
	bool IsDead = false;//死んだか死んでないかのフラグ
	bool DeathAnimation = false;//死んだときにすぐにアニメーションが流れないようにする

	int enemy3State = 0;

	float m_playerDistance = 0.0f;//プレイヤーとの距離が100くらいなら攻撃アニメーションに変える
	enum EnAnimation
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Attack,
		enAnimaitonClip_Dead,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
};

