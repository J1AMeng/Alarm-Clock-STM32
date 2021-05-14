#include "alarm_clock.h"

// Special construction for segments to write directly to MODER Register
uint8_t segment[10] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};

// Special construction for numbers to write directly to MODER Register
uint16_t number[4] = {0x700, 0x680, 0x580, 0x380};

uint8_t digit[4];       // So, and themselves - numbers, which will be written to "display" 

extern uint64_t TIME_X;
extern uint64_t TIME;
extern enum alarm_state ALARM_STATE;


void EXTI4_15_IRQHandler(void)
{
    // Check, which button is pressed

    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13))
    {
        // Call EXTI_FiniteStateMachine
        EXTI_FiniteStateMachine(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13), BUTTON_LEFT);
        
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
    }

    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14))
    {
        // Call EXTI_FiniteStateMachine
        EXTI_FiniteStateMachine(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_14), BUTTON_RIGHT);

        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
    }
}

void EXTI0_1_IRQHandler(void)
{
    // Call EXTI_FiniteStateMachine
    EXTI_FiniteStateMachine(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0), BUTTON_USER);

    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
}

void TIM3_IRQHandler(void)
{
    // The time, which will be displayed
    static uint64_t display_time = 0;
    static uint64_t global_timer = 0;
    
    TIME++;
    global_timer++;

    // To display time while adjusting
    if (ALARM_STATE == TUNE)
        display_time = TIME_X;
    else
        display_time = TIME;

    if ((TIME == TIME_X) && (ALARM_STATE == CLOCK))
    {
        ALARM_STATE = ALARM;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
        LL_TIM_EnableCounter(TIM2);
        LL_TIM_EnableIT_CC1(TIM2);
        
    }

    if (display_time % 500 == 0)
        number[2] = number[2] ^ 0x800;   // dot blinking

    if (display_time % 10 == 0)
    {
        digit[3] = ((display_time / (60 * 1000)) % 60) % 10;
        digit[2] = ((display_time / (60 * 1000)) % 60) / 10;
        digit[1] = ((display_time / (60 * 60 * 1000)) % 24) % 10;
        digit[0] = ((display_time / (60 * 60 * 1000)) % 24) / 10;
    }

    char seg_number = global_timer % 4;

    switch(seg_number)
    {
        case 0:
            LL_GPIO_WriteOutputPort(GPIOC, number[0] | segment[digit[3]]);
            break;
        case 1:
            LL_GPIO_WriteOutputPort(GPIOC, number[1] | segment[digit[2]]);
            break;
        case 2:
            LL_GPIO_WriteOutputPort(GPIOC, number[2] | segment[digit[1]]);
            break;
        case 3:
            LL_GPIO_WriteOutputPort(GPIOC, number[3] | segment[digit[0]]);
            break;
        default:
            break;
    }
    
    LL_TIM_ClearFlag_UPDATE(TIM3);
}

void TIM2_IRQHandler(void)
{
    
    LL_TIM_ClearFlag_CC1(TIM2);
}