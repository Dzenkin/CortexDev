/**
  ******************************************************************************
  * @file    Inductive Proximity Sensor /main.c 
  * @author  Dimitry Zenkin 
  * @version V1.0.0
  * @date    6-Jan-2015
  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 Dimitry Zenkin zendim4@gmail.com </center></h2>
  *
	* @brief   Main program body
  *  Device consist of main timer TIM1, that starts in same time:  
  *  - slave timer TIM2 generate short impulse on sensor coil (pin2),
	*  - and ADC measure echo of impulse after detection (pin1).
	*  Another chn of TIM2 uses as output, (pin3) 
	*  high(1) when coil closed by metal, low(0) when open.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0_Event_Chaining_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

__IO uint16_t  ADC1ConvertedValue = 0;

ADC_InitTypeDef          ADC_InitStructure;
GPIO_InitTypeDef         GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef        TIM_OCInitStructure;

/* Private variables ---------------------------------------------------------*/

/* Width of scanning pulse  */
uint32_t Channel3Pulse = 0x7; 

/* closed sensor threshold  */
uint32_t ClosedLevel =  0xA00;

/* open sensor threshold  */
uint32_t OpenLevel =  0xA60;

/* Set output to zero (about 7mV) */
uint32_t Channel4Pulse = 0; 

/* open-closed sensor trigger  */
uint8_t Trig =  0 ;

/* Private function prototypes -----------------------------------------------*/
void ADC_Config(void);
void TIM2_Config(void);

/* Private functions ---------------------------------------------------------*/
	
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

	
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */

  //  Initialize peripherals
  
	ADC_Config();	
	TIM2_Config();


  /* Infinite loop */
  while (1)
  {
    /* Test EOC flag */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    
    /* Get ADC1 converted data from sensing tube */
    ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
		
		//Calculation for output on pin3 - simple hysteresis switch
		
		if (ADC1ConvertedValue > OpenLevel)
		{ Trig = 0; }
			
		if (ADC1ConvertedValue < ClosedLevel)
		{ Trig = 1; }
		
		if (Trig == 0)
		{Channel4Pulse = 0;}
		else
		{Channel4Pulse = 0xFFFFF ;}
		
		//refreshing pulse register
		TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);
			

  }
}


void ADC_Config(void)
{
	/* ADC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); 
	
	/* Configure ADC Channel1 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in DIScontinous mode with  12 bits resolutuion   */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  
	/***************** Event chaining **************/
	
	/* Initialize slave mode with trigger from TIM2 */	
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;    
  ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T2_TRGO;
	
	/***************** Event chaining **************/

  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 1 with 13.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_13_5Cycles );
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
	
  /* ADC DIScontinous mode selection */
  ADC_DiscModeCmd(ADC1, ENABLE);
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}



/* TIM2 Configuration */

void TIM2_Config(void)
{
	
  TIM_DeInit(TIM2);
  /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* GPIOA Configuration: Channel  3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_2);
 
	 /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  /* Time Base configuration  ~45Hz */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFF;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Channel  3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* low edge by default */

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;

	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 

	
	/***************** Event chaining **************/

	/* Preparing master mode and trigger source from TIM2 Channel3 */
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_OC3Ref);	

	/***************** Event chaining **************/


		// Initialize pulse registers
  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);

  /* TIM2 counter enable */
  TIM_Cmd(TIM2, ENABLE);

  /* TIM2 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM2, ENABLE);
}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  /* Infinite loop */
  while (1)
  {
  }
}
#endif



/************************ (C) COPYRIGHT  2015 Dimitry Zenkin zendim4@gmail.com  *****END OF FILE****/
