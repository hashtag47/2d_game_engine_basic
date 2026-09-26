#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>

Game::Game()
{
  isRunning = false;
  Logger::Log("Game constructor called!\n");
}

Game::~Game()
{
  Logger::Log("Game Destructor called!\n");
}

void Game::Initialize()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    Logger::Err("Error initializing SDL.\n");
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);

  windowWidth = displayMode.w;
  windowHeight = displayMode.h;

  window = SDL_CreateWindow(
      "2d game engine",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      windowWidth,
      windowHeight,
      SDL_WINDOW_BORDERLESS);
  if (!window)
  {
    Logger::Err("Error creating the SDL window.\n");
    return;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    Logger::Err("Error creating SDL renderer.\n");
    return;
  }
  // REAL Fullscreen
  // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::Run()
{
  SetUp();
  while (isRunning)
  {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::ProcessInput()
{
  // typedef structs
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_ESCAPE)
      {
        isRunning = false;
      }
      break;
    }
  };
}

// glm::vec2 playerPosition;
// glm::vec2 playerVelocity;

void Game::SetUp()
{
  // playerPosition = glm::vec2(10.0, 20.0);
  // playerVelocity = glm::vec2(100.0, 5.0);

  // Entity tank = registry.CreateEntity();
  // tank.AddComponent<TransformComponent>();
  // tank.AddComponent<BoxColliderComponent>();
  // tank.AddComponent<SpriteComponent>("./assets/images/tank.png");
}

void Game::Update()
{
  // Wasting the CPU, almost 100% cost
  // while (!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME))
  //   ;
  int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
  if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
  {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

  millisecsPreviousFrame = SDL_GetTicks();

  // playerPosition.x += playerVelocity.x * deltaTime;
  // playerPosition.y += playerVelocity.y * deltaTime;
  // TODO:
  // MovementSystem.Update();
  // CollisionSystem.Update();
  // DamageSystem.Update();
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  // // Loads a PNG texture
  // SDL_Surface *surface = IMG_Load("./assets/images/tank-tiger-right.png");
  // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  // SDL_FreeSurface(surface);

  // // desRect is where and how large this rect should be on our renderer
  // SDL_Rect desRect = {
  //     static_cast<int>(playerPosition.x),
  //     static_cast<int>(playerPosition.y),
  //     32,
  //     32};
  // SDL_RenderCopy(renderer, texture, NULL, &desRect);
  // SDL_DestroyTexture(texture);
  // TODO: Render game objects...

  SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
