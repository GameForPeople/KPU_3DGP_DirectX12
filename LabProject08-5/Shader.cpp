//-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"
#include "DDSTextureLoader12.h"

CShader::CShader()
{
	m_d3dSrvCPUDescriptorStartHandle.ptr = NULL;
	m_d3dSrvGPUDescriptorStartHandle.ptr = NULL;
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i]) m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
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

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, NULL);

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
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

#ifdef NEW_CODE_9

D3D12_RASTERIZER_DESC CObjectsShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	//d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;

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

#endif

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
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
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateCbvAndSrvDescriptorHeaps(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
}

void CShader::CreateConstantBufferViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		D3D12_CPU_DESCRIPTOR_HANDLE d3dCbvCPUDescriptorHandle;
		d3dCbvCPUDescriptorHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * j);
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, d3dCbvCPUDescriptorHandle);
	}
}

D3D12_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc(D3D12_RESOURCE_DESC d3dResourceDesc, UINT nTextureType)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc;
	d3dShaderResourceViewDesc.Format = d3dResourceDesc.Format;
	d3dShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	switch (nTextureType)
	{
	case RESOURCE_TEXTURE2D: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 1)
	case RESOURCE_TEXTURE2D_ARRAY:
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		d3dShaderResourceViewDesc.Texture2D.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2D.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_TEXTURE2DARRAY: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize != 1)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
		d3dShaderResourceViewDesc.Texture2DArray.MipLevels = -1;
		d3dShaderResourceViewDesc.Texture2DArray.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.Texture2DArray.PlaneSlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ResourceMinLODClamp = 0.0f;
		d3dShaderResourceViewDesc.Texture2DArray.FirstArraySlice = 0;
		d3dShaderResourceViewDesc.Texture2DArray.ArraySize = d3dResourceDesc.DepthOrArraySize;
		break;
	case RESOURCE_TEXTURE_CUBE: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D)(d3dResourceDesc.DepthOrArraySize == 6)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		d3dShaderResourceViewDesc.TextureCube.MipLevels = -1;
		d3dShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
		d3dShaderResourceViewDesc.TextureCube.ResourceMinLODClamp = 0.0f;
		break;
	case RESOURCE_BUFFER: //(d3dResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
		d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		d3dShaderResourceViewDesc.Buffer.FirstElement = 0;
		d3dShaderResourceViewDesc.Buffer.NumElements = 0;
		d3dShaderResourceViewDesc.Buffer.StructureByteStride = 0;
		d3dShaderResourceViewDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		break;
	}
	return(d3dShaderResourceViewDesc);
}

void CShader::CreateShaderResourceViews(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CTexture *pTexture, UINT nRootParameterStartIndex, bool bAutoIncrement)
{
	D3D12_CPU_DESCRIPTOR_HANDLE d3dSrvCPUDescriptorHandle = m_d3dSrvCPUDescriptorStartHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE d3dSrvGPUDescriptorHandle = m_d3dSrvGPUDescriptorStartHandle;
	int nTextures = pTexture->GetTextureCount();
	int nTextureType = pTexture->GetTextureType();
	for (int i = 0; i < nTextures; i++)
	{
		ID3D12Resource *pShaderResource = pTexture->GetTexture(i);
		D3D12_RESOURCE_DESC d3dResourceDesc = pShaderResource->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = GetShaderResourceViewDesc(d3dResourceDesc, nTextureType);
		pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, d3dSrvCPUDescriptorHandle);
		d3dSrvCPUDescriptorHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;

		pTexture->SetRootArgument(i, (bAutoIncrement) ? (nRootParameterStartIndex + i) : nRootParameterStartIndex, d3dSrvGPUDescriptorHandle);
		d3dSrvGPUDescriptorHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
	}
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
}

void CShader::ReleaseShaderVariables()
{
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
}

void CShader::ReleaseUploadBuffers()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_ppd3dPipelineStates) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
	pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	UpdateShaderVariables(pd3dCommandList);
}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSPlayer", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSPlayer", "ps_5_1", ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTexturedShader::CTexturedShader()
{
}

CTexturedShader::~CTexturedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTexturedShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTexturedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextured", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTexturedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextured", "ps_5_1", ppd3dShaderBlob));
}

void CTexturedShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CObjectsShader::CObjectsShader()
{
}

CObjectsShader::~CObjectsShader()
{
}

void CObjectsShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes * m_nObjects, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbGameObjects->Map(0, NULL, (void **)&m_pcbMappedGameObjects);
}

void CObjectsShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	for (int j = 0; j < m_nObjects; j++)
	{
		CB_GAMEOBJECT_INFO *pbMappedcbGameObject = (CB_GAMEOBJECT_INFO *)((UINT8 *)m_pcbMappedGameObjects + (j * ncbElementBytes));
		XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World)));
	}
}

void CObjectsShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects)
	{
		m_pd3dcbGameObjects->Unmap(0, NULL);
		m_pd3dcbGameObjects->Release();
	}

	CTexturedShader::ReleaseShaderVariables();
}


#ifdef NEW_CODE_INSTANCING
void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
}
#else
void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

#ifdef NEW_CODE_5
	float fxPitch = 50.0f * 3.5f;
	float fyPitch = 50.0f * 3.5f;
	float fzPitch = 50.0f * 3.5f;
#else
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
#endif


#ifdef NEW_CODE_8
	m_nObjects = 400;
#else
	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = int(fTerrainWidth / fxPitch);
	int yObjects = 1;
	int zObjects = int(fTerrainLength / fzPitch);
	m_nObjects = (xObjects * yObjects * zObjects);
#endif

#ifdef NEW_CODE_9
	//m_nObjects = 1500;
	m_nObjects = 30000;

#endif

#ifdef NEW_CODE_9
	CTexture *pTexture = new CTexture(2, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Trees/Trees.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Grasses/Grass.dds", 1);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 2);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 3, false);

#else
	//NEW_CODE_7
	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Trees/Trees.dds", 0);

	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Grasses/Grass.dds", 0);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 3, false);
#endif

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

#ifdef NEW_CODE_7
	CFaceMeshTextured *pFaceMesh = new CFaceMeshTextured(pd3dDevice, pd3dCommandList, 50.0f, 50.0f, 0);
	CFaceMeshTextured *pGrassMesh = new CFaceMeshTextured(pd3dDevice, pd3dCommandList, 20.0f, 30.0f, 1);

#else 
	CCubeMeshTextured *pCubeMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 50.0f, 50.0f, 0.1f);
	//CCubeMeshTextured *pCubeMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
#endif

	m_ppObjects = new CGameObject*[m_nObjects];
	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;

#ifdef NEW_CODE_9
	CBillboardObject *pRotatingObject = NULL;
	CGrassObject *pGrassObject = NULL;
#else	//NEW_CODE_3
	CBillboardObject *pRotatingObject = NULL;
	//CRotatingObject *pRotatingObject = NULL;
#endif

	for (int i = 0; i < m_nObjects; i)
	{

#ifdef NEW_CODE_9
		if (i < 400) {
			pRotatingObject = new CBillboardObject(1);
			pRotatingObject->SetMesh(0, pFaceMesh);
		}
		else {
			pGrassObject = new CGrassObject(1);
			pGrassObject->SetMesh(0, pGrassMesh);
		}
#else //NEW_CODE_3
		pRotatingObject = new CBillboardObject(1);
#endif

#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif

#ifdef NEW_CODE_9
		float xPosition;
		float zPosition;

		if (i < 100) {
			xPosition = (i % 10) * 50;
			zPosition = (i / 10) * 50;
		}
		else if (i < 200) {
			xPosition = ((i - 100) % 10) * 50 + 1550;
			zPosition = ((i - 100) / 10) * 50 + 1550;
		}
		else if (i < 300) {
			xPosition = ((i - 200) % 10) * 50 + 1550;
			zPosition = ((i - 200) / 10) * 50;
		}
		else if (i < 400) {
			xPosition = ((i - 300) % 10) * 50;
			zPosition = ((i - 300) / 10) * 50 + 1500;
		}
		else if (i < (m_nObjects - 400) / 2 + 400) {
			xPosition = rand() % 2000;
			zPosition = rand() % 900 + 600;
			//xPosition = rand() % 200 + 900;
			//zPosition = rand() % 200 + 900;
		}
		else if (i < m_nObjects) {
			xPosition = rand() % 900 + 600;
			zPosition = rand() % 2000;
			//xPosition = rand() % 200 + 900;
			//zPosition = rand() % 200 + 900;
		}

		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		if (i < 400) {
			pRotatingObject->SetPosition(xPosition, fHeight + 25.0f, zPosition);

			pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppObjects[i++] = pRotatingObject;
		}
		else {
			pGrassObject->SetPosition(xPosition, fHeight, zPosition);
			pGrassObject->Rotate((0.0f, 1.0f, 0.0f), (float)(rand() % 360));
			pGrassObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
			pGrassObject->SetRotationSpeed(4.0f * (i % 4) + 12.0f);
			pGrassObject->SetRotatePower(((i % 4) + 1) * 14);

			pGrassObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppObjects[i++] = pGrassObject;
		}

#else	//NEW_CODE_8
		float xPosition;
		float zPosition;

		if (i < 100) {
			xPosition = (i % 10) * 50;
			zPosition = (i / 10) * 50;
		}
		else if (i < 200) {
			xPosition = ((i - 100) % 10) * 50 + 1550;
			zPosition = ((i - 100) / 10) * 50 + 1550;
		}
		else if (i < 300) {
			xPosition = ((i - 200) % 10) * 50 + 1550;
			zPosition = ((i - 200) / 10) * 50;
		}
		else if (i < 400) {
			xPosition = ((i - 300) % 10) * 50;
			zPosition = ((i - 300) / 10) * 50 + 1500;
		}
		else {
			xPosition = 1000;
			zPosition = 1000;
		}

		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		pRotatingObject->SetPosition(xPosition, fHeight + 25.0f, zPosition);
		//if (y == 0)
		//{
		//	xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
		//	xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
		//	if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
		//	float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
		//	pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
		//}
		//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppObjects[i++] = pRotatingObject;
#endif
	}
}
#endif

