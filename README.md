<h3>Projects describes simple electronic devices, designed using event chaining procedures in Cortex M0 core.</h3>

<h2>Capacitive sensor for fill level of liquid</h2>
This example describes how to measure low capacitances by Cortex M0 chips, using event chaining procedures.

 Timer TIM2 on CH3 generates short impulse on one of sensor tube (pin2),
 ADC (triggered by CH3 of TIM2) measure echo of impulse on other tube (pin1).
 Another output of TIM2 (CH4) uses as simple PWM output, 
 proportional to fill level of liquid (gasoline) 1V=100% (pin3).

<h2>Inductive Proximity Sensor</h2>
This example describes how design inductive proximity sensor with printed coil, 
using event chaining procedures in Cortex M0 chips.

 Timer TIM2 on CH3 generates short impulse on sensor coil (pin2),
 and ADC (triggered by CH3 of TIM2) measure echo of impulse after detection (pin1).
 CH4 of TIM2 uses as output (pin3) 
 high(1) when coil closed by metal, low(0) when open.

<h3>Hardware and Software environment</h3>

  - This examples runs on STM32F0xx Devices.
  
  - This examples has been tested with  STM32F050F4P6 chip
     and can be easily tailored to any other supported device and development board.

  - Code compiled in Keil µVision 4 .71 with standard libraries for STM32F0.
 <br>
  - Capacitive sensor 
  consist of two metal tubes, one inside another, separated by isolator.
  constants tested on tubes with 120mm active zone, diameter 19mm and 28mm (3.5MM gap).
  <br>
  - Inductive Proximity Sensor
  As sensitive inductor used printed coil 10 turns ~1" diameter (or winding of same size)



other details about project: <a href="http://cortexdev.blogspot.com">cortexdev.blogspot.com</a>
