#include <Wire.h>
#include <DS3231.h>
#include <LedControl.h>

int DIN = 5;
int CS = 6;
int CLK = 7;
int MOD = 4;
int Button0 = 10;
int Button1 = 11;
bool century = false;

DS3231 rtc;
LedControl lc(DIN, CLK, CS, MOD);

byte Led_space[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte font[10][8] = {  
  {0x00,0x7C,0xFE,0xA2,0x92,0xFE,0x7C,0x00}, // 0
  {0x00,0x02,0x02,0xFE,0xFE,0x42,0x02,0x00}, // 1
  {0x00,0x62,0xF2,0x9A,0x8E,0xC6,0x42,0x00}, // 2
  {0x00,0x6C,0xFE,0x92,0x82,0xC6,0x44,0x00}, // 3
  {0x00,0x08,0xFE,0xFE,0x68,0x38,0x18,0x00}, // 4
  {0x00,0x9C,0xBE,0xA2,0xA2,0xE6,0xE4,0x00}, // 5
  {0x00,0x0C,0x9E,0x92,0xD2,0x7E,0x3C,0x00}, // 6
  {0x00,0xE0,0xF0,0x9E,0x8E,0xC0,0xC0,0x00}, // 7
  {0x00,0x6C,0xFE,0x92,0x92,0xFE,0x6C,0x00}, // 8
  {0x00,0x78,0xFC,0x96,0x92,0xF0,0x60,0x00},  // 9
  };

void setup() {
  Wire.begin();
  pinMode(Button0, INPUT);
  pinMode(Button1, INPUT);
  // 設一次時間
  //rtc.adjust(DateTime(2026, 1, 8,22,24,40));

  for(int i=0;i<MOD;i++){
    lc.shutdown(i,false);
    lc.setIntensity(i,4);
    lc.clearDisplay(i);
  }
}

void loop() {
  int h, min, sec, d,m;
  bool h12, pm;
  h = rtc.getHour(h12, pm);
  min = rtc.getMinute();
  sec = rtc.getSecond();
  d = rtc.getDate();
  m = rtc.getMonth(century);

  if (digitalRead(Button1) == 0){
    for(int r=0;r<8;r++){
      lc.setRow(3,r,Led_space[r]);
      lc.setRow(2,r,Led_space[r]);
      lc.setRow(1,r,font[sec/10][r]);
      lc.setRow(0,r,font[sec%10][r]);
    }
  }
  else if (digitalRead(Button0) == 0) {
   for(int r=0;r<8;r++){
    lc.setRow(3,r,font[m/10][r]);
    lc.setRow(2,r,font[m%10][r]);
    lc.setRow(1,r,font[d/10][r]);
    lc.setRow(0,r,font[d%10][r]);
    } 
  }
  
  else
    // 顯示 HH:MM
    for(int r=0;r<8;r++){
    lc.setRow(3,r,font[h/10][r]);
    lc.setRow(2,r,font[h%10][r]);
    lc.setRow(1,r,font[min/10][r]);
    lc.setRow(0,r,font[min%10][r]);
    }
  }

//Make by Penguin1223