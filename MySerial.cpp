#include "MySerial.h"


// Constructor
MySerial::MySerial(){}


//////////////////////////////// Transmitter functions
void MySerial::begin_t(byte pin, unsigned int bitTime, unsigned int lineUpTime){
  _pin = pin;
  _bit_time = bitTime;
  _line_up_time = lineUpTime;
  digitalWrite(_pin, LOW);
  pinMode(_pin, OUTPUT);

}


void MySerial::transmit(byte _buf[255], int byteTotal){
  //Arm the receiver. Receiver will start clock when this
  //Signal goes high
  digitalWrite(_pin, HIGH);
  delayMicroseconds(_line_up_time);
  digitalWrite(_pin, LOW);
  delayMicroseconds(_bit_time);

  byte _bits = 0;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    //Compile the data.
    if(byteCntr == -1){
      _bits = byteTotal;
    }
    else{
      _bits = _buf[byteCntr];
    }

    //Transmit the data.
    for(byte bitCntr = 0; bitCntr < 8; bitCntr ++){
      digitalWrite(_pin, (((1 << (7 - bitCntr)) & _bits) >> (7 - bitCntr)));
      delayMicroseconds(_bit_time);
    }

    //Line up transmitter and receiver.
    digitalWrite(_pin, HIGH);
    delayMicroseconds(_bit_time);
    digitalWrite(_pin, LOW);
    delayMicroseconds(_bit_time);
    
  }

}
//////////////////////////////// Transmitter functions


//////////////////////////////// Receiver functions
void MySerial::begin_r(byte pin, unsigned int bitTime){
  _pin = pin;
  _bit_time = bitTime;
  pinMode(_pin, INPUT);

}


bool MySerial::signal(){
  return _signal;
}


void MySerial::listen(){
  if(digitalRead(_pin) == HIGH){
    _signal = true;
  }
}


int MySerial::receive(byte _buf[255]){
  while(digitalRead(_pin) == HIGH){}
  // Start as soon as signal goes low
  delayMicroseconds(_bit_time);

  int byteTotal = 0; // Declare number of bytes (and set it to 0
                     // initially. First byte will determine how
                     // many total bytes there will be)
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr++){
    // Read the data
    delayMicroseconds(_bit_time / 2);

    byte _bits = 0;
    for(byte bitCntr = 0; bitCntr < 8; bitCntr ++){
      _bits ^= (digitalRead(_pin) << (7 - bitCntr)); //Read this bit
      delayMicroseconds(_bit_time);
    }

    // Compile the data
    if(byteCntr == -1){ // If this is the first byte of data, it is the
                        // total number of bytes (not including this byte)
      byteTotal = _bits;
    }
    else{ // Otherwise, store this value in the collection
          // of bytes
      _buf[byteCntr] = _bits;
    }

    // Line up with transmitter
    // If this loop ever gets skipped, there's a problem. In the event of a
    // problem, set byteTotal to -1.
    bool err = true;
    while(digitalRead(_pin) == HIGH){
      err = false;
    }
    if(err){
      byteTotal = -1;
      break;
    }
    
    delayMicroseconds(_bit_time);
    
    // Done with this iteration
  }

  _signal = false;
  return byteTotal;
}
//////////////////////////////// Receiver functions