#ifndef NEW_CODE_8
void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;

	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = int(fTerrainWidth / fxPitch);
	int yObjects = 2;
	int zObjects = int(fTerrainLength / fzPitch);
	m_nObjects = (xObjects * yObjects * zObjects);

	CTexture *pTexture = new CTexture(6, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/Stone.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/rocks2.dds", 1);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/brick02.dds", 2);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/brick01.dds", 3);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/Stone.dds", 4);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"../Assets/Image/Miscellaneous/brick01.dds", 5);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 6);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 3, false);

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

	CCubeMeshTextured *pCubeMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);

	m_ppObjects = new CGameObject*[m_nObjects];

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
#ifndef _WITH_BATCH_MATERIAL
				pRotatingObject->SetMaterial(pCubeMaterial);
#endif
				float xPosition = x * fxPitch;
				float zPosition = z * fzPitch;
				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
				pRotatingObject->SetPosition(xPosition, fHeight + (y * 3.0f * fyPitch) + 6.0f, zPosition);
				if (y == 0)
				{
					xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
					xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
					if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
					float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
					pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
				}
				pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
				pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
				pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
				m_ppObjects[i++] = pRotatingObject;
			}
		}
	}
}
#endif

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) delete m_pMaterial;
#endif
}

void CObjectsShader::AnimateObjects(float fTimeElapsed, CCamera *pCamera)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed, pCamera);
	}
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) m_ppObjects[j]->ReleaseUploadBuffers();
	}

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->ReleaseUploadBuffers();
#endif
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CTexturedShader::Render(pd3dCommandList, pCamera);

#ifdef _WITH_BATCH_MATERIAL
	if (m_pMaterial) m_pMaterial->UpdateShaderVariables(pd3dCommandList);
#endif

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->Render(pd3dCommandList, pCamera);
	}
}

#ifdef NEW_CODE_INSTANCING
CInstancingShader::CInstancingShader()
{
}
CInstancingShader::~CInstancingShader()
{
}

