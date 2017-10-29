#include "stdafx.h"
#include "Shader.h"

#pragma region [CShader Part.]

CShader::CShader()
{
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates) {
		for (int i = 0; i < m_nPipelineStates; i++)
			if (m_ppd3dPipelineStates[i]) m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	//d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;

	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);

}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	//d3dDepthStencilDesc.DepthEnable = FALSE;

	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	return(d3dDepthStencilDesc);
}


D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다. 
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName,
	LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG) 
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}

#define _WITH_WFOPEN

D3D12_SHADER_BYTECODE CShader::ReadCompiledShaderFromFile(WCHAR *pszFileName, ID3DBlob **ppd3dShaderBlob)
{
	UINT nReadBytes = 0;
#ifdef _WITH_WFOPEN
	FILE *pFile = NULL;
	::_wfopen_s(&pFile, pszFileName, L"rb");
	::fseek(pFile, 0, SEEK_END);
	int nFileSize = ::ftell(pFile);
	BYTE *pByteCode = new BYTE[nFileSize];
	::rewind(pFile);
	nReadBytes = (UINT)::fread(pByteCode, sizeof(BYTE), nFileSize, pFile);
	::fclose(pFile);
#endif
#ifdef _WITH_STD_STREAM
	std::ifstream ifsFile;
	ifsFile.open(pszFileName, std::ios::in | std::ios::ate | std::ios::binary);
	nReadBytes = (int)ifsFile.tellg();
	BYTE *pByteCode = new BYTE[*pnReadBytes];
	ifsFile.seekg(0);
	ifsFile.read((char *)pByteCode, nReadBytes);
	ifsFile.close();
#endif
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	if (ppd3dShaderBlob)
	{
		*ppd3dShaderBlob = NULL;
		HRESULT hResult = D3DCreateBlob(nReadBytes, ppd3dShaderBlob);
		memcpy((*ppd3dShaderBlob)->GetBufferPointer(), pByteCode, nReadBytes);
		d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
		d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	}
	else
	{
		d3dShaderByteCode.BytecodeLength = nReadBytes;
		d3dShaderByteCode.pShaderBytecode = pByteCode;
	}

	return(d3dShaderByteCode);
}

//그래픽스 파이프라인 상태 객체를 생성한다.
//그래픽스 파이프라인 상태 객체를 생성한다.


void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]
		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList)
{
}
void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}
void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}
void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, MATERIAL *pMaterial)
{
}

void CShader::ReleaseShaderVariables()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다.
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}
void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

#pragma endregion

#pragma region [CPlayerShader Part.]

CPlayerShader::CPlayerShader()
{
}
CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}
void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CPlayerShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_PLAYER_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbPlayer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbPlayer->Map(0, NULL, (void **)&m_pcbMappedPlayer);
}

void CPlayerShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CPlayerShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	::memcpy(&m_pcbMappedPlayer->m_xmf4x4World, &xmf4x4World, sizeof(XMFLOAT4X4));
}

void CPlayerShader::ReleaseShaderVariables()
{
	if (m_pd3dcbPlayer)
	{
		m_pd3dcbPlayer->Unmap(0, NULL);
		m_pd3dcbPlayer->Release();
	}
}

/*
void CPlayerShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = m_pd3dcbPlayer->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(0, d3dGpuVirtualAddress);
}
*/

#pragma endregion

#pragma region [CObjectShader Part.]

CObjectsShader::CObjectsShader()
{
}
CObjectsShader::~CObjectsShader()
{
}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


void CObjectsShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbGameObjectBytes * m_nObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbGameObjects->Map(0, NULL, (void **)&m_pcbMappedGameObjects);
}

void CObjectsShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	XMFLOAT4X4 xmf4x4World;
	for (int j = 0; j < m_nObjects; j++)
	{
		XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World)));
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)(m_pcbMappedGameObjects + (j * ncbGameObjectBytes));
		::memcpy(&pbMappedcbGameObject->m_xmf4x4World, &xmf4x4World, sizeof(XMFLOAT4X4));
		pbMappedcbGameObject->m_nMaterial = m_ppObjects[j]->m_pMaterial->m_nReflection;	
	}
}

void CObjectsShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects)
	{
		m_pd3dcbGameObjects->Unmap(0, NULL);
		m_pd3dcbGameObjects->Release();
	}
}


// Build Object

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList, void *pContext)
{
#ifdef NEW_CODE
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	float fTerrainWidth = pTerrain->GetWidth(), fTerrainLength = pTerrain->GetLength();
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
	//직육면체를 지형 표면에 그리고 지형보다 높은 위치에 일정한 간격으로 배치한다.
	int xObjects = int(fTerrainWidth / fxPitch), yObjects = 2, zObjects =
		int(fTerrainLength / fzPitch);

	m_nObjects = xObjects * yObjects * zObjects;
	m_ppObjects = new CGameObject*[m_nObjects];
	//CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
	CCubeMeshIlluminated *pCubeMesh = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	CRotatingObject *pRotatingObject = NULL;
	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{
			for (int y = 0; y < yObjects; y++)
			{
				pRotatingObject = new CRotatingObject(1);
				pRotatingObject->SetMesh(0, pCubeMesh);
				float xPosition = x * fxPitch;
				float zPosition = z * fzPitch;
				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
				pRotatingObject->SetPosition(xPosition, fHeight + (y * 10.0f * fyPitch) +
					6.0f, zPosition);
				if (y == 0)
				{
					/*지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선
					벡터 방향과 직육면체의 y-축이 일치하도록 한다.*/
					xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
					xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
						xmf3SurfaceNormal);
					if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f,
						0.0f);
					float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
						xmf3SurfaceNormal));
					pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
				}
				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
				pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
				m_ppObjects[i++] = pRotatingObject;
			}
		}
	}
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
#endif
#ifndef NEW_CODE
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;
	float fTerrainWidth = pTerrain->GetWidth(), fTerrainLength = pTerrain->GetLength();
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
	//직육면체를 지형 표면에 그리고 지형보다 높은 위치에 일정한 간격으로 배치한다.
	int xObjects = int(fTerrainWidth / fxPitch), yObjects = 2, zObjects =
		int(fTerrainLength / fzPitch);

	m_nObjects = xObjects * yObjects * zObjects;
	m_ppObjects = new CGameObject*[m_nObjects];
	//CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
	CCubeMeshIlluminated *pCubeMesh = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;
	CRotatingObject *pRotatingObject = NULL;
	for (int i = 0, x = 0; x < xObjects; x++)
	{
		for (int z = 0; z < zObjects; z++)
		{
			for (int y = 0; y < yObjects; y++)
			{
				pRotatingObject = new CRotatingObject(1);
				pRotatingObject->SetMesh(0, pCubeMesh);
				float xPosition = x * fxPitch;
				float zPosition = z * fzPitch;
				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
				pRotatingObject->SetPosition(xPosition, fHeight + (y * 10.0f * fyPitch) +
					6.0f, zPosition);
				if (y == 0)
				{
					/*지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선
					벡터 방향과 직육면체의 y-축이 일치하도록 한다.*/
					xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
					xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
						xmf3SurfaceNormal);
					if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f,
						0.0f);
					float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
						xmf3SurfaceNormal));
					pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
				}
				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
				pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
				m_ppObjects[i++] = pRotatingObject;
			}
		}
	}
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
#endif
}

