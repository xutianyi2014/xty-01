  /*
  XTY-01 ver 0.1 
 ���ߣ������ص�һ������ѧ������6���� ������
 ָ����ʦ���캣��
 ��������ѭGPL v3Э�鿪Դ�����http://opensource.org/licenses/GPL-3.0��
 */

// ������Ҫʹ�õ�lcd ʱ�� ��������
#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <MsTimer2.h>//��ʱ�ж����� ��Ȩ��ԭ��������
#include <dht11.h>
// �趨�ӿ�
LiquidCrystal lcd(14, 10, 5, 4, 3, 2);
uint8_t CE_PIN   = 7;
uint8_t IO_PIN   = 8;
uint8_t SCLK_PIN = 9;
// ���ڱ������� 
char buf[50];
char buf2[50];
char day[10];
// ���� DS1302 ���� 
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
dht11 DHT11;
#define DHT11PIN 6
void flash()                        //�жϴ�����
{       
  int n =digitalRead(16);
  if (n==LOW){print_time();};
}
void print_time()
{
    //�� DS1302 ��ȡ��ǰʱ�� 
    Time t = rtc.time();
    delay(1000);
    Time t1 = rtc.time();
    if (t.yr <= 2013){t = t1;};
    //�����ڴ�����ת��Ϊ���� 
    // �����ڴ����ʽ���ճ�buf�ȴ���� 
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", t.yr, t.mon, t.date);
    snprintf(buf2, sizeof(buf2), "%02d:%02d:%02d", t.hr, t.min, t.sec);
    // ������ڵ�lcd 
    lcd.clear();
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.print(buf2); 
}
void setup() {
    MsTimer2::set(100, flash);
    pinMode(16,INPUT_PULLUP); 
    lcd.begin(16, 2);
    lcd.print("STARTING...");
    print_time();
    delay(2000);
    MsTimer2::start();
}

void loop() {
    int chk = DHT11.read(DHT11PIN);
    lcd.setCursor(0, 0);
    lcd.print("HUM:");
    lcd.print((float)DHT11.humidity);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("TEM:");
    lcd.print((float)DHT11.temperature);
    lcd.print("oC");
     delay(2000);
}
