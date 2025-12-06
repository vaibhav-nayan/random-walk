#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define SCALE 2
#define AGENT_SIZE 2

typedef struct {
  int vx, vy;
} Velocity;

typedef struct {
  float r, g, b;
} RGB;

typedef struct {
  int x, y;
  RGB rgb_color;
} Agent;

Velocity get_random_v() {
  int choice = (rand() / (RAND_MAX / 4));
  int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  return (Velocity){dir[choice][0], dir[choice][1]};
}

void move_agent(SDL_Surface *pSurface, Agent *pagent) {
  Velocity v = get_random_v();
  RGB rgb = pagent->rgb_color;
  for (int i = 0; i < 10; i++) {
    pagent->x += v.vx;
    pagent->y += v.vy;
    SDL_Rect rect = (SDL_Rect){pagent->x, pagent->y, AGENT_SIZE, AGENT_SIZE};
    Uint32 color = SDL_MapRGB(pSurface->format, rgb.r, rgb.g, rgb.b);
    SDL_FillRect(pSurface, &rect, color);
  }
}

float hue2rgb(float p, float q, float t) {
  if (t < 0)
    t += 1;
  if (t > 1)
    t -= 1;
  if (t < 1. / 6)
    return p + (q - p) * 6 * t;
  if (t < 1. / 2)
    return q;
  if (t < 2. / 3)
    return p + (q - p) * (2. / 3 - t) * 6;

  return p;
}

RGB hsl2rgb(float h, float s, float l) {
  RGB result;

  if (s == 0) {
    result.r = result.g = result.b = l * 255;
  } else {
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    result.r = hue2rgb(p, q, h + 1. / 3) * 255;
    result.g = hue2rgb(p, q, h) * 255;
    result.b = hue2rgb(p, q, h - 1. / 3) * 255;
  }

  return result;
}

void create_agents(Agent *pagents, int num_agent) {

  for (int i = 0; i < num_agent; i++) {
    float h = (float)rand() / (float)RAND_MAX;
    RGB rgb = hsl2rgb(h, 1, 0.5);
    pagents[i] = (Agent){WIDTH / 2, HEIGHT / 2, rgb};
  }
}

int main(int argc, const char *argv[]) {

  int num_agent;
  if (argc == 1) {
    num_agent = 5;
  } else if (argc == 2) {
    num_agent = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-agents>\n", argv[0]);
    return -1;
  }
  srand(time(NULL));

  SDL_Window *pWindow =
      SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *pSurface = SDL_GetWindowSurface(pWindow);

  Agent *pagents = calloc(num_agent, sizeof(Agent));
  create_agents(pagents, num_agent);

  int app_running = 1;
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }

      for (int i = 0; i < num_agent; i++) {
        move_agent(pSurface, &pagents[i]);
      }
      SDL_UpdateWindowSurface(pWindow);
      SDL_Delay(20);
    }
  }
  free(pagents);
}
