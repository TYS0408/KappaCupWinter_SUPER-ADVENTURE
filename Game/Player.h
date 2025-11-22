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

	bool InvincibleJuge = false;//無敵か無敵じゃないかのフラグ

	float InvincibleTime = 3.0f;//無敵時間

    
private:
	//メンバ関数
	ModelRender m_modelRender;

	Vector3 m_moveSpeed = Vector3::Zero;//移動処理

	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定


	bool IsDead = false;//死亡フラグ

	
	int m_playerState = 0;//プレイヤーステート
	

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

