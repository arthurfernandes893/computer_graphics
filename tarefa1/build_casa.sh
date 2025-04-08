#g++  casa.cpp -framework OpenGL -framework GLUT -o casa
g++ -o casa casa.cpp -lglut -lGLU -lGL -lm
./casa
