#include "reg51.h"

#define DO 65536-460800/523
#define RE 65536-460800/587
#define MI 65536-460800/659
#define FA 65536-460800/698
#define SO 65536-460800/785
#define LA 65536-460800/880
#define TI 65536-460800/998
#define DOH 65536-460800/1046
#define REH 65536-460800/1174
#define MIH 65536-460800/1318
#define FAH 65536-460800/1396
#define SOH 65536-460800/1570
#define LAH 65536-460800/1760
#define SIH 65536-460800/1996

sbit P2_3=P2^3;
sbit P3_0=P3^0;
sbit P3_4=P3^4;
sbit P3_5=P3^5;

code unsigned int BeeTone[182]=
{MIH,REH,MIH,REH,MIH,TI,REH,DOH,LA,DO,MI,LA,TI,MI,SO,TI,DO,MI,MIH,REH,MIH,    
REH,MIH,TI,REH,DOH,LA,DO,MI,LA,TI,MI,DOH,TI,LA,TI,DOH,REH,MIH,SO,FAH,MIH,
REH,FA,MIH,REH,DOH,MI,REH,DOH,TI,MI,MIH,DOH,MIH,REH,MIH,REH,MIH,REH,MIH,TI,REH,
DOH,LA,DO,MI,LA,TI,MI,SO,TI,DOH,MI,MIH,REH,MIH,REH,MIH,TI,REH,DOH,LA,DO,
MI,LA,TI,MI,DOH,TI,LA,MIH,REH,MIH,REH,MIH,TI,REH,DOH,LA,DO,MI,LA,TI,MI,SO,TI,DO,MI,MIH,REH,MIH,    
REH,MIH,TI,REH,DOH,LA,DO,MI,LA,TI,MI,DOH,TI,LA,TI,DOH,REH,MIH,SO,FAH,MIH,
REH,FA,MIH,REH,DOH,MI,REH,DOH,TI,MI,MIH,DOH,MIH,REH,MIH,REH,MIH,REH,MIH,TI,REH,
DOH,LA,DO,MI,LA,TI,MI,SO,TI,DOH,MI,MIH,REH,MIH,REH,MIH,TI,REH,DOH,LA,DO,
MI,LA,TI,MI,DOH,TI,LA};
code unsigned int BeeBeat[182]=
{1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,
1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,
1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,
1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,
1,1,2,1,1,1,2};
code unsigned int BeeTonea[65]=
{MI,MI,FA,SO,SO,FA,MI,RE,DO,DO,RE,MI,DO,MI,RE,RE,MI,MI,FA,SO,SO,
FA,MI,RE,DO,DO,RE,MI,DO,RE,DO,DO,RE,RE,MI,DO,RE,MI,FA,MI,DO,
RE,MI,FA,MI,RE,DO,RE,SO,MI,MI,FA,SO,SO,FA,MI,RE,DO,DO,RE,MI,DO,RE,DO,DO};
code unsigned int BeeBeata[65]=
{1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,
1,1,1,1,1,1,1,2,1,2};
 
unsigned int i;
unsigned int Tone;
unsigned int Beat;
unsigned int Length=5;
unsigned int TimeOut;
  
void delay();
 
void main()
{
 TMOD=0x11;
 IP=0x02;
 IE=0x8A;
 TR0=0;
 TR1=0;
 P3_0=0; 
 while(1)
 {
   if(P3_4==0){
	for(i;i<182;i++)
  {	 
	 Tone=BeeTone[i];
	 Beat=BeeBeat[i];
	 TimeOut=0;
   TR0=1;
   TR1=1;
   while(TimeOut==0);
   TR0=0;
   TR1=0;
   delay();		
	}
  delay();  
	i=0;
	P2_3=1;}
  if(P3_5==0){
	for(i;i<65;i++)
  {	 
	 Tone=BeeTonea[i];
	 Beat=BeeBeata[i];
	 TimeOut=0;
   TR0=1;
   TR1=1;
   while(TimeOut==0);
   TR0=0;
   TR1=0;
   delay();		
	}
  delay();  
	i=0;
	P2_3=1;}
 }	
}	 

void Timer0_int() interrupt 1  
{
 TH0=Tone>>8;
 TL0=Tone;	
 TR0=1;
 P2_3=!P2_3;
 
}

void Timer1_int() interrupt 3                               
{
  TH1=(65536-46080)/256;
  TL1=(65536-46080)%256;
  if(--Length==0)                                      
  {
    Length=5;                                    
    if(--Beat==0)                              
      TimeOut=1;                             
  }
}

void delay(void)                                            
{
  int i;
  for(i=0;i<20000;i++);
}