#version 450                          
out vec4 FragColor;

in struct Vertex{
    vec3 WorldNormal; //
    vec3 WorldPosition; //
}vs_out;

struct Material{
    float ambientK;
};

struct DirectionLight{
    vec3 direction;
    vec3 color;
    float intensity;
};

struct Light{
    vec3 position;
    vec3 color;
    float intensity;
    float range;
};

const int MAX_POINTLIGHTS = 8;
uniform pointLight _pointLights[MAX_POINTLIGHTS];
uniform Material material;

void main(){         
    vec3 normal = normalize(vs_out.WorldNormal)
    FragColor = vec4(abs(normal),1.0f);
}