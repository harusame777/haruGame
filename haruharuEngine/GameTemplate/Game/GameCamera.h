#pragma once

class Game;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();

	void Update();

	Vector3 m_toCameraPos;	

	Game *m_game = nullptr;
};

