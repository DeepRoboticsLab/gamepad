/**
 * @file example_skydroid.cpp
 * @brief 
 * @author mazunwang
 * @version 1.0
 * @date 2024-03-27
 * 
 * @copyright Copyright (c) 2024  DeepRobotics
 * 
 */

#include <iostream>

#include "gamepad.h"
#include "skydroid_gamepad.h"
#include "gamepad_keys.h"

#include "fmt/format.h"
#include "fmt/core.h"
#include "fmt/chrono.h"

void InitialSkydroidKeys(SkydroidGamepad& is){
  is.button_status_.clear();
  std::string pressed  = fmt::format("\x1b[32m{:^20}\x1b[0m", "pressed");
  std::string released = fmt::format("\x1b[37m{:^20}\x1b[0m", "released");
  is.button_status_.push_back(released);
  is.button_status_.push_back(pressed);
}

/**
 * @brief Overloaded output stream operator for SkydroidGamepad.
 *
 * Allows printing RetroidGamepad information to an output stream.
 *
 * @param o The output stream.
 * @param is The SkydroidGamepad object.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& o, SkydroidGamepad& is){
  SkydroidKeys keys = is.GetKeys();
  o << "\033c";
  std::string  s = fmt::format(
	"┌{0:─^{1}}┐\n"
	"│{2: ^{1}}│\n"
	"└{0:─^{1}}┘\n", "", 86 ,"Joystick Device: Skydorid(X30)");
  o<<s ;
  s = fmt::format(
    "┌{2:─^{1}}┐┌{3:─^{1}}┐┌{4:─^{1}}┐┌{5:─^{1}}┐\n"
    "│{6: ^{1}}││{7: ^{1}}││{8: ^{1}}││{9: ^{1}}│\n"
    "└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘\n", 
    "", 20, "A", "B", "C", "D", 
    is.button_status_[keys.A], is.button_status_[keys.B], is.button_status_[keys.C], is.button_status_[keys.D]);
  o<<s ;
  s = fmt::format(
    "┌{2:─^{1}}┐┌{3:─^{1}}┐┌{4:─^{1}}┐┌{5:─^{1}}┐\n"
    "│{6: ^{1}}││{7: ^{1}}││{8: ^{1}}││{9: ^{1}}│\n"
    "└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘\n", 
    "", 20, "E", "F", "Reserved", "Right", 
    is.button_status_[keys.E], is.button_status_[keys.F], is.button_status_[keys.reserved], is.button_status_[keys.right]);
  o<<s ;

  s = fmt::format(
    "┌{2:─^{1}}┐┌{3:─^{1}}┐┌{4:─^{1}}┐┌{5:─^{1}}┐\n"
    "│{6: ^{1}}││{7: ^{1}}││{8: ^{1}}││{9: ^{1}}│\n"
    "└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘\n",
    "", 20, "SW1", "SW2", "SW3", "SW4", 
    keys.sw1, keys.sw2, keys.sw3, keys.sw4);
  o<<s ;

  s = fmt::format(
    "┌{2:─^{1}}┐┌{3:─^{1}}┐┌{4:─^{1}}┐┌{5:─^{1}}┐\n"
    "│{6: ^{1}}││{7: ^{1}}││{8: ^{1}}││{9: ^{1}}│\n"
    "└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘└{0:─^{1}}┘\n", 
    "", 20, "left_axis_x", "left_axis_y", "right_axis_x", "right_axis_y", 
    keys.left_axis_x, keys.left_axis_y, keys.right_axis_x, keys.right_axis_y);
  o<<s ;
  return o;
}


int main(int argc, char* argv[]) {
  SkydroidGamepad rc(12121);
  InitialSkydroidKeys(rc);

  rc.StartDataThread();

  rc.updateCallback_ = [&](int32_t count){
    std::cout << rc << std::endl;
  };
    
  for(int i = 0; i < 100000; i ++){
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}