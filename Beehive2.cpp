#include<SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include "Beehive2.h"

using namespace std ;

/*Now we are creating a functions that draws our beehive in which we
are using a pointer to the SDL_Renderer object and renderer parameter
 */
// Function to check if a point is inside a triangle

bool pointInTriangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
    // Calculate the barycentric coordinates
    float denominator = float((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    float alpha = float((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denominator;
    float beta = float((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denominator;
    float gamma = 1.0f - alpha - beta;

    // Check if the point is inside the triangle
    return alpha >= 0 && beta >= 0 && gamma >= 0;
}


// Function to draw a filled triangle

void filledTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3) {
    // Calculate the bounding box of the triangle
    int minX = std::min({ x1, x2, x3 });
    int minY = std::min({ y1, y2, y3 });
    int maxX = std::max({ x1, x2, x3 });
    int maxY = std::max({ y1, y2, y3 });

    // Loop through the bounding box and draw scanlines to fill the triangle
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (pointInTriangle(x, y, x1, y1, x2, y2, x3, y3)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}


// Function to draw a filled hexagon

void filledHexagon(SDL_Renderer* renderer, int centerX, int centerY, int radius, const SDL_Color& color) {
    // Define the vertices of the hexagon
    float angle;
    int x1, y1, x2, y2;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 0; i < 6; i++) {
        angle = 2.0 * M_PI * i / 6;
        x1 = centerX + static_cast<int>(radius * cos(angle));
        y1 = centerY + static_cast<int>(radius * sin(angle));
        angle = 2.0 * M_PI * (i + 1) / 6;
        x2 = centerX + static_cast<int>(radius * cos(angle));
        y2 = centerY + static_cast<int>(radius * sin(angle));

        // Draw a triangle from the center to the two vertices
        filledTriangle(renderer, centerX, centerY, x1, y1, x2, y2);
    }
}

void drawBeehive(SDL_Renderer* renderer) {
    const int numRows = 10; // Number of rows of hexagons
    const int numCols = 10; // Number of columns of hexagons
    const int radius = 50; // Radius of each hexagonal cell
    const int hexWidth = static_cast<int>(radius * sqrt(3.0));
    const int hexHeight = 2 * radius;

    // RGB color for golden brown
    const SDL_Color goldenBrown = { 184, 134, 11, 255 };

    // Loop through rows and columns to draw hexagons in a grid
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int x, y;
            if (col % 2 == 0) {
                // Even columns
                x = col * hexWidth;
                y = row * hexHeight;
            } else {
                // Odd columns
                x = col * hexWidth;
                y = row * hexHeight + radius;
            }

            // Draw a filled hexagon to create the beehive shape
            filledHexagon(renderer, x + radius, y + radius, radius, goldenBrown);
        }
    }
}
