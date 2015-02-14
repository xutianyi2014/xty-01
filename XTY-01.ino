  /*
  XTY-01 ver 0.1 
 作者：滨海县第一初级中学初三（6）班 徐天奕
 指导教师：徐海林
 本程序遵循GPL v3协议开源（详见http://opensource.org/licenses/GPL-3.0）
 */

// 导入需要使用的lcd 时钟 传感器库
#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <MsTimer2.h>//定时中断器库 版权归原作者所有
#include <dht11.h>
// 设定接口
LiquidCrystal lcd(14, 10, 5, 4, 3, 2);
uint8_t CE_PIN   = 7;
uint8_t IO_PIN   = 8;
uint8_t SCLK_PIN = 9;
// 日期变量缓存 
char buf[50];
char buf2[50];
char day[10];
// 创建 DS1302 对象 
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
dht11 DHT11;
#define DHT11PIN 6
void flash()                        //中断处理函数
{       
  int n =digitalRead(16);
  if (n==LOW){print_time();};
}
void print_time()
{
    //从 DS1302 获取当前时间 
    Time t = rtc.time();
    delay(1000);
    Time t1 = rtc.time();
    if (t.yr <= 2013){t = t1;};
    //将星期从数字转换为名称 
    // 将日期代码格式化凑成buf等待输出 
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", t.yr, t.mon, t.date);
    snprintf(buf2, sizeof(buf2), "%02d:%02d:%02d", t.hr, t.min, t.sec);
    // 输出日期到lcd 
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
