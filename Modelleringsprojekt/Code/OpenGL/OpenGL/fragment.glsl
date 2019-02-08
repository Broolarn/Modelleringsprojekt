#version 330 core
in vec2 st ; // Interpolated texture coords , sent from vertex shader
uniform mat4 keygrej;
in vec3 interpolatedNormal ;

out vec4 finalcolor ;
void main () {
    vec3 V=vec3(0 ,0 ,1);
    vec3 lightDirection=normalize(mat3(keygrej)*(vec3 (0.0 , 0.0 , 1.0)));

    float n=10.0f;

    // vec3 ka is the ambient reflection color
    vec3 ka = vec3(0.7,0.7,0.7);//mörkt omdråde
    // vec3 Ia is the ambient illumination color
    vec3 Ia = vec3(0.5,0.5,0.5);//mörkt område
    // vec3 kd is the diffuse surface reflection color
    vec3 kd = vec3(0.9, 0.9, 0.9);//objektets färg
    // vec3 Id is the diffuse illumination color
    vec3 Id = vec3(0.8,0.8,0.8);//mindre ljust ljus....................................................-----------------------------
    // vec3 ks is the specular surface reflection color
    vec3 ks = vec3(1.0,1.0,1.0);//punktsreflektionen
    // vec3 Is is the specular illumination color
    vec3 Is = vec3(1.0,1.0,1.0);//
    // This assumes that N, L and V are normalized .

    vec3 R = 2.0* dot(interpolatedNormal,lightDirection) *interpolatedNormal - lightDirection; // Could also have used the function reflect ()
    float dotNL = max(dot(interpolatedNormal, lightDirection) , 0.0) ; // If negative , set to zero
    float dotRV = max(dot(R, V) , 0.0) ;
    if (dotNL == 0.0) dotRV = 0.0; // Do not show highlight on the dark side
    vec3 shadedcolor = Ia * ka + Id * kd * dotNL + Is * ks * pow(dotRV , n);


    finalcolor = vec4(shadedcolor , 1.0);


}
