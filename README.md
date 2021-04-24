# Computação Gráfica


Para compilar e executar no Windows com make e GCC/G++ instalado:

`make run`

Caso não possua o make: 

`g++ -g -std=c++17 -I./include -L./lib src/*.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32`

`./main`

#### Comando para o cenários:
__W__ - Frente
__S__ - Trás
__D__ - Direita
__A__ - Esquerda
__MOUSE__ - Gira a visão no eixo X

__OBS:__ É preciso alterar caminho do include glut.h e glfw3.h 
