
#include "uart.h"
#include "fifo.h"

fifo_t uart_rx_fifo, uart_tx_fifo;
uint8_t uart_tx_buf[UART_TX_BUFFER_SIZE], uart_rx_buf[UART_RX_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

  
/* Private functions ---------------------------------------------------------*/

void USART_Configuration(void)//���ڳ�ʼ������
{  
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;    
	
	/*Enable the USART1 Interrupt(??USART1??)*/ 													
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;   	      
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
                
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );     
	
  /*
   *  USART1_TX -> PB6 , USART1_RX ->        PB7
   */                                
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;                 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);          
	
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);        
        
  USART_InitStructure.USART_BaudRate = 9600;																			//���ô��ڲ�����
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;											//��������λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;													//����ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;															//����Ч��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//����������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									//���ù���ģʽ
  USART_Init(USART1, &USART_InitStructure); 																			//������ṹ��
  USART_Cmd(USART1, ENABLE);																											//ʹ�ܴ���1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	//ʹ�ܽ����ж�
}			

void UART_send_byte(uint8_t byte) 							//����1�ֽ�����
{
 while(!((USART1->ISR)&(1<<7)));
 USART1->TDR=byte;	
}		

void UART_Send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while(!((USART1->ISR)&(1<<7)));							//�ȴ�������
		USART1->TDR = *Buffer;
		Buffer++;
		Length--;
	}
}

uint8_t UART_Recive(void)
{	
	while(!(USART1->ISR & (1<<5)));								//�ȴ����յ�����
	return(USART1->RDR);			 										//��������
}

PUTCHAR_PROTOTYPE 
{
  /* ��Printf���ݷ������� */
  USART_SendData(USART1, (uint8_t)ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 
  return (ch);
}


//========================================================================================================
//���ڷ�װ�����ݻ�����
//========================================================================================================
/** @brief ���ڳ�ʼ��
  *        1) �����������ݻ�������һ�����ڷ��䣬һ�����ڽ���
  *        2) ��ʼ�����ڲ����ʣ�ȫ˫����ʹ�ܽ����ж�(�����жϣ��������ݷ����ʹ��)
  */
void serial_open(uint8_t port, uint32_t baud) {
	fifo_init(&uart_tx_fifo, uart_tx_buf, UART_TX_BUFFER_SIZE);	
	fifo_init(&uart_rx_fifo, uart_rx_buf, UART_RX_BUFFER_SIZE);
	
  USART_Configuration();
}


/** @brief д���ݵ����ڣ���������
  *        
  * @note ����д�뷢�仺���������������жϣ����жϳ��������Զ�����
  */
uint8_t serial_write_buf(uint8_t* buf, uint16_t length) {
	uint16_t i;
	
	if(length == 0) return false;
  for(i = 0; length > 0; length--, i++)	{
		fifo_write_ch(&uart_tx_fifo, buf[i]);
	}	
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
	return true;
}

/** @brief �Դ��ڶ����� 
  * @return һ�ֽ�����
  */
uint8_t serial_read_ch(void){
	uint8_t ch;	
	fifo_read_ch(&uart_rx_fifo, &ch);	
	return ch;
}

/** @breif ��ⷢ�仺����ʣ���ֽڳ��� 
  * @return ʣ���ֽڳ���
  */
uint16_t serial_free(void){
	return fifo_free(&uart_tx_fifo);
}

uint16_t serial_available(void){
	return fifo_used(&uart_rx_fifo);
}

		
