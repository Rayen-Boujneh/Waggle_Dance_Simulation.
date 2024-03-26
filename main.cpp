#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/stb_image.h"

#include "Beehive2.h"

using namespace std;

const int NUM_FRAMES = 30;


// Function to create a texture from an image
SDL_Texture* createTextureFromImage(SDL_Renderer* renderer, const char* imagePath) {
    int width, height, channels;
    unsigned char* image = stbi_load(imagePath, &width, &height, &channels, 0);
    if (image == nullptr) {
        cerr << "Failed to load image: " << imagePath << endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if (texture == nullptr) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
        stbi_image_free(image);
        return nullptr;
    }

    SDL_UpdateTexture(texture, nullptr, image, width * channels);
    stbi_image_free(image);

    return texture;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Beehive", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_Width,
                                          Window_Height, SDL_WINDOW_SHOWN);

    if (!window) {
        cerr << "The creation of the window failed: " << SDL_GetError() << endl;
        SDL_Quit();
 !       return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        cerr << "Failed to create the renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    // Load the GIF frames into an array of textures
    const char *beeImagePath = "//here we specify the image path ";
    SDL_Texture *beeTextures[NUM_FRAMES];
    int beeWidth, beeHeight;
    for (int i = 0; i < NUM_FRAMES; ++i) {
        beeTextures[i] = createTextureFromImage(renderer, beeImagePath);
        SDL_QueryTexture(beeTextures[i], nullptr, nullptr, &beeWidth, &beeHeight);
    }


    SDL_Rect beeRect;
    beeRect.x = (Window_Width - beeWidth) / 2;
    beeRect.y = (Window_Height - beeHeight) / 2;
    beeRect.w = beeWidth;
    beeRect.h = beeHeight;

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                quit = true;
            }
        }

        Uint32 lastFrameTime = 0;
        const int frameDelay = 100;  // Delay in milliseconds

        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    quit = true;
                }
            }

            Uint32 lastFrameTime = 0;
            const int frameDelay = 100;  // Delay in milliseconds
            int currentFrame = 0;  // Initialize currentFrame

            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    if (e.type == SDL_KEYDOWN) {
                        quit = true;
                    }
                }

                Uint32 currentTime = SDL_GetTicks();
                if (currentTime > lastFrameTime + frameDelay) {
                    currentFrame = (currentFrame + 1) % NUM_FRAMES;
                    lastFrameTime = currentTime;
                    cout << "Current Frame: " << currentFrame << endl;
                }

                SDL_RenderClear(renderer);
                drawBeehive(renderer);
                SDL_RenderCopy(renderer, beeTextures[currentFrame], nullptr, &beeRect);
                SDL_RenderPresent(renderer);
            }

        }

        // Clean up and quit
        for (int i = 0; i < NUM_FRAMES; ++i) {
            SDL_DestroyTexture(beeTextures[i]);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }
}
