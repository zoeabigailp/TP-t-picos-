#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#include <SDL_main.h>
#endif

#include <SDL.h>
#include "tablero.h"

int main(int argc, char *argv[])
{
    juego();
}