D3D12_INPUT_LAYOUT_DESC CInstancingShader::CreateInputLayout()
{
	/*
	UINT nInputElementDescs = 7;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
	D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	//정점 정보를 위한 입력 원소이다.
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	//인스턴싱 정보를 위한 입력 원소이다.
	pd3dInputElementDescs[2] = { "WORLDMATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,
	D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[3] = { "WORLDMATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16,
	D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[4] = { "WORLDMATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32,
	D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[5] = { "WORLDMATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48,
	D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[6] = { "INSTANCECOLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,
	64, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
	*/
	UINT nInputElementDescs = 7;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	//인스턴싱 정보를 위한 입력 원소이다.
	pd3dInputElementDescs[2] = { "WORLDMATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[3] = { "WORLDMATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16,D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[4] = { "WORLDMATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32,D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[5] = { "WORLDMATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48,D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	pd3dInputElementDescs[6] = { "INSTANCETEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 64, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CInstancingShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSInstancing", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CInstancingShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSInstancing", "ps_5_1",
		ppd3dShaderBlob));
}

void CInstancingShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	//UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수

	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CInstancingShader::CreateShaderVariables(ID3D12Device *pd3dDevice,
	ID3D12GraphicsCommandList *pd3dCommandList)
{
	//UINT ncbElementBytes = ((sizeof(VS_VB_INSTANCE) + 255) & ~255);

	//인스턴스 정보를 저장할 정점 버퍼를 업로드 힙 유형으로 생성한다.
	m_pd3dcbGameObjects = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL,
		sizeof(VS_VB_INSTANCE) * m_nObjects, D3D12_HEAP_TYPE_UPLOAD,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);
	//정점 버퍼(업로드 힙)에 대한 포인터를 저장한다.
	m_pd3dcbGameObjects->Map(0, NULL, (void **)& m_pcbMappedGameObjects);
	//정점 버퍼에 대한 뷰를 생성한다.
	m_d3dInstancingBufferView.BufferLocation =
		m_pd3dcbGameObjects->GetGPUVirtualAddress();
	m_d3dInstancingBufferView.StrideInBytes = sizeof(VS_VB_INSTANCE);
	m_d3dInstancingBufferView.SizeInBytes = sizeof(VS_VB_INSTANCE) * m_nObjects;
}

void CInstancingShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObjects) m_pd3dcbGameObjects->Unmap(0, NULL);
	if (m_pd3dcbGameObjects) m_pd3dcbGameObjects->Release();
}

//인스턴싱 정보(객체의 월드 변환 행렬과 색상)를 정점 버퍼에 복사한다.
void CInstancingShader::UpdateShaderVariables(ID3D12GraphicsCommandList
	*pd3dCommandList)
{
	/*

	*/
	//UINT ncbElementBytes = ((sizeof(VS_VB_INSTANCE) + 255) & ~255);

	for (int j = 0; j < m_nObjects; j++)
	{
		//m_pcbMappedGameObjects[j].m_xmf2TexCoord = (j % 2) ? XMFLOAT2(0.5f, 0.0f, 0.0f, 0.0f) :
		//	XMFLOAT2(0.0f, 0.0f, 0.5f, 0.0f); 여기 원래 텍스쳐 코드넘겨줘야하는데 안넘겨줘도되네 ..ㅎㅎㅎ왤까?
		XMStoreFloat4x4(&m_pcbMappedGameObjects[j].m_xmf4x4Transform,
			XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World)));
	}
}

void CInstancingShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	/*
	int xObjects = 10, yObjects = 10, zObjects = 10, i = 0;
	m_nObjects = (xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	m_ppObjects = new CGameObject*[m_nObjects];
	float fxPitch = 12.0f * 2.5f;
	float fyPitch = 12.0f * 2.5f;
	float fzPitch = 12.0f * 2.5f;
	CRotatingObject *pRotatingObject = NULL;
	for (int x = -xObjects; x <= xObjects; x++)
	{
	for (int y = -yObjects; y <= yObjects; y++)
	{
	for (int z = -zObjects; z <= zObjects; z++)
	{
	pRotatingObject = new CRotatingObject();
	pRotatingObject->SetPosition(fxPitch*x, fyPitch*y, fzPitch*z);
	pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingObject->SetRotationSpeed(10.0f*(i % 10));
	m_ppObjects[i++] = pRotatingObject;
	}
	}
	}
	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.
	CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
	12.0f, 12.0f, 12.0f);
	m_ppObjects[0]->SetMesh(pCubeMesh);
	//인스턴싱을 위한 정점 버퍼와 뷰를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	*/

	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)pContext;

#ifdef NEW_CODE_5
	float fxPitch = 50.0f * 3.5f;
	float fyPitch = 50.0f * 3.5f;
	float fzPitch = 50.0f * 3.5f;
#else
	float fxPitch = 12.0f * 3.5f;
	float fyPitch = 12.0f * 3.5f;
	float fzPitch = 12.0f * 3.5f;
#endif


#ifdef NEW_CODE_8
	m_nObjects = 400;
#else
	float fTerrainWidth = pTerrain->GetWidth();
	float fTerrainLength = pTerrain->GetLength();

	int xObjects = int(fTerrainWidth / fxPitch);
	int yObjects = 1;
	int zObjects = int(fTerrainLength / fzPitch);
	m_nObjects = (xObjects * yObjects * zObjects);
