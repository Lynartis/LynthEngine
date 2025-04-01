
# LynthEngine

Game Engine Created by Marc Peregrina Parera

## Description


I'm currently working on a game engine project using OpenGL and C++, along with libraries like GLFW, glm, and assimp. The engine is designed around the Entity-Component-System (ECS) pattern, and I'm using assimp to manage 3D assets. To improve debugging, I've integrated glad and ImGui for a smoother user interface.

It's a learning adventure and a chance to experiment. I want to create a basic game engine that handles rendering, input, and asset management. Along the way, I'm discovering more about graphics and game development. I also hope to use this engine to build a simple game. It's all about learning, and having a personal workspace to create shaders
float2 ParallaxOffset(
    float2 uv,                  // Original UV
    float height_intensity,     // Intensidad del desplazamiento
    Texture2D height_mask,      // Textura de altura (grayscale)
    SamplerState samp,          // Sampler para la textura
    float3 normalWS,            // Normal en espacio mundial
    float3 tangentWS,           // Tangente en espacio mundial
    float3 viewerPosWS,         // Posición del espectador en mundo
    float3 worldPos             // Posición del fragmento en mundo
)
{
    // BiTangent calculation (left-handed tangent space)
    float3 bitangentWS = normalize(cross(normalWS, tangentWS));
    
    // Tangent space view vector
    float3 viewDirWS = normalize(viewerPosWS - worldPos);
    float3x3 TBN = float3x3(tangentWS, bitangentWS, normalWS);
    float3 viewDirTS = mul(TBN, viewDirWS); // Pasamos a tangent space

    // Sample heightmap
    float height = height_mask.Sample(samp, uv).r;

    // Compute parallax offset
    float2 parallaxOffset = (viewDirTS.xy / viewDirTS.z) * (height * height_intensity);

    // Return offset UV
    return uv + parallaxOffset;
}

// Transformamos la dirección del visor de world space a tangent space
float3 viewDirTS = mul(TBN, viewDirWS);

// Calculamos un factor de escala basado en cuán inclinado es el ángulo de visión
// viewDirTS.z es cuánto "miramos de frente"; si es bajo, estamos mirando en ángulo
// En lugar de dividir por z, usamos (1 - z) como multiplicador para simular ese efecto
float scale = saturate(1.0 - viewDirTS.z); // saturate asegura que el valor esté entre 0 y 1

// Calculamos el desplazamiento de parallax multiplicando por ese factor
float2 parallaxOffset = viewDirTS.xy * height * height_intensity * scale;

// Sumamos el desplazamiento a las UV originales
return uv + parallaxOffset;


// Transformamos la dirección del visor de world space a tangent space
float3 viewDirTS = mul(TBN, viewDirWS);

// Calculamos qué tan inclinado está el ángulo del visor usando la longitud del vector en xy
float angleFactor = length(viewDirTS.xy); // mayor inclinación = mayor valor

// Calculamos el desplazamiento normalizando xy y multiplicando por altura, intensidad e inclinación
float2 parallaxOffset = normalize(viewDirTS.xy) * height * height_intensity * angleFactor;

// Sumamos el desplazamiento a las UV originales
return uv + parallaxOffset;
## Getting Started

### Dependencies

assimp
C++
FileWatch
glad
GLFW
glm
ImGui
OpenGL

152658

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release



