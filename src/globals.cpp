#include "api.h"
#include "lemlib/api.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"

namespace Robot {
    namespace Globals {
        //Initialize the controller variable with the primary controller
        pros::Controller controller(pros::E_CONTROLLER_MASTER);
        

        signed char LEFT_BACK = -3;
        signed char LEFT_MID = -4;
        signed char LEFT_FRONT = -                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      1;


        signed char RIGHT_BACK = 18;
        signed char RIGHT_MID = 19;
        signed char RIGHT_FRONT = 20;


        //Initialize the motor group for the left motors with ports 1, 2, and 3, denoting the blue gear cartrige
        pros::MotorGroup left({LEFT_BACK,LEFT_MID, LEFT_FRONT}, pros::v5::MotorGears::blue);

        //Initialize the motor group for the right motors with ports 4, 5, and 6, denoting the blue cartidge
        //The negative sign for the ports indicate the motors will run in reverse, as one side always must
        pros::MotorGroup right({RIGHT_BACK, RIGHT_MID, RIGHT_FRONT}, pros::v5::MotorGears::blue);

        //Initialize the solenoid
        //The specific port we are using is 'A'
        //The false indicated that the piston is starting in the closed state
        pros::adi::Pneumatics clamp('G', false);

        pros::adi::Pneumatics flick('F', false);

        pros::adi::Pneumatics intake_lift('H', false);

        

        //This allows us to change the port easily
        uint8_t vision_port = 20;

        //Distance port
        uint8_t distance_port = 10;

        //Intake port
        uint8_t intake_port = 10;

        //lb port
        signed char lb_port_left = 21;
        signed char lb_port_right = -14;
        

        pros::MotorGroup lb_motor({lb_port_left, lb_port_right});

        //Define intake motor
        pros::Motor intake_motor(intake_port);

        //Initialize ring distance sensor
        pros::Distance ring_detect(distance_port);

        //Intialize the vision sensor
        //pros::Vision vision ( vision_port );

        pros::Optical color(vision_port);
        int BLUE_SIG_NUM = 1;
        int RED_SIG_NUM = 2;

        //Define Blue vision signature
        pros::vision_signature BLUE_SIG = pros::Vision::signature_from_utility (1, -4525, -2797, -3662, 3235, 8341, 5788, 3.000, 0);
        //Define Red vision signature
        pros::vision_signature RED_SIG  = pros::Vision::signature_from_utility (2, 9249, 10975, 10112, -2205, -1165, -1686, 3.000, 0);

        //Red for now ig
        int match_color = 1;

        //Initialize LemLib Drivetrain

        lemlib::Drivetrain drivetrain(
            &left, // the left motor group
            &right, // the right motor group
            25, //25 inch track width
            lemlib::Omniwheel::NEW_325, //Wheel size
            450, // our drivetrain RPM
            2 // optimal drift value for all-omni drivetrain
        );


        //Rotation sensor ports
        uint8_t rot_sensor_horiz = 2;
        uint8_t rot_sensor_vert = 12;

        //Horizontal sensor
        pros::Rotation rotation_horiz(rot_sensor_horiz);

        //Vertical sensor
        pros::Rotation rotation_vert(rot_sensor_vert);

        //Inertial port
        uint8_t inertial_port = 18;

        //Declare IMU
        pros::Imu imu(inertial_port);

        //Define lemblib horizontal tracking wheel
        lemlib::TrackingWheel horizontal_tracking_wheel(
            &rotation_horiz, //encoder
            lemlib::Omniwheel::NEW_2, //wheel size
            -2.75 //offset
        );

        //Define lemblib vertical tracking wheel
        lemlib::TrackingWheel vertical_tracking_wheel(
            &rotation_vert, //encoder
            lemlib::Omniwheel::NEW_2, //wheel size
            0.375 //offset
        );

        // odometry settings
        lemlib::OdomSensors sensors(nullptr,//&vertical_tracking_wheel, // vertical tracking wheel
                                    nullptr, // vertical tracking wheel 2, DNE
                                    nullptr, //&horizontal_tracking_wheel, // horizontal tracking wheel
                                    nullptr, // horizontal tracking wheel 2, DNE
                                    nullptr //&imu // inertial sensor
        );

        // lateral PID controller
        lemlib::ControllerSettings lateral_controller(12, // proportional gain (kP)
                                                    0, // integral gain (kI)
                                                    60, // derivative gain (kD)
                                                    3, // anti windup
                                                    1, // small error range, in inches
                                                    100, // small error range timeout, in milliseconds
                                                    3, // large error range, in inches
                                                    500, // large error range timeout, in milliseconds
                                                    20 // maximum acceleration (slew)
        );

        // angular PID controller
        lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
                                                    0, // integral gain (kI)
                                                    35, // derivative gain (kD)
                                                    3, // anti windup
                                                    1, // small error range, in degrees
                                                    100, // small error range timeout, in milliseconds
                                                    3, // large error range, in degrees
                                                    500, // large error range timeout, in milliseconds
                                                    0 // maximum acceleration (slew)
        );

        lemlib::ExpoDriveCurve driveCurve(5, 12, 1.132);

        lemlib::ExpoDriveCurve angle(5, 0, 1.5);

        // create the chassis
        lemlib::Chassis chassis(drivetrain, // drivetrain settings
                                lateral_controller, // lateral PID settings
                                angular_controller, // angular PID settings
                                sensors,
                                &driveCurve
                                //&angle
        );

    }
}