#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

void set_cell(char x,char y);
 //          y    x
bool cellbit[66][66] = {0};
bool nextcell[66][66] = {0};
bool torf_t[8]={0,0,1,1,0,0,0,0};
bool torf_f[8]={0,0,0,1,0,0,0,0};

bool *mainbits = &(cellbit[0][0]);
bool *nextbits = &(nextcell[0][0]);

void around_call_t(char tx,char ty);
void around_call_f(char tx,char ty);



int main(int argc, char* argv[]) {

    SDL_Window *window;                    // ポインタを宣言する
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // SDL3初期化する

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "MyWindow",                  // ウィンドウのタイトル
        512,                               // 幅のピクセル数
        512,                               // 高さのピクセル数
        SDL_WINDOW_OPENGL                  // フラグ
    );
    SDL_Surface *Winsurface = SDL_GetWindowSurface(window);
    SDL_FillSurfaceRect(Winsurface, NULL,(Uint32)0xdcdcdc);
    SDL_UpdateWindowSurface(window); 
    // ウィンドウの生成に成功したかチェックする
    if (window == NULL) {
        // ここを通ったならばウィンドウを生成できなかった...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ウィンドウを生成できなかった: %s\n", SDL_GetError());
        printf("hello,world");
        return 1;
    }



        
    
    SDL_Rect *cellpool = (SDL_Rect*)malloc(64*64*sizeof(SDL_Rect));
    for(int i = 0;i < 64;i++){
        for(int ii = 0; ii < 64;ii++){
                SDL_Rect *this = &cellpool[i*64+ii];
                this->x = ii*8;
                this->y = i*8;
                this->w = 7;
                this->h = 7;
                
        }
    }


    const SDL_Rect* cells = cellpool;
    SDL_FillSurfaceRects(Winsurface,cells, 64*64, (Uint32)0xffffff);

    printf("%d\n",argc);

    char *default_cell = malloc((argc-1)*sizeof(char));
    
    for(int i = 0;i < argc-1;i++){
        default_cell[i]=(char)atoi(argv[i+1]);
    }
    for(int i = 0;i < argc-1; i+=2){
        set_cell(default_cell[i],default_cell[i+1]);
    }


    
   
 


    

    


    long LoopCount=0;
    while (!done) {



        
        for(char i = 1;i < 65; i++){
            for(char ii = 1;ii <65;ii++){
                if(mainbits[i*66+ii]){
                    around_call_t(ii,i);
                }else{
                    around_call_f(ii,i);
                }
            }
        }
       SDL_Event event;





    SDL_FillSurfaceRects(Winsurface,cells, 64*64, (Uint32)0xffffff);

    for(int i = 0;i<64;i++){
            for(int ii = 0;ii<64;ii++){
                if(mainbits[(i+1)*66+ii+1])
                SDL_FillSurfaceRect(Winsurface,&cells[64*i+ii],(Uint32)0x000000);
            }
    }



        

       usleep(20000);



       SDL_UpdateWindowSurface(window); 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        bool* temp = mainbits;
        mainbits = nextbits;
        nextbits = temp;
       LoopCount++;
    }

    for(int i = 0;i < 66*66;i++){
        mainbits[i]=0;
    }
    

    // ウィンドウを閉じて破棄する
    SDL_DestroyWindow(window);
    free(cellpool);
    // 終了処理
    SDL_Quit();
    return 0;
}


void set_cell(char x,char y)
{
   cellbit[y+1][x+1] = true;
}




void around_call_t(char tx,char ty)
{
    nextbits[ty*66+tx]=torf_t[
    mainbits[(ty-1)*66+tx]
    +mainbits[(ty-1)*66+tx-1]
    +mainbits[(ty-1)*66+tx+1]
    +mainbits[(ty)*66+tx+1]
    +mainbits[(ty)*66+tx-1]
    +mainbits[(ty+1)*66+tx]
    +mainbits[(ty+1)*66+tx-1]
    +mainbits[(ty+1)*66+tx+1]
    ];
}
void around_call_f(char tx,char ty)
{
    nextbits[ty*66+tx]=torf_f[
    mainbits[(ty-1)*66+tx]
    +mainbits[(ty-1)*66+tx-1]
    +mainbits[(ty-1)*66+tx+1]
    +mainbits[(ty)*66+tx+1]
    +mainbits[(ty)*66+tx-1]
    +mainbits[(ty+1)*66+tx]
    +mainbits[(ty+1)*66+tx-1]
    +mainbits[(ty+1)*66+tx+1]
    ];
}
