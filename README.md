<h2>Capacitive sensor for fill level of liquid</h2>

This example describes how to measure low capacitances by CortexM0.


<h3>Hardware and Software environment</h3>

  - This example runs on STM32F0xx Devices.
  
  - This example has been tested with  STM32F050F4P6 chip
     and can be easily tailored to any other supported device and development board.

  - Code compiled in Keil mVision4 .71 with standard libraries for STM32F0.

  - Sensor consist two metal tubes, one inside another, separated by isolator.

  - Constants tested on tubes with 120mm active zone, diameter 19mm and 28mm (3.5MM gap).

 Timer TIM2 on CH3 generates short impulse on one of sensor tube (pin2),
 ADC (triggered by CH3 of TIM2) measure echo of impulse on other tube (pin1).
 Another output of TIM2 (CH4) uses as simple PWM output, 
 proportional to fill level of liquid (gasoline) 1V=100% (pin3).

