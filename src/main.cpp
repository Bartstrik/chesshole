#include <assert.h>
#include "render.hpp"

int main(void)
{
    Window window(800, 800);
    window.init();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        // Draw
        window.drawWindow();
    }


    return 0;
}