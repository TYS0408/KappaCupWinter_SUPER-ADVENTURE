#pragma once
class Player;
class GameClear;
class Game;
class GoalPole : public IGameObject
{ 
public:
	GoalPole();
	~GoalPole();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& pos);

	void Clear();
	Vector3 m_position;


	bool m_isDelete = false;
	bool m_isCreate = false;

	bool m_isGoal = false;
	
private:
	ModelRender m_modelRender;

	PhysicsGhostObject m_GoalGhostObj;


	PhysicsStaticObject m_physicsStaticObject;

	float m_GhostScale = 300.0f;



	SphereCollider m_sphereCollider;

	Player* m_player = nullptr;

	GameClear* m_gameClear = nullptr;

	Game* m_game = nullptr;
	

};

