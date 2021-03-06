#version 330 core
out vec4 FragColor;

in vec3 color;
in vec3 Normal;
in vec3 currentPos;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor.xyz;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.xyz;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor.xyz;  
        
    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0);
}
