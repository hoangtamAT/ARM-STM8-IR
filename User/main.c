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
#include "stm8s_uart1.h"
#include "stm8s_eeprom.h"

#define IR_PORT GPIOD
#define IR_PIN  GPIO_PIN_4
#define BTN     GPIO_ReadInputData(GPIOB)
#define L1      GPIO_PIN_3
#define L2      GPIO_PIN_6
#define L3      GPIO_PIN_5
#define LED     GPIOC
    

uint8_t key;
uint8_t mode=0;

//#define dl200us 47
//#define dl750us 183
//#define dl500us 121
//#define dl500ms 80

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void CLK_Config(void);
void learnKey();
void handle();
void main(void)
{
  /* Infinite loop */
  CLK_Config();
  GPIO_Init(IR_PORT,IR_PIN,GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOB,GPIO_PIN_4,GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC,GPIO_PIN_ALL,GPIO_MODE_OUT_PP_LOW_SLOW);
  
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
/* Unlock Data memory */
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);
  //GPIO_Init(GPIOC,GPIO_PIN_4,GPIO_MODE_OUT_PP_LOW_SLOW);
  //GPIO_Init(GPIOC,GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_SLOW);
  //eepromWriteByte(1,0x55);

  while (1)
  {  
   key=IR_GetCode();
   if((BTN&0x10)==0)
   {
     mode=1;
     GPIO_WriteHigh(LED,L1); 
     delay_us(dl50ms);
     GPIO_WriteLow(LED,L1);
   }
   if(mode!=0) learnKey();
   else
   {
      handle();
   }

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

void learnKey()
{
  switch(mode)
     {
     case 1:
        if(key)
        {
          FLASH_ProgramByte(0x004000,key);
          GPIO_WriteHigh(LED,L1);
          delay_us(dl50ms);
          GPIO_WriteLow(LED,L1);
          delay_us(dl50ms);
          mode=2;
          break;
        }
     case 2:
        if(key)
        {
          FLASH_ProgramByte(0x004001,key);
          GPIO_WriteHigh(LED,L2);
          delay_us(dl50ms);
          GPIO_WriteLow(LED,L2);
          delay_us(dl50ms);
          mode=3;
          break;
        }
     case 3:
        if(key)
        {
          FLASH_ProgramByte(0x004002,key);
          GPIO_WriteHigh(LED,L3);
          delay_us(dl50ms);
          GPIO_WriteLow(LED,L3);
          delay_us(dl50ms);
          GPIO_WriteHigh(LED,L1);
          delay_us(dl50ms);
          delay_us(dl50ms);
          delay_us(dl50ms);
          GPIO_WriteHigh(LED,L2);
          delay_us(dl50ms);
          delay_us(dl50ms);
          delay_us(dl50ms);
          GPIO_WriteHigh(LED,L3);
          delay_us(dl50ms);
          delay_us(dl50ms);
          delay_us(dl50ms);
          GPIO_WriteLow(LED,L1|L2|L3);
          mode=0;
          break;
        }
     }
}

void handle()
{
     if(key)
     {
       if(key==FLASH_ReadByte(0x004000)) GPIO_WriteReverse(LED,L1);
       delay_us(dl50ms);
     }
     if(key)
     {
       if(key==FLASH_ReadByte(0x004001)) GPIO_WriteReverse(LED,L2);
       delay_us(dl50ms);
     }
     if(key)
     {
       if(key==FLASH_ReadByte(0x004002)) GPIO_WriteReverse(LED,L3);
       delay_us(dl50ms);
     }
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
