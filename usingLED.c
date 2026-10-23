#include<reg51.h>
void UART_init(void);
void trans(unsigned char);
unsigned char receive(void);
void UART_string(unsigned char *);
sbit led=P1^1;
void main()
{
	unsigned char x;
	UART_init();
	led=0;
	while(1)
	{
		x=receive();
		trans(x);
		if((x>='0')&&(x<='9'))
		{
			UART_string("led is ON");
			led=1;
		}
		else if((x>='A')&&(x<='Z'))
		{
			UART_string("led is OFF");
			led=0;
		}
	}
}
void UART_init(void)
{
	TMOD=0X20;
	TH1=0XFD;
	TR1=1;
	SCON=0X50;
}
void trans(unsigned char c)
{
	SBUF=c;
	while(TI==0);
	TI=0;
}
unsigned char receive(void)
{
	while(RI==0)
		RI=0;
	return SBUF;
}
void UART_string(unsigned char *p)
{
	while(*p!='\0')
	{
		trans(*p);
		p++;
	}
}
