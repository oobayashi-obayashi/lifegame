#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

//
//for function 

bool handleInlineArgment(int *argc,char* argv[]);
void putBitXY(short x, short y, uint64_t* bits);

//for variables and arrays
uint64_t bitOriginal[256*4] = {0};
uint64_t bitSecond[256*4]= {0};
uint64_t bitDorowAnker[256*4] = {0};

uint64_t* bitMain = bitOriginal;
uint64_t* bitNext = bitSecond;

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
        SDL_FillSurfaceRects(surWin, cellStr_p,256 * 4,(Uint32)0xffffff);

        int cellNumber = 0;
        for(int i = 0;i < 256*4;i++)
        {
            uint64_t lineForcused = bitOriginal[i];

            for(int ii = 0;ii < 64;ii++)
            {
                if(lineForcused & ((uint64_t)1 << ii))
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
        SDL_FillSurfaceRects(surWin, cellStr_p,256 * 4,(Uint32)0xffffff);
        int cellNumber = 0;
        for(int i = 0;i < 256*4;i++)
        {
            uint64_t lineForcused = bitOriginal[i];

            for(int ii = 0;ii < 64;ii++)
            {
                if(lineForcused & ((uint64_t)1 << ii))
                {
                    SDL_FillSurfaceRect(surWin, &cellStr_p[cellNumber],(Uint32)0x000000);
                }
                cellNumber++;
            }
        }
    }


//====================================================================================================
   {
        uint64_t u0m    = bitMain[252];
        uint64_t u1m    = bitMain[253];
        uint64_t u2m    = bitMain[254];
        uint64_t u3m    = bitMain[255];

        uint64_t u0l = u0m >> 1 | u3m << 63; 
        uint64_t u0r = u0m << 1 | u1m >> 63;
        uint64_t u1l = u1m >> 1 | u0m << 63;
        uint64_t u1r = u1m << 1 | u2m >> 63;
        uint64_t u2l = u2m >> 1 | u1m << 63;
        uint64_t u2r = u2m << 1 | u3m >> 63;
        uint64_t u3l = u3m >> 1 | u2m << 63;
        uint64_t u3r = u3m << 1 | u0m >> 63;

        uint64_t u00 = (u0l ^ u0r) ;
        uint64_t u01 = (u0l & u0r) ;
        u01 = u01 | (u00 & u0m) ;
        u00 = (u00 ^ u0m) ;

        uint64_t u10 = (u1l ^ u1r) ;
        uint64_t u11 = (u1l & u1r) ;
        u11 = u11 | (u10 & u1m) ;
        u10 = (u10 ^ u1m) ;

        uint64_t u20 = (u2l ^ u2r) ;
        uint64_t u21 = (u2l & u2r) ;
        u21 = u21 | (u20 & u2m) ;
        u20 = (u20 ^ u2m) ;

        uint64_t u30 = (u3l ^ u3r) ;
        uint64_t u31 = (u3l & u3r) ;
        u31 = u31 | (u30 & u3m) ;
        u30 = (u30 ^ u3m) ;

                                               
        uint64_t c0m    = bitMain[0];
        uint64_t c1m    = bitMain[1];
        uint64_t c2m    = bitMain[2];
        uint64_t c3m    = bitMain[3];

        uint64_t c0l = c0m >> 1 | c3m << 63; 
        uint64_t c0r = c0m << 1 | c1m >> 63;
        uint64_t c1l = c1m >> 1 | c0m << 63;
        uint64_t c1r = c1m << 1 | c2m >> 63;
        uint64_t c2l = c2m >> 1 | c1m << 63;
        uint64_t c2r = c2m << 1 | c3m >> 63;
        uint64_t c3l = c3m >> 1 | c2m << 63;
        uint64_t c3r = c3m << 1 | c0m >> 63;

        uint64_t c00 = (c0l ^ c0r) ;
        uint64_t c01 = (c0l & c0r) ;
        c01 = c01 | (c00 & c0m) ;
        c00 = (c00 ^ c0m) ;

        uint64_t c10 = (c1l ^ c1r) ;
        uint64_t c11 = (c1l & c1r) ;
        c11 = c11 | (c10 & c1m) ;
        c10 = (c10 ^ c1m) ;

        uint64_t c20 = (c2l ^ c2r) ;
        uint64_t c21 = (c2l & c2r) ;
        c21 = c21 | (c20 & c2m) ;
        c20 = (c20 ^ c2m) ;

        uint64_t c30 = (c3l ^ c3r) ;
        uint64_t c31 = (c3l & c3r) ;
        c31 = c31 | (c30 & c3m) ;
        c30 = (c30 ^ c3m) ;

        for(int i = 0;i < 256*4;i+=4)
        {
            uint64_t l0m    = bitMain[(uint8_t)(i+4)];
            uint64_t l1m    = bitMain[(uint8_t)(i+5)];
            uint64_t l2m    = bitMain[(uint8_t)(i+6)];
            uint64_t l3m    = bitMain[(uint8_t)(i+8)];

            uint64_t l0l = l0m >> 1 | l3m << 63; 
            uint64_t l0r = l0m << 1 | l1m >> 63;
            uint64_t l1l = l1m >> 1 | l0m << 63;
            uint64_t l1r = l1m << 1 | l2m >> 63;
            uint64_t l2l = l2m >> 1 | l1m << 63;
            uint64_t l2r = l2m << 1 | l3m >> 63;
            uint64_t l3l = l3m >> 1 | l2m << 63;
            uint64_t l3r = l3m << 1 | l0m >> 63;

            uint64_t l00 = (l0l ^ l0r) ;
            uint64_t l01 = (l0l & l0r) ;
            l01 = l01 | (l00 & l0m) ;
            l00 = (l00 ^ l0m) ;

            uint64_t l10 = (l1l ^ l1r) ;
            uint64_t l11 = (l1l & l1r) ;
            l11 = l11 | (l10 & l1m) ;
            l10 = (l10 ^ l1m) ;

            uint64_t l20 = (l2l ^ l2r) ;
            uint64_t l21 = (l2l & l2r) ;
            l21 = l21 | (l20 & l2m) ;
            l20 = (l20 ^ l2m) ;

            uint64_t l30 = (l3l ^ l3r) ;
            uint64_t l31 = (l3l & l3r) ;
            l31 = l31 | (l30 & l3m) ;
            l30 = (l30 ^ l3m) ;

            uint64_t tc00 = c00;
            uint64_t tc01 = c01;
            uint64_t tc10 = c10;
            uint64_t tc11 = c11;
            uint64_t tc20 = c20;
            uint64_t tc21 = c21;
            uint64_t tc30 = c30;
            uint64_t tc31 = c31;



            c01 = ~(c01 & (~c00 & c0m));
            c00 = c00 ^ c0m;
            c11 = ~(c11 & (~c10 & c1m));
            c10 = c10 ^ c1m;
            c21 = ~(c21 & (~c20 & c2m));
            c20 = c20 ^ c2m;
            c31 = ~(c31 & (~c30 & c3m));
            c30 = c30 ^ c3m;

            uint64_t r00 = c00;
            uint64_t r01 = c01;
            uint64_t r02;

            r02 = (r01 & u01) | (u01 &(r00 & u00));
            r00 = r00 ^ u00;
            r01 = (r01 ^ u01) ^ (r00 & u00);
            
            r00 = r00 ^ l00;
            r02 = ((r01 & l01) | (l01 &(r00 & l00))) ^ r02;
            r01 = (r01 ^ l01) ^ (r00 & l00);

            bitNext[i] = ((r00 & r01) & ~r02) | c0m & (~(r00 | r02) & r01);



            uint64_t r10 = c10;
            uint64_t r11 = c11;
            uint64_t r12;

            r12 = (r11 & u11) | (u11 &(r10 & u10));
            r10 = r10 ^ u10;
            r11 = (r11 ^ u11) ^ (r10 & u10);
            
            r10 = r10 ^ l10;
            r12 = ((r11 & l11) | (l11 &(r10 & l10))) ^ r12;
            r11 = (r11 ^ l11) ^ (r10 & l10);

            bitNext[i+1] = ((r10 & r11) & ~r12) | c1m & (~(r10 | r12) & r11);


            uint64_t r20 = c20;
            uint64_t r21 = c21;
            uint64_t r22;

            r22 = (r21 & u21) | (u21 &(r20 & u20));
            r20 = r20 ^ u20;
            r21 = (r21 ^ u21) ^ (r20 & u20);
            
            r20 = r20 ^ l20;
            r22 = ((r21 & l21) | (l01 &(r20 & l20))) ^ r22;
            r21 = (r01 ^ l01) ^ (r00 & l00);

            bitNext[i+2] = ((r20 & r21) & ~r22) | c2m & (~(r20 | r22) & r21);



            uint64_t r30 = c30;
            uint64_t r31 = c31;
            uint64_t r32;

            r32 = (r31 & u31) | (u31 &(r30 & u30));
            r30 = r30 ^ u30;
            r31 = (r31 ^ u31) ^ (r30 & u30);
            
            r30 = r30 ^ l30;
            r32 = ((r31 & l31) | (l31 &(r30 & l30))) ^ r32;
            r31 = (r31 ^ l31) ^ (r30 & l30);

            bitNext[i+3] = ((r30 & r31) & ~r32) | c3m & (~(r30 | r32) & r31);



            u00 = tc00;
            u01 = tc01;
            u10 = tc10;
            u11 = tc11;
            u20 = tc20;
            u21 = tc21;
            u30 = tc30;
            u31 = tc31;

            
            c00 = l00;
            c01 = l01;
            c10 = l10;
            c11 = l11;
            c20 = l20;
            c21 = l21;
            c30 = l30;
            c31 = l31;



        }
    }

//====================================================================================================




        
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


        uint64_t *temp = bitMain;
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

void putBitXY(short x, short y, uint64_t* bits)
{
    bitOriginal[(y * 4) + (y / 64)] = bitOriginal[(y * 4) + (y / 64)] | ((uint64_t) 1 << (x % 64));
}
