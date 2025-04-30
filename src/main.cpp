#include <iostream>
#include <thread>
#include <atomic>
#include <cstdarg>
#include <chrono>

#include "xinputsimulator.h"
#include "uiohook.h"

std::atomic<bool> should_click{false};

void start_click() {
  using namespace std::literals::chrono_literals;
  XInputSimulator &sim = XInputSimulator::getInstance();
  while (should_click) {
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
    std::this_thread::sleep_for(100ms);
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
    sim.mouseClick(XIS::LEFT_MOUSE_BUTTON);
  }
}

void hotkey_callback(uiohook_event *event) {
  if (event->type == EVENT_KEY_PRESSED) {
    // F6 is our toggle key
    if (event->data.keyboard.keycode == VC_F6) {
      should_click = !should_click;

      if (should_click) {
        std::cout << "Autoclicker started!" << std::endl;
        std::thread clicker_thread(start_click);
        clicker_thread.detach();
      } else {
        std::cout << "Autoclicker stopped!" << std::endl;
      }
    }
  }
}

int main() {
  std::cout << "[AUTOCLICKER]\n";
  std::cout << "Press F6 to start/stop\n";
  hook_set_dispatch_proc(hotkey_callback);
  
  if (hook_run() == UIOHOOK_SUCCESS) {
    std::cout << "Started!\n";
  } else {
    std::cerr << "Failed to start hotkey listener\n";
    return -1;
  }

  return 0;
}
