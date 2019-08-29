#include <SDL2/SDL.h>

namespace Utility {
void sleep(const unsigned int ms) {
    SDL_Delay(ms);
}
}
