#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>

const SDL_Color COLOR_TRANSPARENT   = {0};
const SDL_Color COLOR_BLACK         = {0, 0, 0, 255};
const SDL_Color COLOR_WHITE         = {255, 255, 255, 255};
const SDL_Color COLOR_GRAY          = {100, 100, 100, 255};
const SDL_Color COLOR_DARK_GRAY     = {30, 30, 30, 255};
const SDL_Color COLOR_LIGHT_GRAY    = {200, 200, 200, 255};
const SDL_Color COLOR_RED           = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN         = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE          = {0, 0, 255, 255};
const SDL_Color COLOR_YELLOW        = {255, 255, 0, 255};
const SDL_Color COLOR_ORANGE        = {255, 133, 0, 255};
const SDL_Color COLOR_PINK          = {255, 0, 206, 255};
const SDL_Color COLOR_VIOLET        = {145, 0, 255, 255};


void level1();

void level2();

void level3();

const int SCREEN_WIDTH = 656;
const int SCREEN_HEIGHT = 400;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;








// Load an image and return an SDL_Texture
SDL_Texture* load_texture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Draw a texture at the specified location
void draw_texture(SDL_Texture* texture, int x, int y) {
    SDL_Rect rect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

struct box{
    int x;
    int y;
    int w;
    int h;
};

struct box start = { 248, 100, 160, 60};
struct box options = { 248, 180, 160, 60};
struct box close = { 248, 260, 160, 60};

int check_choice(int x, int y){
    if((x >= start.x && x <= start.x + start.w) && (y >= start.y && y <= start.y + start.h)){
        return 1;
    }else if((x >= options.x && x <= options.x + options.w) && (y >= options.y && y <= options.y + options.h)){
        return 2;
    }else if((x >= close.x && x <= close.x + close.w) && (y >= close.y && y <= close.y + close.h)){
        return 3;
    }
    return 0;
}

void draw_volume_Bar(int volume, SDL_Texture* red, SDL_Texture* white){
    volume /= 10;
    int i = 0;
    while(i < volume){
        draw_texture(red, 128 + 180 + i * 10, 50 + 125);
        SDL_RenderPresent(renderer);
        i++;
    }
    i = volume;
    while(i < 10){
        draw_texture(white, 128 + 180 + i * 10, 50 + 125);
        SDL_RenderPresent(renderer);
        i++;
    }
}








int walls[25][41]={
   //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int wallCollision(int x, int y, int direction) {
    x /= 16;
    y /= 16;
    if(walls[y-1][x] == 1 && direction == 0){
       return 0;
    }else if(walls[y][x-1] == 1 && direction == 1){
        return 0;
    }else if(walls[y+1][x] == 1 && direction == 2){
        return 0;
    }else if(walls[y][x+1] == 1 && direction == 3){
        return 0;
    }
    return 1;
}


void level1(){

    // Load background, character, and obstacle images
        SDL_Texture* bugUp_texture = load_texture("assets/level1/bugUp.png");
        SDL_Texture* bugLeft_texture = load_texture("assets/level1/bugLeft.png");
        SDL_Texture* bugDown_texture = load_texture("assets/level1/bugDown.png");
        SDL_Texture* bugRight_texture = load_texture("assets/level1/bugRight.png");
        SDL_Texture* maze_texture = load_texture("assets/level1/maze.png");

        SDL_Texture* success_texture = load_texture("assets/level1/final.png");
        SDL_Texture* failed_texture = load_texture("assets/level1/finalFail.png");

        SDL_Texture* character_texture = load_texture("assets/level1/character.png");
        SDL_Texture* prison_texture = load_texture("assets/level1/prison.png");


        int x = 0;
        int y = 150;
        int quit = 0;
        while(x < 640){
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {

                } else if (event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        x += 16;
                    }
                }
            }
            SDL_RenderClear(renderer);
            draw_texture(prison_texture, 0, 0);
            draw_texture(character_texture, x, y);
            SDL_RenderPresent(renderer);
        }




        int bugAbs = 0;
        int bugOrd = 48;

        //Drawing the walls

        SDL_SetRenderDrawColor(renderer, 173, 216, 230, 1);
        SDL_RenderClear(renderer);
        draw_texture(maze_texture, 0, 0);
        draw_texture(bugRight_texture,bugAbs,bugOrd);

        SDL_RenderPresent(renderer);


        Uint32 startTime = SDL_GetTicks();
        Uint32 elapsedTime = 0;
        SDL_Event event;
        quit = 0;
        int direction = -1;
        while (!quit && elapsedTime <= 60000) {
            switch(direction){
                case 0:
                    draw_texture(bugUp_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 1:
                    draw_texture(bugLeft_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 2:
                    draw_texture(bugDown_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 3:
                    draw_texture(bugRight_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
            }

            int auxOrd = 0, auxAbs = 0;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = 1;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            auxOrd = -16;
                            direction = 0;
                            break;
                        case SDLK_DOWN:
                            auxOrd = 16;
                            direction = 2;
                            break;
                        case SDLK_LEFT:
                            auxAbs = -16;
                            direction = 1;
                            break;
                        case SDLK_RIGHT:
                            auxAbs = 16;
                            direction = 3;
                            break;
                    }

                }
                if(wallCollision(bugAbs,bugOrd,direction) == 1 && !(bugAbs == 0 && bugOrd == 48 && direction == 1)){

                    bugAbs += auxAbs;
                    bugOrd += auxOrd;
                    SDL_RenderClear(renderer);
                    draw_texture(maze_texture,0,0);
                    switch(direction){
                        case 0:
                            draw_texture(bugUp_texture,bugAbs,bugOrd);
                            break;
                        case 1:
                            draw_texture(bugLeft_texture,bugAbs,bugOrd);
                            break;
                        case 2:
                            draw_texture(bugDown_texture,bugAbs,bugOrd);
                            break;
                        case 3:
                            draw_texture(bugRight_texture,bugAbs,bugOrd);
                            break;
                    }
                    SDL_RenderPresent(renderer);


                    Uint32 currentTime = SDL_GetTicks();
                    elapsedTime = currentTime - startTime;
                    Uint32 elapsedSeconds = elapsedTime / 1000;
                    char timerText[10];
                    sprintf(timerText, "%02d:%02d", elapsedSeconds / 60, elapsedSeconds % 60);
                    stringRGBA(renderer, 597, 20, timerText, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, COLOR_RED.a);
                    //Update Screen
                    SDL_RenderPresent(renderer);

                }

            }
            if(bugAbs == 640 && bugOrd== 304){
                quit = 1;

                draw_texture(success_texture, 0, 0);
                SDL_RenderPresent(renderer);

                SDL_Delay(3000);

                //level2();


            }


        }
        if(elapsedTime > 60000){

            draw_texture(failed_texture, 0, 0);
            SDL_RenderPresent(renderer);

            SDL_Delay(3000);

            level1();
        }


}


