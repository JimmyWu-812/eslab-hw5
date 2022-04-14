/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "stm32l475e_iot01_tsensor.h"
#include "mbed.h"

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
PwmOut led(PWM_OUT);//LED1);

int main()
{
    BSP_TSENSOR_Init();
    float sensor_value = 0;
    // specify period first
    while(true){
        sensor_value = BSP_TSENSOR_ReadTemp();
        printf("\nTEMPERATURE = %.2f degC\n", sensor_value);
        if(sensor_value > 34){
            led.period(0.25f);      // 4 second period
        }
        else if(sensor_value > 33.5){
            led.period(0.5f);      // 4 second period
        }
        else if(sensor_value > 33){
            led.period(1.0f);      // 4 second period
        }
        else if(sensor_value > 32.5){
            led.period(2.0f);      // 4 second period
        }
        led.write(0.50f);      // 50% duty cycle, relative to period
        ThisThread::sleep_for(1000);
    }
    //led = 0.5f;          // shorthand for led.write()
    //led.pulsewidth(2);   // alternative to led.write, set duty cycle time in seconds
    // while (1);
}


// #include "mbed.h"
// PwmOut led_main(D3);
// PwmOut led_t(D10);
// void t1(){
//     led_t.period(0.5f);
//     led_t.write(0.4f);
// }
// void t2(){
//     led_main.period(0.5f);
//     led_main.write(0.4f);
// }
// int main(){
//     EventQueue queue;
//     queue.call_in(0, t1);
//     queue.call_in(250, t2);
//     queue.dispatch_forever();
// }