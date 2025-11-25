# GLFW Star Wars - Documentacao Tecnica

Projeto OpenGL que renderiza cenas do universo Star Wars com naves TIE Fighter e X-Wing utilizando iluminacao Phong.

## Dependencias

- OpenGL 3.3+
- GLFW 3.x
- GLEW 2.x
- GLM

## Compilacao

### Usando vcpkg (Recomendado)

```powershell
# Instalar vcpkg
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install

# Compilar projeto
cd <diretorio_do_projeto>
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

### Usando MinGW/MSYS2

```powershell
# Instalar dependencias via pacman
pacman -S mingw-w64-ucrt-x86_64-glfw
pacman -S mingw-w64-ucrt-x86_64-glew
pacman -S mingw-w64-ucrt-x86_64-glm

# Compilar
cmake -B build -S . -G "MinGW Makefiles"
cmake --build build
```

### Execucao

```powershell
cd build
.\GLFW_Tie_Fighter.exe
```

Os arquivos de shader (.glsl) e a pasta imagens/ sao copiados automaticamente para o diretorio de build pelo CMake.

---

## Sistema de Iluminacao

O projeto implementa o modelo de iluminacao Phong com tres componentes: ambiente, difusa e especular.

### Arquitetura

```
vertex.glsl     -> Transforma vertices e normais para world space
fragment.glsl   -> Calcula iluminacao por fragmento (per-pixel)
```

### Vertex Shader (vertex.glsl)

Responsavel por transformar os dados dos vertices:

```glsl
gl_Position = projection * view * model * vec4(aPos, 1.0f);
FragPos = vec3(model * vec4(aPos, 1.0));
Normal = mat3(transpose(inverse(model))) * aNormal;
```

- `FragPos`: Posicao do fragmento em world space, usada para calcular direcao da luz
- `Normal`: Normal transformada usando a matriz normal (transpose(inverse(model))) para preservar a orientacao correta mesmo com escalas nao-uniformes

### Fragment Shader (fragment.glsl)

Calcula a cor final de cada pixel usando tres componentes de luz:

#### 1. Componente Ambiente

```glsl
float ambientStrength = 0.2;
vec3 ambient = ambientStrength * vec3(1.0);
```

Iluminacao constante que simula luz indireta. Garante que objetos nao fiquem completamente escuros.

#### 2. Componente Difusa

```glsl
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * vec3(1.0);
```

Calcula a intensidade da luz baseada no angulo entre a normal da superficie e a direcao da luz. Usa o produto escalar (dot product) - quanto mais perpendicular a superficie estiver em relacao a luz, mais iluminada.

#### 3. Componente Especular

```glsl
float specularStrength = 0.6;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
vec3 specular = specularStrength * spec * vec3(1.0);
```

Simula o brilho especular (reflexo). O expoente 64 controla o tamanho do brilho - valores maiores geram brilhos menores e mais concentrados.

#### 4. Atenuacao

```glsl
float distance = length(lightPos - FragPos);
float attenuation = 1.0 / (1.0 + 0.009 * distance + 0.0032 * distance * distance);
diffuse *= attenuation;
specular *= attenuation;
```

A intensidade da luz diminui com a distancia seguindo a equacao:

```
atenuacao = 1 / (1 + Kl*d + Kq*d^2)
```

Onde:
- Kl = 0.009 (coeficiente linear)
- Kq = 0.0032 (coeficiente quadratico)
- d = distancia entre fragmento e fonte de luz

#### 5. Composicao Final

```glsl
vec3 lighting = ambient + diffuse + specular;
vec4 texColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
FragColor = vec4(lighting, 1.0) * texColor;
```

A cor final combina a iluminacao calculada com a mistura de duas texturas (50% cada).

### Uniforms Utilizados

| Uniform | Tipo | Descricao |
|---------|------|-----------|
| model | mat4 | Matriz de transformacao do objeto (world space) |
| view | mat4 | Matriz da camera |
| projection | mat4 | Matriz de projecao perspectiva |
| lightPos | vec3 | Posicao da fonte de luz em world space |
| viewPos | vec3 | Posicao da camera em world space |
| texture1 | sampler2D | Textura primaria |
| texture2 | sampler2D | Textura secundaria |

### Atributos de Vertice

Cada vertice contem 8 floats:

| Atributo | Location | Componentes | Descricao |
|----------|----------|-------------|-----------|
| aPos | 0 | 3 (x,y,z) | Posicao do vertice |
| aTexCoord | 1 | 2 (u,v) | Coordenadas de textura |
| aNormal | 2 | 3 (nx,ny,nz) | Vetor normal |

Layout em memoria: `[x, y, z, u, v, nx, ny, nz]` - stride de 32 bytes (8 floats * 4 bytes).

### Estrutura de Classes

```
Object (classe base abstrata)
    |
    +-- Cube
    +-- Sphere
    +-- Cylinder
    +-- Hexagon
    |       |
    |       +-- HexagonalPrism
    +-- Plate
    +-- TieFighter (composicao de objetos)
    +-- XWing (composicao de objetos)
    +-- XWingClosed (composicao de objetos)
```

Cada classe geometrica:
1. Gera vertices com posicao, UV e normais no metodo `init()`
2. Configura VAO/VBO/EBO para renderizacao
3. Aplica transformacoes (translate, scale, rotate) e atualiza uniform `model` no metodo `draw()`

### Fluxo de Renderizacao

1. Limpar buffers de cor e profundidade
2. Ativar shader principal
3. Configurar matrizes view/projection
4. Para cada objeto:
   - Calcular matriz model com transformacoes
   - Enviar uniforms ao shader
   - Bind das texturas
   - Chamada de draw (glDrawElements)
5. Renderizar skybox (sem depth write)
6. Swap buffers

### Controles

| Tecla | Acao |
|-------|------|
| W/A/S/D | Movimento da camera |
| Space/Ctrl | Subir/Descer camera |
| Mouse | Rotacao da camera |
| Setas | Mover fonte de luz (X/Z) |
| PageUp/PageDown | Mover fonte de luz (Y) |
| R | Reset da camera |
| ESC | Sair |

---

## Estrutura de Arquivos

```
/
├── main.cpp                 # Loop principal e controles
├── CMakeLists.txt           # Configuracao de build
├── vcpkg.json               # Dependencias vcpkg
├── vertex.glsl              # Vertex shader principal
├── fragment.glsl            # Fragment shader principal
├── light_vertex.glsl        # Vertex shader da fonte de luz
├── light_fragment.glsl      # Fragment shader da fonte de luz
├── skybox_vertex.glsl       # Vertex shader do skybox
├── skybox_fragment.glsl     # Fragment shader do skybox
├── include/                 # Headers
│   ├── Object.h             # Classe base abstrata
│   ├── Shader.h             # Wrapper para shaders OpenGL
│   ├── Texture.h            # Wrapper para texturas
│   └── [geometrias].h       # Classes de geometria
├── src/                     # Implementacoes
│   └── [geometrias].cpp
└── imagens/                 # Texturas
```
