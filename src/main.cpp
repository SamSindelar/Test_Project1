#include "main.h"

#define BACK_LEFT_WHEEL_PORT 3
#define BACK_RIGHT_WHEEL_PORT 4
#define FRONT_LEFT_WHEELS_PORT 1
#define FRONT_RIGHT_WHEELS_PORT 2

#define VISION_PORT 7

#define GYRO_PORT 12

#define ARM_PORT 13

//#define CLAW_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'

#define ARM_LIMIT_SWITCH_PORT 'h'

#define MOTOR_MAX_SPEED 100 // The motor has the 36 Gearset


pros::Motor backLeft(BACK_LEFT_WHEELS_PORT);
pros::Motor backRight(BACK_RIGHT_WHEELS_PORT);



pros::Motor left_wheels(LEFT_WHEELS_PORT,BACK_LEFT_WHEELS_PORT);
pros::Motor right_wheels(RIGHT_WHEELS_PORT,BACK_RIGHT_WHEELS_PORT);
pros::Motor back_wheels(BACK_LEFT_WHEELS_PORT,BACK_RIGHT_WHEELS_PORT);
pros::Motor front_wheels(LEFT_WHEELS_PORT,RIGHT_WHEELS_PORT);

void moveForward(int distance, int speed)
{
	left_wheels.move_relative(distance, speed);
	right_wheels.move_relative(distance,speed);
}

void moveBackward(int distance, int speed)
{
	left_wheels.move_relative(-distance,-speed);
	right_wheels.move_relative(-distance,-speed);
}

void shuffleLeft(int distance, int speed){
	front_wheels.move_relative(-distance,-speed);
	back_wheels.move_relative(distance,speed);
}

void shuffleRight(int distance, int speed) {
	front_wheels.move_relative(distance,speed);
	back_wheels.move_relative(-distance,-speed);
}

void turnLeft(int distance, int speed){
	left_wheels.move_relative(-distance,-speed);
	right_wheels.move_relative(distance,speed);
}

void turnRight(int distance, int speed) {
	left_wheels.move_relative(distance,speed);
	right_wheels.move_relative(-distance,-speed);
}

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



// THIS IS A TEST FOR THE FIRST COMMIT TO BRANCH Sam_S

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
	moveForward(2*1800,MOTOR_MAX_SPEED);
	turnLeft(1800/4,MOTOR_MAX_SPEED);

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
	pros::Motor left_wheels (FRONT_LEFT_WHEELS_PORT, BACK_LEFT_WHEEL_PORT);
	pros::Motor right_wheels (FRONT_RIGHT_WHEELS_PORT, BACK_RIGHT_WHEEL_PORT);

	pros::Motor back_wheels (BACK_LEFT_WHEEL_PORT, BACK_RIGHT_WHEEL_PORT);
	pros::Motor front_wheels (FRONT_LEFT_WHEELS_PORT, FRONT_RIGHT_WHEELS_PORT);

	pros::Motor back_left_wheel (BACK_LEFT_WHEEL_PORT);
	pros::Motor back_right_wheel (BACK_RIGHT_WHEEL_PORT);
	pros::Motor front_left_wheels (FRONT_LEFT_WHEELS_PORT);
	pros::Motor front_right_wheels (FRONT_RIGHT_WHEELS_PORT);

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
    int back_left = -power + turn;
    int back_right = power - turn;
		int front_left = -power + turn;
		int front_right = power - turn;

		front_left_wheels.move(front_left);
		back_left_wheel.move(back_left);
		front_right_wheels.move(front_right);
		back_right_wheel.move(back_right);
 }
}
