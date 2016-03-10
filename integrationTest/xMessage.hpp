#include "xSerial.hpp"
#include "xmodem.c"
#include <string.h>

using namespace std;

//class for xbee to send messages
class Message{
  private:
//	char* device  = (char*)"/dev/ttyUSB0";
	char* device;
//	string header = "0000";
//	string msgType;
//	string trailer ="0000";
//	string msgConcat(string);
	void sendMessage(char);
  public:
	Message(char*);
	int sendConfigReport();
	void receiveConfigReport();
	int sendTimeSync();
	void receiveLog();
	void sendingImage();
	void receiveReady();
};

Message::Message(char* dev){
this->device = dev;
}


/*
string Message::msgConcat(string type){
	//check different types and customize messages based on it
	string msg = this->header + type + this->trailer;

	return msg;
}
*/

void Message::sendMessage(char type){
//        string msg = msgConcat(type);

        //create char array copy of string to send
//        char msgArr[10];
//        strcpy(msgArr, msg.c_str());
	//open serial port and send message
//	char* temp = &type;
        Serial xbee(this->device, 57600);
        xbee.PutChar(type);
}

int Message::sendConfigReport(){
	sendMessage('3');
	//wait for confirmation and resend if needed

	return 0;
}

void Message::receiveConfigReport(){
	sendMessage('4');
	//wait to receive config report and could timeout
}

int Message::sendTimeSync(){
	sendMessage('6');
	return 0;
}

void Message::receiveLog(){
	sendMessage('5');
	//wait to receive logfile
}

void Message::sendingImage(){
	sendMessage('1');
}

void Message::receiveReady(){
	sendMessage('2');
}

