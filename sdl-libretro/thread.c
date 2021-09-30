#include <SDL_libretro.h>
#include <sdl/src/thread/generic/SDL_syscond.c>
#include <sdl/src/thread/generic/SDL_sysmutex.c>


extern void SDL_RunThread(void *data);

struct SDL_semaphore {
  Uint32 value;
};


SDL_sem *SDL_CreateSemaphore(Uint32 initial_value)
{
  SDL_sem *sem = (SDL_sem *)SDL_malloc(sizeof(*sem));
  if (sem) {
    sem->value = initial_value;
  } else {
    SDL_OutOfMemory();
  }
  return sem;
}

void SDL_DestroySemaphore(SDL_sem *sem)
{
  if (sem) {
    SDL_free(sem);
  }
}

int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 timeout)
{
  Uint32 x = SDL_GetTicks();
  do {
    if (sem->value) {
      sem->value -= 1;
      return 0;
    }
    SDL_libretro_co_yield();
  } while (SDL_GetTicks() - x < timeout);

  return SDL_MUTEX_TIMEDOUT;
}

int SDL_SemTryWait(SDL_sem *sem)
{
  return SDL_SemWaitTimeout(sem, 0);
}

int SDL_SemWait(SDL_sem *sem)
{
  return SDL_SemWaitTimeout(sem, SDL_MUTEX_MAXWAIT);
}

Uint32 SDL_SemValue(SDL_sem *sem)
{
  return sem->value;
}

int SDL_SemPost(SDL_sem *sem)
{
  sem->value += 1;
  return 0;
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
  size_t stack_size = 64*1024;
  void *stack = SDL_malloc(stack_size);
  if (stack == NULL) {
    SDL_OutOfMemory();
    return -1;
  }
  SDL_libretro_co_spawn(SDL_RunThread, args, stack, stack_size);
  return 0;
}

void SDL_SYS_SetupThread(void)
{
}

Uint32 SDL_ThreadID(void)
{
  return 0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
  return;
}
