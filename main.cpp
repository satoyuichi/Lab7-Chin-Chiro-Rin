#include "mbed.h"
#include "HEPTA_EPS.h"
#include "HEPTA_SENSOR.h"
 
RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(p16,p26);
HEPTA_SENSOR sensor(p17,
                  p28,p27,0x19,0x69,0x13,
                  p13, p14,p25,p24);

int main()
{
    float ax,ay,az;
    for(int i = 0; i<50; i++) {
        sensor.sen_acc(&ax,&ay,&az);
        pc.printf("acc : %f,%f,%f\r\n",ax,ay,az);
        wait(1.0);
    }
}