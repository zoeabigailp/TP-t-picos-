#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

///Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>

///Macros
#define SDL_ERROR 1
#define WINDOW_ERROR -1
#define EXITO 0
#define INDEX_F 0
#define INDEX_C 1
#define PATRON 2
#define TAM_SQUARE 10
#define LIVE 1
#define DEAD 0

/// Prototipo de funciones
int ** crearTablero(unsigned int fila, unsigned int columna);
void destruirTablero(int ** tablero, unsigned int fila);
void inicializarTablero(int **tablero, unsigned int fila, unsigned int columna, int patron);
void procesarTablero(int ** tablero, unsigned int fila, unsigned int columna);
int cantVecinosVivos(int ** tablero, int x, int y, unsigned int fila, unsigned int columna);
void configurarTablero(int * config);
void drawSquare(SDL_Renderer * renderer, unsigned int posX, unsigned int posY);
void patronPlaneador(int ** tablero, unsigned int fila, unsigned int columna);
void imprimirTablero(int ** tablero, unsigned int fila, unsigned int columna, SDL_Renderer * renderer);
int mostrarIntro(const char * img);
int juego();
#endif // TABLERO_H_INCLUDED
