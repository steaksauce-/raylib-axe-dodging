#include "raylib.h"

// Project Template Directory for VSCide can be found at https://gitlab.com/GameDevTV/CPPCourse/vscode-template 
// Tutorial Code https://gitlab.com/GameDevTV/CPPCourse/axe-game
// Tutorial from gamedev.tv "C++ Fundamentals: Game Programming For Beginners"
// Template Makefile assumes raylib is installed in C:/raylib on Windows
// Get Raylib: https://www.raylib.com/

// Nice to have would be a scoring function: ie; every time the circle crosses the center of the screen
// where the "axe" is, you get a point and the score is displayed on the game over screen.

int main ()
{
    // Window Dimensions
    int width{800};
    int height{600};

    // circle coordinates
    int circle_x{200};
    int circle_y{300};
    float circle_radius{25};
    // circle edges -- draws a "square" hitbox around the circle
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    // axe coordinates
    int axe_x{400};
    int axe_y{0};
    int axe_size{50};
    // axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_size};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_size};

    int direction{10};

    InitWindow(width, height, "Simple Axe Dodging Game");

    bool collision_with_axe =
        (b_axe_y >= u_circle_y) && 
        (u_axe_y <= b_circle_y) && 
        (l_axe_x <= r_circle_x) && 
        (r_axe_x >= l_circle_x);


    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            ClearBackground(BLACK);
            DrawText("Game Over!", 350, 300, 20, RED);
        }
        else
        {
            // Game Logic Begins

            // Update the edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_size;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_size;

            // Update collision_with_axe
            collision_with_axe =
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (l_axe_x <= r_circle_x) && 
                        (r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_size, axe_size, BLACK);

            // Move the axe
            axe_y += direction;

            // Worth noting in the below if statement, that I couldn't get b_axe_y to provide the desired result
            // even though it's the same as axe_y + axe_size
            if(axe_y + axe_size > height || axe_y < 0) 
            {
                direction = -direction;
            }

            // Move the circle
            if (IsKeyDown(KEY_D) && r_circle_x < width)
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && l_circle_x > 0)
            {
                circle_x -= 10;
            }

            // Game Logic Ends
        }
        EndDrawing();   
    }
}