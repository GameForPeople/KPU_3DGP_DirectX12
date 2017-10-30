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

	//���� ��ü�� ī�޶� ���δ� ���� �˻��Ѵ�.
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

	//��� ���۸� �����Ѵ�.
	//virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	//	*pd3dCommandList);
	////��� ������ ������ �����Ѵ�.
	//virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	//virtual void ReleaseShaderVariables();
	
	virtual void DoColide(float playerX, float playerZ) {};
	virtual void DoColide(float playerX, float playerZ, bool m_isOnInput) {};

	//���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ���Ϳ� ����(x-��, y-��, z-��) ���͸� ��ȯ�Ѵ�.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//���� ��ü�� ��ġ�� �����Ѵ�.
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);
	//���� ��ü�� ���� x-��, y-��, z-�� �������� �̵��Ѵ�.

	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	//���� ��ü�� ȸ��(x-��, y-��, z-��)�Ѵ�.
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
	//������ ���� ������ ����� �̹����̴�.
	CHeightMapImage *m_pHeightMapImage;
	//���� ���� ���ο� ���� ũ���̴�.
	int m_nWidth;
	int m_nLength;
	//������ ������ �� �� Ȯ���� ���ΰ��� ��Ÿ���� ������ �����̴�.
	XMFLOAT3 m_xmf3Scale;
public:
	//������ ���̸� ����ϴ� �Լ��̴�(���� ��ǥ��). ���� ���� ���̿� �������� y�� ���� ���̴�.
	float GetHeight(float x, float z) {
		return(m_pHeightMapImage->GetHeight(x /
			m_xmf3Scale.x, z / m_xmf3Scale.z) * m_xmf3Scale.y);
	}
	//������ ���� ���͸� ����ϴ� �Լ��̴�(���� ��ǥ��). ���� ���� ���� ���͸� ����Ѵ�.
	XMFLOAT3 GetNormal(float x, float z) {
		return(m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z /
			m_xmf3Scale.z)));
	}
	int GetHeightMapWidth() { return(m_pHeightMapImage->GetHeightMapWidth()); }
	int GetHeightMapLength() { return(m_pHeightMapImage->GetHeightMapLength()); }
	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	//������ ũ��(����/����)�� ��ȯ�Ѵ�. ���� ���� ũ�⿡ �������� ���� ���̴�.
	float GetWidth() { return(m_nWidth * m_xmf3Scale.x); }
	float GetLength() { return(m_nLength * m_xmf3Scale.z); }
};


