/*
 * usart1.c
 *
 *  Created on: 19.11.2020
 *      Author: Shady
 */

#include<stddef.h>
#include"gpio.h"
#include"usart1.h"


/*USART1 states definition*/


typedef enum
{

	USART1_IDLE,
	USART1_WAIT_FOR_RESPONSE,
	USART1_ASK_FOR_NAME,
	USART1_WAIT_FOR_NAME,
	USART1_WAIT_FOR_COMMAND,
} USART1_StateType;


static USART1_StateType currentState = USART1_IDLE;

/*USART1 IRQ status definition*/


typedef enum
{

	USART1_NO_IRQ,
	USART1_CHAR_RECEIVED,
	USART1_PARITY_ERROR,
} USART1_IRQStatusType;


static USART1_IRQStatusType currentIRQStatus = USART1_NO_IRQ;

/*Return type*/

typedef enum
{

	STR_NOT_EQUAL,
	STR_EQUAL,
} strcmpReturnType;



/*AF PA9 / PA10 pin masks*/

#define GPIO_AFRH_AFRH9                      ((uint32_t)0x000000F0)
#define GPIO_AFRH_AFRH9_AF7                  ((uint32_t)0x00000070)
#define GPIO_AFRH_AFRH10                     ((uint32_t)0x00000F00)
#define GPIO_AFRH_AFRH10_AF7                 ((uint32_t)0x00000700)


/*Maximum USART reception buffer length*/

#define MAX_BUFFER_LENGTH ((uint32_t) 200u)



static char RxChar = 0;
static char RxBuffer[MAX_BUFFER_LENGTH + 1];
static uint8_t RxMessageLength = 0;


/*USART1 messages to be transmitted*/

static const char hello_world[] = "Hello World!";
static const char ask_for_name[] = "what is your name ?";
static const char hi[] = "Hello";
static const char ask_for_command[] = "please, send command";
static const char ask_for_command_ex[] = "Action[turn on / turn off] Led[green_led / red_led]";
static const char turn_on_green_led[] = "turn_on green_led";
static const char turn_on_red_led[] = "turn_on red_led";
static const char turn_off_green_led[] = "turn_off green_led";
static const char turn_off_red_led[] = "turn_off red_led";
static const char done[] = "Done";
static const char wrong_command[] = "wrong command";
static const char parity_error[] = "Parity Error";

/*Reception parameters*/


/*string transmit*/

static void strTransmit(const char *str , uint8_t size)
{

	/*check null pointers*/
	if(NULL != str)
	{
		/*send all string characters*/
		for(int idx = 0 ; idx < size ; idx++)
		{
			/*check USART status register*/
			while(!(USART1->SR & USART_SR_TXE))
			{
				/*wait for transmission buffer empty flag*/
			}

			/*write data into transmit data register*/
			USART1->DR = str[idx];
		}

	}
	else
	{

		/*Null pointers do nothing*/
	}

}


/* string receive*/

static void strReceive(void)
{
	/*Local string buffer*/
	static char RxLocalBuffer[MAX_BUFFER_LENGTH];

	/*current reception index*/
	static int RxIndex = 0;

	/*check for end-of-line condition*/
	if(RxChar == '\0')
	{

		/*check if string data was received before */
		if(RxIndex != 0)
		{

			/*copy string data from local buffer*/
			for(int idx = 0 ; idx < RxIndex ; idx++)
			{

				RxBuffer[idx] = RxLocalBuffer[idx];

			}

			/*Add terminating NULL at the end*/
			RxBuffer[RxIndex] = 0;

			/*Set message length*/
			RxMessageLength = RxIndex + 1;

			/*Reset current Index*/
			RxIndex = 0;

		}
		else{

			/*String buffer already empty*/
		}
	}
	else
	{
		/*char data was received , Check for buffer overflow*/
		if(MAX_BUFFER_LENGTH == RxIndex)
		{
			/*Reset the reception buffer*/
			RxIndex = 0;
		}
		else
		{
			/*Do nothing , No overflow*/
		}

		/*copy char data into string buffer*/
		RxLocalBuffer[RxIndex]  =RxChar;

		/*Increment current index for the next char reception*/
		RxIndex ++;
	}
}



static strcmpReturnType strCmp(const char *str1, const char *str2, const uint8_t size)
{

	/*compare status*/

	strcmpReturnType cmpStatus = STR_EQUAL;

	/*check null pointers*/

	if((NULL != str1) && (NULL != str2))
	{

		/*start comparing*/

		for(int idx = 0 ; idx < size ; idx ++)
		{
			/*when not equal set the return status*/
			if(str1[idx] != str2[idx])
			{
				cmpStatus = STR_NOT_EQUAL;

			}
			else
			{
				/*Do nothing*/
			}
		}

	}
	else
	{
		/*Null pointers , do nothing */
	}

	return cmpStatus;

}

