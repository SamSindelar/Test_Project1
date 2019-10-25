/* #define VISION_PORT 11
#define EXAMPLE_SIG 11

void opcontrol() {
  pros::Vision vision_sensor (VISION_PORT);
  while (true) {
    vision_object_s_t rtn = vision_sensor.get_by_size(0);
    // Gets the largest object
    std::cout << "sig: " << rtn.signature;
    pros::delay(2);
  }
}

*/
