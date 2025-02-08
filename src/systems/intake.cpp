#include "systems/intake.h"
#include "robot/auton.h"

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
    enabled = true;
    

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

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        enabled = !enabled;

        if (enabled == false) {
            controller.print(0, 0, "Color sort off");
        }
    }

    

if (enabled) {
        controller.clear_line(0);
        
        double col = color.get_hue();

        //std::cout << rtn.signature << std::endl;

        

        if (col > 200 && col < 260) {

            if (Robot::Autonomous::auton == Robot::Autonomous::RED_LEFT) pending_eject = true;
            if (Robot::Autonomous::auton == Robot::Autonomous::RED_RIGHT) pending_eject = true;
        } else if (col > 0 && col < 20) {
            if (Robot::Autonomous::auton == Robot::Autonomous::BLUE_LEFT) pending_eject = true;
            if (Robot::Autonomous::auton == Robot::Autonomous::BLUE_RIGHT) pending_eject = true;
        } else {
            if (Robot::Autonomous::auton == Robot::Autonomous::SKILLS) pending_eject = false;
        }

        


        
        

        //if (abs(rtn.width*rtn.height) < 2500) {
        //    pending_eject = false;
        //}

         if (pending_eject) {
            if (state) { //means the intake is running
                pending_eject = false;
                pros::delay(70);
                intake_motor.brake();
                //maybe make async in future?
                pros::delay(100);
                intake_motor.move_voltage(12000);
            }
        }
} 
    







    


    //eject
}
