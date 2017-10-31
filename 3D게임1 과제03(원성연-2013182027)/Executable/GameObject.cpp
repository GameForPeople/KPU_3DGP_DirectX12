#include "stdafx.h"

#include "GameObject.h"

#include "Shader.h"

#pragma region [Material Function]
CMaterial::CMaterial()
{
	m_xmf4Albedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

CMaterial::~CMaterial()
{
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CMaterial::SetShader(CShader *pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

#pragma endregion

#pragma region [CGameObject Function]

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

CGameObject::CGameObject(int nMeshes)
{
	m_xmf4x4World = Matrix4x4::Identity();
	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;
	if (m_nMeshes > 0)
	{
		m_ppMeshes = new CMesh*[m_nMeshes];
		for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;
	}
}

bool CGameObject::IsVisible(CCamera *pCamera)
{
	OnPrepareRender();
	bool bIsVisible = false;
	BoundingOrientedBox *xmBoundingBox;
	xmBoundingBox = new BoundingOrientedBox[m_nMeshes];

	for (int i = 0; i < m_nMeshes; i++)
		xmBoundingBox[i] = m_ppMeshes[i]->GetBoundingBox();

	//모델 좌표계의 바운딩 박스를 월드 좌표계로 변환한다.
	for (int i = 0; i < m_nMeshes; i++) {
		xmBoundingBox[i].Transform(xmBoundingBox[i], XMLoadFloat4x4(&m_xmf4x4World));
		if (pCamera) bIsVisible = pCamera->IsInFrustum(xmBoundingBox[i]);
	}
	return(bIsVisible);
}

bool CGameObject::IsVisible(CCamera *pCamera, bool boolValue)
{
	OnPrepareRender();
	bool bIsVisible = false;
	BoundingOrientedBox *xmBoundingBox;
	xmBoundingBox = new BoundingOrientedBox[m_nMeshes];

	for (int i = 0; i < m_nMeshes; i++)
		xmBoundingBox[i] = m_ppMeshes[i]->GetBoundingBox();

	//모델 좌표계의 바운딩 박스를 월드 좌표계로 변환한다.
	for (int i = 0; i < m_nMeshes; i++) {
		xmBoundingBox[i].Transform(xmBoundingBox[i], XMLoadFloat4x4(&m_xmf4x4World));
		if (pCamera) bIsVisible = pCamera->IsInFrustum(xmBoundingBox[i]);
	}
	return(boolValue);
}

CGameObject::~CGameObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
	}
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::SetShader(CShader *pShader) { 
#ifdef NEW_CODE
	if (!m_pMaterial)
	{
		m_pMaterial = new CMaterial();
		m_pMaterial->AddRef();
	}
	if (m_pMaterial) m_pMaterial->SetShader(pShader);
#endif
#ifndef NEW_CODE
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader; 
	if (m_pShader) m_pShader->AddRef(); 
#endif
}

void CGameObject::Animate(float fTimeElapsed, void *pContext)
{

	//m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	//XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

void CGameObject::OnPrepareRender()
{
}

void CGameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
#ifdef NEW_CODE
	if (IsVisible(pCamera)) {
		OnPrepareRender();

		if (m_pMaterial)
		{
			if (m_pMaterial->m_pShader)
			{
				m_pMaterial->m_pShader->Render(pd3dCommandList, pCamera);
				m_pMaterial->m_pShader->UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);
			}
		}
		if (m_ppMeshes)
		{
			{
				for (int i = 0; i < m_nMeshes; i++)
				{
					{
						if (m_ppMeshes[i]) m_ppMeshes[i]->Render(pd3dCommandList);
					}
				}
			}
		}
	}
#endif
#ifndef NEW_CODE
	//게임 객체가 카메라에 보이면 렌더링한다.-> 어케암?
	if (IsVisible(pCamera))
	{
//		UpdateShaderVariables(pd3dCommandList);
		if (m_pShader) m_pShader->Render(pd3dCommandList, pCamera);
		//게임 객체가 포함하는 모든 메쉬를 렌더링한다.~~~~~~~~~~~~~~~~~
		if (m_ppMeshes)
		{
			{
				for (int i = 0; i < m_nMeshes; i++)
				{
					{
						if (m_ppMeshes[i]) m_ppMeshes[i]->Render(pd3dCommandList);
					}
				}
			}
		}
	}
#endif // !NEW_CODE
}

void CGameObject::SetMesh(int nIndex, CMesh *pMesh)
{
	if (m_ppMeshes)
	{
		if (m_ppMeshes[nIndex]) m_ppMeshes[nIndex]->Release();
		m_ppMeshes[nIndex] = pMesh;
		if (pMesh) pMesh->AddRef();
	}
}

void CGameObject::SetMaterial(CMaterial *pMaterial)
{
	if (m_pMaterial) m_pMaterial->Release();
	m_pMaterial = pMaterial;
	if (m_pMaterial) m_pMaterial->AddRef();
}

void CGameObject::SetMaterial(UINT nReflection)
{
	if (!m_pMaterial) m_pMaterial = new CMaterial();
	m_pMaterial->m_nReflection = nReflection;
}

void CGameObject::ReleaseUploadBuffers()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->ReleaseUploadBuffers();
		}
	}
}

