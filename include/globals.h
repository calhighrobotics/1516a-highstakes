#include "api.h"
#include "lemlib/api.hpp"

namespace Robot {
    namespace Globals {

        extern pros::Controller controller;

        extern pros::MotorGroup left;

        extern pros::MotorGroup right;

        extern pros::ADIPneumatics clamp;

        extern pros::Distance ring_detect;

        extern pros::Vision vision ;
        extern pros::vision_signature BLUE_SIG;

        extern pros::vision_signature RED_SIG;

        extern pros::Motor intake_motor;

        extern pros::Motor lb_motor;

        extern lemlib::Drivetrain drivetrain;

        extern int BLUE_SIG_NUM;
        extern int RED_SIG_NUM;

        extern int match_color;

        extern lemlib::Chassis chassis;
    }
}