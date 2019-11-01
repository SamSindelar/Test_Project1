#include "main.h"

#define BACK_LEFT_WHEELS_PORT 4
#define BACK_RIGHT_WHEELS_PORT 12

#define LEFT_WHEELS_PORT 9
#define RIGHT_WHEELS_PORT 3

#define VISION_PORT 7

#define ARM_PORT 1

//#define CLAW_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'

#define ARM_LIMIT_SWITCH_PORT 'h'

#define MOTOR_MAX_SPEED 100 // The motor has the 36 Gearset

//using namespace std;


//Functions 01 & 02 for tank drive control

//01 The controller joystick can be read with the following function:
//std::int32_t pros::Controller::get_analog ( pros::controller_analog_e_t channel );

//02 The motors can be set with the following function:
//std::int32_t motor_move ( const std::int8_t voltage );


//Functions 03 & 04 for Arm Control

//03 Function for reading button press from controller
//std::int32_t pros::Controller::get_digital ( pros::controller_digital_e_t button )

//04 Function for velocity-controlled movement
//std::int32_t pros::Motor::move_velocity ( const std::int32_t velocity )

//Function 05 for Reading Switches

//05 This Function will be using the digital reading functionality of the ADI for this
// std::int32_t pros::ADIDigitalIn::get_value ( ) const





/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Sup bitches!");

	//vision sensor

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
//zach wuz here
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	//The autonomous program runs without the use of a controller.
	//We will make a simple autonomous program that drives straight.
	pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor

  right_wheels.move_relative(1000, MOTOR_MAX_SPEED);
  left_wheels.move_relative(1000, MOTOR_MAX_SPEED);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
//Clawbot code for Drive Control
	pros::Motor left_wheels (LEFT_WHEELS_PORT);
	pros::Motor back_left_wheels (BACK_LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT);
	pros::Motor back_right_wheels (BACK_RIGHT_WHEELS_PORT);

	//Vision Sensor stuff
	pros::Vision vision_sensor (VISION_PORT);


//Arm Control
 pros::Motor arm (ARM_PORT, MOTOR_GEARSET_36); // The arm motor has the 100rpm (red) gearset

//Claw Control
//	pros::Motor claw (CLAW_PORT, MOTOR_GEARSET_36);

//Bumper Switches
	pros::ADIDigitalIn left_bumper (LEFT_BUMPER_PORT);
	pros::ADIDigitalIn right_bumper (RIGHT_BUMPER_PORT);

//Limit Switch
	pros::ADIDigitalIn arm_limit (ARM_LIMIT_SWITCH_PORT);

  pros::Controller master (CONTROLLER_MASTER);



//Drive Control
	while (true)
	{
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_LEFT_X);
    int left = -power - turn;
    int right = power - turn;

//Bumper Switch Controls
if (left_bumper.get_value() || right_bumper.get_value())
{
	// One of the bump switches is currently pressed
	if (left < 0)
	{
		left = 0;
	}
	if (right < 0)
	{
		right = 0;
	}
}

	//if(power > 5)
/*
    left_wheels.move(left);
		back_left_wheels.move(left);
    right_wheels.move(right);
		back_right_wheels.move(right);

*/


		while (master.get_digital(DIGITAL_A))
				{
		      arm.move_relative(1800,100); // This is 100 because it's a 100rpm motor
		    }
		while (master.get_digital(DIGITAL_B)){
//wrgwrgwtgwrgwtgrs
				 // Gets the largest object
				 //std::cout << "sig: " << rtn.signature;
				 //pros::delay(2);
				 while (true)
				 {
 			    pros::vision_object_s_t obj = vision_sensor.get_by_sig(0,1);
 			    // Gets the largest object
 			    std::cout << "sig: " << obj.signature;
 			    pros::delay(2);
					double cord = obj.x_middle_coord;
					if (cord > 316/2)
					{
						left_wheels.move_relative(1800,100);
						back_left_wheels.move_relative(1800, 100);
				    right_wheels.move_relative(-1800,100);
						back_right_wheels.move_relative(-1800, 100);
					}
 			  }
}
//Arm control
/*		if (master.get_digital(DIGITAL_R1))
		{
      arm.move_velocity(100); // This is 100 because it's a 100rpm motor
    }
    else if (master.get_digital(DIGITAL_R2) && !arm_limit.get_value())
		{
      arm.move_velocity(-100);
    }
    else
		{
      arm.move_velocity(0);
    }

//Claw Control
		if (master.get_digital(DIGITAL_L1))
		{
      claw.move_velocity(100);
    }
    else if (master.get_digital(DIGITAL_L2))
		{
      claw.move_velocity(-100);
    }
    else
		{
      claw.move_velocity(0);
    }

    pros::delay(2);


*/
    //pros::delay(2);

//Clawbot code for Arcade Control
/*
pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true);
  pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;
    left_wheels.move(left);
    right_wheels.move(right);

    pros::delay(2);
*/

//Default PROS code
	/*pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);


	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);

		*/
	}
}
