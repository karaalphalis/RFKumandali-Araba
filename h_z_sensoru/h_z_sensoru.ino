
int data[3];
//mesafe sensoru
int trigPin = 7;                                        
int echoPin = 6;                                        
int sure;                                               
int uzaklik;  

int trigPin2 = 9;                                        
int echoPin2 = 8;                                        
int sure2;                                               
int uzaklik2;

// Hız sensorü
int encoder_pin = 22; // modülden sinyal çıkış pini
unsigned int rpm; // rpm tutan veri
volatile byte pulses; // sinyal sayısı
unsigned long timeold;
// devir başına sinyal sayısı
// kodlayıcı diskinize göre
unsigned int pulsesperturn = 20;
void counter()
{
   //sayımı arttır
   pulses++;
}
void setup()
{

Serial.begin(9600);
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
}
void loop()
{  


  digitalWrite(trigPin, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH, 11600);                
  uzaklik= sure*0.0345/2;  

  digitalWrite(trigPin2, LOW);                         
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  sure2 = pulseIn(echoPin2, HIGH, 11600);                
  uzaklik2= sure2*0.0345/2;  
   if (millis() - timeold >= 1000) {
      //Hesaplamalar sırasında kesintileri işlemeyin
      detachInterrupt(0);
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
      timeold = millis();
      pulses = 0;
     
      //Kesinti işlemeyi yeniden başlatın
      attachInterrupt(0, counter, FALLING);

      
      
   }

   data[0]=rpm;
   data[1]=uzaklik;
   data[2]=uzaklik2;



    Serial.print("RPM = ");
      Serial.println(rpm);
   Serial.println(uzaklik);
   Serial.println(uzaklik2);
   delay(100);
}