void CObjectsShader::BuildWallObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	//직육면체를 지형 표면에 그리고 지형보다 높은 위치에 일정한 간격으로 배치한다.
	
	float x_len = 15.0f;
	float xPosition{ 0 };
	float zPosition{ 0 };
	float fHeight{ 0 };
	m_nObjects = 100;	//92;
	m_ppObjects = new CGameObject*[m_nObjects];
	CWallMeshDiffused *pWallMesh1 = new CWallMeshDiffused(pd3dDevice, pd3dCommandList,x_len, 150.0f, 1.0f, 1);
	CWallMeshDiffused *pWallMesh2 = new CWallMeshDiffused(pd3dDevice, pd3dCommandList,x_len, 150.0f, 1.0f, 2);
	CWallMeshDiffused *pWallMesh3 = new CWallMeshDiffused(pd3dDevice, pd3dCommandList,100.0f, 1.0f, 100.0f, 1);	//이놈이 아래 바닥 할꺼야

	CGameObject *pGameObject = NULL;

	for (int j = 0; j < m_nObjects; j++) {
		
		pGameObject = new CGameObject(1);

		int vUpObject = 0;

		/*
		if (j >= 0 && j < 5) {
			pGameObject->SetMesh(0, pWallMesh1);
			xPosition = 800 - ((float)5 / (float)2 * x_len) + x_len * j + x_len / 2;
			zPosition = 780;
		}
		else if (j >= 5 && j < 15) {
			pGameObject->SetMesh(0, pWallMesh2);

			if (j < 10) {
				xPosition = 800 - ((float)5 / (float)2 * x_len);
				zPosition = 780 + x_len * (j - 5) + x_len / 2;
			}
			else {
				xPosition = 800 + ((float)5 / (float)2 * x_len);
				zPosition = 780 + x_len * (j - 10) + x_len / 2;
			}
		}
		else if (j >= 15 && j < 17) {
			pGameObject->SetMesh(0, pWallMesh1);

			if (j < 16) {
				xPosition = 800 - ((float)5 / (float)2 * x_len) + x_len * (j - 15) + x_len / 2;
				zPosition = 830;
			}
			else {
				xPosition = 800 - ((float)5 / (float)2 * x_len) + x_len * (j - 12) + x_len / 2;
				zPosition = 830;
			}
		}
		else if (j >= 17 && j < 40) {
			pGameObject->SetMesh(0, pWallMesh1);

			if (j < 22) {
				xPosition = 800 - ((float)5 / (float)2 * x_len) - x_len * (j - 16) + x_len / 2;
				zPosition = 830;
			}
			else if (j < 37) {
				xPosition = 800 - ((float)5 / (float)2 * x_len) + x_len * (j - 27) + x_len / 2;
				zPosition = 860;
			}
			else if (j < 38) {
				xPosition = 830 + x_len * (j - 37);
				zPosition = 830;
			}
			else if (j < 40) {
				xPosition = 830 + x_len * (j - 35);
				zPosition = 830;
			}
		}
		else if (j >= 40 && j < 46) {
			pGameObject->SetMesh(0, pWallMesh2);
			if (j < 43) {
				xPosition = 725;
				zPosition = 835 + (j - 40) * x_len;
			}
			else if (j < 46) {
				xPosition = 875;
				zPosition = 835 + (j - 43) * x_len;
			}
		}
		else if (j >= 46 && j < 66) {
			pGameObject->SetMesh(0, pWallMesh2);
			if (j < 56) {
				xPosition = 835;
				zPosition = 825 - (j - 46) * x_len;
			}
			else if (j < 66) {
				xPosition = 855;
				zPosition = 825 - (j - 56) * x_len;
			}
		}
		else if (j >= 66 && j < 68) {
			pGameObject->SetMesh(0, pWallMesh1);
			if (j < 68) {
				xPosition = 840 + (j - 66) * x_len;
				zPosition = 730;
			}
		}
		else if (j >= 68 && j < 76) {
			pGameObject->SetMesh(0, pWallMesh1);
			if (j < 73) {
				xPosition = 860 + (j - 68) * x_len;
				zPosition = 790;
			}
			else if (j < 76) {
				xPosition = 860 + (j - 73) * x_len;
				zPosition = 810;
			}
		}
		else if (j >= 76 && j < 102) {
			pGameObject->SetMesh(0, pWallMesh2);
			if (j < 90) {
				if (j == 86 || j == 87) {
					xPosition = 925;
					zPosition = 795 + (j - 76) * x_len;
				}
				else {
					xPosition = 905;
					zPosition = 795 + (j - 76) * x_len;
				}
			}
			else if (j < 100) {
				xPosition = 885;
				zPosition = 795 + (j - 90) * x_len;
			}
			else if (j < 102) {
				xPosition = 885;
				zPosition = 795 + (j - 88) * x_len;
			}
		}*/

		if (j < 20) {
			pGameObject->SetMesh(0, pWallMesh1);
			xPosition = 800 - x_len * (j - 9.5f);
			zPosition = 950;	//200차이가 나야함 오그래?? 오~~~
		}
		else if (j < 40) {
			int h = j - 20;
			pGameObject->SetMesh(0, pWallMesh1);
			xPosition = 800 - x_len * (h - 9.5f);
			zPosition = 650;
		}
		else if (j < 60) {
			int h = j - 40;
			pGameObject->SetMesh(0, pWallMesh2);
			xPosition = 950;
			zPosition = 800 - x_len * (h - 9.5f);
		}
		else if (j < 80) {
			int h = j - 60;
			pGameObject->SetMesh(0, pWallMesh2);
			xPosition = 650;
			zPosition = 800 - x_len * (h - 9.5f);
		}
		else if (j < 90) {
			int h = (j - 80);
			vUpObject = h / 3; 
			h = h % 3;
			// 0 0, 1 0, 2 0, 0 1, 1 1, 2 1, 0 2, 1 2, 2 2

			pGameObject->SetMesh(0, pWallMesh3);
			xPosition = 700 + 100 * h;
			zPosition = 700 + 100 * vUpObject;

			if (j == 89) {
				zPosition = -1000;
			}
		}
		else if (j < 100) {
			int h = (j - 90);
			vUpObject = h / 3;
			h = h % 3;

			pGameObject->SetMesh(0, pWallMesh3);
			xPosition = 700 + 100 * h;
			zPosition = 700 + 100 * vUpObject;

			if (j == 99) {
				zPosition = -1000;
			}
		}

		//fHeight = pTerrain->GetHeight(xPosition, zPosition);
		if(j < 80)
			pGameObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 6.0f, zPosition);
		else if (j < 90)
			pGameObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 80.0f, zPosition);
		else
			pGameObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition), zPosition);

		/*
		if (y == 0)
		{
		//지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선벡터 방향과 직육면체의 y-축이 일치하도록 한다.
		xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
		xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
		xmf3SurfaceNormal);
		if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f,
		0.0f);
		float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
		xmf3SurfaceNormal));
		pGameObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
		}
		*/
		m_ppObjects[j] = pGameObject;