void CGameObject::Rotate(XMFLOAT3 *pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis),
		XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

//void CGameObject::CreateShaderVariables(ID3D12Device *pd3dDevice,
//	ID3D12GraphicsCommandList *pd3dCommandList)
//{
//}
//void CGameObject::ReleaseShaderVariables()
//{
//}

//void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
//{
//	XMFLOAT4X4 xmf4x4World;
//	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
//	//객체의 월드 변환 행렬을 루트 상수(32-비트 값)를 통하여 셰이더 변수(상수 버퍼)로 복사한다.
//	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
//}
void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}
void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}
XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}
//게임 객체의 로컬 z-축 벡터를 반환한다.
XMFLOAT3 CGameObject::GetLook()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32,
		m_xmf4x4World._33)));
}
//게임 객체의 로컬 y-축 벡터를 반환한다.
XMFLOAT3 CGameObject::GetUp()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22,
		m_xmf4x4World._23)));
}
//게임 객체의 로컬 x-축 벡터를 반환한다.
XMFLOAT3 CGameObject::GetRight()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12,
		m_xmf4x4World._13)));
}
//게임 객체를 로컬 x-축 방향으로 이동한다.
void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}
//게임 객체를 로컬 y-축 방향으로 이동한다.
void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}
//게임 객체를 로컬 z-축 방향으로 이동한다.
void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}
//게임 객체를 주어진 각도로 회전한다.
void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch),
		XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

#pragma endregion

#pragma region [CRotaiongObject Function]

CRotatingObject::CRotatingObject(int nMeshes) : CGameObject(nMeshes)
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 15.0f;

	m_dirVector.x = rand() % 50 - 25;
	m_dirVector.z = rand() % 50 - 25;

	//	m_dirVector.x = 200;
}

CRotatingObject::~CRotatingObject()
{
}

void CRotatingObject::DoColide(float playerX, float playerZ) {
	ColidePoint buffer;
	buffer.Create(5, playerX, playerZ);

	if (m_ColidePoint.SayHello(buffer)) {
		m_dirVector.x = -m_dirVector.x;
		m_dirVector.z = -m_dirVector.z;
	}
}

void CRotatingObject::DoColide(float playerX, float playerZ, bool& m_isOnInput) {
	ColidePoint buffer;
	buffer.Create(5, playerX, playerZ);

	if (m_ColidePoint.SayHello(buffer)) {
		m_dirVector.x = -m_dirVector.x;
		m_dirVector.z = -m_dirVector.z;
		m_isOnInput = false;
	}
}

