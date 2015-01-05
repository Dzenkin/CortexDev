/**
  @page Inductive sensor
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 Dmitry Zenkin *******************
  * @file    readme.txt  
  * @author  Dmitry Zenkin
  * @version V1.0.0
  * @date    27-Oct-2014
  * @brief   Inductive sensor
  ******************************************************************************
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *   
  ******************************************************************************
   @endverbatim

@par Description 

This example describes how to measure dissipation at low inductance by CortexM0.

 Device consist of main timer TIM1, that starts in same time:  
 - slave timer TIM2 generate short impulse on sensor coil (pin2),
  - and ADC measure echo of impulse after detection on D2 (pin1).
 Another output of TIM2 uses as PWM output, 
 proportional to distanse (pin3).




@par Directory contents 

  - TIM_ADC_Trigger/stm32f0xx_conf.h    Library Configuration file
  - TIM_ADC_Trigger/stm32f0xx_it.c      Interrupt handlers
  - TIM_ADC_Trigger/stm32f0xx_it.h      Interrupt handlers header file
  - TIM_ADC_Trigger/main.c              Main program
  - TIM_ADC_Trigger/system_stm32f0xx.c  STM32F0xx system source file
  

@par Hardware and Software environment

  - This example runs on STM32F0xx Devices.
  
  - This example has been tested with  STM32F050F4P6
     and can be easily tailored to any other supported device and development board.

  - Constants tested on 10 turns winding coil with 20x30mm frame.

    - Schematics:

  


           D1   coil            ___100k
  pin2 ---|>|---uuuu-----------|___|-----o +V
             |          |    |
             V  D2     | |   = 0.1uF
             -     100k| |   |
             |          |    |
             o pin1    ---  ---


            ____
    pin3 ---____------- output 1v/100%
             50k   |
                   =1uf
                   |
                  ---

    

@par How to use it ? 

In order to make the program work, you must do the following :


 + MDK-ARM
    - Open the TIM_ADC_Trigger.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)    

 

 * <h3><center>&copy; COPYRIGHT Dmitry Zenkin </center></h3>
 */
