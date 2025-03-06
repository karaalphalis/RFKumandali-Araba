#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

#define CE_PIN   9
#define CSN_PIN 10
#define x_axis A0 // x axis
#define y_axis A1 //y axis

int on_far = 6;

int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //LCD'nin pin değişkenlerini tanımlıyoruz.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  
int dusur = 7;    
int yukselt = 8;               


int vites_durum;
int data_far;
int data_vites;



int hiz_lcd;
int on_sensor,arka_sensor;
int arka_deger,on_deger;

const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipe1 =0xF0F0F0F0A1LL;
RF24 radio(CE_PIN, CSN_PIN); 
int data[4];  
int veri[3];
void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN); 
 radio.openWritingPipe(pipe);
  radio.openReadingPipe(1, pipe1); // bilgi alındığı adres
   lcd.begin(16, 2); 
}

void loop()   
{


  delay(5);
 radio.stopListening(); 

  data[0] = analogRead(x_axis);
  data[1] = analogRead(y_axis);
  data[2]=data_far;
  data[3]=data_vites;
  radio.write( data, sizeof(data) ); 
     Serial.println(data[0]);
     Serial.println(data[1]);

  radio.startListening(); 
  
  if(radio.available()){
      hiz_lcd = veri[0];
      arka_sensor = veri[1];
      on_sensor = veri[2];
      radio.read( veri, sizeof(veri) ); 
      
     Serial.println(arka_sensor);
     Serial.println(on_sensor);
     if((arka_sensor<50 && data[0]>600 && arka_sensor!=0 ) || (on_sensor<50 && data[0]<450 && on_sensor!=0 )  ){
      vites_dusur();
      delay(100);
     }
     if((arka_sensor<20 && data[0]>600 && arka_sensor!=0)|| (on_sensor<20 && data[0]<450 && on_sensor!=0)){
      vites_dusur();
      delay(100);
     }

  }
  else{
    Serial.println("sinyal yok");

  }

     
   
  lcd.clear();                                      
  lcd.setCursor(0, 0);                                        
  lcd.print("Vites durumu:");                                
  lcd.setCursor(14, 0);                                 
  lcd.print(data[3]); 

  lcd.setCursor(0, 1);                                        
  lcd.print("Hiz durumu:");                                
  lcd.setCursor(12, 1);                                 
  lcd.print(hiz_lcd);                     

 if(digitalRead(on_far)==1){
  
data_far=digitalRead(on_far);
  }
 if(digitalRead(on_far)==0){
  
data_far=digitalRead(on_far);
  }

 if(digitalRead(dusur)==1){
  vites_dusur();

  }
 if(digitalRead(yukselt)==1){
  vites_yukselt();

  }

}


void vites_dusur(){

  if(vites_durum==0){
    vites_durum=0;
    }
  
  else{
      vites_durum-=1;
    }
    
    delay(100);
   data_vites=vites_durum;
}

void vites_yukselt(){
     vites_durum+=1;
    if(vites_durum==4){
     vites_durum=3;
    } 

   delay(100);
  data_vites=vites_durum;
   
}
