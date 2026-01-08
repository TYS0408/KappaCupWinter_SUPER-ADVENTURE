#include "stdafx.h"
#include "GoalPole.h"
#include "Player.h"
#include "GameClear.h"
#include"Game.h"
GoalPole::GoalPole()
{

}


GoalPole::~GoalPole()
{

}


bool GoalPole::Start()
{	
	m_player = FindGO<Player>("player");
	m_position = Vector3(550.0f, 230.0f, 3200.0f);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Init("Assets/Stage/GoalPole.tkm");

	m_sphereCollider.Create(m_GhostScale);
	//大きさ調整
	m_modelRender.SetScale(Vector3::One * 5.0f);

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//ゴーストオブジェクトの作成
	m_GoalGhostObj.CreateCapsule(
		nsK2EngineLow::Vector3(50.0f, 50.0f, 50.0f) + m_position,
		Quaternion::Identity,
		50.0f,
		500.0f);
	return true;
}



void GoalPole::Update()
{
	Game* game = FindGO<Game>("game");
	if (game)
	{
		game->OnGoal();
	}

	m_GoalGhostObj.SetPosition(m_position + Vector3(-500.0f, 700.0f,230.0f));
	

	if (m_isGoal)
	{
		return;
	}
	if (m_player == nullptr)
	{
		return;
	}
	
	PhysicsWorld::GetInstance()->ContactTest(m_player->GetCharacterController(), [&](const btCollisionObject& contactObject)
		{
			//接触相手がGoalPoleかどうか
			if (m_GoalGhostObj.IsSelf(contactObject))
			{

				m_isGoal = true;
				//m_isCreate = true;
				//m_isDelete = true;
			}
		}
	);
	m_modelRender.Update();

}

void GoalPole::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}