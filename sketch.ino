#include <LiquidCrystal.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

LiquidCrystal lcd(7,6,5,4,3,2);
DHT dht(8, DHT22);

// LEDs
#define RED 9
#define GREEN 10
#define BLUE 11
#define LED_SD A4

#define BUZZER 12
#define BTN_RESET 13
#define BTN_REPORT A0

#define SD_CS A2
#define LDR A1

File arquivo;

// CONTADORES
int contBom=0, contChuva=0, contFrio=0, contSeco=0, contNublado=0;
String climaAtual="";
String climaAnterior="";
unsigned long debounce=0;
bool mostrarRelatorio=false;

// ===== ICONES LCD =====
byte iconSol[8]   ={B00100,B10101,B01110,B11111,B01110,B10101,B00100,B00000};
byte iconChuva[8] ={B00000,B01110,B11111,B11111,B00000,B01010,B00100,B01010};
byte iconFrio[8]  ={B00100,B01010,B00100,B11111,B00100,B01010,B00100,B00000};
byte iconSeco[8]  ={B00100,B00100,B10101,B01110,B10101,B00100,B00100,B00000};
byte iconLua[8]   ={B00110,B01100,B11000,B11000,B11000,B01100,B00110,B00000};
byte iconSolPeq[8]={B00100,B10101,B01110,B11111,B01110,B10101,B00100,B00000};

// 🔔 BUZZERS
void beepInicial(){
  tone(BUZZER,1200,200); delay(300);
  tone(BUZZER,1500,200);
}
void beepMudanca(){ tone(BUZZER,1000,200); }

// BARRA CARREGAMENTO
void loadingBar(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Iniciando dados");
  lcd.setCursor(0,1);
  lcd.print("[              ]");

  for(int i=1;i<=14;i++){
    lcd.setCursor(i,1);
    lcd.print("#");
    tone(BUZZER,900,40);
    delay(180);
  }
  lcd.clear();
  lcd.print("Sistema pronto!");
  delay(1500);
}

// RESET TOTAL
void resetTotal(){
  contBom=contChuva=contFrio=contSeco=contNublado=0;
  climaAnterior="";
  SD.remove("clima.txt");
  lcd.clear();
  lcd.print("MEMORIA APAGADA");
  tone(BUZZER,1500,400);
  delay(2000);
}

// DESLIGA LEDS
void ledsOff(){
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
}

// EFEITOS LEDS
void efeitoChuva(){
  digitalWrite(BLUE,HIGH); delay(300);
  digitalWrite(BLUE,LOW); delay(300);
}
void efeitoNublado(){
  digitalWrite(RED,HIGH); delay(250);
  digitalWrite(RED,LOW);
  digitalWrite(BLUE,HIGH); delay(250);
  digitalWrite(BLUE,LOW);
}

void setup(){
  lcd.begin(16,2);
  dht.begin();

  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(LED_SD,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BTN_RESET,INPUT_PULLUP);
  pinMode(BTN_REPORT,INPUT_PULLUP);

  lcd.createChar(0,iconSol);
  lcd.createChar(1,iconChuva);
  lcd.createChar(2,iconFrio);
  lcd.createChar(3,iconSeco);
  lcd.createChar(4,iconLua);
  lcd.createChar(5,iconSolPeq);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Projeto Sistema");
  lcd.setCursor(0,1);
  lcd.print("Clima");
  beepInicial();
  delay(2000);

  loadingBar();
  SD.begin(SD_CS);
}

void loop(){

  if(digitalRead(BTN_RESET)==LOW && millis()-debounce>400){
    debounce=millis();
    resetTotal();
  }

  mostrarRelatorio = digitalRead(BTN_REPORT)==LOW;

  float umidade=dht.readHumidity();
  float temp=dht.readTemperature();

  int luz = analogRead(LDR);
  bool dia = luz > 500;

  // CLASSIFICA CLIMA
  if(temp<=12) climaAtual="FRIO";
  else if(umidade>=70 && temp<26) climaAtual="CHUVA";
  else if(temp>=33 && umidade<50) climaAtual="SECO";
  else if(temp>=20 && temp<=30 && umidade>=50 && umidade<=70) climaAtual="BOM";
  else climaAtual="NUBLADO";

  // SE CLIMA MUDOU → BUZZER + CONTADOR
  if(climaAtual!=climaAnterior){
    beepMudanca();
    if(climaAtual=="BOM") contBom++;
    if(climaAtual=="CHUVA") contChuva++;
    if(climaAtual=="FRIO") contFrio++;
    if(climaAtual=="SECO") contSeco++;
    if(climaAtual=="NUBLADO") contNublado++;
    climaAnterior=climaAtual;
  }

  // GRAVA NO SD
  digitalWrite(LED_SD,HIGH);
  arquivo=SD.open("clima.txt",FILE_WRITE);
  if(arquivo){
    arquivo.print("Temp:");
    arquivo.print(temp);
    arquivo.print(" Umid:");
    arquivo.print(umidade);
    arquivo.print(" Clima:");
    arquivo.println(climaAtual);
    arquivo.close();
  }
  digitalWrite(LED_SD,LOW);

  // RELATÓRIO
  if(mostrarRelatorio){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bom:");
    lcd.print(contBom);
    lcd.print(" Ch:");
    lcd.print(contChuva);
    lcd.setCursor(0,1);
    lcd.print("Fr:");
    lcd.print(contFrio);
    lcd.print(" Se:");
    lcd.print(contSeco);
    delay(1000);
    return;
  }

  ledsOff();
  if(climaAtual=="BOM") digitalWrite(GREEN,HIGH);
  else if(climaAtual=="SECO") digitalWrite(RED,HIGH);
  else if(climaAtual=="FRIO") digitalWrite(BLUE,HIGH);
  else if(climaAtual=="CHUVA") efeitoChuva();
  else if(climaAtual=="NUBLADO") efeitoNublado();

  // LCD NORMAL
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temp,1);
  lcd.print(" U:");
  lcd.print(umidade,0);
  lcd.print("%");

  lcd.setCursor(15,0);
  if(dia) lcd.write(byte(5));
  else lcd.write(byte(4));

  lcd.setCursor(0,1);
  if(climaAtual=="BOM") lcd.write(byte(0));
  else if(climaAtual=="CHUVA") lcd.write(byte(1));
  else if(climaAtual=="FRIO") lcd.write(byte(2));
  else if(climaAtual=="SECO") lcd.write(byte(3));
  lcd.print(" ");
  lcd.print(climaAtual);

  delay(2000);
}