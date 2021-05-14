#ifndef ALARM_СLOCK_H
#define ALARM_CLOCK_H

#include "alarm_config.h"

//=================================================================================
//  @descr IRQ Handler for Lines from EXTI4 to EXTI15
//         We use this handler for Left Button (EXTI13) and Right Button (EXTI14)
//
//
//  @note just calling exti_finite_state_machine() with different arguments
//=================================================================================
void EXTI4_15_IRQHandler(void);

//==========================================================================
//  @descr IRQ Handler for EXTI0 and EXTI1 Lines
//         We use this handler only for User Button (EXTI0)
//
//
//  @note just calling exti_finite_state_machine()
//==========================================================================
void EXTI0_1_IRQHandler(void);

//=================================================================================
//  @descr Finite State Machine for Exti, Heart of this project
//         Swithches between Buttons and its States
//         Finite state realisation for convenience
//         And to avoid battle rattling
//
//
//  @note call alarm_finite_state_machine with different conditions
//=================================================================================
void EXTI_FiniteStateMachine(enum edge edge, enum button button);

//==============================================================================================
//  @descr Finite State Machine for Alarm, ane more heart (but such smaller) of this project
//         Swithches between States of Alarm
//         finite state realisation for convenience
//
//
//  @note calls tune_finite_state_machine where it is nececary
//==============================================================================================
void AlarmFiniteStateMachine(enum button_state button_state);

//==============================================================================================
//  @descr Finite State Machine for Tune mode of Alarm
//         Swithches between States of Tuning
//         finite state realisation for convenience
//
//==============================================================================================
void TuneFiniteStateMachine(enum button_state button_state);


#endif //ALARM_CLOCK_H