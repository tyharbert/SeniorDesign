
#include "xMessage.hpp"

int main(){

Message test;
test.sendConfigReport();
test.receiveConfigReport();
test.sendTimeSync();
test.receiveLog();
system("date 0820102508.30");
return 0;
}
