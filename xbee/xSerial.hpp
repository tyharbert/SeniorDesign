#include <wiringSerial.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

//class for xbee serial communication
class Serial {
  private:
	char* device;
	int baud;
	int fd;
  public:
	//constructor
	Serial(char*, int);
	//opens serial port
	int Open();
	//closes serial port
	void Close();
	//sends single byte across serial port
	void  PutChar (unsigned char c);
	//send nul-terminated string across serial port
	void  PutMsg (char *s);
	//returns number of characters available for reading -1 for error
	int   DataAvail ();
	//returns next character available on serial device
	int   GetChar ();
	//discards all data received waiting to be sent down the port
	void  FlushData ();
	//reads number of bytes of data
	size_t Read(void *buf, size_t count);
	//writes count num of bytes starting at buf
	size_t Write(const void *buf, size_t count); 
};

Serial::Serial(char* usbDevice, int baudRate){
	this->device = usbDevice;
	this->baud   = baudRate;
//	this->fd = serialOpen(usbDevice, baudRate);
}

int   Serial::Open (){
        if ((this->fd = serialOpen (this->device, this->baud)) < 0)
          {
		std::cout << "Unable to open serial device\n";
          	return 0 ;
          }
	else
	  {
		//std::cout << "Serial port opened\n";
		this->fd = serialOpen(this->device, this->baud);
		return 1;
	  }
}

void Serial::Close(){
	//std::cout << "Serial port closed\n";
	serialClose(this->fd);
}

void Serial::PutChar(unsigned char c){
	if(Open()){
	std::cout << "Wrote character: " << c << std::endl;
	serialPutchar(this->fd, c);
	Close();
	}
}

void  Serial::PutMsg (char *s){
	if(Open()){
	std::cout << "Wrote message: " << s << std::endl;
	serialPuts(this->fd, s);
	Close();
	}
}

int   Serial::DataAvail (){
	if(serialDataAvail(this->fd) > 0){
	return serialDataAvail(this->fd);
	}
}

int   Serial::GetChar (){
	if(serialDataAvail(this->fd) > 0){
	return serialGetchar(this->fd);
	}
}

void  Serial::FlushData (){
//	if(Open()){
	serialFlush(this->fd);
//	}
}

size_t Serial::Read(void *buf, size_t count){
//	if(Open()){
	return read(this->fd, buf, count);
//	}
}

size_t Serial::Write(const void *buf, size_t count){
	if(Open()){
	return write(this->fd, buf, count);
	Close();
	}
}
