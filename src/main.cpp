#include <SDL2/SDL.h>
#include <chrono>
#include <vector>
#include <random>
#include <SDL2/SDL_ttf.h>
#include <string>



// adding Square.h human edit
#include <Square.h>


// adding TextWrapper
//#include <TextWrapper.h>



// Bot forgot to include iostream again
#include <iostream>

int main(int argc, char* argv[])
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    // An error occurred while initializing SDL
    // Print the error message and exit
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create the window
  SDL_Window* window = SDL_CreateWindow("My SDL Window",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640, 640,
                                        SDL_WINDOW_SHOWN);
  if (!window)
  {
    // An error occurred while creating the window
    // Print the error message and exit
    std::cout << "Error creating SDL window: " << SDL_GetError() << std::endl;
    return 1;
  }



  // Create the renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    // An error occurred while creating the renderer
    // Print the error message and exit
    std::cout << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
    return 1;
  }


   // Create the squares
  Square spaceship(renderer, 320, 320, 30, 30);

  float time = 0;

  std::vector<Square> squares; // A vector to store the squares

  std::vector<Square> enemies; // A vector to store the enemies

  std::mt19937 rng(std::random_device{}()); // Initialize the random number generator
  std::uniform_int_distribution<int> dist(0, 16); // Initialize the random number distribution (random x coordinate)

  int HowManyEnemiesThisRound = 0;

  // Main loop
  bool running = true;
  std::chrono::high_resolution_clock clock;
  auto previousTime = clock.now();
  int PlayerPosition = 320;

  //TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24); // Load the font
  //TextWrapper text(renderer, font, 10, 10, 640, 480); // Initialize the text wrapper


  while (running)
  {

    // Update the game state
    auto currentTime = clock.now();
    float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
    previousTime = clock.now();
    // Update the game state using deltaTime


    time += deltaTime;


    // Process events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        // The user pressed the close button
        running = false;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        // A key was pressed
        if (event.key.keysym.sym == SDLK_LEFT)
        {
          PlayerPosition -= 10;
          if (PlayerPosition < 0)
          {
            PlayerPosition = 0;
          }
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
          PlayerPosition += 10;
          if (PlayerPosition > 610)
          {
            PlayerPosition = 610;
          }
        }
        else if (event.key.keysym.sym == SDLK_SPACE)
        {
          // The space bar was pressed
          // Create a new square and add it to the vector
          Square square(renderer, PlayerPosition, 640 * 7 / 8, 4, 15);
          squares.push_back(square);
        }
      }
    }


    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 120, 255); // Set the render color to black
    SDL_RenderClear(renderer); // Clear the screen with the render color

    // Update the squares
    for (auto it = squares.begin(); it != squares.end(); )
    {
      Square& square = *it;
      square.setPosition(square.getX(), square.getY() - (0.0000000002 * deltaTime));
      if (square.getY() < 1)
      {
        // The square has reached the top of the screen, delete it
        it = squares.erase(it);
      }
      else
      {
        ++it;
      }
    }

    for (auto it = enemies.begin(); it != enemies.end(); )
    {
      Square& enemy = *it;
      enemy.setPosition(enemy.getX(), enemy.getY() + (1020 * deltaTime));

      bool TakeDown = false;

      for (auto ist = squares.begin(); ist != squares.end(); ) {
        Square& square = *ist;
        if (enemy.isIntersecting(square)) {
          TakeDown = true;
        }
        ++ist;
      }


      if (enemy.getY() > 600 || TakeDown)
      {
        if (enemy.getY() > 600) {
          return 1;
        }
        // The enemy has reached the bottom of the screen, delete it
        it = enemies.erase(it);
      }
      else
      {
        ++it;
      }
    }






    if (int(time) % 3 == 0) {
      if (HowManyEnemiesThisRound < 4) {
        // Generate a new enemy
        int x = dist(rng);
        Square enemy(renderer, 40*x, 0, 20, 30);
        enemies.push_back(enemy);
        HowManyEnemiesThisRound += 1;
      }
    } else {
      HowManyEnemiesThisRound = 0;
    }

    // Draw the enemies
    for (Square& enemy : enemies)
    {
      enemy.draw();
    }

    // Draw the squares
    for (Square& square : squares)
    {
      square.draw();
    }

    spaceship.setPosition(PlayerPosition, 640 * 7 / 8);
    spaceship.draw();

    //text.setText("Points");


    //text.draw();

    // Update the screen
    SDL_RenderPresent(renderer); // Present the rendered frame to the screen
  }

  // Clean up
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