/*Configure GPIO with AF7 , USART1 connected to APB2 with 90 MHz clock
 * PA9 -> USART1_TX , PA10 -> USART1_RX*/

void USART1_GPIO_Config(void)
{

	/*Enable port A clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/*select alternate function mode*/
	GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
	GPIOA->MODER |=  (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);

	/*select output type push-pull for Tx(PA9)*/
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_9);

	/*select output speed medium for Tx(PA9)*/
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR9);
	GPIOA->OSPEEDR |=  GPIO_OSPEEDER_OSPEEDR9_0;

	/*select pull-up*/
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10);
	GPIOA->PUPDR |=  (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0);

	/*select AF7*/
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH9 | GPIO_AFRH_AFRH10);
	GPIOA->AFR[1] |=  (GPIO_AFRH_AFRH9_AF7 | GPIO_AFRH_AFRH10_AF7);


}


/*Configure USART1 for ST virtual COM port (VCP*/

void USART1_Init(void)
{

	/*Enable USART1 clock*/
	RCC->APB2ENR = RCC_APB2ENR_USART1EN;

	/*select over-sampling by 16 mode*/
	USART1->CR1 &= ~USART_CR1_OVER8;

	/*select one sample bit method*/
	USART1->CR3 |= USART_CR3_ONEBIT;

	/*select 1 start bit , 9 Data bits, n Stop bit*/
	USART1->CR1 |= USART_CR1_M;

	/*select 1 stop bit*/
	USART1->CR2 &= ~USART_CR2_STOP;

	/*Enable parity control*/
	USART1->CR1 |= USART_CR1_PCE;

	/*select odd parity*/
	USART1->CR1 |= USART_CR1_PS;

	/*Set Baud rate = 115200 BPS
	 * USARTDIV = Fck / (16 * baud_rate) = 90000000 / (16 * 115200) = 48.82
	 *
	 * DIV_Fraction = 16 * 0.82 = 13.12 = 13 = 0xD
	 * DIV_Mantissa = 48 = 0x30
	 *
	 * BRR = 0x30D*/

	USART1->BRR = 0x30D;


}


/*Enable USART1 transmitter and receiver*/

void USART1_Enable(void)
{

	/*Enable USART*/
	USART1->CR1 |= USART_CR1_UE;

	/*Enable transmitter*/
	USART1->CR1 |= USART_CR1_TE;

	/*Enable receiver*/
	USART1->CR1 |= USART_CR1_RE;

	/*Enable reception buffer not empty flag interrupt*/
	USART1->CR1 |= USART_CR1_RXNEIE;

	/*Enable parity error interrupt*/
	USART1->CR1 |= USART_CR1_PEIE;

}



/*Sending and receiving data*/

