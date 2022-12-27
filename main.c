#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>
#include "PORT_interface.h"
#include "PWM_interface.h"
#include "USART_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"

#include "SERVO_interface.h"


USART_t var = {TRANS_AND_REC,CHAR_SIZE_8,ASYNCHRONOUS,NO_PARITY,ONE_STOP_BIT};
USART_t * ptr = &var ;

u8  leds = '\0';
u8  password='\0' ;
u8  username = '\0' ;


/**********************************Functions' prototypes******************************/

void func (void);   //for call back of asynchornous character receive

/*dividing main into functions*/
void CorrectPassAndUsername(void);
void userA(void);
void userB(void);
void userC(void);
void userD(void);
void userE(void);
void userF(void);
void userG(void);
void userH(void);
void userI(void);
void userJ(void);
void alarm(void);


void CorrectUserName(void);

/***********************************main function*************************************/

void main(void)
{

	PORT_voidInit();
	USART_u8Init(ptr);
	GIE_voidEnableGlobalInterrupt();

	/*the door is closed*/
	SERVO_u8Rotate(CHANNEL_A , 0);

		/****************start of system*******************/

		/*asking for username*/
		USART_voidSendStringSync("Hello! Enter your user name") ;

		/*waiting till the user enters username*/
		while(username == '\0')
		{
			USART_u8ReceiveCharAsync(&username , func);
		}

		if(username>= 65 && username <= 74)         //in case of correct user name
		{
			CorrectUserName();
		}

		else                                        //in case of wrong user name
 	    {
	    	/*asking to reneter username*/
	    	USART_voidSendStringSync("Wrong username , try again") ;

	    	/*resetting user name*/
	    	username = '\0' ;

	    	/*waiting till user re-enters username*/
	    	while(username == '\0')
	    	{
	    		USART_u8ReceiveCharAsync(&username , func);
	    	}

	    	if(username>= 65 && username <= 74)         //in case of correct user name
			{
				CorrectUserName();
			}

			else                                        //in case of wrong user name
	 	    {
		    	/*asking to reneter username*/
		    	USART_voidSendStringSync("Wrong username , try again") ;

		    	/*resetting user name*/
		    	username = '\0' ;

		    	/*waiting till user re-enters username*/
		    	while(username == '\0')
		    	{
		    		USART_u8ReceiveCharAsync(&username , func);
		    	}

		    	if(username>= 65 && username <= 74)         //in case of correct user name
				{
					CorrectUserName();
				}

		    	else
		    	{
		    		USART_voidSendStringSync("INVALID USERNAME");
		    		alarm();
		    	}

	 	    }

	    }

		while(1);
}


/**********************************functions' implementation******************************/

void func (void)
{
	//DIO_u8SetPinValue(DIO_u8PORTC , DIO_u8PIN0 , DIO_u8PIN_HIGH);
}

void CorrectPassAndUsername(void)
{
		/*the door opens*/
		SERVO_u8Rotate(CHANNEL_A , 180);

		/*asking for light state*/
		USART_voidSendStringSync("LEDs ON or OFF ?");

		/*waiting till user enters light state*/
		while(leds == '\0')
		{
			USART_u8ReceiveCharAsync(&leds , func) ;
		}

		/*in case of lights on*/
		if(leds == 'N')
		{
			DIO_u8SetPinValue(DIO_u8PORTC , DIO_u8PIN0 , DIO_u8PIN_HIGH);
		}

		/*in case of lights off*/
		else if(leds == 'F')
		{
			DIO_u8SetPinValue(DIO_u8PORTC , DIO_u8PIN0 , DIO_u8PIN_LOW);
		}

		/*welcome msg ^^*/
		USART_voidSendStringSync("welcome home ^^");

		_delay_ms(1000);

		/*close the door*/
		SERVO_u8Rotate(CHANNEL_A,0);

}

void userA(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '0')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '0')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '0')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}

}


void userB(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '1')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '1')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '1')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}

void userC(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '2')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '2')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '2')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}




void userD(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '3')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '3')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '3')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}

void userE(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '4')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '4')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '4')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}


void userF(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '5')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '5')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '5')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}


void userG(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '6')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '6')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '6')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}


void userH(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '7')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '7')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '7')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}


void userI(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '8')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '8')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '8')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}


void userJ(void)
{
	/*asking for password*/
	USART_voidSendStringSync("Enter ur password");

	/*waiting till user enters password*/
	while((password == '\0'))
	{
		USART_u8ReceiveCharAsync(&password , func);
	}


	/*in case of correct password*/
	if(password == '9')
	{
		CorrectPassAndUsername();
	}

	/*in case of wrong password*/
	else
	{
		/*asking to re-enter password*/
		USART_voidSendStringSync("Wrong pass , try again");

		/*resetting password value*/
		password = '\0';

		/*waiting till user enters password*/
		while((password == '\0'))
		{
			USART_u8ReceiveCharAsync(&password , func);
		}

			/*in case of correct password*/
			if(password == '9')
			{
				CorrectPassAndUsername();
			}
			else
			{
				/*asking to re-enter password*/
				USART_voidSendStringSync("Wrong pass , try again");

				/*resetting password value*/
				password = '\0';

				/*waiting till user enters password*/
				while((password == '\0'))
				{
					USART_u8ReceiveCharAsync(&password , func);
				}

				/*in case of correct password*/
				if(password == '9')
				{
					CorrectPassAndUsername();
				}

				else
				{
					USART_voidSendStringSync("INVALID PASSWORD");
					alarm();
				}
			}
	}
}

void alarm(void)
{
	u8 counter ;
	for(counter = 0 ; counter <3 ; counter++)
	{
	PWM_u8Init(CHANNEL_B,FREQUENCY_1000, 50);
	_delay_ms(1000);

	PWM_u8Init(CHANNEL_B,FREQUENCY_500  , 50);
	_delay_ms(1000);
	}
	PWM_u8Stop();

}


void CorrectUserName(void)
{
	/*in case of correct username*/
	if(username == 'A')
    {
		userA();
	}

	else if(username == 'B')
	{
		userB();
	}

	else if(username == 'C')
	{
		userC();
	}

	else if(username == 'D')
	{
		userD();
	}

	else if(username == 'E')
	{
		userE();
	}

	else if(username == 'F')
	{
		userF();
	}

	else if(username == 'G')
	{
		userG();
	}
	else if(username == 'H')
	{
		userH();
	}
	else if(username == 'I')
	{
		userI();
	}
	else if(username == 'J')
	{
		userJ();
	}

}

