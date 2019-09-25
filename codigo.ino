#include <SoftwareSerial.h>

#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#include <EEPROM.h>

#include <Keypad.h>

SoftwareSerial SIM800(8, 9); // Configura el puerto serial para el SIM800



Servo servo1,servo2,servo3;
  int value=0;
  int value1=0;
  int value2=0;
 int j=0,f=0,w=0,k=0;
 int contador=0;
 int contador1=0;
const byte filas=3;
const byte columnas=3;
char keys[filas][columnas]=  //crear el teclado como en fisico
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
  
};
byte filpins[filas]={7,6,5};  //pines para las filas 1234
byte colpins[columnas]={4,3,2};  //pines para las columnas ABCD

//crea y nombra el teclado
Keypad teclado=Keypad(makeKeymap(keys),filpins,colpins,filas,columnas);


LiquidCrystal_I2C lcd(0x3F,16,2); 


char pss1[10],pss2[10],pss3[10],pss4[10],tecla;
int led=15;
int ledazul=14;
int buzzer=10;
int sensor=16;





void setup()
{
  
   SIM800.begin(19200); //Configura velocidad del puerto serie para el SIM800
  Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  Serial.println("OK");
   pinMode(led,OUTPUT);
   pinMode(ledazul,OUTPUT);
    pinMode(sensor,INPUT);
     pinMode(buzzer,OUTPUT);
   servo1.attach(11);
   servo2.attach(12);
   servo3.attach(13);
   
    servo1.write(0);
   servo2.write(0);
   servo3.write(0);

   menu();


}

void loop()
{
  
  
  tecla = teclado.waitForKey();
   noTone(10);  
  tone(10, 523, 300);
  delay(300);
  
 

  switch (tecla) {
   
    case '1': 
       administrador();
       break;



   
    case '2': 
  
  char  picatoste = EEPROM.read(0);
 //bucle para ingresar contraseña
  while(f==0)
  {
    //pide que ingreses la contraseña
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("PASSWORD");
    lcd.setCursor(6,1);
    for(j=0;j<=3;j++)
    {
       pss2[j]=teclado.waitForKey();
        noTone(10);  
   tone(10, 523, 300);
  delay(300);
       lcd.print("*");
       EEPROM.write(1,pss2[j]-48);
       Serial.print(pss2[j]);
       
       
       Serial.println(EEPROM.read(1));
 }
    delay(50);
     //verifica los caracteres correctos
    w=0;
    for(k=0;k<=3;k++)
    {
      char colin = EEPROM.read(1);
      if( picatoste==colin)
      {
        w++;
    }
    }
   //compara la contraseña original vs la ingresada
    if(w==4)
    {
      lcd.clear();
      digitalWrite(led,HIGH);
      lcd.setCursor(2,0);
      lcd.print("PASS CORRECTO");
      lcd.setCursor(0,1);
      lcd.print("ACCESO PERMITIDO");
      delay(3000);
      lcd.clear();
      digitalWrite(led,LOW);
      delay(1500);
        lcd.clear();
     lcd.print("ABRIENDO CAJA....");
    servo1.write(90);
    delay(500);
   servo2.write(90);
   delay(500);
   servo3.write(90);
      delay(500);
 
     mensaje();
   
       break;
      }
   
   
    else
    {
     contador++;
     Serial.print(contador);
     
     
       if (contador==3){
         
      digitalWrite(ledazul,HIGH);
      delay(3000);
      lcd.clear();
      
  
        llamar();
        break;
      }
     
     
     for( int x = 1; x <= 10; x++ )
  {
  noTone(10);			
  tone(10, 44, 200);
  delay(200);      
} 
      lcd.clear(); 
       digitalWrite(ledazul,HIGH);
      lcd.setCursor(1,0);
      lcd.print("ERROR DE CODIGO");
      lcd.setCursor(0,1);
      lcd.print("INTENTE DE NUEVO");
           delay(3000);
        digitalWrite(ledazul,LOW);
      delay(2000);
    }
    
    
    
    }
    
    

  }
  
}

    void menu(void) {
        digitalWrite(ledazul,LOW);
          digitalWrite(led,LOW);
        lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Admin:  Press 1");
  lcd.setCursor (0,1);
  lcd.print ("User :  Press 2");
     
    }
 
 
  void cerrar(void){

    char  picatoste = EEPROM.read(0);
    
     lcd.clear();
  
    lcd.print(" CERRAR PUERTA");
   
      delay(3000);
    
  while(f==0)
  {
    //pide que ingreses la contraseña
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("PASSWORD");
    lcd.setCursor(6,1);
    for(j=0;j<=3;j++)
    {
       pss2[j]=teclado.waitForKey();
        noTone(10);  
     tone(10, 523, 300);
      delay(300);
       lcd.print("*");
       EEPROM.write(1,pss2[j]-48);
       Serial.print(pss2[j]);
       Serial.println(EEPROM.read(1));
 }
    delay(50);
     //verifica los caracteres correctos
    w=0;
    for(k=0;k<=3;k++)
    {
      char colin = EEPROM.read(1);
      if( picatoste==colin)
      {
        w++;
    }
    }
   //compara la contraseña original vs la ingresada
    if(w==4)
    {
      lcd.clear();
      digitalWrite(led,HIGH);
      lcd.setCursor(2,0);
      lcd.print("PASS CORRECTO");
      lcd.setCursor(0,1);
      lcd.print("ACCESO PERMITIDO");
      delay(3000);
      lcd.clear();
      digitalWrite(led,LOW);
      delay(1500);
        
          lcd.clear();
     lcd.print("CERRANDO CAJA....");
    servo1.write(0);
    delay(500);
   servo2.write(0);
   delay(500);
   servo3.write(0);
      delay(500);
 
          menu();
       break; 
    
            
      }
    else
   {
     contador1++;
     
     if (contador1==3){
      
       digitalWrite(ledazul,HIGH);
      delay(3000);
   
        llamar();
             break;
      }
     
     for( int x = 1; x <= 10; x++ )
{
  noTone(10);			
  tone(10, 44, 200);
  delay(200);      
} 
      lcd.clear(); 
       digitalWrite(ledazul,HIGH);
      lcd.setCursor(1,0);
      lcd.print("ERROR DE CODIGO");
      lcd.setCursor(0,1);
      lcd.print("INTENTE DE NUEVO");
           delay(3000);
       digitalWrite(ledazul,LOW);
      delay(2000);
    }
    }
  }




