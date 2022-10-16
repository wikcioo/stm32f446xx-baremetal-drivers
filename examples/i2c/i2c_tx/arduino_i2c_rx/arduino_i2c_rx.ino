// Wire Slave Receiver
//Uno, Ethernet A4 (SDA), A5 (SCL)
#include <Wire.h>
#define MY_ADDR   0x68

void setup()
{
  Serial.begin(9600);
  
  // Start the I2C Bus as Slave on address 0X68
  Wire.begin(MY_ADDR); 
  
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  uint8_t message[50];
  sprintf(message,"Slave is ready : Address %#X",MY_ADDR);
  Serial.println((char*)message);  
  Serial.println("Waiting for data from master");  
}

void loop(void)
{
}

void receiveEvent(int bytes) 
{
  static char rx_buffer[32];
  static uint32_t cnt = 0;
  while( Wire.available())
  {
    rx_buffer[cnt++] = Wire.read();
  }
  rx_buffer[cnt] = '\0';
  cnt=0;
  Serial.print("Received:");  
  Serial.print((char*)rx_buffer);  
}
