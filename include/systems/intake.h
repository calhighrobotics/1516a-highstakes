#pragma once
#include <queue>
#include "lemlib/api.hpp"

namespace Robot {


    /**
     * @breif Class to deal with handling of intake
     */
    class Intake {
        public:

            Intake();

            /**
             * @breif Running the intake
             * 
             * This should run the intake like normal, taking account for states 
             */
            void run();
        
        private:

            int rings_red;

            bool enabled;

            int rings_blue;

            bool state;

            bool pending_eject;

    };
}