void CRotatingObject::Animate(float fTimeElapsed, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);	
	CRotatingObject::LimitMove(fTimeElapsed);

	SetPosition(GetPosition().x + m_dirVector.x * 3, pTerrain->GetHeight(GetPosition().x, GetPosition().z) + 10, GetPosition().z + m_dirVector.z * 3);
	
	m_ColidePoint.Animate(GetPosition().x, GetPosition().z);
	//m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
	//XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
}

void CRotatingObject::LimitMove(float fTimeElapsed) {
	int xPos = GetPosition().x;
	int zPos = GetPosition().z;

	if (xPos <= 10) {
		m_dirVector.x = -1 * m_dirVector.x;
	}
	else if (xPos >= 1590) {
		m_dirVector.x = -1 * m_dirVector.x;
	}

	if (zPos <= 10) {
		m_dirVector.z = -1 * m_dirVector.z;
	}
	else if (zPos >= 1590) {
		m_dirVector.z = -1 * m_dirVector.z;
	}

	if (xPos >= 640 && xPos <= 960) {
		if (zPos >= 635 && zPos <= 645) {
			m_dirVector.z = -1 * m_dirVector.z;
			SetPosition(xPos, GetPosition().y, 633);
		}
		else if (zPos <= 965 && zPos >= 955) {
			m_dirVector.z = -1 * m_dirVector.z;
			SetPosition(xPos, GetPosition().y, 968);
		}
	}

	if (zPos >= 640 && zPos <= 960) {
		if (xPos >= 635 && xPos <= 645) {
			m_dirVector.x = -1 * m_dirVector.x;
			SetPosition(633, GetPosition().y, zPos);
		}
		else if (xPos <= 965 && xPos >= 955) {
			m_dirVector.x = -1 * m_dirVector.x;
			SetPosition(968, GetPosition().y, zPos);
		}
	}

}

#pragma endregion

#pragma region [CHeightMapTerrain]

