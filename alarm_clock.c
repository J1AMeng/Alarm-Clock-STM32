#include "alarm_clock.h"

uint64_t TIME_X = 500000000;                    // TIME of ALARM (init value)

enum alarm_state ALARM_STATE = CLOCK;    // Variable to make noise during ALARMING!!!                         

uint64_t TIME = 0;  // Global time in ms (init value)


void EXTI_FiniteStateMachine(enum edge edge, enum button button)
{
    switch (button)
    {
        case BUTTON_USER:
        {
            static enum button_state user_button_state = USER_BUTTON_RELEASED;
            static uint64_t user_button_timestamp  = 0;
            static uint64_t user_button_press_time = 0;
            
            switch(user_button_state)
            {
                case USER_BUTTON_RELEASED:
                {
                    if ((edge == RISING) && (abs(TIME - user_button_timestamp) > 50))
                    {
                        // The situation when we notice that button is pressed, but don't know type of press
                        user_button_state = USER_BUTTON_PRESSED;
                        user_button_timestamp  = TIME;
                        user_button_press_time = TIME;
                    }

                    break;
                }

                case USER_BUTTON_PRESSED:
                {
                    if((edge == FALLING) && (abs(TIME - user_button_timestamp) > 50))
                    {
                        // The situaton, when button is pressed for a long time
                        if (abs(TIME - user_button_press_time) > 250)
                            AlarmFiniteStateMachine(USER_BUTTON_LONG_PRESSED);

                        // The situaton, when button is pressed in a usual way
                        else
                            AlarmFiniteStateMachine(USER_BUTTON_PRESSED);

                        user_button_state = USER_BUTTON_RELEASED;
                        user_button_timestamp  = TIME;
                        user_button_press_time = 0;
                    }

                    break;
                }
                
                default:
                    while(1);
            }

            break;
        }

        case BUTTON_LEFT:
        {
            static enum button_state left_button_state = LEFT_BUTTON_RELEASED;
            static uint64_t left_button_timestamp  = 0;
            static uint64_t left_button_press_time = 0;

            switch(left_button_state)
            {
                case LEFT_BUTTON_RELEASED:
                {
                    if ((edge == RISING) && (abs(TIME - left_button_timestamp) > 50))
                    {
                        // The situation when we notice that button is pressed, but don't know type of press
                        left_button_state = LEFT_BUTTON_PRESSED;
                        left_button_timestamp  = TIME;
                        left_button_press_time = TIME;
                    }
                    
                    break;
                }

                case LEFT_BUTTON_PRESSED:
                {
                    if((edge == FALLING) && (abs(TIME - left_button_timestamp) > 50))
                    {
                        // The situaton, when button is pressed for a long time
                        if (abs(TIME - left_button_press_time) > 250)
                            AlarmFiniteStateMachine(LEFT_BUTTON_LONG_PRESSED);
                        // The situaton, when button is pressed in a usual way
                        else
                            AlarmFiniteStateMachine(LEFT_BUTTON_PRESSED);

                        left_button_state = LEFT_BUTTON_RELEASED;
                        left_button_timestamp  = TIME;
                        left_button_press_time = 0;
                    }
                    
                    break;
                }
                
                default:
                    while(1);
            }

            break;
        }

        case BUTTON_RIGHT:
        {
            static enum button_state right_button_state = RIGHT_BUTTON_RELEASED;
            static uint64_t right_button_timestamp  = 0;
            static uint64_t right_button_press_time = 0;

            switch(right_button_state)
            {
                case RIGHT_BUTTON_RELEASED:
                {
                    if ((edge == RISING) && (abs(TIME - right_button_timestamp) > 50))
                    {
                        // The situation when we notice that button is pressed, but don't know type of press
                        right_button_state = RIGHT_BUTTON_PRESSED;
                        right_button_timestamp  = TIME;
                        right_button_press_time = TIME;
                    }

                    break;
                }

                case RIGHT_BUTTON_PRESSED:
                {
                    if((edge == FALLING) && (abs(TIME - right_button_timestamp) > 50))
                    {
                        // The situaton, when button is pressed for a long time
                        if(abs(TIME - right_button_press_time) > 250)
                            AlarmFiniteStateMachine(RIGHT_BUTTON_LONG_PRESSED);
                        // The situaton, when button is pressed in a usual way
                        else
                            AlarmFiniteStateMachine(RIGHT_BUTTON_PRESSED);

                        right_button_state = RIGHT_BUTTON_RELEASED;
                        right_button_timestamp  = TIME;
                        right_button_press_time = 0;
                    }

                    break;
                }

                default:
                    while(1);
            }

            break;
        }

        default:
            while(1);
    }
}


void AlarmFiniteStateMachine(enum button_state button_state)
{
    static enum alarm_state alarm_state = CLOCK;

    switch (ALARM_STATE)
    {
        case CLOCK:
        {
            if (button_state == USER_BUTTON_LONG_PRESSED)
            {
                TIME_X = 0;
                alarm_state = TUNE;
            }

            break;
        }

        case TUNE:
        {
            if (button_state == USER_BUTTON_LONG_PRESSED)
                alarm_state = CLOCK;
            else
                TuneFiniteStateMachine(button_state);

            break;
        }

        case ALARM:
        {
            LL_TIM_DisableIT_CC1(TIM2);
            LL_TIM_DisableCounter(TIM2);
            LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
            
            if (button_state == USER_BUTTON_PRESSED)
                alarm_state = CLOCK;

            // Set Alarm at 10 Min later
            if (button_state == RIGHT_BUTTON_PRESSED)
            {
                TIME_X += 10 * 60 * 1000;
                alarm_state = CLOCK;
            }

            // Set Alarm at 5 Min later
            if (button_state == LEFT_BUTTON_PRESSED)
            {
                TIME_X += 5 * 60 * 1000;
                alarm_state = CLOCK;
            }

            break;
        }

        default:
            while(1);
      }

      ALARM_STATE = alarm_state;
}


void TuneFiniteStateMachine(enum button_state button_state)
{
    static enum tune_state tune_state = TUNE_MINUTE;

    switch (tune_state)
    {
        case TUNE_MINUTE:
        {
            if (button_state == LEFT_BUTTON_LONG_PRESSED)
              tune_state = TUNE_HOUR;
            else
            {
                if (button_state == LEFT_BUTTON_PRESSED)
                    TIME_X = TIME_X - 60 * 1000;
                else if (button_state == RIGHT_BUTTON_PRESSED)
                    TIME_X = TIME_X + 60 * 1000;
            }
            
            break;
        }
        
        case TUNE_HOUR:
        {
            if (button_state == RIGHT_BUTTON_LONG_PRESSED)
                  tune_state = TUNE_MINUTE;
            else
            {
                if (button_state == LEFT_BUTTON_PRESSED)
                    TIME_X = TIME_X - 60 * 60 * 1000;
                else if (button_state == RIGHT_BUTTON_PRESSED)
                    TIME_X = TIME_X + 60 * 60 * 1000;
            }
            
            break;
        }
        
        default:
            while(1);
    }
}