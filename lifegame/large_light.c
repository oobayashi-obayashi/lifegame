#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

void set_cell(short x,short y);
 //          y    x
bool cellbit[194][194] = {0};
bool nextcell[194][194] = {0};
bool torf_t[8]={0,0,1,1,0,0,0,0};
bool torf_f[8]={0,0,0,1,0,0,0,0};
//           cell memo[n] = n's X
//           cell memo[n+1] = n's Y 
//       n = 2*k    
short cell_memo[192*192*2] = {0};
short cell_memo_next[192*192*2] = {0};
int cell_memo_l = 0;
int cell_memo_l_next = 0;

short *main_stock = cell_memo;
short *next_stock = cell_memo_next;
int *main_l = &cell_memo_l;
int *next_l = &cell_memo_l_next;


bool *mainbits = &(cellbit[0][0]);
bool *nextbits = &(nextcell[0][0]);

void around_call_t(int tx,int ty);
void around_call_f(int tx,int ty);



int main(int argc, char* argv[]) {

    SDL_Window *window;                    // ポインタを宣言する
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // SDL3初期化する

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "MyWindow",                  // ウィンドウのタイトル
        768,                               // 幅のピクセル数
        768,                               // 高さの192セル数
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



        
    
    SDL_Rect *cellpool = (SDL_Rect*)malloc(192*192*sizeof(SDL_Rect));
    for(int i = 0;i < 192;i++){
        for(int ii = 0; ii < 192;ii++){
                SDL_Rect *this = &cellpool[i*192+ii];
                this->x = ii*4;
                this->y = i*4;
                this->w = 3;
                this->h = 3;
                
        }
    }


    const SDL_Rect* cells = cellpool;
    SDL_FillSurfaceRects(Winsurface,cells, 192*192, (Uint32)0xffffff);

    printf("%d\n",argc);

    short *default_cell = malloc((argc-1)*sizeof(short));
    
    for(int i = 0;i < argc-1;i++){
        default_cell[i]=(short)atoi(argv[i+1]);
    }
    for(int i = 0;i < argc-1; i+=2){
        set_cell(default_cell[i],default_cell[i+1]);
            cell_memo[cell_memo_l] = default_cell[i];
            cell_memo[cell_memo_l+1]= default_cell[i+1];
            cell_memo_l += 2;
    }
        


    
 


    

    


    long LoopCount=0;
    while (!done) {

       SDL_Event event;
               
       for(int i = 1;i<193;i++){
            for(int ii = 1; ii < 193;ii++){
                if(mainbits[i*194+ii]){
                    around_call_t(ii,i);
                }else{
                    around_call_f(ii,i);
                }
            }
       }





    SDL_FillSurfaceRects(Winsurface,cells, 192*192, (Uint32)0xffffff);

    for(int i = 0;i<192;i++){
            for(int ii = 0;ii<192;ii++){
                if(mainbits[(i+1)*194+ii+1])
                SDL_FillSurfaceRect(Winsurface,&cells[192*i+ii],(Uint32)0x000000);
            }
    }



        

   usleep(10000);



    for(int i = 0;i < 194*194;i++){
        mainbits[i]=false;
    }
       SDL_UpdateWindowSurface(window); 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }


        bool* temp = mainbits;
        mainbits = nextbits;
        nextbits = temp;

        short* temp_stock = next_stock;
        next_stock = main_stock;
        main_stock = temp_stock;

        int* temp_l = next_l;
        next_l = main_l;
        main_l = temp_l;


       LoopCount++;
       if((LoopCount % 1000)==0){
            printf("%d\n",LoopCount);
       }
    }

    

    // ウィンドウを閉じて破棄する
    SDL_DestroyWindow(window);
    free(cellpool);
    // 終了処理
    SDL_Quit();
    return 0;
}


void set_cell(short x,short y)
{
   cellbit[y+1][x+1] = true;
}




void around_call_t(int tx,int ty)
{
    nextbits[ty*194+tx]=torf_t[
    mainbits[(ty-1)*194+tx]
    +mainbits[(ty-1)*194+tx-1]
    +mainbits[(ty-1)*194+tx+1]
    +mainbits[(ty)*194+tx+1]
    +mainbits[(ty)*194+tx-1]
    +mainbits[(ty+1)*194+tx]
    +mainbits[(ty+1)*194+tx-1]
    +mainbits[(ty+1)*194+tx+1]
    ];
}
void around_call_f(int tx,int ty)
{
    nextbits[ty*194+tx]=torf_f[
    mainbits[(ty-1)*194+tx]
    +mainbits[(ty-1)*194+tx-1]
    +mainbits[(ty-1)*194+tx+1]
    +mainbits[(ty)*194+tx+1]
    +mainbits[(ty)*194+tx-1]
    +mainbits[(ty+1)*194+tx]
    +mainbits[(ty+1)*194+tx-1]
    +mainbits[(ty+1)*194+tx+1]
    ];
}
