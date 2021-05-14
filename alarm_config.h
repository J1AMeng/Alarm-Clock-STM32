#ifndef ALARM_CONFIG_H
#define ALARM_CONFIG_H

#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_tim.h"

#include "stdlib.h"

#ifndef TRUE
#define TRUE 1
#endif

//=========================================================

// Enums for exti_finite_state_machine

enum button_state
{
    USER_BUTTON_RELEASED      = 0,
    USER_BUTTON_PRESSED       = 1,
    USER_BUTTON_LONG_PRESSED  = 2,
    LEFT_BUTTON_RELEASED      = 3,
    LEFT_BUTTON_PRESSED       = 4,
    LEFT_BUTTON_LONG_PRESSED  = 5,
    RIGHT_BUTTON_RELEASED     = 6,
    RIGHT_BUTTON_PRESSED      = 7,
    RIGHT_BUTTON_LONG_PRESSED = 8,
    BUTTON_STATES_DEFAULT     = 9
};

enum edge
{
    FALLING      = 0,
    RISING       = 1,
    EDGE_DEFAULT = 2
};

enum button
{
    BUTTON_USER     = 0,
    BUTTON_LEFT     = 1,
    BUTTON_RIGHT    = 2,
    BUTTONS_DEFAULT = 3
};

//=========================================================

// Enum for alarm_finite_state_machine

enum alarm_state
{
    CLOCK                = 0,
    TUNE                 = 1,
    ALARM                = 2,
    ALARM_STATES_DEFAULT = 3
};

//=========================================================

// Enum for tune_finite_state_machine

enum tune_state
{
    TUNE_HOUR           = 0,
    TUNE_MINUTE         = 1,
    TUNE_STATES_DEFAULT = 2
};

//=========================================================

// Some general configurations
void RCC_Config(void);
void GPIO_Config(void);
void TimersConfig(void);

// Buttons' initialisations
void UserButtonInit(void);
void FirstButtonInit(void);
void SecondButtonInit(void);

//=========================================================

#endif //ALARM_CONFIG_H