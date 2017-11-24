//#define _WITH_CONSTANT_BUFFER_SYNTAX
#define NEW_CODE_1 //-->이거하면 스카이박스 안나옴;; //이제 잘나옴!!!!!!!히히
#define NEW_CODE_2 //--> 알파값을 검색하여 0인 친구들을 삭제해주는 작업을 할거야!
#define NEW_CODE_9 //--> 본코드 9번놈에서 정의된 짓을 할꺼야! --> 텍스쳐 어레이 인자2로 늘리고, 포지션으로 거짓말할꺼야..어 아니면 받은 인자개수알수있다면??
#define NEW_CODE_10//---> 기존의 포지션이 아닌 UV좌표를 활용해서 이를 구분

#define NEW_CODE_INSTANCING


#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
struct CB_PLAYER_INFO
{
	matrix		mtxWorld;
}; 

struct CB_GAMEOBJECT_INFO
{
	matrix		mtxWorld;
};

struct CB_CAMERA_INFO
{
	matrix		mtxView;
	matrix		mtxProjection;
};

ConstantBuffer<CB_PLAYER_INFO> gcbPlayerObjectInfo : register(b0);
ConstantBuffer<CB_CAMERA_INFO> gcbCameraInfo : register(b1);
ConstantBuffer<CB_GAMEOBJECT_INFO> gcbGameObjectInfo : register(b2);
#else
cbuffer cbPlayerInfo : register(b0)
{
	matrix		gmtxPlayerWorld : packoffset(c0);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
};

cbuffer cbGameObjectInfo : register(b2)
{
	matrix		gmtxWorld : packoffset(c0);
};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct VS_DIFFUSED_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_DIFFUSED_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_DIFFUSED_OUTPUT VSDiffused(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif

	output.color = input.color;

	return(output);
}

float4 PSDiffused(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
VS_DIFFUSED_OUTPUT VSPlayer(VS_DIFFUSED_INPUT input)
{
	VS_DIFFUSED_OUTPUT output;

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbPlayerObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxPlayerWorld), gmtxView), gmtxProjection);
#endif
	output.color = input.color;

	return(output);
}

float4 PSPlayer(VS_DIFFUSED_OUTPUT input) : SV_TARGET
{
	return(input.color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef NEW_CODE_9
Texture2D gtxtTextures[2] : register(t0);
#else
Texture2D gtxtTextures[1] : register(t0);
#endif

SamplerState gWrapSamplerState : register(s0);
SamplerState gClampSamplerState : register(s1);

struct VS_TEXTURED_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_TEXTURED_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
   
    #ifdef NEW_CODE_9
    bool isGrass : GRASS;
    #endif
};

#ifdef NEW_CODE_INSTANCING
//정점 데이터와 인스턴싱 데이터를 위한 구조체이다.
struct VS_INSTANCING_INPUT
{
    float3 position : POSITION;
    //float4 color : COLOR;
    float2 uv : TEXCOORD;

    float4x4 mtxTransform : WORLDMATRIX;
    float2 instanceuv : INSTANCETEXCOORD;
};

struct VS_INSTANCING_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    int1 isGrass : GRASS;
};

VS_INSTANCING_OUTPUT VSInstancing(VS_INSTANCING_INPUT input)
{
    VS_INSTANCING_OUTPUT output;

    //if (input.uv.x >= 2.0f || input.uv.y >= 2.0f)
    //{
    //    output.isGrass = true;
    //    input.uv.x -= 2.0f;
    //    input.uv.y -= 2.0f;
    //}
    if (input.instanceuv.g == 1.0f)
    {
        if (input.instanceuv.r < 3000.0f)
        {
            output.isGrass = 2;
        }
        else
        {
            output.isGrass = 1;
        }
    }
    else
    {
        output.isGrass = 0;
    }
        output.position = mul(mul(mul(float4(input.position, 1.0f), input.mtxTransform),
gmtxView), gmtxProjection);
    
    output.uv = input.uv;
    return (output);
}

float4 PSInstancing(VS_INSTANCING_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET
{
#ifdef NEW_CODE_9
    float4 cColor;
    if (input.isGrass == 1)
        cColor = gtxtTextures[NonUniformResourceIndex((nPrimitiveID + 2) / 2)].Sample(gWrapSamplerState, input.uv);
    else if(input.isGrass == 0)
    {
        cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID / 2)].Sample(gWrapSamplerState, input.uv);
    }
    else if (input.isGrass == 2)
    {
        clip(-73);
    }
#else
    float4 cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID/2)].Sample(gWrapSamplerState, input.uv);
#endif

    
#ifdef NEW_CODE_2
  
    if (cColor.a <= 0.9f)
    {
        clip(-73);
    }
    
    if(input.isGrass == 1)
        if(cColor.r <= 0.1 && cColor.g <= 0.1 && cColor.b <= 0.1)
            clip(-73);

    if(input.isGrass == 2)
        clip(-73);

   //if (!input.isGrass)
    //    input.isGrass = true;

    return (cColor);

