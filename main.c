#include "alarm_clock.h"

extern uint16_t number[4];
extern uint8_t segment[10];
extern uint8_t digit[4];

int main(void)
{
    RCC_Config();
    GPIO_Config();
    TimersConfig();
    
    UserButtonInit();
    FirstButtonInit();
    SecondButtonInit();
    
    while(TRUE);
}