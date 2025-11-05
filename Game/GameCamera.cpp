#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"


bool GameCamera::Start()
{
	m_CameraPos.Set(0.0f, 125.0f, -250.0f);

	//カメラのニアクリップとファークリップを設定する
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(100000.0f);

	return true;
}

void GameCamera::Update()
{
	// まだプレイヤーのポインタを保持していないなら探す
	if (m_player == nullptr) 
	{
		m_player = FindGO<Player>("player");
		if (m_player == nullptr) 
		{
			// プレイヤーがまだ見つからなければ何もしない
			return;
		}
	}


	//注視点を計算
	Vector3 target = m_player->m_position;
	//プレイヤーの足元より少し上を注視点にする。
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_CameraPos;
	//右スティック入力取得でカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	rot.Apply(m_CameraPos);
	//X軸周りの回転
	/*Vector3 axisX;
	axisX.Cross(Vector3::AxisX, m_CameraPos);
	axisX.Normalize();
	rot.SetRotationDeg(axisX, 1.3f * y);
	rot.Apply(m_CameraPos);*/

	// --- 上下回転修正版 ---
	//「カメラの右方向」を現在の m_CameraPos から正しく計算し、
    //それを使ってX軸回転を行っている。
	Vector3 forward = m_CameraPos;
	forward.Normalize();

	// ワールド上方向
	Vector3 up = Vector3::AxisY;

	// カメラの右方向を算出
	Vector3 right;
	right.Cross(up, forward);
	right.Normalize();

	// 上下回転
	rot.SetRotationDeg(right, 1.3f * y);
	rot.Apply(m_CameraPos);

	
	Vector3 dir = m_CameraPos;
	dir.Normalize();
	float limit = 0.95f; // cos角度による制限(= 約72°)
	if (fabsf(dir.Dot(Vector3::AxisY)) > limit) 
	{
		// 上向きすぎ・下向きすぎを防止
		m_CameraPos = toCameraPosOld;
	}
	//視点の計算
	Vector3 pos = target + m_CameraPos;
	//メインカメラに注視点と視点を設定
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
//カメラの更新
	g_camera3D->Update();



}