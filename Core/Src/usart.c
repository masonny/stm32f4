/***
	************************************************************************************
	*	@file  	usart.c
	*	@version V1.0.0	
	*	@brief   usart �ӿ���غ���
   ************************************************************************************
   *  @description
	*
	*  1.��ʼ��USART1������ PA9/PA10��
	*  2.����USART1�������շ�ģʽ����λ8λ��ֹͣλ1λ����У�顢��ʹ��Ӳ�����������ƣ�
	*    ���ڵĲ���������Ϊ115200������Ҫ���Ĳ�����ֱ���޸�usart.h��ĺ궨��USART1_BaudRate��
	*  3.�ض���fputc����,����֧��ʹ��printf������ӡ����
	*
	************************************************************************************
***/

#include "usart.h"

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(int ch)

// ������usart IO�ڳ�ʼ��
void USART_GPIO_Config(void) {

  // �������,printf���Բ���\n
  setvbuf(stdout, NULL, _IONBF, 0);

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(USART1_TX_CLK | USART1_RX_CLK, ENABLE);    //IO��ʱ������

  //IO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;     //����ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;     //����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //�ٶȵȼ�

  //��ʼ�� TX	����
  GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
  GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
  //��ʼ�� RX ����
  GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
  GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);

  //IO���ã����õ�USART1
  GPIO_PinAFConfig(USART1_TX_PORT, USART1_TX_PinSource, GPIO_AF_USART1);
  GPIO_PinAFConfig(USART1_RX_PORT, USART1_RX_PinSource, GPIO_AF_USART1);
}

// ������USART �ڳ�ʼ��
//
void Usart_Config(void) {
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  // IO�ڳ�ʼ��
  USART_GPIO_Config();

  // ���ô��ڸ������
  USART_InitStructure.USART_BaudRate = USART1_BaudRate; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No; //��У��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ģʽ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_Cmd(USART1, ENABLE);    //ʹ�ܴ���1
}

PUTCHAR_PROTOTYPE {
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {

  }
  return ch;
};

GETCHAR_PROTOTYPE {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {

  }
  return (int) USART_ReceiveData(USART1);
};

