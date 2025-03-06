
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN  9
#define CSN_PIN 10
const uint64_t pipe1 = 0xF0F0F0F0A1LL;
RF24 radio(CE_PIN, CSN_PIN);

int veri[3];
//mesafe sensoru
int trigPin = 7;                                        
int echoPin = 6;                                        
int sure;                                               
int arka_uzaklik;  

int trigPin2 = 5;                                        
int echoPin2 = 4;                                        
int sure2;                                               
int on_uzaklik;

int arka_deger,on_deger;

// Hız sensorü
int encoder_pin = 2; // modülden sinyal çıkış pini
unsigned int rpm; // rpm tutan veri
volatile byte pulses; // sinyal sayısı
unsigned long timeold;
// devir başına sinyal sayısı
// kodlayıcı diskinize göre
unsigned int pulsesperturn = 12;
void counter()
{
   //sayımı arttır
   pulses++;
}
void setup() {
  // 9600 baud hızında seri iletişim başlatıldı.
  Serial.begin(9600);
  radio.begin();
  pinMode(encoder_pin, INPUT);
   //Interrupt 0 is digital pin 2
   //boşlukta tetikleme olur (YÜKSEK'ten DÜŞÜK'e değiştirin)
   attachInterrupt(0, counter, FALLING);
   // başlat
   pulses = 0;
   rpm = 0;
   timeold = 0;

   //mesafe sensorleri
  pinMode(trigPin, OUTPUT);                         
  pinMode(echoPin,INPUT);  
  pinMode(trigPin2, OUTPUT);                         
  pinMode(echoPin2,INPUT);  
  
  radio.setPALevel(RF24_PA_MIN); 
  radio.openWritingPipe(pipe1);
  radio.stopListening();
}

void loop() {

  digitalWrite(trigPin, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH, 11600);     

  digitalWrite(trigPin2, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  sure2 = pulseIn(echoPin2, HIGH, 11600);                
  on_uzaklik= sure2*0.0345/2;  
  arka_uzaklik= sure*0.0345/2;  
  if(arka_uzaklik<20){
    arka_deger=1;
  }
  else{
  arka_deger=0;
  }
  if(on_uzaklik<20){
    on_deger=1;
  }
  else{
  on_deger=0;
  }
  
  
   if (millis() - timeold >= 1000) {
      //Hesaplamalar sırasında kesintileri işlemeyin
      detachInterrupt(0);
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
      timeold = millis();
      pulses = 0;
     
      //Kesinti işlemeyi yeniden başlatın
      attachInterrupt(0, counter, FALLING);
   }

   delay(100);
   radio.stopListening();
   veri[0]=rpm;
   veri[1]=arka_deger;
   veri[2]=on_deger;
   radio.write( veri, sizeof(veri) ); 

   /*for(int deger=0;deger<3;deger++){
    Serial.print(dizi[deger]);
   delay(1000);

   }*/



}
