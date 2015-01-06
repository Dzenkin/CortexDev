/**
  @page Inductive sensor
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 Dmitry Zenkin *******************
  * @file    readme.txt  
  * @author  Dmitry Zenkin
  * @version V1.0.0
  * @date    5-Jan-2015
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

 Timer TIM2 generate on CH3 short impulse on sensor coil (pin2),
  - and ADC measure echo of impulse after detection on D2 (pin1).
 CH4 of TIM2 uses as output, (pin3).
 Output (pin3) high(1) when coil closed by metal target, low(0) when open.




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
    
                             D2
                          |--|>|------ o pin1 ADC
                          C
                    Coil  C
                          C
           D1             |                ___100k
  pin2 ---|>|-----------------------------|___|-----o +V 3.3V
  TIM2Ch3              |    |
                      | |   = 0.1uF
                  100k| |   |
                       |    |
                      ---  ---




@par How to use it ? 

In order to make the program work, you must do the following :


 + MDK-ARM
    - Open the TIM_ADC_Trigger.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)    

 

 * <h3><center>&copy; COPYRIGHT Dmitry Zenkin </center></h3>
 */
