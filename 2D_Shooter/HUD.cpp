#include "HUD.h"



HUD::HUD()
{
}


HUD::~HUD()
{
	delete m_OpenSansFont;

}


void HUD::init(int screenWidth, int screenHeight)
{
	m_HudBatch.init();
	m_HudCamera.init(screenWidth, screenHeight);
	m_HudCamera.setPosition(glm::vec2(screenWidth / 2.0f , screenHeight / 2.0f));

	m_OpenSansFont = new MexEngine::SpriteFont("Fonts/OpenSans/OpenSans-Light.ttf", 64);

}


void HUD::draw(MexEngine::GLSLProgram& colorProgram)
{
	m_HudCamera.update();

	char buffer[256];

	GLint pLocation = colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_HudCamera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_HudBatch.begin();

	sprintf_s(buffer, "HUD drawing test");


	m_OpenSansFont->draw(m_HudBatch, buffer, glm::vec2(0.0f, 0.0f), 
						 glm::vec2(0.5f), 0.0f, MexEngine::ColorRGBA8());


	m_HudBatch.end();
	m_HudBatch.renderBatch();

}