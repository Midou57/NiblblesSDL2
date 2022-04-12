#include <SDL2/SDL.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <deque>


#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

int main(int argc, char** argv){


    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    //position de head
    SDL_Rect head {500,500,10,10};

    enum direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

   
    //size de nibble 
    int size = 1;
    SDL_Event e;

    //nibbles corp
    std::deque<SDL_Rect>rq;

    //object à manger
    std::vector<SDL_Rect>obs;

    //creation de map

    //erreur je n'ai pas encore trouvé la solution
    for (int i = 0; i < 100; i++)
    {
       // obs.emplace_back(rand()%100*10, rand()%100*10, 10, 10);
        obs.push_back({rand()%100*10, rand()%100*10, 10, 10});
    }
    
 
    bool running = true;
    int direction = 0;


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
        //Bouger
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

        //detection des collisions avec les objects à manger
        std::for_each(obs.begin(), obs.end(), [&](auto& ob){
            if (head.x == ob.x && head.y == ob.y)
            {
                size +=10;
                //on la déplace juste hors lecran
                ob.x = -10;
                ob.y = -10;
            }
            
        });

        //detection des collisions avec lui meme (nibble meme !)
        std::for_each(rq.begin(), rq.end(), [&](auto& nibble_seg ){
            if(head.x == nibble_seg.x && head.y == nibble_seg.y)
                size = 1;
        });

        // on ajoute un nouveau head à nibble
        rq.push_front(head);

        // on enleve le dernier elem
        while (rq.size() > size )
            rq.pop_back();
        
       

        //effacer la fenetre
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //dessin du corp
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        std::for_each(rq.begin(), rq.end(), [&](auto& nibble_seg ){
            SDL_RenderFillRect(renderer, &nibble_seg);
        });

        //dessin des objects à manger
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        std::for_each(obs.begin(), obs.end(), [&](auto& ob){
             SDL_RenderFillRect(renderer, &ob);
        });
        
       // SDL_RenderFillRect(renderer, &head);

        SDL_RenderPresent(renderer);
        SDL_Delay(40);
    }

    return 0;
}