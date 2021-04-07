// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

InterruptIn up(A0);
InterruptIn select_button(A2);
InterruptIn down(A4);
AnalogOut out(D7);
AnalogOut filtered_out(D13);
AnalogIn filtered_data(A5);
//DigitalOut led2(LED2);

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;


int selection_flag = 0;
float ADCdata1[1000];
float ADCdata2[5000];
float ADCdata3[10000];
int period_count = 0;
int period_count2 = 0;
int period_count3 = 0;
int loop_flag = 0;
int loop_flag2 = 0;
int loop_flag3 = 0;

void normal_mode()
{
    uLCD.background_color(WHITE);
    uLCD.color(BLUE);
    //uLCD.text_width(1); //4X size text
    //uLCD.text_height(1);
    //uLCD.printf("\nSelect the slew rate\n");

    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.color(GREEN);
    uLCD.locate(2,0);
    uLCD.printf("\n  1");

    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.locate(2,2);
    uLCD.printf("\n  1/2");

    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.locate(2,4);
    uLCD.printf("\n  1/4");

    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.locate(2,6);
    uLCD.printf("\n  1/8");
}

void mode_up()
{
    selection_flag = (selection_flag+3)%4;
    if(selection_flag == 0)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 1)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 2)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 3)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
}

void mode_down()
{
    selection_flag = (selection_flag+1)%4;
    if(selection_flag == 0)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 1)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 2)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
    else if(selection_flag == 3)
    {
        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(WHITE);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");

        uLCD.text_width(2); //4X size text
        uLCD.text_height(2);
        uLCD.color(GREEN);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }
}

void mode_select()
{
    //led2 = !led2;
    if(selection_flag == 0)
    {        
        uLCD.text_width(2); 
        uLCD.text_height(2);
        uLCD.color(RED);
        uLCD.locate(2,0);
        uLCD.printf("\n  1");
    }
    else if(selection_flag == 1)
    {
        uLCD.text_width(2); 
        uLCD.text_height(2);
        uLCD.color(RED);
        uLCD.locate(2,2);
        uLCD.printf("\n  1/2");
    }
    else if(selection_flag == 2)
    {
        uLCD.text_width(2); 
        uLCD.text_height(2);
        uLCD.color(RED);
        uLCD.locate(2,4);
        uLCD.printf("\n  1/4");
    }
    else if(selection_flag == 3)
    {
        uLCD.text_width(2); 
        uLCD.text_height(2);
        uLCD.color(RED);
        uLCD.locate(2,6);
        uLCD.printf("\n  1/8");
    }

    float data;
    if(selection_flag == 0) //1
    {
        while(1)
        {
            //loop_flag = loop_flag % 10;
            for(int i=0;i<80;i++)
            {
                data = (3.0f / 80.0f * i)/3.3f;
                out = data;
                wait_us(500);

                filtered_out = filtered_data; //adc
                //ADCdata1[loop_flag*100+i] = filtered_data;
                //printf("%f\r\n", ADCdata1[loop_flag*100+i]);

                wait_us(500);
            }
            ThisThread::sleep_for(80ms);
            for(int j=0;j<80;j++)
            {
                data = (3.0f - 3.0f / 80.0f * j)/3.3f;
                out = data;
                wait_us(500);

                filtered_out = filtered_data; //adc
                //ADCdata1[loop_flag*100+j+70] = filtered_data;
                //printf("%f\r\n", ADCdata1[loop_flag*100+j+70]);

                wait_us(500);
            } 
            //loop_flag++;
            //period_count++;
        }
    }
    else if(selection_flag == 1) //50hz
    {
        while(period_count2 <= (1500))
        {
            loop_flag2 = loop_flag2 % 50;
            for(int i=0;i<70;i++)
            {
                data = (3.0f / 70.0f * i)/3.3f;
                out = data;
                wait_us(70);

                filtered_out = filtered_data; //adc
                ADCdata2[loop_flag2*100+i] = filtered_data;
                //printf("%f\r\n", ADCdata2[loop_flag2*100+i]);

                wait_us(70);
            }
            for(int j=0;j<30;j++)
            {
                data = (3.0f - 3.0f / 30.0f * j)/3.3f;
                out = data;
                wait_us(70);

                filtered_out = filtered_data; //adc
                ADCdata2[loop_flag2*100+j+70] = filtered_data;
                //printf("%f\r\n", ADCdata2[loop_flag2*100+j+70]);

                wait_us(70);
            }
            loop_flag2++; 
            period_count2++;              
        }
    }
    else if(selection_flag == 2) //100hz
    {
        while(period_count3 <= (3000))
        {
            loop_flag3 = loop_flag3 % 100;
            for(int i=0;i<70;i++)
            {
                data = (3.0f / 70.0f * i)/3.3f;
                out = data;
                wait_us(50);

                filtered_out = filtered_data; //adc
                ADCdata3[loop_flag3*100+i] = filtered_data;
                //printf("%f\r\n", ADCdata3[loop_flag3*100+i]);

                //wait_us(10);
            }
            for(int j=0;j<30;j++)
            {
                data = (3.0f - 3.0f / 30.0f * j)/3.3f;
                out = data;
                wait_us(50);

                filtered_out = filtered_data; //adc
                ADCdata3[loop_flag3*100+j+70] = filtered_data;
                //printf("%f\r\n", ADCdata3[loop_flag3*100+j+70]);

                //wait_us(20);             
            }
            loop_flag3 ++;
            period_count3++;
        }
    }
    ThisThread::sleep_for(10s);
    if(selection_flag == 0)
    {
        for(int i=0; i<1000; i++) printf("%f\r\n", ADCdata1[i]);
    }
    else if(selection_flag == 1)
    {
        for(int i=0; i<5000; i++) printf("%f\r\n", ADCdata2[i]);
    }
    else if(selection_flag == 2)
    {
        for(int i=0; i<10000; i++) printf("%f\r\n", ADCdata3[i]);
    }
}

void print_data()
{
    for(int i=0; i<1000; i++)
    {
        printf("%f\r\n",(float)filtered_out);
        ThisThread::sleep_for(10ms);
    }
}
int main()
{
    normal_mode();
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    //while(true)
    //{
    //    ThisThread::sleep_for(20s);
    //queue.call(print_data);
    //queue.call_(print_data);
    //}
    /*while(true)
    {
        //printf("%f %f %f\n",up*1.0f, select_button*1.0f, down*1.0f);
        if(up)
        {
            mode_up();
        }        
        else if(select_button)
        {
            mode_select();
        }
        else if(down)
        {
            mode_down();
        }
    }*/
    up.rise(queue.event(mode_up));
    select_button.rise(queue.event(mode_select));
    //select_button.fall(&print_data);
    down.rise(queue.event(mode_down));
    //queue.dispatch();
}