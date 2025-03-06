/* Robimek - Robotik Sistemler
www.robimek.com */
#include <TimerOne.h>
unsigned int sayac=0;
  

void say() // sayma işlemi
{
 sayac++; // sayacı bir arttır
} 
  
void timerIsr()
{
 Timer1.detachInterrupt(); //zamanlayıcıyı durdur
 Serial.print("Motor hızı: "); 
 int devir = (sayac / 15); // buradaki 15 sayısı encoderdeki boşluk veya delik sayısıdır. Sizdeki kaç delik ise o sayıyı yazın.
 Serial.print(devir,DEC); 
 Serial.println(" Saniyedeki Devir Sayısı"); 
 sayac=0; // sayacı sıfırla
 Timer1.attachInterrupt( timerIsr ); //zamanlayıcıyı etkinleştir
}
  
void setup() 
{
 Serial.begin(9600);
  

 Timer1.initialize(1000000); // zamanlayıcıyı bir saniyeye ayarla
 attachInterrupt(0, say, RISING); // Sensör pini high olduğunda sayacı bir arttır.
 Timer1.attachInterrupt( timerIsr ); // timerIsr zamanlayıcıyı etkinleştir
} 
  
void loop()
{
 
  
}