#else
        return (cColor);
#endif
    return (cColor);
}

#endif

VS_TEXTURED_OUTPUT VSTextured(VS_TEXTURED_INPUT input)
{
	VS_TEXTURED_OUTPUT output;

	#ifdef NEW_CODE_10
    if (input.uv.x >= 2.0f || input.uv.y >= 2.0f)
    {
        output.isGrass = true;
        input.uv.x -= 2.0f;
        input.uv.y -= 2.0f;
    }
    else 
        output.isGrass = false;
    #else // NEW_CODE_9
    float4 bufferPos = mul(float4(input.position, 1.0f), gmtxWorld);
    if (bufferPos.x >= 600 && bufferPos.x <= 1400)
        output.isGrass = true;
    else 
        output.isGrass = false;
    #endif

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
    //#ifdef NEW_CODE_9
    //output.position = mul(mul(bufferPos, gmtxView), gmtxProjection);
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif
	output.uv = input.uv;

	return(output);
}

float4 PSTextured(VS_TEXTURED_OUTPUT input, uint nPrimitiveID : SV_PrimitiveID) : SV_TARGET
{
/*
	float4 cColor;
	if (nPrimitiveID < 2)
		cColor = gtxtTextures[0].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 4)
		cColor = gtxtTextures[1].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 6)
		cColor = gtxtTextures[2].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 8)
		cColor = gtxtTextures[3].Sample(gWrapSamplerState, input.uv);
	else if (nPrimitiveID < 10)
		cColor = gtxtTextures[4].Sample(gWrapSamplerState, input.uv);
	else
		cColor = gtxtTextures[5].Sample(gWrapSamplerState, input.uv);
*/
	#ifdef NEW_CODE_9
    float4 cColor;
    if (input.isGrass == true)
        cColor = gtxtTextures[NonUniformResourceIndex((nPrimitiveID + 2) / 2)].Sample(gWrapSamplerState, input.uv);
    else
        cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID/2)].Sample(gWrapSamplerState, input.uv);
    #else
    float4 cColor = gtxtTextures[NonUniformResourceIndex(nPrimitiveID/2)].Sample(gWrapSamplerState, input.uv);
    #endif

    
#ifdef NEW_CODE_2
  
    if (cColor.a <= 0.9f)
    {
       // cColor.g = 0; //? 이새낑 뭔데
      clip(-1);

      return (cColor);
    }
    else
        return (cColor);

#else
        return (cColor);
#endif

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Texture2D gtxtTerrainBaseTexture : register(t6);
Texture2D gtxtTerrainDetailTexture : register(t7);
Texture2D gtxtTerrainDetailTexture2 : register(t8);

struct VS_TERRAIN_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0;
	float2 uv1 : TEXCOORD1;
#ifdef NEW_CODE_1
    float2 uv2 : TEXCOORD2;
#endif
};


struct VS_TERRAIN_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv0 : TEXCOORD0;
	float2 uv1 : TEXCOORD1;
#ifdef NEW_CODE_1
    float2 uv2 : TEXCOORD2;
#endif

};

VS_TERRAIN_OUTPUT VSTerrain(VS_TERRAIN_INPUT input)
{
	VS_TERRAIN_OUTPUT output;

#ifdef _WITH_CONSTANT_BUFFER_SYNTAX
	output.position = mul(mul(mul(float4(input.position, 1.0f), gcbGameObjectInfo.mtxWorld), gcbCameraInfo.mtxView), gcbCameraInfo.mtxProjection);
#else
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
#endif
	output.color = input.color;
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;

    #ifdef NEW_CODE_1
	output.uv2 = input.uv2;
    #endif


	return(output);
}

float4 PSTerrain(VS_TERRAIN_OUTPUT input) : SV_TARGET
{
	float4 cBaseTexColor = gtxtTerrainBaseTexture.Sample(gWrapSamplerState, input.uv0);
	float4 cDetailTexColor = gtxtTerrainDetailTexture.Sample(gWrapSamplerState, input.uv1);

    #ifdef NEW_CODE_1
    float4 cDetailTexColor2 = gtxtTerrainDetailTexture2.Sample(gWrapSamplerState, input.uv2);
    #endif
	
    #ifdef NEW_CODE_1
   // float4 cColor = input.color * saturate((cBaseTexColor * 0.05f) + (cDetailTexColor * 0.25f) + (cDetailTexColor2 * 0.7f));
    float4 cColor = input.color * saturate((cBaseTexColor * 0.05f) + (cDetailTexColor * 0.05f) + (cDetailTexColor2 * 0.9f));
   
    #else
    float4 cColor = input.color * saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f));
    #endif

	return(cColor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifdef NEW_CODE_1
Texture2D gtxtSkyBox : register(t9);
#else
Texture2D gtxtSkyBox : register(t8);
#endif

float4 PSSkyBox(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float4 cColor = gtxtSkyBox.Sample(gClampSamplerState, input.uv);

	return(cColor);
}
