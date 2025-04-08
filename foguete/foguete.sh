nome="foguete"

 g++  "$nome.cpp" -framework OpenGL -framework GLUT -o "$nome.vis" -lm
#g++ -o "$nome.vis" "$nome.cpp" -lglut -lGLU -lGL -lm
chmod +x "$nome.vis"

./"$nome.vis"
