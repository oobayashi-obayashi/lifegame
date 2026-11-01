#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer; // レンダラー用のポインタを追加
    bool done = false;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // ウィンドウとレンダラーを同時に作成する
    // SDL3では SDL_CreateWindowAndRenderer が便利です
    if (!SDL_CreateWindowAndRenderer("An SDL3 window", 640, 480, SDL_WINDOW_OPENGL, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ウィンドウまたはレンダラーを生成できなかった: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // 画面を黒色でクリアして描画を更新する（Waylandでウィンドウを表示させるために必要）
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // 終了処理
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
