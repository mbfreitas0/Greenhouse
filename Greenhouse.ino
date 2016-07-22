////////////////////////////////////////////////////////////
//                                                        //
//        Trabalho de Graduação Fatec Itapetininga        //
//        Trabalho: CONTECSI - 2016                       //
//        Integrantes: Marcelo Barbosa de Freitas         //
//                     Tibério Augusto dos Santos         //
//                     Lucas Guilherme de Arruda          //
//                     Ciclo: 5º                          //
//        Data: 16/04/2016                                //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////

  #include <dht11.h>
  #include <LiquidCrystal_I2C.h>
  #include <Wire.h>
  #include "RTClib.h"
  
  RTC_DS1307 RTC;
  
  #define RELAY1 7 //pino do rele
  
  dht11 DHT; // Cria um objeto que o sensor DHT11
  
  int solo;
  String irrigacao;
  
  int dhtpin = A1; // Pino analógico em que o sensor DHT11 está conectado
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
  //LiquidCrystal_I2C lcd(0x20,16,2);
  
  void setup() {
  
    Wire.begin(); // Inicia a porta I2C
    RTC.begin(); // Inicia a comunicação com o módulo RTC
    RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
    
    Serial.begin(9600);
  
  pinMode(RELAY1, OUTPUT); 
  lcd.begin(16,2); // Define o display com 16 colunas e 2 linhas
  delay(2000);
  
  }
  
  void loop() {
  
    DateTime now = RTC.now(); // Obtem e fecha a hora do RTC
  
    solo = analogRead(A0);
    int Porcentagem = map(solo, 1023, 0, 0, 100);
    
    DHT.read(dhtpin); //Lê as informações do sensor
  
    
    if (Porcentagem <= 85  ){
  
      digitalWrite(RELAY1, LOW); // Acionando o rele
      irrigacao = "Irrigando ...";
          
    }
    else {
  
      digitalWrite(RELAY1, HIGH); // Desligando o rele
      irrigacao = "Irrigacao ->OFF";
    }
    
  
      Serial.print(irrigacao);
      Serial.print(" ");
      Serial.print(Porcentagem);
      Serial.print("%");
      Serial.print(" ");
      Serial.print("Umidade :");
      Serial.print(DHT.humidity);
      Serial.print("%");
      Serial.print(" ");
      Serial.print("Temperatura :");
      Serial.print(DHT.temperature);
      Serial.write(B11011111);
      Serial.print("\n");  
    
      /*------------------ Impressões LCD --------------*/
  
      /*------------------GREENHOUSE - AJH5-------------*/
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GREENHOUSE");
      lcd.setCursor(0,1);
      lcd.print("Estufa Agricola");
      delay(5000);
      
      /*-------------Informações de Data e Hora --------*/
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print(now.day(), DEC); 
      lcd.print('/');
      lcd.print(now.month(), DEC);
      lcd.print('/');
      lcd.print(now.year(), DEC);
      lcd.setCursor(4,1);
      lcd.print(now.hour(), DEC);
      lcd.print(':');
      lcd.print(now.minute(), DEC);
      lcd.print(':');
      lcd.print(now.second(), DEC);
      delay(5000);
      
      /*-------Informações: Solo, Umidade e Temperatura*/
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Umid. solo: ");
      lcd.print(Porcentagem);
      lcd.print(" %");
      lcd.setCursor(0,1);
      lcd.print(irrigacao);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Umidade: ");
      lcd.print(DHT.humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Temperatura: ");
      lcd.print(DHT.temperature);
      lcd.write(B11011111);
      delay(3000);
  }