//		m_ppObjects[j]->SetOOBB(XMFLOAT3(xPosition, 0.0f, zPosition), XMFLOAT3(5.0f, 30.0f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::BuildBallObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	// 공친구들을 지형 표면에 그리고 지형보다 높은 위치에 배치한다.

	float x_len = 10.0f;

	float xPosition{ 0 };
	float zPosition{ 0 };
	float fHeight{ 0 };
	m_nObjects = 50;

	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 0;
	float fzPitch = 12.0f * 2.5f;

	m_ppObjects = new CGameObject*[m_nObjects];

	CSphereMeshDiffused *pMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 10.0f, 20.0f, 20.0f);
	CRotatingObject  *pGameObject = NULL;

	for (int j = 0; j < m_nObjects; j++) {
		pGameObject = new CRotatingObject(1);

		if (j == 0) {
			pGameObject->SetMesh(0, pMesh);
			xPosition = 0;
			zPosition = 0;
			pGameObject->m_dirVector = { 0.1f , 0.0f, 0.0f };

			pGameObject->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 50.0f));
			pGameObject->SetRotationSpeed(-300.0f);
		}
		else if (j < 51) {
			pGameObject->SetMesh(0, pMesh);
			//pGameObject->m_dirVector = { 0.0f , 0.0f, 0.05f };

			pGameObject->m_dirVector.x = (rand() % 4 + 1) / (float)10;
			pGameObject->m_dirVector.z = (rand() % 4 + 1) / (float)10;

			pGameObject->SetRotationAxis(XMFLOAT3(50.0f, 0.0f, 0.0f));
			pGameObject->SetRotationSpeed(-300.0f);

			xPosition = rand() % 1600;
			zPosition = rand() % 1600;

			while (zPosition > 630 && zPosition < 980 && xPosition > 630 && xPosition < 980)
				xPosition = rand() % 1600;
				zPosition = rand() % 1600;
		}
		
		fHeight = pTerrain->GetHeight(xPosition, zPosition);
		pGameObject->SetPosition(xPosition, pTerrain->GetHeight(xPosition, zPosition) + 6.0f, zPosition);

		/*
		if (y == 0)
		{
		//지형의 표면에 위치하는 직육면체는 지형의 기울기에 따라 방향이 다르게 배치한다. 직육면체가 위치할 지형의 법선벡터 방향과 직육면체의 y-축이 일치하도록 한다.
		xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
		xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
		xmf3SurfaceNormal);
		if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f,
		0.0f);
		float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f),
		xmf3SurfaceNormal));
		pGameObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
		}
		*/

		m_ppObjects[j] = pGameObject;

		m_ppObjects[j]->m_ColidePoint.Create(10, xPosition, zPosition);
	
		//m_ppObjects[j]->SetOOBB(XMFLOAT3(0, 0, 0), XMFLOAT3(20.0f, 20.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		//m_ppObjects[j]->SetOOBB(XMFLOAT3(xPosition, pTerrain->GetHeight(xPosition, zPosition), zPosition), XMFLOAT3(20.0f, 20.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

