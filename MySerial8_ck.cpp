#include "MySerial8_ck.h"


MySerial8_ck::MySerial8_ck(){}


////////////////////////// Transmitter functions
void MySerial8_ck::begin_t(unsigned int bitTime, unsigned int lineUpTime){
  _bit_time = bitTime;
  _line_up_time = lineUpTime;
  PORTB &= ~1;
  DDRB |= 1;
  PORTD = 0;
  DDRD = 0b11111111;
}


void MySerial8_ck::transmit(byte _buf[255], int byteTotal){
  //Arm the receiver
  PORTB |= 1;
  delayMicroseconds(_line_up_time);

  byte _bits = 0;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr++){
    //Compile the data
    if(byteCntr == -1){
      _bits = byteTotal;
    }
    else{
      _bits = _buf[byteCntr];
    }

    //Transmit the data
    PORTD = _bits;
    PORTB ^= 1;  // Data first so that
                 // when clock comes
                 // through, data will
                 // already be ready
    delayMicroseconds(_bit_time);

  }
  // Make sure the transmitter always ends low
  PORTB &= ~1;
  PORTD = 0;

}
////////////////////////// Transmitter functions






////////////////////////// Receiver functions
void MySerial8_ck::begin_r(){
  DDRD = 0;  // Set port d as input
  DDRB &= ~1;  // Set PB0 (clock line) as input

}


bool MySerial8_ck::signal(){
  return _signal;
}


void MySerial8_ck::listen(){
  if(PINB & 1){ // Check for clock line high
    _signal = true;
  }
}


int MySerial8_ck::receive(byte _buf[255]){
  int byteTotal = 0; //Declare number of bytes (and set it to 0
                   //initially. First byte will determine how
                   //many total bytes there will be)
  bool err = false;
  bool _ck_pin_st = LOW;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    
    //Read the data
    unsigned long num_times = 0;
    while((PINB & 1) != _ck_pin_st){
      if(num_times > 100000){
        err = true; 
        break;
      }
      num_times += 1;
    }
    _ck_pin_st = !_ck_pin_st;
    delayMicroseconds(1);  // Wait for more stable signal

    // Read and compile the data simultaneously
    if(byteCntr == -1){ //If this is the first byte of data, it is the
                      //total number of bytes (not including this byte)
      byteTotal = PIND;
    }
    else{ //Otherwise, store this value in the collection
          //of bytes
      _buf[byteCntr] = PIND;
    }
    
    if(err) break;
    //Done with this byte
  }
  
  if(err) byteTotal = -1;
  _signal=false;
  return byteTotal;

}
////////////////////////// Receiver functions
