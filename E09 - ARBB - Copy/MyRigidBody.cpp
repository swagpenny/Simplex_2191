#include "MyRigidBody.h"
using namespace Simplex;
//Allocation
void MyRigidBody::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();
	m_bVisibleOBB = true;
	m_bVisibleARBB = true;

	m_fRadius = 0.0f;

	m_v3ColorColliding = C_RED;
	m_v3ColorNotColliding = C_WHITE;

	m_v3Center = ZERO_V3;
	m_v3Minimum = ZERO_V3;
	m_v3Maximum = ZERO_V3;

	m_v3MinimumG = ZERO_V3;
	m_v3MaximumG = ZERO_V3;

	m_v3Size = ZERO_V3;
	m_v3ARBBSize = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;
}
void MyRigidBody::Swap(MyRigidBody& other)
{
	std::swap(m_pMeshMngr, other.m_pMeshMngr);
	std::swap(m_bVisibleOBB, other.m_bVisibleOBB);
	std::swap(m_bVisibleARBB, other.m_bVisibleARBB);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3ColorColliding, other.m_v3ColorColliding);
	std::swap(m_v3ColorNotColliding, other.m_v3ColorNotColliding);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Minimum, other.m_v3Minimum);
	std::swap(m_v3Maximum, other.m_v3Maximum);

	std::swap(m_v3MinimumG, other.m_v3MinimumG);
	std::swap(m_v3MaximumG, other.m_v3MaximumG);

	std::swap(m_v3Size, other.m_v3Size);
	std::swap(m_v3ARBBSize, other.m_v3ARBBSize);

	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_CollidingRBSet, other.m_CollidingRBSet);
}
void MyRigidBody::Release(void)
{
	m_pMeshMngr = nullptr;
	ClearCollidingList();
}
//Accessors
bool MyRigidBody::GetVisibleOBB(void) { return m_bVisibleOBB; }
void MyRigidBody::SetVisibleOBB(bool a_bVisible) { m_bVisibleOBB = a_bVisible; }
bool MyRigidBody::GetVisibleARBB(void) { return m_bVisibleARBB; }
void MyRigidBody::SetVisibleARBB(bool a_bVisible) { m_bVisibleARBB = a_bVisible; }
float MyRigidBody::GetRadius(void) { return m_fRadius; }
vector3 MyRigidBody::GetColorColliding(void) { return m_v3ColorColliding; }
vector3 MyRigidBody::GetColorNotColliding(void) { return m_v3ColorNotColliding; }
void MyRigidBody::SetColorColliding(vector3 a_v3Color) { m_v3ColorColliding = a_v3Color; }
void MyRigidBody::SetColorNotColliding(vector3 a_v3Color) { m_v3ColorNotColliding = a_v3Color; }
vector3 MyRigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 MyRigidBody::GetMinLocal(void) { return m_v3Minimum; }
vector3 MyRigidBody::GetMaxLocal(void) { return m_v3Maximum; }
vector3 MyRigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyRigidBody::GetMinGlobal(void) { return m_v3MinimumG; }
vector3 MyRigidBody::GetMaxGlobal(void) { return m_v3MaximumG; }
vector3 MyRigidBody::GetSize(void) { return m_v3Size; }
matrix4 MyRigidBody::GetModelMatrix(void) { return m_m4ToWorld; }
void MyRigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
	//to save some calculations if the model matrix is the same there is nothing to do here
	if (a_m4ModelMatrix == m_m4ToWorld)
		return;

	//Assign the model matrix
	m_m4ToWorld = a_m4ModelMatrix;

	//create vertices for the box to store them into a v3list
	std::vector<vector3> v3List;

	// vector4(x,y,z) for combos of min and max
	// for all combos of min and max per each  
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Minimum.x, m_v3Minimum.y, m_v3Minimum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Maximum.x, m_v3Minimum.y, m_v3Minimum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Minimum.x, m_v3Maximum.y, m_v3Minimum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Minimum.x, m_v3Minimum.y, m_v3Maximum.z, 1.0f)));

	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Maximum.x, m_v3Maximum.y, m_v3Minimum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Minimum.x, m_v3Maximum.y, m_v3Maximum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Maximum.x, m_v3Minimum.y, m_v3Maximum.z, 1.0f)));
	v3List.push_back(vector3(m_m4ToWorld * vector4(m_v3Maximum.x, m_v3Maximum.y, m_v3Maximum.z, 1.0f)));

	// Set to the start of the list
	m_v3MinimumG = v3List[0];
	m_v3MaximumG = v3List[0];

	// Loop through all the vectors and determine min and max
	for (int i = 1; i < v3List.size(); ++i)
	{

		// check global x
		if (m_v3MaximumG.x < v3List[i].x)
			m_v3MaximumG.x = v3List[i].x;

		else if (m_v3MinimumG.x > v3List[i].x)
			m_v3MinimumG.x = v3List[i].x;

		// check global y
		if (m_v3MaximumG.y < v3List[i].y)
			m_v3MaximumG.y = v3List[i].y;

		else if (m_v3MinimumG.y > v3List[i].y)
			m_v3MinimumG.y = v3List[i].y;

		// check global z
		if (m_v3MaximumG.z < v3List[i].z)
			m_v3MaximumG.z = v3List[i].z;

		else if (m_v3MinimumG.z > v3List[i].z)
			m_v3MinimumG.z = v3List[i].z;
	}

	// Calculate the distance between min and max vectors
	m_v3ARBBSize = m_v3MaximumG - m_v3MinimumG;
}
//The big 3
MyRigidBody::MyRigidBody(std::vector<vector3> a_pointList)
{
	Init();
	// Count the points of the incoming list
	uint uVertexCount = a_pointList.size();

	// If there are none just return, we have no information to create the BS from
	if (uVertexCount == 0)
		return;

	// Max and min as the first vector of the list
	m_v3Maximum = m_v3Minimum = a_pointList[0];

	// Get the max and min out of the list
	for (uint i = 1; i < uVertexCount; ++i)
	{
		if (m_v3Maximum.x < a_pointList[i].x) m_v3Maximum.x = a_pointList[i].x;
		else if (m_v3Minimum.x > a_pointList[i].x) m_v3Minimum.x = a_pointList[i].x;

		if (m_v3Maximum.y < a_pointList[i].y) m_v3Maximum.y = a_pointList[i].y;
		else if (m_v3Minimum.y > a_pointList[i].y) m_v3Minimum.y = a_pointList[i].y;

		if (m_v3Maximum.z < a_pointList[i].z) m_v3Maximum.z = a_pointList[i].z;
		else if (m_v3Minimum.z > a_pointList[i].z) m_v3Minimum.z = a_pointList[i].z;
	}

	// with model matrix being the identity, local and global are the same
	m_v3MinimumG = m_v3Minimum;
	m_v3MaximumG = m_v3Maximum;

	// with the max and the min we calculate the center
	m_v3Center = (m_v3Maximum + m_v3Minimum) / 2.0f;

	// Calculate the distance between min and max vectors
	m_v3Size = m_v3Maximum - m_v3Minimum;

	// Get the distance between the center and either the min or the max
	m_fRadius = glm::distance(m_v3Center, m_v3Minimum);
}
MyRigidBody::MyRigidBody(MyRigidBody const& other)
{
	m_pMeshMngr = other.m_pMeshMngr;
	m_bVisibleOBB = other.m_bVisibleOBB;
	m_bVisibleARBB = other.m_bVisibleARBB;

	m_fRadius = other.m_fRadius;

	m_v3ColorColliding = other.m_v3ColorColliding;
	m_v3ColorNotColliding = other.m_v3ColorNotColliding;

	m_v3Center = other.m_v3Center;
	m_v3Minimum = other.m_v3Minimum;
	m_v3Maximum = other.m_v3Maximum;

	m_v3MinimumG = other.m_v3MinimumG;
	m_v3MaximumG = other.m_v3MaximumG;

	m_v3Size = other.m_v3Size;
	m_v3ARBBSize = other.m_v3ARBBSize;

	m_m4ToWorld = other.m_m4ToWorld;

	m_CollidingRBSet = other.m_CollidingRBSet;
}
MyRigidBody& MyRigidBody::operator=(MyRigidBody const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyRigidBody temp(other);
		Swap(temp);
	}
	return *this;
}
MyRigidBody::~MyRigidBody() { Release(); };

