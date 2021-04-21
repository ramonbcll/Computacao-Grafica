# Computação Gráfica


Para compilar e executar no Windows com make e GCC/G++ instalado:

`make run`

Caso não possua o make: 

`g++ -g -std=c++17 -I./include -L./lib src/*.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32`
`./main`