void CObjectsShader::AnimateObjects(float fTimeElapsed, void *pContext)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed , pContext);
	}
}

void CObjectsShader::DoColide(float playerX, float playerZ) {
	for (int j = 0; j < m_nObjects - 1; j++)
	{
		m_ppObjects[j]->DoColide(playerX,playerZ);

		for (int k = j + 1; k < m_nObjects; k++) {
			if (m_ppObjects[j]->m_ColidePoint.SayHello(m_ppObjects[k]->m_ColidePoint)) {
				if (k != m_nObjects - 1) {
					XMFLOAT3 bufVector = m_ppObjects[j]->m_dirVector;
					m_ppObjects[j]->m_dirVector = m_ppObjects[k]->m_dirVector;
					m_ppObjects[k]->m_dirVector = bufVector;
				}
			}
		}
	}
	m_ppObjects[m_nObjects - 1]->DoColide(playerX, playerZ);
}

void CObjectsShader::DoColide(float playerX, float playerZ, bool& m_isOnInput) {
	for (int j = 0; j < m_nObjects - 1; j++)
	{
		m_ppObjects[j]->DoColide(playerX, playerZ);

		for (int k = j + 1; k < m_nObjects; k++) {
			if (m_ppObjects[j]->m_ColidePoint.SayHello(m_ppObjects[k]->m_ColidePoint)) {
				if (k != m_nObjects - 1) {
					XMFLOAT3 bufVector = m_ppObjects[j]->m_dirVector;
					m_ppObjects[j]->m_dirVector = m_ppObjects[k]->m_dirVector;
					m_ppObjects[k]->m_dirVector = bufVector;
				}
			}
		}
	}
	m_ppObjects[m_nObjects - 1]->DoColide(playerX, playerZ);
}


void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
#ifdef NEW_CODE
#pragma region [New Code]
	CShader::Render(pd3dCommandList, pCamera);
	UpdateShaderVariables(pd3dCommandList);
	UINT ncbGameObjectBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	D3D12_GPU_VIRTUAL_ADDRESS d3dcbGameObjectGpuVirtualAddress = m_pd3dcbGameObjects->GetGPUVirtualAddress();
	
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbGameObjectGpuVirtualAddress + (ncbGameObjectBytes * j));
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
#endif
#pragma endregion
#ifndef NEW_CODE
#pragma region [Old Code]
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
#endif
#pragma endregion
}

#pragma endregion

#pragma region [CTeRRainShader Part.]

CTerrainShader::CTerrainShader()
{
}
CTerrainShader::~CTerrainShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}
void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

#pragma endregion