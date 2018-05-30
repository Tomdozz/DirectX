
cbuffer MatrixBuffer : register(b0)
{
	matrix ModelToWorldMatrix;
	matrix WorldToViewMatrix;
	matrix ProjectionMatrix;
};

struct VSIn
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float2 TexCoord : TEX;

	//float3 normalModel:NORMALl0;
	//float3 normalView : NORMAL1;
	//float3 color : COLOR0;
	//float3 backColor : COLOR1;
};

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
	float4 WorldPos : POSITION;

	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	
	//float3 normalModel:NORMALl0;
	//float3 normalView : NORMAL1;
	//float3 color : COLOR0;
	//float3 backColor : COLOR1;
};

//-----------------------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------------------

PSIn VS_main(VSIn input)
{
	PSIn output = (PSIn)0;
	
	// Model->View transformation
	matrix MV = mul(WorldToViewMatrix, ModelToWorldMatrix);

	// Model->View->Projection (clip space) transformation
	// SV_Position expects the output position to be in clip space
	matrix MVP = mul(ProjectionMatrix, MV);
	
	// Perform transformations and send to output
	output.Pos = mul(MVP, float4(input.Pos, 1));
	output.Normal = normalize( mul(ModelToWorldMatrix, float4(input.Normal,0)).xyz );
	
	output.Binormal = normalize( mul(ModelToWorldMatrix, float4(input.Binormal,0)).xyz );
	output.Tangent = normalize( mul(ModelToWorldMatrix, float4(input.Tangent,0)).xyz );
	
	output.TexCoord = input.TexCoord;
	output.WorldPos = mul(ModelToWorldMatrix, float4(input.Pos,1));
	
	//---Cal Tangent and binormal-----
	//output.Tangent = mul(input.Tangent, (float3)(ModelToWorldMatrix,1));
	//output.Tangent = normalize(output.Tangent);
	//
	//output.Binormal = mul(input.Binormal, (float3)(ModelToWorldMatrix,0));
	//output.Binormal = normalize(output.Binormal);

	//output.Tangent = mul(ModelToWorldMatrix, float4(input.Tangent,0)).xyz;
	//output.Tangent = normalize(output.Tangent);
	//output.Tangent = normalize(output.Tangent - dot(output.Tangent, output.Normal) * output.Normal);
	//output.Binormal = mul(ModelToWorldMatrix, float4(input.Binormal,0)).xyz;
	//output.Binormal = normalize(output.Binormal);

	//output.Tangent = mul(float4(input.Tangent,0), ModelToWorldMatrix);
	//output.Tangent = normalize(output.Tangent);
	//
	//output.Binormal = mul(float4(input.Binormal,0), ModelToWorldMatrix);
	//output.Binormal = normalize(output.Binormal);
	
	//--------------------------------------------------------------

	//output.normalModel = input.Normal.xyz;
	//output.normalView = input.Normal.xyz;
	//
	//output.color = input.color;
	//output.backColor = input.backColor;
	
	return output;
}