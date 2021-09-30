||||Currently, MySerial4_ck has not been converted to a library, so the .ino file for it is instead included.||||

Make sure to read through the READMEs for MySerial, MySerial_ck, and MySerial2_ck, as there is data in those I have not repeated here.
MySerial4_ck and MySerial8_ck are different from the others in that you cannot choose which pins they use.
MySerial4_ck uses PD4-PD7 (digital pins 4-7) for data, and PB0 (digital pin 8) for the clock.
MySerial4_ck and MySerial8_ck were both designed for use where speed is what's really important. Thus, instead of using the Arduino digitalWrite
    and digitalRead functions, which take a lot of time when dealing with 5 or 9 pins, these serial protocols write to and read from the
    registers associated with their pins.
MySerial8_ck was designed before MySerial4_ck. After realizing that MySerial8_ck occupied the USART pins on the ATMEGA, preventing the use of
    Arduino's Serial interface, MySerial4_ck was developed.

Class name: MySerial4_ck

Functions:
    begin_t(unsigned int bitTime, unsigned int lineUpTime)
    
    transmit(byte _buf[255], int byteTotal)
    
    begin_r()
    
    listen()
    
    bool signal()
    
    int receive(byte _buf[255])
