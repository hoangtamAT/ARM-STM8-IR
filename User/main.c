/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_clk.h"
#include "IR.h"

#define IR_PORT GPIOD
#define IR_PIN  GPIO_PIN_4

uint32_t key;

//#define dl200us 47
//#define dl750us 183
//#define dl500us 121
//#define dl500ms 80

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void CLK_Config(void);
//void delay_us(uint16_t n)
//{
//   while(n-- >0);
//}
//void delay_ms(uint16_t n)
//{
//  uint32_t n2=n*200;
//   while(n2-- >0);
//}
void main(void)
{
  /* Infinite loop */
  CLK_Config();
  GPIO_Init(IR_PORT,IR_PIN,GPIO_MODE_IN_PU_NO_IT);
  //GPIO_Init(IR_PORT,IR_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  
  
  while (1)
  {
     //GPIO_WriteReverse(IR_PORT,IR_PIN);
     //delay_us(dl50ms);
    key=IR_GetCode();
  }
  
}

void CLK_Config(void)
{
  CLK_DeInit();
  
  /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
  
  /* Output Fcpu on CLK_CCO pin */
  CLK_CCOConfig(CLK_OUTPUT_MASTER);
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
