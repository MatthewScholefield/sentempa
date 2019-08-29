#include <SDL2/SDL.h>

namespace Utility {
void sleep(const long ms) {
    SDL_Delay(ms);
}
}
