#include "mbed.h"

#define BLINKING_RATE    1000ms // Blinking rate in milliseconds

Timeout  timer;                  // define ticker timer object
DigitalOut led(LED1);

static volatile int blink_state = 1;
static volatile int intr_occurred = 0;

void isr_timer()
{
    blink_state = !blink_state; 
    intr_occurred = 1 ;
}

int main()
{   
  timer.attach(&isr_timer, 8000ms);  // attach timer interrupt isr
  led = 0;
    
  while (true) {
      if(blink_state){
        led =!led;
        ThisThread::sleep_for(BLINKING_RATE);
      }
      if(intr_occurred){
          printf("Timer interrupt has occured ! \r\n");
          intr_occurred = 0; 
      }
  }
}
