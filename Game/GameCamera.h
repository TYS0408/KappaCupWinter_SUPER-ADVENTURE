#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera() {};
	~GameCamera() {};
	void Update()override;
	bool Start();
	void SetTarget(Player* player) { m_player = player; }

private:
	Player* m_player = nullptr;
	Vector3 m_CameraPos;

};

