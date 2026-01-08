#pragma once
class Player;
class Game;

class Display_Bone :public IGameObject
{
public:
	Display_Bone() {};
	~Display_Bone() {};


	bool Start();

	void Update();

	void SetPosition(const Vector3 pos);

	void Render(RenderContext& rc);

	void SetVelocity(const Vector3& v);
	
	void FoundBone();//œ‚ğE‚¤ŠÖ”

	void ThrowBone();

	void CheakHitBone();//œ‚É‚ ‚½‚Á‚½‚ç“G‚ğ“|‚·ˆ—

	bool isDead = false;

	bool IsDead()const { return m_isDead; }
	
	bool m_isPicked = false;//œ‚ğE‚Á‚½‚©‚Ìƒtƒ‰ƒO

	bool m_isThrown = false;//œ‚ğ“Š‚°‚½‚©“Š‚°‚Ä‚¢‚È‚¢‚©‚Ìƒtƒ‰ƒO
private:
	

	Player* m_player = nullptr;

	Game* m_game = nullptr;

	ModelRender m_modelRender;

	Vector3 m_position;

	Quaternion m_rotation;//‰ñ“]

	Vector3 m_foundBone;//œ‚ğæ“¾‚·‚é

	Vector3 m_velocity = Vector3::Zero;

	SphereCollider m_sphereCollider;
	//float m_collisionRadius = 60.0f;//“Š‚°‚½œ‚Ì“–‚½‚è”»’è
	//CharacterController m_characterController;//ƒLƒƒƒ‰ƒRƒ“
};

