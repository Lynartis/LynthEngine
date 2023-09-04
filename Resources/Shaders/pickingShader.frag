  #version 330 core
    out vec4 FragColor;
    
    uniform int entityId; // Entity ID being rendered
    
    void main()
    {
       vec3 encodedColor = vec3(float(entityId & 0xFF) / 255.0, float((entityId >> 8) & 0xFF) / 255.0, float((entityId >> 16) & 0xFF) / 255.0);
       FragColor = vec4(encodedColor, 1.0);
       // FragColor  = vec4(float(entityId), 0.0, 1.0, 1.0);
    }