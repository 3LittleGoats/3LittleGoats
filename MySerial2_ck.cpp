#include "MySerial2_ck.h"


MySerial2_ck::MySerial2_ck(){}


////////////////////////// Transmitter functions
MySerial2_ck::begin_t(byte pin1, byte pin2, byte pin3, unsigned int bitTime, unsigned int lineUpTime){
  _pin1 = pin1;
  _pin2 = pin2;
  _ck_pin = pin3;
  _bit_time = bitTime;
  _line_up_time = lineUpTime;
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
  digitalWrite(_ck_pin, LOW);
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_ck_pin, OUTPUT);
}


MySerial2_ck::transmit(byte _buf[255], int byteTotal){
  //Arm the receiver
  digitalWrite(_ck_pin, 1);
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
    for(byte bitCntr = 0; bitCntr < 8; bitCntr += 2){
      digitalWrite(_pin1, (((1<<(7-bitCntr))&_bits)>>(7-bitCntr)));
      digitalWrite(_pin2, (((1<<(6-bitCntr))&_bits)>>(6-bitCntr)));
      digitalWrite(_ck_pin, _ck_pin_st);  // Data first so that
                                              // when clock comes
                                              // through, data will
                                              // already be ready
      delayMicroseconds(_bit_time);
      _ck_pin_st = !_ck_pin_st;
    }

  }
  // Make sure the transmitter always ends low
  digitalWrite(_ck_pin, LOW);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);

}
////////////////////////// Transmitter functions






////////////////////////// Receiver functions
MySerial2_ck::begin_r(byte pin1, byte pin2, byte pin3){
  _pin1 = pin1;
  _pin2 = pin2;
  _ck_pin = pin3;
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
  pinMode(_ck_pin, INPUT);

}


bool MySerial2_ck::signal(){
  return _signal;
}


MySerial2_ck::listen(){
  if(digitalRead(_ck_pin) == HIGH){
    _signal = true;
  }
}


int MySerial2_ck::receive(byte _buf[255]){
  
  int byteTotal = 0; //Declare number of bytes (and set it to 0
                   //initially. First byte will determine how
                   //many total bytes there will be)
  bool err = false;
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    
    //Read the data
    bool _ck_pin_st = LOW;
    byte _bits = 0;
    for(byte bitCntr = 0; bitCntr < 8; bitCntr += 2){
        unsigned long num_times = 0;
      while(digitalRead(_ck_pin) != _ck_pin_st){
        if(num_times > 100000){
          err = true;
          break;
        }
        num_times += 1;
      }
      delayMicroseconds(1);
      
      _bits ^= (digitalRead(_pin1)<<(7-bitCntr)); // Read this bit
      _bits ^= (digitalRead(_pin2)<<(6-bitCntr)); // Read this bit
      _ck_pin_st = !_ck_pin_st;
      
      if(err) break;
    }

    //Compile the data
    if(byteCntr == -1){ //If this is the first byte of data, it is the
                      //total number of bytes (not including this byte)
      byteTotal = _bits;
    }
    else{ //Otherwise, store this value in the collection
          //of bytes
      _buf[byteCntr] = _bits;
    }
    
    if(err) break;
    //Done with this iteration
  }

  while((digitalRead(_ck_pin) == HIGH) && (!err)){}
  
  if(err) byteTotal = -1;
  _signal=false;
  return byteTotal;

}
////////////////////////// Receiver functions
