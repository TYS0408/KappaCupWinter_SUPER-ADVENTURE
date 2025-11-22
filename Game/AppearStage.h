#pragma once
class AppearStage :public IGameObject
{

	/**
	 *メンバ関数
	 */
public:
	AppearStage();
	~AppearStage();

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	void Appear();//クリボーを三体倒すとステージを出現させるための関数

private:
	Vector3 m_position;

	ModelRender m_modelRender;

	PhysicsStaticObject m_physicsStaticObject;

	bool m_isAppeard = false;//クリボーを三体倒すとステージを出現させるためのフラグ

};

