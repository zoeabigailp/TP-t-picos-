#include "tablero.h"

/** D
* La función me permite inicializar la matriz dinamica incial.
* Algoritmo:
*   1. Recorro la matriz para inicializarla en 0.
*   2. Le agrego un patron
*
* @param int ** tablero - Matriz con la primer generación
* @param unsigned int fila - fila del tablero
* @param unsigned int columna - columna del tablero
*/
void inicializarTablero(int **tablero, unsigned int fila, unsigned int columna, int patron)
{

    int cx = (fila) / 2;
    int cy = (columna) / 2;

    switch(patron)
    {
    case 1: //Planeador - Glider
        if(fila >= 3 && columna >=3)
        {
           int x = cx-1;
           int y = cy-1;

            tablero[x][y] = LIVE;
            tablero[x][y + 1] = LIVE;
            tablero[x+1][y+1] = LIVE;
            tablero[x+2][y+1] = LIVE;
            tablero[x+1][y+2] = LIVE;

        }
        break;
    case 2: //sapo (4*2)
        if(fila >= 2 && columna >=4)
        {
            int x = cx - 1;
            int y = cy - 2;

            tablero[x][y+1]= LIVE;
            tablero[x][y+2]= LIVE;
            tablero[x][y+3]= LIVE;
            tablero[x+1][y]= LIVE;
            tablero[x+1][y+1]= LIVE;
            tablero[x+1][y+2]= LIVE;
        }
        break;
    case 3: //Cañon de planeadores
        if( fila >= 9 && columna >= 36)
        {
            int x = (fila - 9) / 2;
            int y = (columna - 36) / 2;

            //Izquierda
            tablero[x+5][y+1] = LIVE;
            tablero[x+5][y+2] = LIVE;
            tablero[x+6][y+1] = LIVE;
            tablero[x+6][y+2] = LIVE;

            //Centro izq
            tablero[x+3][y+13] = LIVE;
            tablero[x+3][y+14] = LIVE;
            tablero[x+4][y+12] = LIVE;
            tablero[x+4][y+16] = LIVE;
            tablero[x+5][y+11] = LIVE;
            tablero[x+5][y+17] = LIVE;
            tablero[x+6][y+11] = LIVE;
            tablero[x+6][y+15] = LIVE;
            tablero[x+6][y+17] = LIVE;
            tablero[x+6][y+18] = LIVE;
            tablero[x+7][y+11] = LIVE;
            tablero[x+7][y+17] = LIVE;
            tablero[x+8][y+12] = LIVE;
            tablero[x+8][y+16] = LIVE;
            tablero[x+9][y+13] = LIVE;
            tablero[x+9][y+14] = LIVE;

            //Centro der
            tablero[x+1][y+25] = LIVE;
            tablero[x+2][y+23] = LIVE;
            tablero[x+2][y+25] = LIVE;
            tablero[x+3][y+21] = LIVE;
            tablero[x+3][y+22] = LIVE;
            tablero[x+4][y+21] = LIVE;
            tablero[x+4][y+22] = LIVE;
            tablero[x+5][y+21] = LIVE;
            tablero[x+5][y+22] = LIVE;
            tablero[x+6][y+23] = LIVE;
            tablero[x+6][y+25] = LIVE;
            tablero[x+7][y+25] = LIVE;

            //Derecha
            tablero[x+3][y+35] = LIVE;
            tablero[x+3][y+36] = LIVE;
            tablero[x+3][y+35] = LIVE;
            tablero[x+3][y+36] = LIVE;
        }
        else{
            printf("\nEl tablero es muy pequeño para el canon planeador.");

             /* Usamos de nuevo el patrón 1 */
            int x = cx - 1, y = cy - 1;
            tablero[x  ][y  ] = LIVE;
            tablero[x  ][y+1] = LIVE;
            tablero[x+1][y+1] = LIVE;
            tablero[x+2][y+1] = LIVE;
            tablero[x+1][y+2] = LIVE;
        }
        break;

    default:
        printf("Patron (%d) invalido.", patron);
        break;


    }


}
/** D
* La función me permite crear y reservar memoria dinamica para una matriz.
* Algoritmo:
*   1. Declaro un puntero doble
*   2. Valido si puedo reservar memoria para las filas
*   3. Recorro y valido si puedo reservar memoria para las columnas
*
* @param unsigned int fila - fila del tablero
* @param unsigned int columna - columna del tablero
*
*
* @return int ** tablero - Puntero a la matriz creada
*/
int ** crearTablero(unsigned int fila, unsigned int columna)
{
    int ** tablero = (int **)calloc(fila, sizeof(int *));

    if(tablero == NULL)
    {
        printf("\nError en la asginacion de memoria para las filas");
        return NULL;
    }

    for(int i = 0; i<fila; i++)
    {
        tablero[i] = (int *)calloc(columna, sizeof(int));
        if(tablero[i] == NULL)
        {
            for(int j = 0; j<i; j++)
            {
                free(tablero[j]);
            }

            free(tablero);
            printf("\nError en la asignacion de memoria para las columnas");
            return NULL;
        }
    }
    return tablero;
}
/** D
* La función me permite destruir la matriz en caso de que haya sido creada
*
* Algoritmo:
*   1. Recorro la matriz y libero memoria
*   2. Al final libero lo que queda de la matriz
*
* @param unsigned int fil - fila del tablero
* @param unsigned int col - columna del tablero
*/
void destruirTablero(int ** tablero, unsigned int fila)
{
    for(int i = 0; i<fila; i++)
    {
        free(tablero[i]);
    }

    free(tablero);
}
/** D
* La función me permite contar la cantidad de vecinos vivos que hay alrededor,
* según la coordenada (x,y) pasada.
* Algoritmo:
*   1. Declarar una variable para contar vecinos vivos.
*   2. Recorrer los vecinos alrededor de la celula en la posición(x,y)
*   3. Al recorrer, no se debe exceder de los limites del tablero
*   4. Si la matriz en una determinada posicion [i][j] es 1 el vecino esta vivo
*       y no se debe contar la celda (x,y) como vecino.
*
* @param int ** tablero - matriz que contiene una generacion
* @param int x - coordenadas x de la celula
* @param int y - coordenadas y de la celula
* @param unsigned int fila - Cantidad de filas del tablero.
* @param unsigned int col - Cantidad de columnas del tablero.
*
* @return int cantVivas: Cantidad de vecinos vivos encontrados
*/
int cantVecinosVivos(int ** tablero, int x, int y, unsigned int fila, unsigned int columna)
{
    int cantVivas = 0;
    //Recorrido de los vecinos
    for(int i = x-1; i<= x+1; i++)
    {
        for(int j = y-1; j<=y+1; j++)
        {

            /*
                   evito excederme de los limites del tablero:
                   i no pueden ser nunca negativas (significa que esto al limite del lado izquierdo del tablero)
                   j no pueden ser nunca negativas (significa que esto al limite del lado superior del tablero)
                   i no pueden exceder a la cantidad de filas (significa que estoy al limite del lado derecho)
                   j no pueden exceder a la cantidad de columnas (significa que estoy al limite del lado inferior del tablero)
               */

            if( i>= 0 && i<fila && j>=0 && j<columna)  // evita desbordamiento
            {

                if(tablero[i][j] == 1 && !(i==x && j==y))
                {
                    //Si la celda esta viva y no es la celda central
                    cantVivas++;
                }
            }
        }
    }

    return cantVivas;
}
/** D
* La función crea un tablero auxiliar que calcula la sigueinte generación, según sus vecinos vivos.
* Algoritmo:
*   1. Recorro toda la matriz actual (tablero).
*   2. Cuento y guardo la cantidad de vecinos vivos que hay en ea posicion
*   3. Valido segun las reglas de conway y que celula hay en esa posicion
*   4. Copia la nueva generacion en la matriz actual
*
* @param int **tablero - Matriz que contiene la generación actual.
* @param unsigned int fila - Cantidad de filas del tablero.
* @param unsigned int columna - Cantidad de columnas del tablero.
*/
void procesarTablero(int ** tablero, unsigned int fila, unsigned int columna)
{
    int ** tableroSiguiente = crearTablero(fila, columna);
    int cantVecinos = 0;

    for(int i = 0; i<fila; i++)
    {
        for(int j = 0; j<columna; j++)
        {

            cantVecinos = cantVecinosVivos(tablero, i, j, fila, columna);
            if( (cantVecinos == 2 || cantVecinos == 3) && tablero[i][j] == 1)
            {
                tableroSiguiente[i][j]= LIVE; //Sigue viva
            }
            else if( tablero[i][j] == 0 && cantVecinos == 3)
            {
                tableroSiguiente[i][j] = LIVE; //Nace una nueva celula
            }
            else
            {
                tableroSiguiente[i][j] = DEAD; //Muere
            }
        }
    }

    //Copiar los tableros

    for(int i = 0; i <fila; i++)
    {

        for(int j = 0; j<columna; j++)
        {
            tablero[i][j] = tableroSiguiente[i][j];
        }
    }

    destruirTablero(tableroSiguiente, fila);
}
/** D
* La función permite configurar el tamaño del tablero y el patron a usar.
* Algoritmo:
*   1. Ingreso de la cantidad de filas.
*   2. Valido que se encuentre dentro del rango [5-80].
*   3. Ingreso de la cantidad de columnas.
*   4. Valido que se encuentre dentro del rango [5-60].
*   5. Elijo el patron a usar
*
* @param int * config - Puntero donde se guarda la configuracion de las filas y columnas
*/
void configurarTablero(int * config)
{
    //Declaro variables
    const int MIN_FILAS = 15;
    const int MAX_FILAS = 100;
    const int MIN_COLS = 15;
    const int MAX_COLS = 80;

    printf("\n--------------------CONFIGURACIONES INICIALES--------------------\n");

    //Ingresar filas
    printf("\nIngrese la cantidad de FILAS entre [%d-%d]:", MIN_FILAS, MAX_FILAS);
    scanf("%d", config);
    while(*config < MIN_FILAS || *config> MAX_FILAS)
    {
        printf("\nNumero de filas invalido, vuelva a ingresar otra cantidad:");
        scanf("%d", config);
    }

    //Ingresar columnas
    printf("\nIngrese la cantidad de COLUMNAS entre [%d-%d]:", MIN_COLS, MAX_COLS);
    config++;
    scanf("%d", config);
    while(*config < MIN_COLS || *config> MAX_COLS)
    {
        printf("\n Numero de columnas invalido, vuelva a ingresar otra cantidad:");
        scanf("%d", config);
    }

    //Elegir el patron
    config++;
    printf("\nPatrones disponibles:");
    printf("\n1.Planeador/Glider");
    printf("\n2.Sapo");
    printf("\n3.Canon de planeadores");
    printf("\nSeleccione el patron a utilizar [1-3]:");
    scanf("%d", config);
    while(*config < 1 || *config >3)
    {
        printf("\nElegi un patron valido:");
        scanf("%d", config);
    }

    printf("\n----------------------------------------------------------------------\n");
}
/** D
* La funcion me permite mostrar una matriz
* Algoritmo:
*   1. Recorro la matriz y muestro
*
* @param int matriz[][] - matriz con la generacion a mostrar
*/
void imprimirTablero(int ** tablero, unsigned int fila, unsigned int columna, SDL_Renderer * renderer)
{

    // Se limpia la pantalla
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0xFF);  // gris medio, combina suave con gris oscuro
    SDL_RenderClear(renderer);

    int i = 0;
    int j = 0;

    for(i =  0; i<fila; i++)
    {
        for(j = 0; j<columna; j++)
        {
            if(tablero[i][j] != 0)
            {
                drawSquare(renderer, i * TAM_SQUARE, j * TAM_SQUARE);
            }
        }
        //printf("\n");
    }

    SDL_RenderPresent(renderer);
}
/**
* La funcion me permite dibujar un cuadrado en el renderer
*
* @param SDL_Renderer * renderer - puntero al renderer
* @param unsigned int posX - posicion en x
* @param unsigned int posY - posicion en y
*/
void drawSquare(SDL_Renderer * renderer, unsigned int posX, unsigned int posY)
{
    SDL_Rect square;

    //Posicion
    square.x = posX;
    square.y = posY;

    //Tamaño
    square.h = TAM_SQUARE;
    square.w = TAM_SQUARE;

    //Plantilla para pintar cuadrados
    //SDL_SetRenderDrawColor(renderer, 0, 200, 0, 0xFF); // verde
    SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);  // Light Pink

    SDL_RenderFillRect(renderer, &square);
}
/** D
* La funcion me permite mostrar una imagen antes de comenzar con el juego
*
* @param cont char * img - puntero a la imagen que quiero mostrar
*
* @return EXITO si la imagen se muestra correctamente
* @return SDL_ERROR - WINDOW_ERROR en caso de error
*/
int mostrarIntro(const char * img){
    // Creo una ventana para poder mostrar la imagen
  SDL_Window * win = SDL_CreateWindow(
        "Conway - Intro",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 400, SDL_WINDOW_SHOWN);

    //Valido que se crea bien la ventana
    if (!win) return WINDOW_ERROR;

    //Creo y valido el renderer
    SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        SDL_DestroyWindow(win);
        return SDL_ERROR;
    }

    //Cargo la imagen y valido
    SDL_Surface * surf = SDL_LoadBMP(img);
    if (!surf) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return SDL_ERROR;
    }

    //Convierto/Creacion a textura SDL
    SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);

    if (!tex) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return SDL_ERROR;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    //Guardo el time en milisegundos desde que se inicializo el SDL
    Uint32 start = SDL_GetTicks();
    SDL_Event ev;
    int loop = 1;

    //Bucle que dura hasta 2000ms (2seg) y valida eventos
    while (loop && SDL_GetTicks() - start < 2000) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT || ev.type == SDL_KEYDOWN) loop = 0;
        }
    }

    //Libero
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    return EXITO;
}
/**
* Funcion principal donde se ejecuta el Juego - Conway
*/
int juego(){

    ///Inicializar variables
    unsigned char done;
    int delay               = 100;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    int config[2];


    ///Inicializado del SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! ERROR: %s\n", SDL_GetError());
        return SDL_ERROR;
    }

        if(mostrarIntro("conway.bmp") != EXITO){
        SDL_Quit();
        return SDL_ERROR;
    }

    ///Configurar el tablero inicial
    configurarTablero(config);

    ///Create window
    window = SDL_CreateWindow("Juego de Conway", // Nombre de la ventana
                              SDL_WINDOWPOS_UNDEFINED, //Posicion
                              SDL_WINDOWPOS_UNDEFINED, //Posicion
                              config[INDEX_F]*TAM_SQUARE, // width
                              config[INDEX_C]*TAM_SQUARE, // height
                              SDL_WINDOW_SHOWN); // visibilidad


    ///Validar que se crea la ventana
    if (!window)
    {
        SDL_Log("Error! No se puede crear la ventana: %s\n", SDL_GetError());
        SDL_Quit(); //Limpia y libera todos los recursos de SDL
        return WINDOW_ERROR;
    }

    /// Creacion del render
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return WINDOW_ERROR;
    }


    ///Inicializar tablero
    int ** tablero = crearTablero(config[INDEX_F], config[INDEX_C]);
    inicializarTablero(tablero, config[INDEX_F], config[INDEX_C], config[PATRON]);

    ///Evento principal
    while (!done)  //Se puede parar tambien cuando no se observen cambios!
    {

        //Captura eventos
        while (SDL_PollEvent(&e) != 0)
        {
            // Salida del usuario
            if (e.type == SDL_QUIT)
            {
                done = 1;
            }
        }

        //
        imprimirTablero(tablero, config[INDEX_F], config[INDEX_C], renderer);
        //
        procesarTablero(tablero, config[INDEX_F], config[INDEX_C]);

        // Actualizacion del "lienzo"
        SDL_RenderPresent(renderer);
        //SDL_UpdateWindowSurface(window);

        //Titulo/caption de la ventana
        //SDL_SetWindowTitle(window, "Porque no usar esto para poner alguna info del proceso?");
        SDL_Delay(delay);

        //Procesamiento de matriz?
    }


    /// Finalizo el programa

    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    destruirTablero(tablero, config[INDEX_F]);

    return EXITO;
}
