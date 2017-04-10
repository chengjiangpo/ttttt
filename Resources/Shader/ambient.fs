void main()
{
    vec4 u_ambientLightColor = vec4(0.2,0.2,0.2,1.0);
    vec4 u_ambientMaterial = vec4(0.2,0.2,0.2,1.0);
    
    vec4 ambientColor = u_ambientLightColor*u_ambientMaterial;
    gl_FragColor=ambientColor;
}