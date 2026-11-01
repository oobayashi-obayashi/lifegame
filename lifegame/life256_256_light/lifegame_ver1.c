#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

//
typedef unsigned _BitInt(256) uint256_t;

//for function 

bool handleInlineArgment(int *argc,char* argv[]);
void putBitXY(short x, short y, uint256_t* bits);

//for variables and arrays
uint256_t bitOriginal[256] = {0};
uint256_t bitSecond[256] = {0};
uint256_t bitDorowAnker[256] = {0};

uint256_t* bitMain = bitOriginal;
uint256_t* bitNext = bitSecond;

//unsigned char activeline[256] = {0};

//main

int main(int argc,char* argv[])
{
    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);//----------------------------------- This is the point where SDL was initialised.

    window = SDL_CreateWindow
    (
        "LifeGame256*256",
        768,
        768,
        SDL_WINDOW_OPENGL
    );

    SDL_Surface *surWin = SDL_GetWindowSurface(window);
    //check if the window was created successfully
    if(window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Can\'generated the window successfully");
        return 1;
    }

    //start drowing

    SDL_FillSurfaceRect(surWin, NULL, (Uint32)0xdcdcdc);

    SDL_Rect cellStr[256*256];
    for(short i = 0; i < 256; i++)
    {
        for(short ii = 0; ii < 256; ii++)
        {
            SDL_Rect *picked = &cellStr[i * 256 + ii];
            picked -> x = ii * 3;
            picked -> y = i * 3;
            picked -> w = 2;
            picked -> h = 2;
        }
    }
    const SDL_Rect* cellStr_p = cellStr;
    SDL_FillSurfaceRects(surWin, cellStr_p, 256*256, (Uint32)0xffffff);

    handleInlineArgment(&argc,argv);

    SDL_FillSurfaceRects(surWin,cellStr_p,256*256,(Uint32)0xffffff);
    {
        int cellNumber = 0;
        for(int i = 0;i < 256;i++)
        {
            uint256_t lineForcused = bitOriginal[i];
            for(int ii = 0;ii < 256;ii++)
            {
                if(lineForcused & ((uint256_t)1 << ii))
                {
                    SDL_FillSurfaceRect(surWin, &cellStr_p[cellNumber],(Uint32)0x000000);
                }
                cellNumber++;
            }
        }
    }
    printf("initialasiation succesed\n");

    SDL_UpdateWindowSurface(window);
   
   usleep(1000000);
    //----------------------------------------start of roop----------------------------------------
    

    unsigned long long int roopCount = 0;
    unsigned int eventClock = 0;
    unsigned int roopClock = 0;
    unsigned long long int roopClockroop = 0;

    while(!done)
    {
        SDL_Event event;

        {
            int cellNumber = 0;
            for(int i = 0;i < 256;i++)
            {
                uint256_t lineForcused = bitMain[i];
                uint256_t lineDrowAnker = bitDorowAnker[i];
                if(lineDrowAnker)
                {
                    for(int ii = 0;ii < 256;ii++)
                    {
                        if(lineDrowAnker & ((uint256_t)1 << ii))
                        {
                            SDL_FillSurfaceRect(surWin, &cellStr_p[cellNumber],((Uint32)0xffffff) + ((lineForcused  >> ii) & 1));
                        }
                        cellNumber++;
                    }
                }else{
                    cellNumber += 256;

                }
            }
        }
   //usleep(20000);



        for(int i = 0; i < 256; i++)
        {
            uint256_t lineUpper = bitMain[(unsigned char)(i-1)];
            uint256_t lineMain = bitMain[(unsigned char)i];
            uint256_t linelower = bitMain[(unsigned char)(i+1)];
            uint256_t lineMainNext = 0;

            for(int ii = 0; ii < 256;ii++)
            {
                unsigned char id = 
                         ((lineUpper >> (unsigned char)(ii+1)) & (uint256_t)1)
                        +((lineUpper >> (unsigned char)(ii  )) & (uint256_t)1)
                        +((lineUpper >> (unsigned char)(ii-1)) & (uint256_t)1)

                        +((lineMain  >> (unsigned char)(ii+1)) & (uint256_t)1)
                        +((lineMain  >> (unsigned char)(ii-1)) & (uint256_t)1)

                        +((linelower >> (unsigned char)(ii+1)) & (uint256_t)1)
                        +((linelower >> (unsigned char)(ii  )) & (uint256_t)1)
                        +((linelower >> (unsigned char)(ii-1)) & (uint256_t)1);
                //id = (((unsigned _BitInt(3))id-4) > ((!((lineMain >> (ii)) & (uint256_t)1))+5));
                id = ((lineMain >> (ii)&1) && id == 2) || id == 3;
                lineMainNext  = (((uint256_t)id) << (unsigned char)ii) ^ lineMainNext;
            }
            bitNext[i] = lineMainNext; 
            bitDorowAnker[i]= lineMainNext | lineMain;
        }

        for(int i = 0; i < 256; i++)
        {
            bitMain[i] = 0;
        }
        




        
        if(eventClock = 40)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_EVENT_QUIT)
                {
                    done = true;
                }
            }
           eventClock = 0;
        }


        uint256_t *temp = bitMain;
        bitMain = bitNext;
        bitNext = temp;


       SDL_UpdateWindowSurface(window);
        if(roopCount == 1000)
        {
            printf("1000\n");
            roopCount = 0;
        }

        roopCount++;
        eventClock++;
    }

    //----------------------------------------end of roop----------------------------------------


    printf("finishing...\n");



    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

//========================================end of function `main`========================================


bool handleInlineArgment(int *argc,char* argv[])
{
    for(int i = 1; i < *argc; i+=2)
    {
        short x = atoi(argv[i]);
        short y = atoi(argv[i+1]);
        putBitXY(x,y,bitOriginal);
    }
    return 0;
}

void putBitXY(short x, short y, uint256_t* bits)
{
   uint256_t temp = 1;
   temp = temp << x;
   bits[y] = bits[y] | temp;
}
