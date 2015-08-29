
#include "OpenTel_Mavlink.h"
#include "uart.h"

mavlink_system_t mavlink_system;
mavlink_message_t* msg;

uint8_t testTxBuf[10] = {1,2,3,4,5,6,7,8,9,10};
uint16_t tranlTimer;

void delay(void){
	uint16_t count = 30000;
	while(count--);
}

/**
  * @brief  ����48M��Ϊϵͳʱ��.
  * @param  
  * @retval 
  */
void RCC_Configuration(void) { 
    //����PLLʱ��Դ����Ƶϵ��  
    //PLL input clock*12
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);   
	
		//ʹ��PLL  
		RCC_PLLCmd(ENABLE);  
		//�ȴ�PLL��ʼ���ɹ�  
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);       
	
		//�ȴ�ϵͳʱ�ӳ�ʼ���ɹ� 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
		while(RCC_GetSYSCLKSource() != 0x08);     
}

/*
 *
 */
int main(void){	
	RCC_Configuration();	
  SysTick_Config(SystemCoreClock / 1000);		
	
	serial_open(0, 0);		
	
	mavlink_system.sysid = MAV_TYPE_GENERIC;
	mavlink_system.compid = MAV_AUTOPILOT_GENERIC;
	
	while(1) {
		mavlink_send_message(0, MSG_HEARTBEAT, 0);
		mavlink_send_message(0, MSG_LOCATION, 0);
				
		while(1){
			if(tranlTimer > 100) {
				tranlTimer = 0;
				mavlink_send_message(0, MSG_HEARTBEAT, 0);
		    mavlink_send_message(0, MSG_ATTITUDE, 0);
		    mavlink_send_message(0, MSG_AHRS, 0);
			}
			update();
		}
		
		#ifdef TEST_UART
		serial_write_buf(testTxBuf, 10);	
		delay();
		
		for(i=0; i<10; i++) testTxBuf[i]++;
    delay();		
		#endif
	}
}


