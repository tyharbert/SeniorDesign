#include "xSerial.hpp"

//class for xbee to send messages
class Message{
  private:
	//USB device port from constructor
	char* device;
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


void Message::sendMessage(char type){
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

