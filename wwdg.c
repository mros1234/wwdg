#include <main.h>

uint8_t wwdg_max = 0x7F;
uint8_t sstr,sswr;

int main(void)
{
   WWDG_Init(0x7F,0x5F);
   while(1)
   {
      /*WWDG在初始化之后，中断持续喂狗，若线程出错即系统复位*/
   }
}

void WWDG_Init(uint8_t tr,uint8_t wr)
{ 
	  wwdg_max = tr&wwdg_max;
	  Iwwdg.Init.Prescaler = WWDG_PRESCALER_8;
		Iwwdg.Init.Window = wr;
		Iwwdg.Init.Counter = wwdg_max;
	  Iwwdg.Init.EWIMode = WWDG_EWI_ENABLE;
	  Iwwdg.Instance = WWDG;
	
	  HAL_WWDG_Init(&Iwwdg);
	  __HAL_WWDG_ENABLE_IT(&Iwwdg,WWDG_IT_EWI);
  	HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void)
{
		sstr=WWDG->CR&0X7F;
		sswr=WWDG->CFR&0X7F;
		if(sstr<sswr)
		{
			HAL_WWDG_Refresh(&Iwwdg);	
			HAL_WWDG_IRQHandler(&Iwwdg);
		}
}


