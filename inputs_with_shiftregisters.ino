#include <SPI.h>

unsigned long lm = 0;

byte Output0;
byte Output1;
byte Check0 = 1;
byte Check1 = 1;
int j, k;
const byte LATCH = 10;

void setup()
{
  Output0 = 0;
  Output1 = 0;
  pinMode(LATCH, OUTPUT);//latch
  pinMode(2, INPUT);//Input from buttons
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
  digitalWrite(LATCH, LOW);
  SPI.transfer(255);
  SPI.transfer(255);
  SPI.transfer(Output1);
  SPI.transfer(Output0);
  digitalWrite(LATCH, HIGH);
  Serial.begin(9600);
  attachInterrupt(0, pin_read, RISING);
  pinMode(7, OUTPUT);
}//setup

void loop()
{
}//loop

void pin_read()
{
  for (j = 0; j < 50; j++)
    delayMicroseconds(1000);
  Check0 = 1;
  Check1 = 1;
  for (j = 0; j < 8; j++)
  {
    digitalWrite(LATCH, LOW);
    SPI.transfer(Check1);
    SPI.transfer(Check0);
    SPI.transfer(Output1);
    SPI.transfer(Output0);
    digitalWrite(LATCH, HIGH);
    delayMicroseconds(500);
    if (digitalRead(2) == HIGH)
    {
      //bitWrite(Output0, j, !(bitRead(Output0, j) == 1)); //dig check
      //bitWrite(Output1, j, !(bitRead(Output1, j) == 1)); //dig check
      bitWrite(Output1, j, !(bitRead(Output1, j) == 1)); //dig check
    }
    Check1 = Check1 << 1;
  }//j
  for (k = 0; k < 8; k++)
  {
    digitalWrite(LATCH, LOW);
    SPI.transfer(Check1);
    SPI.transfer(Check0);
    SPI.transfer(Output1);
    SPI.transfer(Output0);
    digitalWrite(LATCH, HIGH);
    delayMicroseconds(500);
    if (digitalRead(2) == HIGH)
    {
      bitWrite(Output0, k, !(bitRead(Output0, k) == 1)); //dig check
    }
    Check0 = Check0 << 1;
  }//k
  digitalWrite(LATCH, LOW);
  SPI.transfer(255);
  SPI.transfer(255);
  SPI.transfer(Output1);
  SPI.transfer(Output0);
  digitalWrite(LATCH, HIGH);
  while (digitalRead(2) == HIGH)
    ;
}//pin_read