#ifdef NEW_CODE
CHeightMapTerrain::CHeightMapTerrain(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList, ID3D12RootSignature *pd3dGraphicsRootSignature, LPCTSTR pFileName, int
	nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT3
	xmf3Normal) : CGameObject(0)
{
	//지형에 사용할 높이 맵의 가로, 세로의 크기이다.
	m_nWidth = nWidth;
	m_nLength = nLength;
	/*지형 객체는 격자 메쉬들의 배열로 만들 것이다. nBlockWidth, nBlockLength는 격자 메쉬 하나의 가로, 세로 크
	기이다. cxQuadsPerBlock, czQuadsPerBlock은 격자 메쉬의 가로 방향과 세로 방향 사각형의 개수이다.*/
	int cxQuadsPerBlock = nBlockWidth - 1;
	int czQuadsPerBlock = nBlockLength - 1;
	//xmf3Scale는 지형을 실제로 몇 배 확대할 것인가를 나타낸다.
	m_xmf3Scale = xmf3Scale;
	//지형에 사용할 높이 맵을 생성한다.
	m_pHeightMapImage = new CHeightMapImage(pFileName, nWidth, nLength, xmf3Scale);
	//지형에서 가로 방향, 세로 방향으로 격자 메쉬가 몇 개가 있는 가를 나타낸다.
	long cxBlocks = (m_nWidth - 1) / cxQuadsPerBlock;
	long czBlocks = (m_nLength - 1) / czQuadsPerBlock;
	//지형 전체를 표현하기 위한 격자 메쉬의 개수이다.
	m_nMeshes = cxBlocks * czBlocks;
	//지형 전체를 표현하기 위한 격자 메쉬에 대한 포인터 배열을 생성한다.
	m_ppMeshes = new CMesh*[m_nMeshes];

	for (int i = 0; i < m_nMeshes; i++)m_ppMeshes[i] = NULL;
	CHeightMapGridMesh *pHeightMapGridMesh = NULL;
	for (int z = 0, zStart = 0; z < czBlocks; z++)
	{
		for (int x = 0, xStart = 0; x < cxBlocks; x++)
		{
			//지형의 일부분을 나타내는 격자 메쉬의 시작 위치(좌표)이다.
			xStart = x * (nBlockWidth - 1);
			zStart = z * (nBlockLength - 1);
			//지형의 일부분을 나타내는 격자 메쉬를 생성하여 지형 메쉬에 저장한다.
			pHeightMapGridMesh = new CHeightMapGridMesh(pd3dDevice, pd3dCommandList, xStart,
				zStart, nBlockWidth, nBlockLength, xmf3Scale, xmf3Normal, m_pHeightMapImage);
			SetMesh(x + (z*cxBlocks), pHeightMapGridMesh);
		}
	}
	//지형을 렌더링하기 위한 셰이더를 생성한다.
	CTerrainShader *pShader = new CTerrainShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);
}
#endif
CHeightMapTerrain::CHeightMapTerrain(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList, ID3D12RootSignature *pd3dGraphicsRootSignature, LPCTSTR pFileName, int
	nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4
	xmf4Color) : CGameObject(0)
{
	//지형에 사용할 높이 맵의 가로, 세로의 크기이다.
	m_nWidth = nWidth;
	m_nLength = nLength;
	/*지형 객체는 격자 메쉬들의 배열로 만들 것이다. nBlockWidth, nBlockLength는 격자 메쉬 하나의 가로, 세로 크
	기이다. cxQuadsPerBlock, czQuadsPerBlock은 격자 메쉬의 가로 방향과 세로 방향 사각형의 개수이다.*/
	int cxQuadsPerBlock = nBlockWidth - 1;
	int czQuadsPerBlock = nBlockLength - 1;
	//xmf3Scale는 지형을 실제로 몇 배 확대할 것인가를 나타낸다.
	m_xmf3Scale = xmf3Scale;
	//지형에 사용할 높이 맵을 생성한다.
	m_pHeightMapImage = new CHeightMapImage(pFileName, nWidth, nLength, xmf3Scale);
	//지형에서 가로 방향, 세로 방향으로 격자 메쉬가 몇 개가 있는 가를 나타낸다.
	long cxBlocks = (m_nWidth - 1) / cxQuadsPerBlock;
	long czBlocks = (m_nLength - 1) / czQuadsPerBlock;
	//지형 전체를 표현하기 위한 격자 메쉬의 개수이다.
	m_nMeshes = cxBlocks * czBlocks;
	//지형 전체를 표현하기 위한 격자 메쉬에 대한 포인터 배열을 생성한다.
	m_ppMeshes = new CMesh*[m_nMeshes];

	for (int i = 0; i < m_nMeshes; i++)m_ppMeshes[i] = NULL;
	CHeightMapGridMesh *pHeightMapGridMesh = NULL;
	for (int z = 0, zStart = 0; z < czBlocks; z++)
	{
		for (int x = 0, xStart = 0; x < cxBlocks; x++)
		{
			//지형의 일부분을 나타내는 격자 메쉬의 시작 위치(좌표)이다.
			xStart = x * (nBlockWidth - 1);
			zStart = z * (nBlockLength - 1);
			//지형의 일부분을 나타내는 격자 메쉬를 생성하여 지형 메쉬에 저장한다.
			pHeightMapGridMesh = new CHeightMapGridMesh(pd3dDevice, pd3dCommandList, xStart,
				zStart, nBlockWidth, nBlockLength, xmf3Scale, xmf4Color, m_pHeightMapImage);
			SetMesh(x + (z*cxBlocks), pHeightMapGridMesh);
		}
	}
	//지형을 렌더링하기 위한 셰이더를 생성한다.
	SetMaterial(7);
	CTerrainShader *pShader = new CTerrainShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	//pShader->CreateShaderVariables

	SetShader(pShader);
}

CHeightMapTerrain::~CHeightMapTerrain(void)
{
	if (m_pHeightMapImage) delete m_pHeightMapImage;
}

#pragma endregion