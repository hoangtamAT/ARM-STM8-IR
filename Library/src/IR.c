#include "IR.h"

void delay_us(int n)
{ 
	while (n>0) n--;
}

uint8_t IR_CheckStart()
{
    uint8_t i;

    if(IR_DATA==0)         
    {
        delay_us(dl500us);       
        if(IR_DATA==0)     
        {   
            for(i=0;i<40;i++)
            {
                delay_us(dl200us);
                if(IR_DATA==1) return 0; 
            }
            while(IR_DATA==1);           
            return 1;       
        }
		}
		return 0;
}
uint32_t IR_GetCode(void)
{
    uint8_t i;
    uint32_t data_infr=0;
    if(IR_CheckStart())             // Neu dung xung START
    {
        while(IR_DATA==0);          // Cho het bit 0 tiep theo
        for(i=0;i<24;i++)             // Lay 24 bit du lieu (bao gom 8 bit 0 va 8 bit 1 dau tien sau xung start)
        {    
            delay_us(dl750us);            // Delay 750us de kiem tra bit
            data_infr=data_infr<<1;
            if(IR_DATA==0) data_infr|=1;
            while(IR_DATA==1);      // cho canh len
            while(IR_DATA==0);     
        }
        delay_us(dl50ms);               // Cho het tin hieu (chong nhieu) 
    }
		return data_infr;                  // Gia tri ma kenh tra ve  
} 