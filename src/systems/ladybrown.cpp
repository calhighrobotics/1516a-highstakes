#include "systems/ladybrown.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

//Constructor for intake
LadyBrown::LadyBrown() {
    //default idle state
    state = 0;

    //idle angle 0 degrees
    idle_angle = lb_motor.get_position();

    //score angle 180 degrees
    score_angle = 750;

    

    //collecting angle 45 degrees
    collect_angle = 265;
    collect2_angle = 330;


}

//define the running method for the intake
void LadyBrown::run() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        //Collecting state
        //Go to collect angle at full speed of 127
        lb_motor.move_absolute(collect_angle-idle_angle, 127);
        //set to collect state
        state = 1;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        //Scoring state
        //Go to score angle at full speed of 127
        lb_motor.move_absolute(collect2_angle-idle_angle, 127);
        //set to score state
        state = 2;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        //Idle state
        //Go to idle angle at full speed of 127
        lb_motor.move_absolute(score_angle-idle_angle, 127);
        //set to idle state
        state = 3;
    }
    /*
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        //Idle state
        //Go to idle angle at full speed of 127
        lb_motor.move_absolute(idle_angle-idle_angle, 127);
        //set to idle state
        state = 0;
    }
    */

}
