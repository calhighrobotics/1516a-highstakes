#include "robot/auton.h"
#include "main.h" // IWYU pragma: export
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string Autonomous::autonName;

// Red Left
void Autonomous::Auton1(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {
   // chassis.setPose(0, 0, 0);
   // // Move to first stake, then a bit farther at a slower speed for alignment
   // chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   // chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
   // chassis.waitUntilDone();
   // pros::delay(200);
   // // Grab the closest MOGO mech
   // clamp.extend();
   // // Load the ring onto the stake
   // intake_motor.move_voltage(12000);
   // pros::delay(5000);
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, -14, 15000);
}

// Red Right
void Autonomous::Auton2(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {
   chassis.setPose(0, 0, 0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
   chassis.waitUntilDone();
   pros::delay(200);
   // Grab the closest MOGO mech
   clamp.extend();
   // Load the ring onto the stake
   intake_motor.move_voltage(12000);
   pros::delay(300);
   intake_motor.move_voltage(0);
   chassis.setPose(0, 0, 0);
   // Point at the blue left side bottom ring for scoring
   chassis.turnToHeading(-75, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 70}, true);
   chassis.waitUntilDone();
   chassis.setPose(0, 0, 0);
   // Start the intake and hook for the rest of auton
   intake_motor.move_voltage(12000);
   // Move to and back from the blue low ring
   chassis.moveToPoint(0, 22, 1250, {.forwards = true, .maxSpeed = 70}, true);
   chassis.moveToPoint(0, -5, 1250, {.forwards = false, .maxSpeed = 90}, true);
   chassis.waitUntilDone();
   // Turn to ladder cone
   chassis.turnToHeading(180, 2000);
   chassis.moveToPoint(0, -21, 1250, {.forwards = true, .maxSpeed = 50}, true);
}

// Blue left
void Autonomous::Auton3(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {
      chassis.setPose(0, 0, 0);

   // Move to first stake
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   clamp.extend();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(25, -27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   intake_motor.move_voltage(12000);

   // Moves to 2 ring stack

   chassis.moveToPoint(25, -27, 1250, {.forwards = true});
   chassis.turnToPoint(33.5, 6, 1000);
   flick.extend();
   chassis.moveToPoint(35, 7, 1500);
   chassis.waitUntilDone();
   intake_motor.move_voltage(0);

   chassis.moveToPose(25, -4, 170, 2000, {.horizontalDrift = 2});
   chassis.moveToPoint(32, 10, 1000, {.forwards = false});
   chassis.waitUntilDone();
   clamp.retract();
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::Auton4(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {

   chassis.setPose(0, 0, 0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
   chassis.waitUntilDone();
   pros::delay(200);
   // Grab the closest MOGO mech
   clamp.extend();
   // Load the ring onto the stake
   intake_motor.move_voltage(12000);
   pros::delay(5000);
}

void Autonomous::Auton5(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {
   // Autonomous routine for the Skills challenge
}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(pros::Motor intake_motor, pros::adi::Pneumatics clamp) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_LEFT:
      Auton1(intake_motor, clamp);
      break;
   case RED_RIGHT:
      Auton2(intake_motor, clamp);
      break;
   case BLUE_LEFT:
      Auton3(intake_motor, clamp);
      break;
   case BLUE_RIGHT:
      Auton4(intake_motor, clamp);
      break;
   case SKILLS:
      Auton5(intake_motor, clamp);
      break;
   }
}

void Autonomous::AutonSwitcher(int autonNum) {
   switch (autonNum) {
   case 1:
      Autonomous::autonName = "Red Left";
      Autonomous::auton = RED_LEFT;
      break;
   case 2:
      Autonomous::autonName = "Red Right";
      Autonomous::auton = RED_RIGHT;
      break;
   case -1:
      Autonomous::autonName = "Blue Left";
      Autonomous::auton = BLUE_LEFT;
      break;
   case -2:
      Autonomous::autonName = "Blue Right";
      Autonomous::auton = BLUE_RIGHT;
      break;
   case 0:
      Autonomous::autonName = "Skills";
      Autonomous::auton = SKILLS;
   }
   std::cout << "Current auton: " + Autonomous::autonName << std::endl;
}