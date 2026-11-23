#version 410 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 Position;

out vec4 FragColor;

uniform float u_Value;
uniform sampler2D u_DiffuseTexture;
uniform sampler2D u_NormalTexture;
uniform vec4 u_Color;

void main()
{
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

    // 当前还没有 Lighting
    // worldNormal 暂时只完成 Normal Mapping 数据链

    vec3 lightDirection = normalize(vec3(-1.0, 2.0, 1.0));

    float diffuse = max(dot(Position, lightDirection), 0.0);

    vec3 color = texture(u_DiffuseTexture, TexCoords).rgb;
    color *= diffuse;


    FragColor = vec4(color, 1.0);
}