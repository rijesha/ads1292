#include "morse.h"
#include "ads1292r.h"

#include "config.h"
#include "gpsParser.h"


MyParser parser;
unsigned long time;

// MORSE //
char MorseCode[] = "VA6RJA";

// Create variable to define the output pins
//int led13 = 1;      // blink an led on output 1
int led5 = 5;        // blink an led on output 6
int ledArray[] = {led5};
Morse m(ledArray, sizeof(ledArray));
int count = 0;

// ADC //
ads1292r ADS1292;
 
volatile int datalen = 135;

volatile byte SPI_RX_Buff[150];
volatile static int SPI_RX_Buff_Count = 0;
volatile char *SPI_RX_Buff_Ptr;
volatile int Responsebyte = false;
volatile int32_t chan1, chan2;
volatile byte DataPacket[9];

unsigned long Time1;
unsigned long Time2;
unsigned long StartTime;

void setup() {
  Serial1.begin(57600);
  Serial3.begin(57600);
  
  setup_Morse();
  setup_ADS1292();
  time = millis();
}

void setup_Morse(){
  Serial.begin(57600);
  
  // initialize the digital pin as an output for LED lights.
  //pinMode(led13, OUTPUT);
  pinMode(led5, OUTPUT);

  //Send Morse
  m.sendMorse(MorseCode, sizeof(MorseCode));
  
}

void setup_ADS1292(){
  //Initialize ADS1292 Pins
  pinMode(ADS1292_DRDY_PIN, INPUT);
  pinMode(ADS1292_CS_PIN, OUTPUT);
  pinMode(ADS1292_START_PIN, OUTPUT);
  pinMode(ADS1292_PWDN_PIN, OUTPUT);

  ADS1292.ads1292_Init();
  ADS1292.ads1292_Reg_Read_All();
  ADS1292.ads1292_Offset_Calib();
  delay(1000);
  ADS1292.ads1292_Reg_Read_All();
  ADS1292.start();
  
  Time1 = millis();
  StartTime = millis();
  Serial.flush();
  Serial3.flush();
  
  
  DataPacket[0] = 20; //Start Byte
  DataPacket[1] = 6;  // Type/length of packet
  DataPacket[8] = 19; //End Byte
}

// Create a loop of the letters/words you want to output in morse code (defined in string at top of code)
void loop()
{
  GPS_loop();
  ADS1292_loop();
}

void GPS_loop() {
  if (Serial1.available()) {
    parser.parse(Serial1.read());
    //Serial.println(micros()-time);
  }
}

void ADS1292_loop() {
  volatile int i;

  if((digitalRead(ADS1292_DRDY_PIN)) == LOW)
  {  
    SPI_RX_Buff_Ptr = ADS1292.ads1292_Read_Data();
    for(i = 0; i < 9; i++)
    {
      SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);
    }
  }
    
  if(SPI_RX_Buff_Count >= 9)
  {
    DataPacket[2] = SPI_RX_Buff[3];
    DataPacket[3] = SPI_RX_Buff[4];
    DataPacket[4] = SPI_RX_Buff[5]; 
    
    DataPacket[5] = SPI_RX_Buff[6];            // 4 bytes Respiration data
    DataPacket[6] = SPI_RX_Buff[7];
    DataPacket[7] = SPI_RX_Buff[8];

    #ifdef ENABLE_RADAR
    #ifdef DEBUG_RADAR
    chan1 = (((uint32_t)SPI_RX_Buff[3] << 24) | ((uint32_t)SPI_RX_Buff[4] << 16) | ((uint32_t)SPI_RX_Buff[5] << 8)) >> 8; 
    chan2 = (((uint32_t)SPI_RX_Buff[6] << 24) | ((uint32_t)SPI_RX_Buff[7] << 16) | ((uint32_t)SPI_RX_Buff[8] << 8)) >> 8; 
    Serial.println(chan1);
    Serial3.println(chan1);
    #else
    for (byte b : DataPacket) {
      Serial.write(b);
      Serial3.write(b);
    }
    #endif
    #endif

    SPI_RX_Buff_Count = 0; 
   }
}
