#include "systems/intake.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

//Constructor for intake
Intake::Intake() {
    //num rings on screen
    rings_red = 0;

    rings_blue = 0;

    //State is the if the intake is running in an ejectable state or not
    state = false;

    //Wheter we are waiting to eject a ring
    pending_eject = false;

}

//define the running method for the intake
void Intake::run() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        //Full bore forwards
        intake_motor.move_voltage(12000);
        state = true;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        //Full bore backwards
        intake_motor.move_voltage(-12000);
        state = false;
    } else {
        intake_motor.brake();
        state = false;
    }

    //Now, vision sensor logic

    int current_red = 0;
    int current_blue = 0;

    /// Count the amount of rings
    for (int obj = 0; obj < vision.get_object_count(); ++obj) {
        pros::vision_object_s_t rtn = vision.get_by_size(obj);

        //TODO: handle possible error here
        
        if (rtn.signature == RED_SIG_NUM) current_red++;
        if (rtn.signature == BLUE_SIG_NUM) current_blue++;
    }

    //Check case to eject red ring if its up in the top of the intake
    if (current_red < rings_red && match_color != 1) {
        pending_eject = true;
    } 


    //same in the case of blue
    if (current_blue < rings_blue && match_color != 2) {
        pending_eject = true;
    } 

    //set blue and red counts
    rings_red = current_red;
    rings_blue = current_blue;

    //eject
    if (pending_eject) {
        if (state) { //means the intake is running
            pending_eject = false;
            intake_motor.brake();
            //maybe make async in future?
            pros::delay(20);
            intake_motor.move_voltage(12000);
        }
    }
}
