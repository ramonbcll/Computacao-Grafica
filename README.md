# Projeto final de Computação Gráfica

Projeto final da disciplina de Computação Gráfica ministrada pelo professor Marcelo Costa Oliveira no curso de Ciência da Computação (UFAL) com o intuito de modelar um quarto 3D utilizando OpenGL.

#### Vídeo da apresentação:

https://youtu.be/7WAL8gfkIfs

## Requisitos

### Requisitos relacionados a nota da AB1:

- [x] Modelar o interior do Quarto: paredes, teto, piso, etc.; 
- [x] O quarto deverá ter no mínimo 5 objetos, além da cama, mesa, cadeira, ventilador e quadro; 
- [x] 1 Porta: a porta do Quarto deverá ser aberta e fechada usando o teclado
- [x] 1 Janela: a janela deverá ser aberta e fechada usando o teclado;
- [x] O usuário deverá navegar com o teclado/mouse na modelagem permitindo ao usuário visualizar o Quarto em 360º;

### Requisitos relacionados a nota da AB2:

- [x] O quarto deverá ter 1 Quadro de Vincent Van Gogh; 
- [x] 1 ventilador de mesa com hélice girando no sentido horário em baixa velocidade; 
- [x] 1 luminária simulando a spot encima da mesa; 
- [x] Aplicar Iluminação (especular e difusa) a modelagem;
- [x] Aplicar mapeamento de textura em 5 objetos (no mínimo);

## Para compilar e executar no Windows com make e GCC/G++ instalado:

`make run`

Caso não possua o make: 

`g++ -g -std=c++17 -I./include -L./lib src/*.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32`

`./main`

#### Comando para o cenários:

__MOUSE__ - Rotaciona a visão em 360°

__W__ - Frente

__S__ - Trás

__D__ - Direita

__A__ - Esquerda

__P__ - Abrir e fechar a porta

__J__ - Abrir e fechar a janela

__G__ - Acender e apagar a iluminação geral

__L__ - Acender e apagar a iluminação spot em cima da mesa

## Informações sobre o projeto:

__Equipe__: Ramon Basto Callado e Matheus Gomes de Oliveira;

__Editor de código__: Visual Studio Code;

__Sistema Operacional utilizado__: Windows 10;

__Referência__: https://www.youtube.com/playlist?list=PLVRDPs83ZhmcXYuktF3r2hfyoabg_EVPO
                https://www.programmersought.com/article/1263524392/
                https://www.glfw.org/documentation.html
                http://docs.gl/
                

__OBS:__ É preciso alterar caminho dos includes das bibliotecas glut.h e glfw3.h 
