/*
 * Control LED 7 segment 2 digits COMMON ANODE by MAX7219 chip
 * With SPI chip communication
 * By: Tran Ngoc Tien 2019
 */
#include <SPI.h>

const int slaveSelect= 10; //pin used to enable the active slave

const int numberofDigits= 2;

const int maxCount= 99;
#define DECODE_MODE   0x09                       
#define INTENSITY     0x0a                        
#define SCAN_LIMIT    0x0b                        
#define SHUTDOWN      0x0c                        
#define DISPLAY_TEST  0x0f   

// standard 7 seg display numbers
byte number_seg[]=
{
  0b00111111,  // 0 
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5  
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111   // 9
};

byte display_num[4];  // array to hold our 4 digits

int number=0;


void setup()
{
  Serial.begin(9600); 
  
  pinMode(slaveSelect, OUTPUT);
  SPI.begin(); //initialize SPI
  
  Serial.println("TienTN: SPI inited");
  
  // Disabled BCD mode
  sendCommand(DECODE_MODE, 0x00); //decode command, if 0x0F use standard 7-segment digits
  
  //prepare the 7219 to display 7-segment data
  sendCommand (SCAN_LIMIT, 0x07); //in default MAX7219 behaviour, this is for digits block
  sendCommand (INTENSITY,0xF); //set max intensity (range is 0-15)
  sendCommand (SHUTDOWN,0x01); //normal mode (default is shutdown mode)
  
  sendCommand (DISPLAY_TEST,0x00); //Display test off

}


void loop(){

  //display from 0 to 100 between delay
  for (int i = 0; i < 100; i++) {
    displayNumber(i);
    delay(1000);
  }

}

void manualBitDisplay(byte num1, byte num2) {

   display_num[0] = num1;
   display_num[1] = num2;

   for (byte each_segment=1;each_segment<=8;each_segment++)
   {
     // build the byte to send 
     byte output=0b00000000;

     for (byte digits = 0; digits < 4; digits++)
     {
      
      byte number_to_display = display_num[digits];  
    
     // for out chosen number to display get it's segment bit at the position current position of 'each_segment'
      bool seg= number_seg[number_to_display] & (0b00000001 << (each_segment-1) );
   
      //we shift to skip unused digits block
       output = output | (seg << (digits+5));
      
     }

     sendCommand ( each_segment, output);
  }
  
}

void displayNumber (int number)
{
  byte n1, n2;
  n2 = number % 10; //get the value of the rightmost digit
  n1 = (number / 10) % 10;

  manualBitDisplay(n2, n1);
}

void sendCommand(uint8_t address, uint8_t value) 
{
  // Ensure LOAD/CS is LOW
  digitalWrite(slaveSelect, LOW);

  // Send the register address
  SPI.transfer(address);

  // Send the value
  SPI.transfer(value);

  // Tell chip to load in data
  digitalWrite(slaveSelect, HIGH);
}
