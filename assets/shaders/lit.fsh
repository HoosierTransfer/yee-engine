#version 330 core
#define DIRECTIONAL_LIGHTS 2
#define POINT_LIGHTS 4

struct Material {
    vec3 ambient;
#ifdef DIFFUSE_TEXTURE
    sampler2D diffuse;
#else
    vec3 diffuse;
#endif
#ifdef SPECULAR_TEXTURE
    sampler2D specular;
#else
    vec3 specular;
#endif
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    bool enabled;
};

struct PointLight {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    
    // enabled prevents nan values when the light is not used
    bool enabled;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
#if defined(DIFFUSE_TEXTURE) || defined(SPECULAR_TEXTURE)
in vec2 TexCoords;
#endif

uniform vec3 viewPos;

uniform Material material;
uniform DirectionalLight dirLight[DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[POINT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    if (!light.enabled) return vec3(0.0);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
#ifdef DIFFUSE_TEXTURE
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
#else
    vec3 ambient  = light.ambient  * vec3(material.diffuse);
    vec3 diffuse  = light.diffuse  * diff * vec3(material.diffuse);
#endif
#ifdef SPECULAR_TEXTURE
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
#else
    vec3 specular = light.specular * spec * vec3(material.specular);
#endif
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if (!light.enabled) return vec3(0.0);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));    
#ifdef DIFFUSE_TEXTURE
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
#else
    vec3 ambient  = light.ambient  * vec3(material.diffuse);
    vec3 diffuse  = light.diffuse  * diff * vec3(material.diffuse);
#endif  
#ifdef SPECULAR_TEXTURE
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
#else
    vec3 specular = light.specular * spec * vec3(material.specular);
#endif
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main() {
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = vec3(0.0);
    
    for(int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
        result += CalcDirLight(dirLight[i], normal, viewDir);
    }
    
    for(int i = 0; i < POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    }
    
    FragColor = vec4(result, 1.0);
}
