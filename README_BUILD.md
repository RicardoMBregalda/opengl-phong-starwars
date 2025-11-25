# Como Compilar o Projeto

## Opção 1: Usando vcpkg (Recomendado - Mais Fácil)

### 1. Instale o vcpkg
```powershell
# Clone o vcpkg em algum diretório (ex: C:\vcpkg)
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

### 2. Integre o vcpkg com o sistema
```powershell
.\vcpkg integrate install
```

### 3. Compile o projeto
```powershell
# Volte para o diretório do projeto
cd C:\Users\ricar\Documents\GLFW_Tie_Fighter

# Configure o CMake (vcpkg instalará as dependências automaticamente)
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

# Compile
cmake --build build --config Release
```

### 4. Execute
```powershell
.\build\Release\GLFW_Tie_Fighter.exe
```

---

## Opção 2: Instalar Dependências Manualmente

### 1. Instale CMake
- Baixe de: https://cmake.org/download/
- Adicione ao PATH durante a instalação

### 2. Instale um compilador
- **Visual Studio 2022** (Community é grátis): https://visualstudio.microsoft.com/
  - Selecione "Desenvolvimento para Desktop com C++"
- OU **MinGW-w64**: https://www.mingw-w64.org/

### 3. Instale as bibliotecas

#### GLFW
- Baixe de: https://www.glfw.org/download.html
- Extraia para `C:\Libraries\glfw-3.4`

#### GLEW
- Baixe de: http://glew.sourceforge.net/
- Extraia para `C:\Libraries\glew-2.1.0`

#### GLM
- Baixe de: https://github.com/g-truc/glm/releases
- Extraia para `C:\Libraries\glm`

### 4. Configure as variáveis de ambiente (ou use -D no cmake)
```powershell
# Se usar Visual Studio:
cmake -B build -S . -DGLFW_DIR="C:/Libraries/glfw-3.4/lib/cmake/glfw3" -DGLEW_DIR="C:/Libraries/glew-2.1.0" -DGLM_DIR="C:/Libraries/glm"

# Compile
cmake --build build --config Release
```

---

## Opção 3: Usando Visual Studio diretamente

1. Instale o Visual Studio 2022
2. Abra o Visual Studio
3. File → Open → CMake → Selecione `CMakeLists.txt`
4. O Visual Studio configurará automaticamente (se usar vcpkg integrado)
5. Build → Build All

---

## Resolução de Problemas

### "GLFW not found"
```powershell
# Com vcpkg:
C:\vcpkg\vcpkg install glfw3:x64-windows

# Manual: verifique se GLFW está instalado e adicione:
cmake -B build -S . -DGLFW_DIR="caminho/para/glfw/lib/cmake/glfw3"
```

### "GLEW not found"
```powershell
# Com vcpkg:
C:\vcpkg\vcpkg install glew:x64-windows
```

### "GLM not found"
```powershell
# Com vcpkg:
C:\vcpkg\vcpkg install glm:x64-windows
```

### Shaders não encontrados
Os shaders (.glsl) serão copiados automaticamente para o diretório de build. Certifique-se de executar o programa a partir do diretório `build/` ou `build/Release/`.
