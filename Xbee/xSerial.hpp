#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wiringSerial.h>

//class for xbee packets
class Serial {
  private:
	int port;
	int baud;
	char letter;
	char* msg;
  public:
	//opens serial port
	int   xserialOpen (char *device, int baud);
	//closes serial port
	void  xserialClose (int fd);
	//sends single byte across serial port
	void  xserialPutChar (int fd, unsigned char c);
	//send nul-terminated string across serial port
	void  xserialPutMsg (int fd, char *s);
	//emulates printf function to serial device
	void  xserialPrintf (int fd, char *message);
	//returns number of characters available for reading -1 for error
	int   xserialDataAvail (int fd);
	//returns next character available on serial device
	int   xserialGetChar (int fd);
	//discards all data received waiting to be sent down the port
	void  xserialFlushData (int fd);
	//reads number of bytes of data
	int serialRead(int fd, void *buf, int count);
	//writes count num of bytes starting at buf
	int serialWrite(int fd, const void *buf, size_t count); 
};

int   xserialOpen (char *device, int baud){
	return serialOpen(device, baud);
}

void xserialClose(int fd){
	serialClose(fd);
}

void xserialPutChar(int fd, unsigned char c){
	serialPutchar(fd, c);
}

void  xserialPutMsg (int fd, char *s){
	serialPuts(fd, s);
}

void  xserialPrintf (int fd, char *msg){
	serialPrintf(fd, msg);
}

int   xserialDataAvail (int fd){
	return serialDataAvail(fd);
}

int   xserialGetChar (int fd){
	return serialGetchar(fd);
}

void  xserialFlushData (int fd){
	serialFlush(fd);
}

int serialRead(int fd, void *buf, int count){
	return read(fd, buf, count);
}

int serialWrite(int fd, const void *buf, int count){
	return write(fd, buf, count);
}
