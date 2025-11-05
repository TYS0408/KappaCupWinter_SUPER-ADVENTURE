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

	int m_playerState = 0;//プレイヤーステート
	//メンバ関数
	ModelRender m_modelRender;

	Vector3 m_position;//座標

	Vector3 m_moveSpeed = Vector3::Zero;//移動処理

	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定

	bool IsDead = false;//死亡フラグ
	
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

