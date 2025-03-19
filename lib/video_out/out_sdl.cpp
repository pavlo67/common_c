#include <SDL.h>
#include <unistd.h>
#include <opencv2/core.hpp>

#include "out.h"

using namespace cv;
using namespace std;

// TODO??? use class inheritance to store related objects in Writer object

SDL_Window   *window;
SDL_Renderer *renderer;
SDL_Surface  *image;

VideoOut::VideoOut(const char* path, int width, int height, float fps, bool grayscale) {
    width_  = width;
    height_ = height;
    path_   = path ? path : "view";
}

void VideoOut::write(Mat frame, int frame_n) {
    // TODO!!! be careful: initiation must be executed in the thread where Writer::write() is called

    if (!window) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("SDL could not initialize");
        }

        // #if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)    // Disable compositor bypass
        if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
            throw std::runtime_error("SDL can not disable compositor bypass!\n");
        }

        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        int v;
        SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &v);
        printf("SDL_GL_DOUBLEBUFFER: %d\n", v);

        if (!(window = SDL_CreateWindow(path_,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width_, height_,SDL_WINDOW_SHOWN))) {
            printf("SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Window could not be created!");
        }

        if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))  {
            printf("SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Renderer could not be created!");
        }
    }

    // printf("writing...\n");

    SDL_RenderClear(renderer);

    int depth = 8 * frame.channels();
    int stride = width_ * frame.channels();

    // printf("depth = %d, stride = %d\n", depth, stride);

    image = SDL_CreateRGBSurfaceFrom((void*)frame.data,
                width_, height_, depth, stride,
                0xff0000, 0x00ff00, 0x0000ff, 0 );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);

    // SDL_Event e;
    SDL_PumpEvents();
    if (SDL_HasEvents(SDL_QUIT, SDL_APP_TERMINATING)) {
        throw std::runtime_error("SDL window got terminating event");
    } else if (SDL_HasEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN)) {
        throw std::runtime_error("e.type == SDL_MOUSEBUTTONDOWN");
    }
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

    // usleep(10000);
    // SDL_Event e;
    // SDL_WaitEventTimeout(&e, 100);
}

void VideoOut::release() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

    // SDL_Rect squareRect;
    // squareRect.w = std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
    // squareRect.h = std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
    // squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
    // squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;

    // if (SDL_HasEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN + 1)) {
    //     break;
    // }

    // if (SDL_WaitEventTimeout(&e, 30) && e.type == SDL_QUIT) {
    //     printf("e.type: %d\n", e.type == SDL_QUIT );
    // }