#endif

#ifdef NEW_CODE_9
	//m_nObjects = 1500;
	m_nObjects = 3000;
	m_nObjects2 = 0; // 27000;

#endif

#ifdef NEW_CODE_9
	CTexture *pTexture = new CTexture(2, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Trees/Trees_3.dds", 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Grasses/Grass_6.dds", 1);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 2);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 3, false);

#else
	//NEW_CODE_7
	CTexture *pTexture = new CTexture(1, RESOURCE_TEXTURE2D_ARRAY, 0);
	pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Trees/Trees.dds", 0);

	//pTexture->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Assets/Image/Grasses/Grass.dds", 0);

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	CreateCbvAndSrvDescriptorHeaps(pd3dDevice, pd3dCommandList, m_nObjects, 1);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, pd3dCommandList, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, pd3dCommandList, pTexture, 3, false);
#endif

#ifdef _WITH_BATCH_MATERIAL
	m_pMaterial = new CMaterial();
	m_pMaterial->SetTexture(pTexture);
#else
	CMaterial *pCubeMaterial = new CMaterial();
	pCubeMaterial->SetTexture(pTexture);
#endif

#ifdef NEW_CODE_7
	CFaceMeshTextured *pFaceMesh = new CFaceMeshTextured(pd3dDevice, pd3dCommandList, 50.0f, 50.0f, 0);
	CFaceMeshTextured *pGrassMesh = new CFaceMeshTextured(pd3dDevice, pd3dCommandList, 20.0f, 30.0f, 1);

#else 
	CCubeMeshTextured *pCubeMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 50.0f, 50.0f, 0.1f);
	//CCubeMeshTextured *pCubeMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
#endif

	m_ppObjects = new CGameObject*[m_nObjects];
	//DIS
	//m_ppObjects2 = new CGameObject*[m_nObjects2];

	XMFLOAT3 xmf3RotateAxis, xmf3SurfaceNormal;

#ifdef NEW_CODE_9
	CBillboardObject *pRotatingObject = NULL;
	CGrassObject *pGrassObject = NULL;
#else	//NEW_CODE_3
	CBillboardObject *pRotatingObject = NULL;
	//CRotatingObject *pRotatingObject = NULL;
#endif

	/*
	for (int i = 0; i < m_nObjects; i)
	{

#ifdef NEW_CODE_9
		if (i < 400) {
			pRotatingObject = new CBillboardObject(1);
			//pRotatingObject->SetMesh(0, pFaceMesh);
		}
		else {
			pGrassObject = new CGrassObject(1);
			//pGrassObject->SetMesh(0, pGrassMesh);
		}
#else //NEW_CODE_3
		pRotatingObject = new CBillboardObject(1);
#endif

#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif

#ifdef NEW_CODE_9
		float xPosition;
		float zPosition;

		if (i < 100) {
			xPosition = (i % 10) * 50;
			zPosition = (i / 10) * 50;
		}
		else if (i < 200) {
			xPosition = ((i - 100) % 10) * 50 + 1550;
			zPosition = ((i - 100) / 10) * 50 + 1550;
		}
		else if (i < 300) {
			xPosition = ((i - 200) % 10) * 50 + 1550;
			zPosition = ((i - 200) / 10) * 50;
		}
		else if (i < 400) {
			xPosition = ((i - 300) % 10) * 50;
			zPosition = ((i - 300) / 10) * 50 + 1500;
		}
		else if (i < (m_nObjects - 400) / 2 + 400) {
			xPosition = rand() % 2000;
			zPosition = rand() % 900 + 600;
			//xPosition = rand() % 200 + 900;
			//zPosition = rand() % 200 + 900;
		}
		else if (i < m_nObjects) {
			xPosition = rand() % 900 + 600;
			zPosition = rand() % 2000;
			//xPosition = rand() % 200 + 900;
			//zPosition = rand() % 200 + 900;
		}

		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		if (i < 400) {
			pRotatingObject->SetPosition(xPosition, fHeight + 25.0f, zPosition);

			pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppObjects[i++] = pRotatingObject;
		}
		else {
			pGrassObject->SetPosition(xPosition, fHeight, zPosition);
			pGrassObject->Rotate((0.0f, 1.0f, 0.0f), (float)(rand() % 360));
			pGrassObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
			pGrassObject->SetRotationSpeed(4.0f * (i % 4) + 12.0f);
			pGrassObject->SetRotatePower(((i % 4) + 1) * 14);

			pGrassObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
			m_ppObjects[i++] = pGrassObject;
		}

#else	//NEW_CODE_8
		float xPosition;
		float zPosition;

		if (i < 100) {
			xPosition = (i % 10) * 50;
			zPosition = (i / 10) * 50;
		}
		else if (i < 200) {
			xPosition = ((i - 100) % 10) * 50 + 1550;
			zPosition = ((i - 100) / 10) * 50 + 1550;
		}
		else if (i < 300) {
			xPosition = ((i - 200) % 10) * 50 + 1550;
			zPosition = ((i - 200) / 10) * 50;
		}
		else if (i < 400) {
			xPosition = ((i - 300) % 10) * 50;
			zPosition = ((i - 300) / 10) * 50 + 1500;
		}
		else {
			xPosition = 1000;
			zPosition = 1000;
		}

		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		pRotatingObject->SetPosition(xPosition, fHeight + 25.0f, zPosition);
		//if (y == 0)
		//{
		//	xmf3SurfaceNormal = pTerrain->GetNormal(xPosition, zPosition);
		//	xmf3RotateAxis = Vector3::CrossProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal);
		//	if (Vector3::IsZero(xmf3RotateAxis)) xmf3RotateAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
		//	float fAngle = acos(Vector3::DotProduct(XMFLOAT3(0.0f, 1.0f, 0.0f), xmf3SurfaceNormal));
		//	pRotatingObject->Rotate(&xmf3RotateAxis, XMConvertToDegrees(fAngle));
		//}
		//pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		//pRotatingObject->SetRotationSpeed(36.0f * (i % 10) + 36.0f);
		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppObjects[i++] = pRotatingObject;
#endif
	}
	*/
	//인스턴싱을 사용하여 렌더링하기 위하여 하나의 게임 객체만 메쉬를 가진다.

