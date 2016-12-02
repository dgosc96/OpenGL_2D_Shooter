#pragma once
#include <MexEngine/SpriteFont.h>
#include <MexEngine/SpriteBatch.h>

#include <MexEngine/Camera2D.h>
#include <MexEngine/GLSLProgram.h>

class HUD
{
public:
	HUD();
	~HUD();

	void init(int screenWidth, int screenHeight);

	void draw(MexEngine::GLSLProgram& colorProgram);

private: 

	MexEngine::Camera2D		m_HudCamera;
	MexEngine::SpriteFont*	m_OpenSansFont;
	MexEngine::SpriteBatch	m_HudBatch;

};

