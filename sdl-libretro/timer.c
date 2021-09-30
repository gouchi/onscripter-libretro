#include <SDL_libretro.h>
#include <sdl/src/timer/SDL_timer_c.h>

static uint8_t timer_stack[4*1024];

void SDL_StartTicks(void)
{
}

Uint32 SDL_GetTicks(void)
{
  return SDL_libretro_now / 1000;
}

void SDL_Delay(Uint32 ms)
{
  Uint32 x = SDL_GetTicks();
  do {
    SDL_libretro_co_yield();
  } while (SDL_GetTicks() - x < ms);
}

void RunTimer(void *unsued)
{
  while (true) {
    SDL_ThreadedTimerCheck();
    SDL_libretro_co_yield();
  }
}

int SDL_SYS_TimerInit(void)
{
  SDL_libretro_co_spawn(RunTimer, NULL, &timer_stack, sizeof(timer_stack));
  return SDL_SetTimerThreaded(1);
}

void SDL_SYS_TimerQuit(void)
{
}

int SDL_SYS_StartTimer(void)
{
  SDL_SetError("Internal logic error: threaded timer in use");
  return -1;
}

void SDL_SYS_StopTimer(void)
{
}
