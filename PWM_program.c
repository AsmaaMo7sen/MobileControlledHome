#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PWM_interface.h"
#include "PWM_register.h"
#include "PWM_private.h"
#include "PWM_config.h"


u8 PWM_u8Init(u8 Copy_u8Channel , u16 Copy_u8Frequency , u16 Copy_u16OCRValue)
{
	/*local variable for error checking*/
	u8 Local_u8ErrorState = OK ;

	/* 1- setting mode of TIMER/COUNTER1 to be fast PWM (mode no.14)*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/* 2-setting non inverted mode on OC1A | OC1B pins */
	/*switching over channels*/
	switch(Copy_u8Channel)
		{
			/*choosing Channel A*/
			case CHANNEL_A :
				CLR_BIT(TCCR1A ,TCCR1A_COM1A0);
				SET_BIT(TCCR1A ,TCCR1A_COM1A1);
				break ;

			/*choosing Channel B*/
			case CHANNEL_B :
				CLR_BIT(TCCR1A ,TCCR1A_COM1B0);
				SET_BIT(TCCR1A ,TCCR1A_COM1B1);
				break ;

			default :
				Local_u8ErrorState = WRONG_CHANNEL ;
				break ;
		}


	/* 3- Setting value of ICR register to set frequency*/
	/*checking for right configuration of frequency*/
	if(Copy_u8Frequency >= FREQUENCY_1000 || Copy_u8Frequency <= FREQUENCY_20)
	{
		ICR1 = Copy_u8Frequency ;
	}
	else
	{
		Local_u8ErrorState = WRONG_FREQ ;
	}


	/* 4-setting value of OCR to set duty cycle*/
	/*checking for valid value of duty cycle*/
	if(Copy_u16OCRValue >= 0 && Copy_u16OCRValue <=65536)
	{
		/*switching over channels*/
		switch(Copy_u8Channel)
			{
				/*choosing Channel A*/
				case CHANNEL_A :
					OCR1A = Copy_u16OCRValue ;
					break ;

				/*choosing Channel B*/
				case CHANNEL_B :
					OCR1B = Copy_u16OCRValue ;
					break ;

				default :
					Local_u8ErrorState = WRONG_CHANNEL ;
					break ;
			}
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	/* 5-disable all interrupts*/
	TIMSK = 0 ;

	/* 6- setting prescaler to run TIMER/COUNTER1*/
	/*setting prescaler=8 to get tick time = 1us*/
	TCCR1B &= CLK_MASK ;
	TCCR1B |= PRESCALER_8 ;

	/*return from this function*/
	return Local_u8ErrorState ;
}

void PWM_u8Stop(void)
{
	TCCR1B &= CLK_MASK ;
	TCCR1B |= NO_CLOCK ;
}


