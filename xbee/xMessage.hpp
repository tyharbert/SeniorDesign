#include "xSerial.hpp"
#include "xmodem.cpp"
#include <string.h>

using namespace std;

//class for xbee to send messages
class Message{
  private:
	char* device  = (char*)"/dev/ttyUSB1";

	string header = "0000";
	string msgType;
	string trailer ="0000";
	string msgConcat(string);
	void sendMessage(string);
  public:
	int sendConfigReport();
	void receiveConfigReport();
	int sendTimeSync();
	void receiveLog();
	void sendingImage();
	void receiveReady();
};

string Message::msgConcat(string type){
	//check different types and customize messages based on it
	string msg = this->header + type + this->trailer;

	return msg;
}

void Message::sendMessage(string type){
        string msg = msgConcat(type);

        //create char array copy of string to send
        char msgArr[10];
        strcpy(msgArr, msg.c_str());
	//open serial port and send message
        Serial xbee(this->device, 9600);
        xbee.PutMsg(msgArr);
}

int Message::sendConfigReport(){
	sendMessage("SC");
	//wait for confirmation and resend if needed

	return 0;
}

void Message::receiveConfigReport(){
	sendMessage("RC");
	//wait to receive config report and could timeout
}

int Message::sendTimeSync(){
	sendMessage("TS");
	return 0;
}

void Message::receiveLog(){
	sendMessage("RL");
	//wait to receive logfile
}

void Message::sendingImage(){
	sendMessage("SI");
}

void Message::receiveReady(){
	sendMessage("RR");
}

