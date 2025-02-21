#include "main.h"
#include "globals.h"
#include "screen/selector.h"
#include "systems/intake.h"
#include "systems/ladybrown.h"
#include "lemlib/api.hpp"

using namespace Robot::Globals;
using namespace Robot;

//struct for systems

struct Systems {
	Intake intake;
	LadyBrown lb;
	selector_screen sel;
} systems;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void intakeRun(void* args) {
	while (true) {
		systems.intake.run();
		pros::delay(10);
	}

	
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//Basic intitialization of the screen
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Team 1516A");
	//Add button to screen
	pros::lcd::register_btn1_cb(on_center_button);

	//Set blue signature as 1 on bot
	//vision.set_signature(1, &BLUE_SIG);

	//Set red signature as 2 on bot
	color.set_led_pwm(100);
	//vision.set_signature(2, &RED_SIG);

	chassis.calibrate();
	chassis.setPose({0, 0, 0});

	systems.sel.selector();




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
//load the test.txt path
ASSET(test_txt);

void autonomous() {
    // set chassis pose to 0
    chassis.setPose(0, 0, 0, 180);

	//Tell the chassis to follow the path provided
    chassis.moveToPoint(0, -9, 5000, {.forwards=false}, false);
	clamp.set_value(1);
	//chassis.moveToPoint(0,-3,5000,{.forwards=false},false);
	// chassis.moveToPose(0,-10, 5000, , false)
	//left.move_relative(-5,200);
	//right.move_relative(-5,200);
	
	
	

	
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

	pros::Task intakeTask(intakeRun);

	while (true) {


		//Drivetrain Block
		chassis.arcade(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_X));


		//Pneumatics Block
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			clamp.set_value(1);
		} else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			clamp.set_value(0);
		} 


		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			flick.set_value(1);
		} else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			flick.set_value(0);
		} 

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			intake_lift.set_value(1);
		} else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			intake_lift.set_value(0);
		} 

		systems.lb.run();

		pros::delay(10);                               		// Wait 20 ms each iteration to avoid excessive compute
	}
}