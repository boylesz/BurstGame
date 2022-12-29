#include <iostream>
#include "../headers/Game.h"
#include <time.h>

int main() {

    srand(static_cast<unsigned>(time(0)));

    // Init game engine
    Game game;

    // Game Loop
    while (game.isRunning()) {
        // Update
        game.update();

        // Render
        game.render();
        
    }

    return 0;
}