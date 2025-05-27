#!/bin/bash

# Nome do programa (sem extensão)
nome="$fname"

# Verifica o sistema operacional
os_name=$(uname)

if [ "$os_name" == "Darwin" ]; then
    # Compilação para macOS
    g++ "3d/$nome/$nome.cpp" -framework OpenGL -framework GLUT -o "3d/$nome/$nome.vis" -lm
    echo "Compilado para macOS: $nome/$nome.vis"
elif [ "$os_name" == "Linux" ]; then
    # Compilação para Linux
    g++ -o "3d/$nome/$nome.vis" "3d/$nome/$nome.cpp" -lglut -lGLU -lGL -lm
    echo "Compilado para Linux: $nome.vis"
else
    echo "Sistema operacional não suportado: $os_name"
    exit 1
fi

chmod +x "3d/$nome/$nome.vis"
echo "Running $nome/$nome.vis ..."
./"3d/$nome/$nome.vis"