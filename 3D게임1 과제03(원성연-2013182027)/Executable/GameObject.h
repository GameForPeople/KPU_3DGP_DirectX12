#pragma once

#include "Mesh.h"
class CShader;
class CCamera;

struct MATERIAL
{
	XMFLOAT4						m_xmf4Ambient;
	XMFLOAT4						m_xmf4Diffuse;
	XMFLOAT4						m_xmf4Specular; //(r,g,b,a=power)
	XMFLOAT4						m_xmf4Emissive;
};

struct ColidePoint {
	struct Pos2D {
		float x;
		float z;
	};
	float	size;

	Pos2D	mXmZ;	// mi X, mi Z
	Pos2D	pXpZ;	// pl X, pl Z
	//Pos2D	mXpZ;	// mi x, pl Z
	//Pos2D	pXmZ;	// pl X, mi Z

	void Create(float size, float x, float z) {
		this->size = size;
		Animate(x, z);
	}

	void Animate(float x, float z) {
		mXmZ.x = x - size;
		mXmZ.z = z - size;

		//mXpZ.x = x - size;
		//mXpZ.z = z + size;

		pXpZ.x = x + size;
		pXpZ.z = z + size;

		//pXmZ.x = x + size;
		//pXmZ.z = z - size;
	}

	bool SayHello(ColidePoint inputColidePoint) {
		if (mXmZ.x > inputColidePoint.pXpZ.x) return false;
		else if (mXmZ.z > inputColidePoint.pXpZ.z) return false;
		else if (pXpZ.x < inputColidePoint.mXmZ.x) return false;
		else if (pXpZ.z < inputColidePoint.mXmZ.z) return false;

		return true;
	}
};

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

private:
	int								m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	XMFLOAT4						m_xmf4Albedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	UINT							m_nReflection = 0;
	CShader							*m_pShader = NULL;

	void SetAlbedo(XMFLOAT4& xmf4Albedo) { m_xmf4Albedo = xmf4Albedo; }
	void SetReflection(UINT nReflection) { m_nReflection = nReflection; }
	void SetShader(CShader *pShader);
};

class CGameObject
{
private:
	int m_nReferences = 0;

public:
	CGameObject();
	CGameObject(int nMeshes = 1);
	virtual ~CGameObject();

	//게임 객체가 카메라에 보인는 가를 검사한다.
	bool IsVisible(CCamera *pCamera = NULL);
	bool IsVisible(CCamera *pCamera, bool a);

	XMFLOAT3 m_dirVector{ 0, 0, 0 };
	float m_fRotationSpeed;
	int m_isStatus = 0;
public:
	int m_nMeshes = 0;

	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	XMFLOAT4X4 m_xmf4x4World;
	CMesh							**m_ppMeshes = NULL;
	CShader							*m_pShader = NULL;
	
	ColidePoint						m_ColidePoint;

	CMaterial						*m_pMaterial = NULL;

public:
	void ReleaseUploadBuffers();
	virtual void SetMesh(int nIndex, CMesh *pMesh);
	virtual void SetShader(CShader *pShader);
	virtual void SetMaterial(CMaterial *pMaterial);
	virtual void SetMaterial(UINT nReflection);

	virtual void Animate(float fTimeElapsed, void *pContext);
	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);

	//상수 버퍼를 생성한다.
	//virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	//	*pd3dCommandList);
	////상수 버퍼의 내용을 갱신한다.
	//virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	//virtual void ReleaseShaderVariables();
	
	virtual void DoColide(float playerX, float playerZ) {};
	virtual void DoColide(float playerX, float playerZ, bool m_isOnInput) {};

	//게임 객체의 월드 변환 행렬에서 위치 벡터와 방향(x-축, y-축, z-축) 벡터를 반환한다.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//게임 객체의 위치를 설정한다.
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);
	//게임 객체를 로컬 x-축, y-축, z-축 방향으로 이동한다.

	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	//게임 객체를 회전(x-축, y-축, z-축)한다.
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	//BoundingOrientedBox		m_xmOOBB;
	//BoundingOrientedBox		m_xmOOBBTransformed;
	//void SetOOBB(XMFLOAT3& xmCenter, XMFLOAT3& xmExtents, XMFLOAT4& xmOrientation) { m_xmOOBBTransformed = m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation); }

	void Rotate(XMFLOAT3 *pxmf3Axis, float fAngle);
};

class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	CRotatingObject(int nMeshes = 1);
	virtual ~CRotatingObject();
private:
	XMFLOAT3 m_xmf3RotationAxis;
public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis =
			xmf3RotationAxis;
	}
	virtual void Animate(float fTimeElapsed, void *pContext);
	void LimitMove(float fTimeElapsed);
	
	virtual void DoColide(float playerX, float playerZ);
	virtual void DoColide(float playerX, float playerZ, bool& m_isOnInput);

};

class CHeightMapTerrain : public CGameObject
{
public:
	CHeightMapTerrain(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, ID3D12RootSignature *pd3dGraphicsRootSignature, LPCTSTR pFileName, int
		nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4
		xmf4Color);
	CHeightMapTerrain(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList, ID3D12RootSignature *pd3dGraphicsRootSignature, LPCTSTR pFileName, int
		nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT3
		xmf3Normal);
	virtual ~CHeightMapTerrain();
private:
	//지형의 높이 맵으로 사용할 이미지이다.
	CHeightMapImage *m_pHeightMapImage;
	//높이 맵의 가로와 세로 크기이다.
	int m_nWidth;
	int m_nLength;
	//지형을 실제로 몇 배 확대할 것인가를 나타내는 스케일 벡터이다.
	XMFLOAT3 m_xmf3Scale;
public:
	//지형의 높이를 계산하는 함수이다(월드 좌표계). 높이 맵의 높이에 스케일의 y를 곱한 값이다.
	float GetHeight(float x, float z) {
		return(m_pHeightMapImage->GetHeight(x /
			m_xmf3Scale.x, z / m_xmf3Scale.z) * m_xmf3Scale.y);
	}
	//지형의 법선 벡터를 계산하는 함수이다(월드 좌표계). 높이 맵의 법선 벡터를 사용한다.
	XMFLOAT3 GetNormal(float x, float z) {
		return(m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z /
			m_xmf3Scale.z)));
	}
	int GetHeightMapWidth() { return(m_pHeightMapImage->GetHeightMapWidth()); }
	int GetHeightMapLength() { return(m_pHeightMapImage->GetHeightMapLength()); }
	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	//지형의 크기(가로/세로)를 반환한다. 높이 맵의 크기에 스케일을 곱한 값이다.
	float GetWidth() { return(m_nWidth * m_xmf3Scale.x); }
	float GetLength() { return(m_nLength * m_xmf3Scale.z); }
};


