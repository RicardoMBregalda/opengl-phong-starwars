# Compilador
CXX = g++
CXXFLAGS = -Wall -fexceptions -g -D_USE_MATH_DEFINES

# Diretórios
INCLUDES = -Iinclude

SRC_DIR = src
OBJ_DIR = obj\\Debug
BIN_DIR = bin\\Debug
TARGET = $(BIN_DIR)\\GLFW_Tie_Fighter.exe

# Bibliotecas (MSYS2/MinGW)
LIBS = -lglfw3 -lglew32 -lopengl32 -lgdi32

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJ)
	@echo Linking...
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) -o $@ $(OBJ) $(LIBS)
	@echo Build completo: $@

# Regra de compilação
$(OBJ_DIR)/%.o: %.cpp
	@echo Compilando $<
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpeza (Windows)
clean:
	@echo Limpando...
	@if exist "$(OBJ_DIR)" (rmdir /S /Q "$(OBJ_DIR)") else (echo Nenhum objeto para remover)
	@if exist "$(TARGET)" (del /Q "$(TARGET)") else (echo Nenhum executável para remover)
	@echo Limpeza concluída.

# Executar o programa
run: all
	@echo Executando $(TARGET)...
	@cd $(BIN_DIR) && GLFW_Tie_Fighter.exe

.PHONY: all clean run
