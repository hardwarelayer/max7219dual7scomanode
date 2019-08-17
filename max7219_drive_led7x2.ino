/*
#include "LedControl.h"
// thêm thư viện

const int DIN = 11;
const int LOAD = 10;
const int CLK = 13;
//LedControl lc=LedControl(DIN,CLK,LOAD,1);

LedControl segment = LedControl(DIN, CLK, LOAD, 1);
// Chân 2 nối với chân DataIn
// Chân 4 nối với chân CLK
// Chân 3 nối với chân LOAD
// Sử dụng 1 IC MAX7219
int s=0;
void setup() {
    segment.shutdown(0, false); // Bật hiển thị
    segment.setIntensity(0, 0); // Đặt độ sáng lớn nhất
    delay(500);

    segment.clearDisplay(0); // Tắt tất cả led

}
void loop() {

    segment.setDigit(0,0,2,false);  // (Max7219 chip #, Digit, value, DP on or off)
    segment.setDigit(0,1,3,false);

    delay(500);
    segment.clearDisplay(0); // Tắt tất cả led
    delay(500);
}

*/
