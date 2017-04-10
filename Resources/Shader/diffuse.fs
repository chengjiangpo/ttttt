varying vec3 v_normal;
void main()
{
    vec3 lightPos = vec3(10.0,10.0,0.0);
    vec3 L = lightPos;
    L = normalize(L);
    vec3 N = normalize(v_normal);
    // ambient
    vec4 u_ambientLightColor = vec4(0.2,0.2,0.2,1.0);
    vec4 u_ambientMaterial = vec4(0.2,0.2,0.2,1.0);
    vec4 ambientColor = u_ambientLightColor*u_ambientMaterial;
    
    //diffuse
    vec4 u_diffuseLightColor = vec4(1.0,1.0,1.0,1.0);
    vec4 u_diffuseMaterial = vec4(0.4,0.4,0.4,1.0);
    vec4 diffuseColor = u_diffuseLightColor*u_diffuseMaterial*max(0.0,dot(L,N));
    
    
    gl_FragColor=ambientColor + diffuseColor;
//    gl_FragColor = vec4(0.0,1.0,1.0,1.0);
}