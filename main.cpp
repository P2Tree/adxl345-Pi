#include "ADXL345PiSPI.hpp"
#include "ADXL345.hpp"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <fstream>

#include <wiringPi.h>   //for io
//#define BUG

using namespace std;

bool stopI2C = false;

void handleSigInt(int param) {
        cout << "CTRL-C\n";
        stopI2C = true;
}

int main() {
        signal(SIGINT, handleSigInt);

        cout << "Attempting to measure from ADX345.\n";

#ifdef BUG
        streambuf* coutBuf = cout.rdbuf();
        ofstream of("outdata.txt");
        streambuf* fileBuf = of.rdbuf();
        cout.rdbuf(fileBuf);
#endif
        wiringPiSetup();
        wiringPiISR(0, INT_EDGE_FALLING, inactivity_int);      //!< 0 for GPIO17 in Pi
        wiringPiISR(1, INT_EDGE_FALLING, activity_int);         //!< 1 for GPIO18 in Pi
        try {
                ADXL345PiSPI sensor(0, Scale_FullRes);
                sensor.writeRegister(INT_ENABLE, 0x00);         // clear interrupt bits
                sensor.zeroOffsets();
                //sensor.initOffset();
                sensor.writeRegister(THRESH_ACT, 0x40);
                sensor.writeRegister(THRESH_INACT, 0x20);
                sensor.writeRegister(TIME_INACT, 0x05);
                sensor.writeRegister(ACT_INACT_CTL, 0xFF);
                sensor.writeRegister(ACT_TAP_STATUS, 0x70);
                sensor.writeRegister(POWER_CTL, 0x20);
                sensor.setActive(true);
                sensor.writeRegister(INT_MAP, 0x10);
                sensor.writeRegister(INT_ENABLE, 0x18);
                while(!stopI2C)
                {
                        /*
                        if(dataUpdate_flag){
                                dataUpdate_flag = 0;
                                cout << sensor.readData().toString() << endl;
                        }
                        */
                        if(activity_flag){
                                activity_flag = 0;
                                cout << "activity catch!" << endl;
                                //cout << "act = " << activity_flag << endl;
                        }
                        if(inactivity_flag){
                                inactivity_flag = 0;
                                cout << "inactivity catch!" << endl;
                                //cout << "inact = " << inactivity_flag << endl;
                        }
                        sensor.readRegister(INT_SOURCE);
                }
                cout << "Shutting down." << endl;
                sensor.setActive(false);
        }
        catch (const string& str) {
                cerr << "Failed: " << str << endl;
        }

#ifdef BUG
        of.flush();
        of.close();
        cout.rdbuf(coutBuf);
#endif
  // all done.
        return 0;
}
