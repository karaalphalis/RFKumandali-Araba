#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define LED_BUILTIN 23
#define CE_PIN  9
#define CSN_PIN 10
#include <TimerOne.h>
//hız sensoru
unsigned int sayac=0;
  
int devir;
void say() // sayma işlemi
{
 sayac++; // sayacı bir arttır
} 
  
void timerIsr()
{
 Timer1.detachInterrupt(); //zamanlayıcıyı durdur
 devir = (sayac /20); // buradaki 15 sayısı encoderdeki boşluk veya delik sayısıdır. Sizdeki kaç delik ise o sayıyı yazın.
 sayac=0; // sayacı sıfırla
 Timer1.attachInterrupt( timerIsr ); //zamanlayıcıyı etkinleştir
}
   //Radio
const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipe1 = 0xF0F0F0F0A1LL;
RF24 radio(CE_PIN, CSN_PIN);  

int data[4];
int veri[3];
//MOTOR
int hiz;
const int Motor1_Ileri = 4;//Sağ Motor
const int Motor1_Geri = 22;
const int Motor1_PWM = 3;

const int Motor2_Ileri = 7;//Sol Motor
const int Motor2_Geri = 6;
const int Motor2_PWM = 5; 

int vites_durum_2;
int vites_durum;
int on_far;
int arka_deger,on_deger;



//mesafe sensoru
int trigPin = 13;                                        
int echoPin = 12;                                        
int sure;                                               
int arka_uzaklik;  

int trigPin2 = 11;                                        
int echoPin2 = 8;                                        
int sure2;                                               
int on_uzaklik;






void setup()   
{

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);                         
  pinMode(echoPin,INPUT);  
  pinMode(trigPin2, OUTPUT);                         
  pinMode(echoPin2,INPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Motor1_Ileri,OUTPUT);
  pinMode(Motor1_Geri,OUTPUT);
  pinMode(Motor1_PWM,OUTPUT);
  pinMode(Motor2_Ileri,OUTPUT);
  pinMode(Motor2_Geri,OUTPUT);
  pinMode(Motor2_PWM,OUTPUT);
  

Timer1.initialize(1000000); // zamanlayıcıyı bir saniyeye ayarla
 attachInterrupt(0, say, RISING); // Sensör pini high olduğunda sayacı bir arttır.
 Timer1.attachInterrupt( timerIsr ); // timerIsr zamanlayıcıyı etkinleştir

  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(pipe1);
  radio.openReadingPipe(1, pipe); // bilgi alındığı adres
  
}


void loop() {

  digitalWrite(trigPin, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH, 11600);     
  
  arka_uzaklik= sure*0.0345/2;  
  digitalWrite(trigPin2, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  sure2 = pulseIn(echoPin2, HIGH, 11600);                
  on_uzaklik= sure2*0.0345/2; 



  Serial.print("RPM = ");
  Serial.println(devir);
  Serial.println(arka_uzaklik);
  Serial.println(on_uzaklik);


  delay(5);

   radio.stopListening();
   
   veri[0]=devir;
   veri[1]=arka_uzaklik;
   veri[2]=on_uzaklik;
   radio.write( veri, sizeof(veri) );

   radio.startListening(); 
  if ( radio.available() ) //Eğer sinyal algılarsan...
  { 
   int x = data[0];
   int y = data[1];
    on_far = data[2];
   vites_durum = data[3];  
   
   radio.read( data, sizeof(data) ); 
    


//vitesler
if(vites_durum>vites_durum_2 || vites_durum<vites_durum_2){
  
   vites_durum_2 = vites_durum;

if(vites_durum==0 ){
hiz=0;
}

if(vites_durum==1){
hiz=85;
}

if(vites_durum==2){
hiz=170;
}

if(vites_durum==3){
hiz=255;
}

}
if(on_far==0){
   digitalWrite(LED_BUILTIN, LOW);
}
          if(on_far==1){
   digitalWrite(LED_BUILTIN, HIGH);
}
   if((y >= 400 && y <= 600)&&(x >= 400 && x <= 600)) {
    
     digitalWrite(Motor1_Ileri,LOW);
    digitalWrite(Motor1_Geri,LOW);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,LOW);
    digitalWrite(Motor2_Geri,LOW);
    analogWrite(Motor2_PWM,hiz);
    }
     if(y >= 800 && y <= 1023) {
  

     digitalWrite(Motor1_Ileri,LOW);
    digitalWrite(Motor1_Geri,HIGH);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,LOW);
    digitalWrite(Motor2_Geri,HIGH);
    analogWrite(Motor2_PWM,hiz);
    }
    if(y >= 0 && y <= 450) {
 

     digitalWrite(Motor1_Ileri,HIGH);
    digitalWrite(Motor1_Geri,LOW);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,HIGH);
    digitalWrite(Motor2_Geri,LOW);
    analogWrite(Motor2_PWM,hiz);
    }

    //ileri
    if(x >= 0 && x <= 450) {


     digitalWrite(Motor1_Ileri,LOW);
    digitalWrite(Motor1_Geri,HIGH);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,HIGH);
    digitalWrite(Motor2_Geri,LOW);
    analogWrite(Motor2_PWM,hiz);
    
    }
    
   if(x >= 600 && x <= 1023) {
     digitalWrite(Motor1_Ileri,HIGH);
    digitalWrite(Motor1_Geri,LOW);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,LOW);
    digitalWrite(Motor2_Geri,HIGH);
    analogWrite(Motor2_PWM,hiz);
    }
    
    // ileri giderken dön
 if((x >= 0 && x <= 450)&& ((y >= 0 && y <= 450)|| (y >= 800 && y <= 1023) )) {
  

   if(y >= 0 && y <= 450){
    digitalWrite(Motor1_Ileri,LOW);
    digitalWrite(Motor1_Geri,HIGH);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,HIGH);
    digitalWrite(Motor2_Geri,LOW);
    analogWrite(Motor2_PWM,hiz/5);
     }
   if(y >= 800 && y <= 1023){
    digitalWrite(Motor1_Ileri,LOW);
    digitalWrite(Motor1_Geri,HIGH);
    analogWrite(Motor1_PWM,hiz/5);
    digitalWrite(Motor2_Ileri,HIGH);
    digitalWrite(Motor2_Geri,LOW);
    analogWrite(Motor2_PWM,hiz);
     }
     
    }

  if((x >= 600 && x <= 1023)&& ((y >= 0 && y <= 450)|| (y >= 800 && y <= 1023) )) {
       if(y >= 0 && y <= 450){
    digitalWrite(Motor1_Ileri,HIGH);
    digitalWrite(Motor1_Geri,LOW);
    analogWrite(Motor1_PWM,hiz);
    digitalWrite(Motor2_Ileri,LOW);
    digitalWrite(Motor2_Geri,HIGH);
    analogWrite(Motor2_PWM,hiz/5);
       }
       if(y >= 800 && y <= 1023){
    digitalWrite(Motor1_Ileri,HIGH);
    digitalWrite(Motor1_Geri,LOW);
    analogWrite(Motor1_PWM,hiz/5);
    digitalWrite(Motor2_Ileri,LOW);
    digitalWrite(Motor2_Geri,HIGH);
    analogWrite(Motor2_PWM,hiz);
        
       }
      
     }
 
  }
 

  

      
 
}