for (int i = 0; i < m_nObjects; i) {
		pRotatingObject = new CBillboardObject(1);

#ifndef _WITH_BATCH_MATERIAL
		pRotatingObject->SetMaterial(pCubeMaterial);
#endif
		float xPosition = rand() % 2000;
		float zPosition = rand() % 2000;

		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		pRotatingObject->SetPosition(xPosition, fHeight + 25.0f, zPosition);

		pRotatingObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * i));
		m_ppObjects[i++] = pRotatingObject;
	}
	m_ppObjects[0]->SetMesh(0, pFaceMesh);
	//m_ppObjects2[0]->SetMesh(0, pGrassMesh);

	//pRotatingObject->SetMesh(0, pFaceMesh);
	//pGrassObject->SetMesh(0, pGrassMesh);

	//인스턴싱을 위한 정점 버퍼와 뷰를 생성한다.
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CInstancingShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera
	*pCamera)
{
	CObjectsShader::Render(pd3dCommandList, pCamera);
	//모든 게임 객체의 인스턴싱 데이터를 버퍼에 저장한다.
	UpdateShaderVariables(pd3dCommandList);
	//하나의 정점 데이터를 사용하여 모든 게임 객체(인스턴스)들을 렌더링한다.
	m_ppObjects[0]->Render(pd3dCommandList, pCamera, 400, m_d3dInstancingBufferView);
	m_ppObjects[400]->Render(pd3dCommandList, pCamera, m_nObjects, m_d3dInstancingBufferView);
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTerrainShader::CTerrainShader()
{
}

CTerrainShader::~CTerrainShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
#ifdef NEW_CODE_1
	UINT nInputElementDescs = 5;
#else
	UINT nInputElementDescs = 4;
#endif
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[2] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[3] = { "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

#ifdef NEW_CODE_1
	pd3dInputElementDescs[4] = { "TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
#endif

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTerrain", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTerrain", "ps_5_1", ppd3dShaderBlob));
}

void CTerrainShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CSkyBoxShader::CSkyBoxShader()
{
}

CSkyBoxShader::~CSkyBoxShader()
{
}

D3D12_DEPTH_STENCIL_DESC CSkyBoxShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	d3dDepthStencilDesc.DepthEnable = FALSE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0xff;
	d3dDepthStencilDesc.StencilWriteMask = 0xff;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_DECR;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	return(d3dDepthStencilDesc);
}

D3D12_SHADER_BYTECODE CSkyBoxShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSSkyBox", "ps_5_1", ppd3dShaderBlob));
}

void CSkyBoxShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}