void crear (void) {
  int i=0;
    //Primero se crea un password
  lcd.setCursor(1,0);
  lcd.print("CREAR PASSWORD");
  lcd.setCursor(2,1);
  lcd.print("DE 4 DIGITOS");
  delay(4500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CAPTURAR  CODIGO");
  lcd.setCursor(6,1);
for(i=0;i<=3;i++)
  {
    pss1[i]=teclado.waitForKey();
    lcd.print("*");
       noTone(10);  
  tone(10, 523, 300);
  delay(300);  
    delay(100);
    EEPROM.write(0,pss1[i]-48);
    Serial.print(pss1[i]);
    Serial.println(EEPROM.read(0));
    }
     menu();


}





 void administrador(void){
  int j=0,f=0,w=0,k=0;
     //pide que ingreses la contraseña
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("ADMINISTRADOR");
    lcd.setCursor(6,1);
    for(j=0;j<=3;j++)
    {
       pss2[j]=teclado.waitForKey();
          noTone(10);  
  tone(10, 523, 300);
  delay(300);
       lcd.print("*");
       EEPROM.write(1,pss2[j]-48);
       Serial.print(pss2[j]);
       Serial.println(EEPROM.read(1));
 }
    delay(50);
     //verifica los caracteres correctos
    w=0;
    for(k=0;k<=3;k++)
    {
      char colin = EEPROM.read(1);
      char picatoste = EEPROM.read(0);
      if( picatoste==colin)
      {
        w++;
    }
    }
    if (w == 4) {
       crear();
       
       }
       else {
for( int x = 1; x <= 10; x++ )
{
  noTone(10);			
  tone(10, 44, 200);
  delay(200);      
} 
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("ERROR");
        lcd.setCursor(4,1);
        lcd.print("PASSWORD");
        delay(3000);
        administrador();
        
       }
 }
 
 
 void llamar()
{
  lcd.clear();
  lcd.print("ERROR DE INTENTOS");
      lcd.setCursor(0,1);
      lcd.print(" CAJA BLOQUEDA.");
      
  Serial.println("Realizando llamada...");
  SIM800.println("ATD3006867316;"); //Comando AT para realizar una llamada
  delay(20000); // Espera 2 segundos mientras realiza la llamada
  SIM800.println("ATH"); // Cuelga la llamada
  delay(10000);
  Serial.println("Llamada finalizada");
  delay(1000);
menu();

}

void mensaje()
   {
   
      Serial.println("Enviando SMS...");
      SIM800.print("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
      delay(1000);
      SIM800.println("AT+CMGS=\"3006867316\"");  //Numero al que vamos a enviar el mensaje
      delay(1000);
      SIM800.println("!caja fuerte abierta!!.");  // Texto del SMS
      delay(100);
      SIM800.println((char)26); //Comando de finalización ^Z
      delay(100);
      SIM800.println();
      delay(5000);  // Esperamos un tiempo para que envíe el SMS
      Serial.println("SMS enviado");
  
      cerrar();
   }
 
 
