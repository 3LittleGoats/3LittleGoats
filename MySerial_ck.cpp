#include "MySerial_ck.h"


MySerial_ck::MySerial_ck(){}


////////////////////////// Transmitter functions
void MySerial_ck::begin_t(byte pin1, byte pin2, unsigned int bitTime, unsigned int lineUpTime){
  _pin = pin1;
  _ck_pin = pin2;
  _bit_time = bitTime;
  _line_up_time = lineUpTime;
  digitalWrite(_pin, LOW);
  digitalWrite(_ck_pin, LOW);
  pinMode(_pin, OUTPUT);
  pinMode(_ck_pin, OUTPUT);
}


void MySerial_ck::transmit(byte _buf[255], int byteTotal){
  //Arm the receiver
  digitalWrite(_ck_pin, HIGH);
  delayMicroseconds(_line_up_time);

  byte _bits = 0;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    //Compile the data
    if(byteCntr == -1){
      _bits = byteTotal;
    }
    else{
      _bits = _buf[byteCntr];
    }

    //Transmit the data
    bool _ck_pin_st = LOW;
    for(byte bitCntr = 0; bitCntr < 8; bitCntr++){
      //digitalWrite(_pin, (((1 << (7 - bitCntr)) & _bits) >> (7 - bitCntr))); // Avg 3.4uS
      digitalWrite(_pin, ((_bits << bitCntr) >> 7)); // Avg 2.7uS
      digitalWrite(_ck_pin, _ck_pin_st);  // Data first so that
                                              // when clock comes
                                              // through, data will
                                              // already be ready. 2.3uS
      delayMicroseconds(_bit_time);  // _bit_time=10, 9.6uS
      _ck_pin_st = !_ck_pin_st;  // 0.063uS
    }

  }
  // Make sure the transmitter always ends low
  digitalWrite(_ck_pin, LOW);
  digitalWrite(_pin, LOW);

}
////////////////////////// Transmitter functions






////////////////////////// Receiver functions
void MySerial_ck::begin_r(byte pin1, byte pin2){
  _pin = pin1;
  _ck_pin = pin2;
  pinMode(_pin, INPUT);
  pinMode(_ck_pin, INPUT);

}


bool MySerial_ck::signal(){
  return _signal;
}


void MySerial_ck::listen(){
  if(digitalRead(_ck_pin) == HIGH){
    _signal = true;
  }
}


int MySerial_ck::receive(byte _buf[255]){
  
  int byteTotal = 0; //Declare number of bytes (and set it to 0
                   //initially. First byte will determine how
                   //many total bytes there will be)
  bool err = false;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    
    //Read the data
    bool _ck_pin_st = LOW;
    byte _bits = 0;
    for(byte bitCntr = 0; bitCntr < 8; bitCntr ++){
    
      unsigned long num_times = 0;
      while(digitalRead(_ck_pin) != _ck_pin_st){
        if(num_times > 100000){
          err = true;
          break;
        }
        num_times += 1;
      }
      
      //delayMicroseconds(1);
      _bits ^= (digitalRead(_pin) << (7 - bitCntr));  // Avg 2.0uS
      _ck_pin_st = !_ck_pin_st;
      if(err) break;
    }

    //Compile the data
    if(byteCntr == -1){ //If this is the first byte of data, it is the
                      //total number of bytes (not including this byte).
      byteTotal = _bits;
    }
    else{ //Otherwise, store this value in the collection
          //of bytes
      _buf[byteCntr] = _bits;
    }
    
    if(err) break;
    //Done with this iteration
  }
  
  // Wait for transmitter to finish
  while((digitalRead(_ck_pin) == HIGH) && (!err)){}
  
  if(err) byteTotal = -1;
  _signal=false;
  return byteTotal;

}
////////////////////////// Receiver functions
