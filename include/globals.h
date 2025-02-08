#include "api.h"
#include "lemlib/api.hpp"

namespace Robot {
    namespace Globals {

        extern pros::Controller controller;

        extern pros::MotorGroup left;

        extern pros::MotorGroup right;

        extern pros::adi::Pneumatics clamp;
         extern pros::adi::Pneumatics flick;
          extern pros::adi::Pneumatics intake_lift;

        extern pros::Distance ring_detect;

        extern pros::Optical color;
        extern pros::vision_signature BLUE_SIG;

        extern pros::vision_signature RED_SIG;

        extern pros::Rotation rotation_horiz;

        //Vertical sensor
        extern pros::Rotation rotation_vert;

        extern pros::Motor intake_motor;

        extern pros::MotorGroup lb_motor;

        extern lemlib::Drivetrain drivetrain;

        extern int BLUE_SIG_NUM;
        extern int RED_SIG_NUM;

        extern int match_color;

        extern lemlib::Chassis chassis;
    }
}