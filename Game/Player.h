#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();

	bool Start();

	void Move();

	void Rotation();

	void Render(RenderContext& rc);

	void ManageState();

	void Invincible();

	void PlayAnimation();

	const Vector3& GetPos()
	{
		return m_position;
	}

	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	int m_HP = 3;//プレイヤーの体力
	Vector3 m_position;//座標


	//bool m_isInvincible = false;//無敵の時はtrue、無敵じゃないときはfalseにする

	//bool m_isVisible = true;//点滅を表すための変数

	//float m_invincibleTimer = 0.0f;//無敵時間

	//float m_invincibleDuration = 1.5;//無敵になる時間

	//float m_blinkingTimer = 0.0f;//点滅する時間



private:
	//メンバ関数
	ModelRender m_modelRender;

	

	Vector3 m_moveSpeed = Vector3::Zero;//移動処理

	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定


	bool IsDead = false;//死亡フラグ


	

	int m_playerState = 0;//プレイヤーステー
	

	//アニメーション
	enum EnPlayAnimation
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];

};

