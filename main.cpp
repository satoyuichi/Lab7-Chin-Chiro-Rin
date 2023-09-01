#include "mbed.h"
#include "HEPTA_EPS.h"
#include "HEPTA_SENSOR.h"
RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(p16,p26);
HEPTA_SENSOR sensor(p17,
                  p28,p27,0x19,0x69,0x13,
                  p13, p14,p25,p24);

int rcmd = 0, cmdflag = 0;
int dice = 0, cmd = 0;

void commandget()
{
    rcmd = pc.getc();
    cmdflag = 1;
}

void receive(int rcmd, int cmdflag)
{
    pc.attach(commandget, Serial::RxIrq);
}

void initialize()
{
    rcmd = 0;
    cmdflag = 0;
    dice = 0;
    cmd = 0;
}

int main()
{
    float ax,ay,az;
    receive(rcmd, cmdflag);
    for(int i = 0; i<50; i++) {
        sensor.sen_acc(&ax,&ay,&az);
//        pc.printf("acc : %f,%f,%f\r\n",ax,ay,az);
        pc.printf("Please input 1 to 6.\r\n");
        if (ax < -9){
            dice = 1;
        }
        else if (ay < -9) {
            dice = 2;
        }
        else if (az < -9) {
            dice = 3;
        }
        else if (az > 9) {
            dice = 4;
        }
        else if (ay > 9) {
            dice = 5;
        }
        else if (ax > 9) {
            dice = 6;
        }
        wait(1.0);

        if(cmdflag == 1) {
            cmd = rcmd - '1' + 1;
            if(cmd == dice) {
                pc.printf("%d is Correct!!\r\n", cmd);
            }
            else {
                pc.printf("%d is Incorrect!!\r\n", cmd);
            }
            initialize();
        }
    }
}
