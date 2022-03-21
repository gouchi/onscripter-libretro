#include <SDL_libretro.h>
#include <sdl/src/events/SDL_events_c.h>
#include <sdl/src/video/dummy/SDL_nullevents_c.h>


static void PumpKeyboardEvents(void)
{
  static int16_t keys[RETROK_LAST] = {0};
  static SDL_keysym sym;
  for (int i = 0; i < RETROK_LAST; ++i) {
    int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, i);
    if (keys[i] != state) {
      keys[i] = state;
      sym.scancode = i;
      sym.sym = i;
      SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
    }
  }
}

static void PumpMouseEvents(void)
{
  int16_t x = SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
  int16_t y = SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
  if (x != 0 || y != 0)
    SDL_PrivateMouseMotion(0, 1, x, y);

  static uint16_t btn_left = 0;
  static uint16_t btn_middle = 0;
  static uint16_t btn_right = 0;
  uint16_t state;

  state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT);
  if (state != btn_left) {
    btn_left = state;
    SDL_PrivateMouseButton(state ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_LEFT, 0, 0);
  }

  state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_MIDDLE);
  if (state != btn_middle) {
    btn_middle = state;
    SDL_PrivateMouseButton(state ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_MIDDLE, 0, 0);
  }

  state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT);
  if (state != btn_right) {
    btn_right = state;
    SDL_PrivateMouseButton(state ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_RIGHT, 0, 0);
  }
}

void DUMMY_PumpEvents(_THIS)
{
  PumpKeyboardEvents();
  PumpMouseEvents();
  SDL_libretro_co_yield();
}

void DUMMY_InitOSKeymap(_THIS)
{
}
