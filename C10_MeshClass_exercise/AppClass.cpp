#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Model = IDENTITY_M4;
	// Translating
	// m4Model[3][3] = 1.0f; // by value
	// m4Model[3] = vector4(1.0f); // by column
	// m4Model = glm::translate(IDENTITY_M4, vector3(1.0f)); // using glm library

	// Scaling
	// m4Model[1][1] = 2.0f; // by value 
	// m4Model = glm::scale(IDENTITY_M4, vector3(2.0f)); // using glm library

	//static float fDisp = 0.0f;
	static float xOffset = 0.0f;
	m4Model = glm::translate(IDENTITY_M4, vector3(xOffset, 0.5f * sin(xOffset), 0.0f));
	//fDisp += 0.01f;
	xOffset += 0.02f;

	//m_pMesh->Render(m4Projection, m4View, m4Model);

	// Draw the invader (center)
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f)));

	// Invader (left part)
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-1.0f, -3.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, 3.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-2.0f, -3.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, 4.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-3.0f, -2.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-4.0f, 0.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(-5.0f, -2.0f, 0.0f)));

	// Invader (right part)
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(1.0f, -3.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, 3.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(2.0f, -3.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, 4.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(3.0f, -2.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4.0f, 1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(4.0f, 0.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5.0f, -1.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, vector3(5.0f, -2.0f, 0.0f)));

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}