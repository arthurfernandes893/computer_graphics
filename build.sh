#!/bin/bash

# Nome do programa (sem extensão)
nome="carro"

# Verifica o sistema operacional
os_name=$(uname)

if [ "$os_name" == "Darwin" ]; then
    # Compilação para macOS
    g++ "$nome/$nome.cpp" -framework OpenGL -framework GLUT -o "$nome/$nome.vis" -lm
    echo "Compilado para macOS: $nome/$nome.vis"
elif [ "$os_name" == "Linux" ]; then
    # Compilação para Linux
    g++ -o "$nome/$nome.vis" "$nome/$nome.cpp" -lglut -lGLU -lGL -lm
    echo "Compilado para Linux: $nome.vis"
else
    echo "Sistema operacional não suportado: $os_name"
    exit 1
fi

chmod +x "$nome/$nome.vis"
echo "Running..."
./"$nome/$nome.vis"