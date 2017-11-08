#include "IR.h"

void delay_us(int n)
{ 
	while (n>0) n--;
}
char ch=0;
uint8_t IR_CheckStart()
{
    uint16_t i;

    ch=IR_DATA;
    if((IR_DATA&0x10)==0)         
    {
        delay_us(dl200us);  
        ch=IR_DATA;
        if((IR_DATA&0x10)==0)     
        {   
            for(i=0;i<30;i++)
            {
                delay_us(dl200us);
                ch=IR_DATA;
                if((IR_DATA&0x10)==0x10) 
                {
                  return 0; 
                }
            }
            while((IR_DATA&0x10)==0);           
            return 1;
        }
     }
return 0;
}
uint8_t IR_GetCode(void)
{
  uint8_t i,Data=0;
  uint32_t data_infr=0;
  if(IR_CheckStart())             // Neu dung xung START
  {
    while((IR_DATA&0x10)==0x10); 
    while((IR_DATA&0x10)==0);
    for(i=0;i<32;i++)             // Lay 24 bit du lieu (bao gom 8 bit 0 va 8 bit 1 dau tien sau xung start)
    {    
      //GPIO_WriteReverse(GPIOD,GPIO_PIN_3);
      
      delay_us(dl750us);            // Delay 750us de kiem tra bit
      if((IR_DATA&0x10)==0x10)
      {
        data_infr=(data_infr<<1)|1; 
      }
      if((IR_DATA&0x10)==0)
      {
        data_infr=data_infr<<1; 
      }
      while((IR_DATA&0x10)==0x10);      // cho canh len
      while((IR_DATA&0x10)==0);     
    }
    Data=(data_infr&0x000000ff);
    delay_us(dl50ms);
    //delay_us(dl50ms);
    //delay_us(dl50ms);               // Cho het tin hieu (chong nhieu) 
  }
  return Data;                  // Gia tri ma kenh tra ve  
}  