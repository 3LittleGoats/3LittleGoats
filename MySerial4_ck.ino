/*
 * This version of MySerial uses 4 fixed pins for data and 1
 * fixed pin for clock. It uses PD4-PD7 (digital pins 4-7) for
 * data and PB0 (digital pin 8) for clock.
 */


unsigned int _bit_time;
unsigned int _line_up_time;

bool _signal = false;


////////////////////////// Transmitter functions.
void begin_t(unsigned int bitTime, unsigned int lineUpTime){
  _bit_time = bitTime;
  _line_up_time = lineUpTime;
  PORTD &= 0b00001111;  // Set PD4-PD7 (data pins) low
  PORTB &= ~1;  // Set PB0 (clock pin) low
  DDRD |= 0b11110000;
  DDRB |= 1;
}


void transmit(byte _buf[255], int byteTotal){
  //Arm the receiver
  PORTB |= 1;
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

    // Transmit first nibble
    PORTD = (PORTD & 0b00001111) + (_bits & 0b11110000);
    PORTB ^= 1;  // Half-cycle clock
    delayMicroseconds(_bit_time);
    // Transmit last nibble
    PORTD = (PORTD & 0b00001111) + (_bits << 4);
    PORTB ^= 1;  // Half-cycle clock
    delayMicroseconds(_bit_time);

  }
  // Make sure the transmitter always ends low
  PORTD &= 0b00001111;  // Set PD4-PD7 low
  PORTB &= ~1;  // Set PB0 low

}
////////////////////////// Transmitter functions






////////////////////////// Receiver functions
void begin_r(){
  DDRD &= 0b00001111;  // Set PD4-PD7 (data pins) low
  DDRB &= ~1;  // Set PB0 (clock pin) low

}


bool signal(){
  return _signal;
}


void listen(){
  if((PINB & 1) == HIGH){
    _signal = true;
  }
}


int receive(byte _buf[255]){
  
  int byteTotal = 0; //Declare number of bytes (and set it to 0
                   //initially. First byte will determine how
                   //many total bytes there will be)
  for(int byteCntr = -1; byteCntr < byteTotal; byteCntr ++){
    
    //Read the data
    byte _bits = 0;
    // Read first nibble
    while((PINB & 1) != LOW){}  // Read as soon as low
    _bits += PIND & 0b11110000;
    // Read last nibble
    while((PINB & 1) != HIGH){}  // Read as soon as high
    _bits += (PIND >> 4);

    //Compile the data
    if(byteCntr == -1){ //If this is the first byte of data, it is the
                      //total number of bytes (not including this byte)
      byteTotal = _bits;
    }
    else{ //Otherwise, store this value in the collection
          //of bytes
      _buf[byteCntr] = _bits;
    }
    
    //Done with this iteration
  }

  while((PINB & 1) == HIGH){}

  _signal = false;
  return byteTotal;

}
////////////////////////// Receiver functions.
