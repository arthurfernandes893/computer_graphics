nome="casa"

# g++  "$nome.cpp" -framework OpenGL -framework GLUT -o castelo
g++ -o "$nome.vis" "$nome.cpp" -lglut -lGLU -lGL -lm
chmod +x "$nome.vis"
