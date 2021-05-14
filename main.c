#include "alarm_clock.h"

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
