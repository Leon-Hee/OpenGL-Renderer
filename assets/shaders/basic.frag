#version 410 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 WorldPosition;
in vec4 v_LightSpacePosition;

out vec4 FragColor;

uniform vec3 u_LightDirection;
uniform vec3 u_LightPosition;
uniform int u_LightType;
uniform float u_Intensity;
uniform float u_LightConstant;
uniform float u_LightLinear;
uniform float u_LightQuadratic;
uniform float u_LightInnerCutoff;
uniform float u_LightOuterCutoff;
uniform vec3 u_LightColor;

uniform sampler2D u_DiffuseTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_ShadowMap;

void main()
{
    vec3 shadowCoords =
        v_LightSpacePosition.xyz /
        v_LightSpacePosition.w;

    shadowCoords =
        shadowCoords * 0.5 + 0.5;

    float shadowDepth =
        texture(
            u_ShadowMap,
            shadowCoords.xy
        ).r;



    float currentDepth =
        shadowCoords.z;

    float bias = 0.005;

    float shadow = 0.0;

    if (

        shadowCoords.x >= 0.0 &&

        shadowCoords.x <= 1.0 &&

        shadowCoords.y >= 0.0 &&

        shadowCoords.y <= 1.0 &&

        shadowCoords.z >= 0.0 &&

        shadowCoords.z <= 1.0

    )

    {

        float shadowDepth =

            texture(

                u_ShadowMap,

                shadowCoords.xy

            ).r;

        float currentDepth =

            shadowCoords.z;

        float bias = 0.0001;

        if (currentDepth > shadowDepth + bias)

        {

            shadow = 1.0;

        }

    }

    // 1. 从 Normal Map 采样 Tangent-space Normal
    vec3 tangentNormal =
        texture(u_NormalTexture, TexCoords).rgb;

    // 2. [0, 1] → [-1, 1]
    tangentNormal =
        tangentNormal * 2.0 - 1.0;

    // 3. 规范化 World-space Normal
    vec3 N =
        normalize(Normal);

    // 4. 重新正交化 Tangent
    vec3 T =
        normalize(
            Tangent -
            dot(Tangent, N) * N
        );

    // 5. 计算 Bitangent
    vec3 B =
        normalize(
            cross(N, T)
        );

    // 6. 构建 TBN Matrix
    mat3 TBN =
        mat3(T, B, N);

    // 7. Tangent Space → World Space
    vec3 worldNormal =
        normalize(
            TBN * tangentNormal
        );

    // 8. 根据 Light Type 计算光线方向
    vec3 lightDirection;
    float attenuation = 1.0;
    float spotIntensity = 1.0;

    if (u_LightType == 0)
    {
        // Directional Light
        lightDirection =
            normalize(u_LightDirection);
    }
    else if (u_LightType == 1)
    {
        // Point Light
        lightDirection =
            normalize(
                u_LightPosition - WorldPosition
            );

        float distance =
            length(
                u_LightPosition - WorldPosition
            );

        attenuation =
            1.0 /
            (
                u_LightConstant +
                u_LightLinear * distance +
                u_LightQuadratic * distance * distance
            );
    }
    else if (u_LightType == 2)
    {
        // Spot Light
        lightDirection =
            normalize(
                u_LightPosition - WorldPosition
            );

        float distance =
            length(
                u_LightPosition - WorldPosition
            );

        attenuation =
            1.0 /
            (
                u_LightConstant +
                u_LightLinear * distance +
                u_LightQuadratic * distance * distance
            );

        // Light → Fragment
        vec3 lightToFragment =
            -lightDirection;

        // Spot Light 的角度
        float theta =
            dot(
                lightToFragment,
                normalize(u_LightDirection)
            );

        // Inner / Outer Cone 平滑过渡
        float epsilon =
            u_LightInnerCutoff -
            u_LightOuterCutoff;

        spotIntensity =
            clamp(
                (theta - u_LightOuterCutoff) / epsilon,
                0.0,
                1.0
            );
    }

    // 9. Lambert Diffuse
    float diffuse =
        max(
            dot(
                worldNormal,
                lightDirection
            ),
            0.0
        );

    // 10. Diffuse Texture
    vec3 color =
        texture(
            u_DiffuseTexture,
            TexCoords
        ).rgb;

    
    // 11. Lighting
    color *= diffuse;
    color *= attenuation;
    color *= spotIntensity;
    color *= u_Intensity;
    color *= u_LightColor;

    // 12. Shadow

    color *= (1.0 - shadow);
    
    FragColor = vec4(color, 1.0);
    
}