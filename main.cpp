#include "mbed.h"
#include "HEPTA_EPS.h"
#include "HEPTA_SENSOR.h"
#include "HEPTA_COM.h"

RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(p16,p26);
HEPTA_SENSOR sensor(p17,
                  p28,p27,0x19,0x69,0x13,
                  p13, p14,p25,p24);
HEPTA_COM com(p9, p10, 9600);

int rcmd = 0, cmdflag = 0;
int dice = 0, cmd = 0;

int main()
{
    float ax,ay,az;
    com.printf("Please input 1 to 6.\r\n");
    while(1) {
        sensor.sen_acc(&ax,&ay,&az);
        com.xbee_receive(&rcmd, &cmdflag);
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
                com.printf("%d is Correct!!\r\n", cmd);
                com.printf("You win!!\r\n");
                break;
            }
            else {
                com.printf("%d is Incorrect!!\r\n", cmd);
            }
            com.initialize();
        }
    }
}
