#include <SDL.h> 
#include <stdio.h>



int main(){

    enum direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Nibbles",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    int direction = 0;

    SDL_Rect head {500,500,10,10};
    SDL_Event e;

    while (running)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type ==SDL_QUIT) {running = false;}
             if (e.type == SDL_KEYDOWN){
                 if (e.key.keysym.sym == SDLK_DOWN) {direction=DOWN;}
                 if (e.key.keysym.sym == SDLK_UP) {direction=UP;}
                  if (e.key.keysym.sym == SDLK_LEFT) {direction=LEFT;}
                   if (e.key.keysym.sym == SDLK_RIGHT) {direction=RIGHT;}
             }

        }
        switch (direction)
        {
        case DOWN:
            head.y += 10;
            break;
        case UP:
            head.y -= 10;
            break;    
        case LEFT:
            head.x -= 10;
            break;
        case RIGHT:
            head.x += 10;
            break;    
        
        }
    }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &head);

        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    

    return 0;
}