
cbuffer ConstantBuffer
{
    float4x4 transformation;
    float4x4 rotation;    // the rotation matrix
    float4 lightVector;      // the light's vector
    float4 lightColor;      // the light's color
    float4 ambientColor;    // the ambient light's color
}

Texture2D Texture;
SamplerState ss;

struct VOut
{
	float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};


struct POut
{
	float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};





// Vertex Shader
VOut VShader(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VOut output;

    output.position = mul(transformation, position);


    // set the ambient light
    output.color = ambientColor;

    // calculate the diffuse light and add it to the ambient light

	float4 vectorBackToLight = -lightVector;
    float4 adjustedNormal = normalize(mul(rotation, normal));//    float4 adjustedNormal = normalize(mul(rotation, normal));
    
	adjustedNormal = normalize(adjustedNormal);
	
	float diffusebrightness = saturate(dot(adjustedNormal, vectorBackToLight));
    output.color += lightColor * diffusebrightness;
/*
	output.texcoord = texcoord + 2.51;
*/
    return output;
}




// Pixel shader
float4 PShader(float4 position : POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
//	float4 textureColor;
//	float3 lightDir;
//   float  lightIntensity;
//	float4  ambientColor;
 //   POut output;

/*



	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
//    return color * Texture.Sample(ss, texcoord);
	textureColor = Texture.Sample(ss, texcoord);

	// Set the default output color to the ambient light value for all pixels.
    ambientColor = color;	
	
// Invert the light direction for calculations.
    lightDir = -lightVector;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(texcoord, lightDir)) + 10.1;

    if(lightIntensity > 0.0f)
    {
        // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
        color += (lightColor * lightIntensity);
    }

    // Saturate the final light color.
    color = saturate(ambientColor);

	//The texture pixel is combined with the light color to create the final color result.

    // Multiply the texture pixel and the final light color to get the result.
    color = color * textureColor;
*/


	return color;
}