// functions of level2


void level2(){
    int success = 0;
    if(success == 1){
        level3();
    }else if(success == 0){
        level2();
    }

}





// functions of level3



void level3(){
    int success = 0;
    if(success == 1){

    }else if(success == 0){
        level3();
    }

}


int main(int argc, char* argv[]) {

    (void) argc;
    (void) argv;

    // Initialize SDL2 and create a window and renderer
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    window = SDL_CreateWindow("The Big 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* homepage_texture = load_texture("assets/homepage/homepage.png");
    SDL_Texture* options_texture = load_texture("assets/homepage/options.png");
    SDL_Texture* redBar_texture = load_texture("assets/homepage/redBar.png");
    SDL_Texture* whiteBar_texture = load_texture("assets/homepage/whiteBar.png");

    int volume = 70;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    Mix_Music* music = Mix_LoadMUS("assets/homepage/musicHome.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(((float)volume / 100) * 128);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    draw_texture(homepage_texture, 0, 0);

    SDL_RenderPresent(renderer);



    int quit = 0;

    int setting = 0;

    int x;
    int y;



    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            Mix_VolumeMusic(((float)volume / 100) * 128);
            if (event.type == SDL_QUIT) {
                quit = 1;
            }else if (event.type == SDL_MOUSEBUTTONDOWN){
                x = event.button.x;
                y = event.button.y;
                if(setting == 0){
                    if(check_choice(x, y) != 0){
                        int choice = check_choice(x, y);
                        switch(choice){
                            case 1:
                                // start
                                level1();
                                draw_texture(homepage_texture, 0, 0);

                                SDL_RenderPresent(renderer);
                                break;
                            case 2:
                                // options
                                draw_texture(options_texture, 128, 50);

                                draw_volume_Bar(volume, redBar_texture, whiteBar_texture);

                                setting = 1;
                                break;
                            case 3:
                                // exit
                                quit = 1;
                        }
                    }
                }else{
                        if((x >= 145 + 128 && x <= 145 + 24 + 128) && (y >= 125 +50 && y <= 125 + 24 + 50)){
                            if(volume != 0){
                                volume -= 10;
                                draw_volume_Bar(volume, redBar_texture, whiteBar_texture);
                            }
                        }else if((x >= 286 + 128 && x <= 286 + 24 + 128) && (y >= 125 +50 && y <= 125 + 24 + 50)){
                            if(volume != 100){
                                volume += 10;
                                draw_volume_Bar(volume, redBar_texture, whiteBar_texture);
                            }
                        }else if((x >= 340 + 128  && x <= 340 + 20 + 128) && (y >= 20 +50 && y <= 20 + 30 + 50)){
                            SDL_RenderClear(renderer);
                            draw_texture(homepage_texture, 0, 0);
                            SDL_RenderPresent(renderer);
                            setting = 0;
                        }
                    }
                }
            }


        }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    return 0;
}