//--- other Methods
void MyRigidBody::AddCollisionWith(MyRigidBody* other)
{
	/*
		check if the object is already in the colliding set, if
		the object is already there return with no changes
	*/
	auto element = m_CollidingRBSet.find(other);
	if (element != m_CollidingRBSet.end())
		return;
	// we couldn't find the object so add it
	m_CollidingRBSet.insert(other);
}
void MyRigidBody::RemoveCollisionWith(MyRigidBody* other)
{
	m_CollidingRBSet.erase(other);
}
void MyRigidBody::ClearCollidingList(void)
{
	m_CollidingRBSet.clear();
}
bool MyRigidBody::IsColliding(MyRigidBody* const other)
{
	// Check if spheres are colliding
	bool bColliding = true;

	if (this->m_v3MaximumG.x < other->m_v3MinimumG.x)
		bColliding = false;
	if (this->m_v3MinimumG.x > other->m_v3MaximumG.x)
		bColliding = false;

	if (this->m_v3MaximumG.y < other->m_v3MinimumG.y)
		bColliding = false;
	if (this->m_v3MinimumG.y > other->m_v3MaximumG.y)
		bColliding = false;

	if (this->m_v3MaximumG.z < other->m_v3MinimumG.z)
		bColliding = false;
	if (this->m_v3MinimumG.z > other->m_v3MaximumG.z)
		bColliding = false;

	if (bColliding) // Colliding with bounding box also
	{
		this->AddCollisionWith(other);
		other->AddCollisionWith(this);
	}
	else // Not colliding with bounding box
	{
		this->RemoveCollisionWith(other);
		other->RemoveCollisionWith(this);
	}

	return bColliding;
}

void MyRigidBody::AddToRenderList(void)
{
	if (m_bVisibleOBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3Size), m_v3ColorColliding);
		else
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3Size), m_v3ColorNotColliding);
	}
	if (m_bVisibleARBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
		else
			m_pMeshMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
	}
}