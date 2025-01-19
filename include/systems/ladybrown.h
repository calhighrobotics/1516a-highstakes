#pragma once
#include <queue>
#include "lemlib/api.hpp"

namespace Robot {


    /**
     * @breif Class to deal with handling of intake
     */
    class LadyBrown{
        public:

            /**
             * @breif Running the intake
             * 
             * This should run the intake like normal, taking account for states 
             */
            void run();
        
        private:

            int state;
            int idle_angle;
            int score_angle;
            int collect_angle;

    };
}