void USART1_Process(void)
{

	/*check error status*/

	switch (currentIRQStatus)
	{
	  case USART1_PARITY_ERROR:

		/*Transmit parity error*/
		strTransmit(parity_error, sizeof(parity_error));

		/*Reset USART1 state*/
		currentState = USART1_IDLE;

		/*Reset IRQ status*/
		currentIRQStatus = USART1_NO_IRQ;
		break;

	  case USART1_CHAR_RECEIVED:
		  /*Receive string data*/
		  strReceive();

		  /*Reset IRQ status*/
		  currentIRQStatus = USART1_NO_IRQ;
		  break;

	  case USART1_NO_IRQ:
		  break;

	  default:
		  break;

	}

	/*check current USART state*/

	switch (currentState)
	{
	  case USART1_IDLE:
		  /*Transmit data */
		  strTransmit(hello_world , sizeof(hello_world));

		  /*Go to next state */
		  currentState = USART1_WAIT_FOR_RESPONSE;
		  break;

	  case USART1_WAIT_FOR_RESPONSE:
		  /*check if new message received*/
		  if(0 != RxMessageLength)
		  {
			  /*Reset message length*/
			  RxMessageLength = 0;

			  /*Go to next state*/
			  currentState = USART1_ASK_FOR_NAME;

		  }
		  else
		  {
			  /*Nothing received yet*/

		  }
		  break;


	  case USART1_ASK_FOR_NAME:

		  /*Transmit data*/

		  strTransmit(ask_for_name , sizeof(ask_for_name));

		  /*Go to next state */
		  currentState = USART1_WAIT_FOR_NAME;
		  break;

	  case USART1_WAIT_FOR_NAME:

		  /*check if new message received*/

		  if(0 != RxMessageLength)
		  {

			  /*Transmit data*/
			  strTransmit(hi, sizeof(hi));
			  strTransmit(RxBuffer, RxMessageLength);
			  strTransmit(ask_for_command , sizeof(ask_for_command));
			  strTransmit(ask_for_command_ex, sizeof(ask_for_command_ex));


			  /*Reset message length*/

			  RxMessageLength = 0;

			  /*Go to next state*/

			  currentState = USART1_WAIT_FOR_COMMAND;

		  }
		  else
		  {
			  /*Nothing received yet*/

		  }

		  break;

	  case USART1_WAIT_FOR_COMMAND:

		  /*check if new message received*/

		  if( 0 != RxMessageLength)
		  {

			  /*Reset message length*/
			  RxMessageLength = 0;

			  /*String compare results*/

			  strcmpReturnType isMatch_01 = STR_NOT_EQUAL;
			  strcmpReturnType isMatch_02 = STR_NOT_EQUAL;
			  strcmpReturnType isMatch_03 = STR_NOT_EQUAL;
			  strcmpReturnType isMatch_04 = STR_NOT_EQUAL;

			  /*compare with turn on green led command*/
			  isMatch_01 = strCmp(turn_on_green_led, RxBuffer, sizeof(turn_on_green_led));

			  /*check return status*/

			  if(STR_EQUAL == isMatch_01)
			  {
				  /*Turn on green led*/
				  GPIO_TurnON_LED(EVAL_GREEN_LED);

				  /*Transmit data*/
				  strTransmit(done, sizeof(done));

			  }
			  else
			  {
				  /*compare with turn on red led command*/

				  isMatch_02 = strCmp(turn_on_red_led, RxBuffer, sizeof(turn_on_red_led));
			  }

			  /*check return status*/

			  if(STR_EQUAL == isMatch_02)
			  {
				  /*Turn on red led*/
				  GPIO_TurnON_LED(EVAL_RED_LED);

				  /*Transmit data*/
				  strTransmit(done,sizeof(done));

			  }
			  else if (STR_NOT_EQUAL == isMatch_01)
			  {
				  /*compare with turn off green led command*/
				  isMatch_03 = strCmp(turn_off_green_led , RxBuffer, sizeof(turn_off_green_led));
			  }
			  else
			  {
				  /*do nothing*/
			  }

			  /*check return status*/
			  if(STR_EQUAL == isMatch_03)
			  {
				  /*Turn off green led*/
				  GPIO_TurnOFF_LED(EVAL_GREEN_LED);

				  /*Transmit data*/
				  strTransmit(done,sizeof(done));

			  }
			  else if ((STR_NOT_EQUAL == isMatch_02) && (STR_NOT_EQUAL == isMatch_01))
			  {
				  /*compare with turn off red led command*/

				  isMatch_04 = strCmp(turn_off_red_led , RxBuffer , sizeof(turn_off_red_led));

			  }
			  else
			  {
				  /*Do nothing*/
			  }

			  /*check return status*/

			  if(STR_EQUAL == isMatch_04)
			  {
				  /*Turn off red led*/
				  GPIO_TurnOFF_LED(EVAL_RED_LED);

			      /*Transmit data*/
				  strTransmit(done,sizeof(done));
			  }
			  else if ((STR_NOT_EQUAL == isMatch_03) && (STR_NOT_EQUAL == isMatch_02) && (STR_NOT_EQUAL == isMatch_01))
			  {

				  /*transmit data*/
				  strTransmit(wrong_command , sizeof(wrong_command));

			  }
			  else
			  {

				  /*Do nothing*/
			  }


		  }
		  else
		  {
			  /*Nothing received yet*/
		  }
		  break;

	  default:
		  break;
	}


}

void USART1_IRQ_Callback(void)
{

	/*check if parity error detected*/
	if((USART1->SR & USART_SR_PE) == USART_SR_PE)
	{
		while((USART1->SR & USART_SR_RXNE) != USART_SR_RXNE)
		{
			/*wait for RXNE flag to be set*/

		}

		/*Read data register to clear parity error */
		USART1->DR;

		/*Set Parity error*/
		currentIRQStatus = USART1_PARITY_ERROR;
	}
	else
	{
		/*No parity error*/
	}


	/*check USART receiver*/
	if((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE)
	{
		/*Read character*/

		RxChar = USART1->DR;

		/*Set IRQ status*/
		currentIRQStatus = USART1_CHAR_RECEIVED;

	}
	else
	{
		/*No new data received*/
	}

}




