/*
 mbed_usbps4.hのスケッチ例です。多分、作世界初OSSのarduino GIGA R1対応のps４コントローラー用ライブラリ
 対応ボードはarduino_GIGA_R1の内臓USB（STM32H747）で、usb host shield 2.0(MAX3421E)とは一切互換性がありません。
 ですが、usb host shield 2.0のps4.hとなるべく互換性を持たせるために関数名はほぼすべて同じにしています。
 ロボコン等で使用することを想定しており、LEDや振動機能はそぎ落としたライブラリになっています。
 < library_ver:1.0.0 >
 連絡先 < X(旧Twitter)@kakitama2000 >
*/

#include <mbed_usbps4.h>

PS4USB PS4;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.print(F("\r\nPS4 USB Library Started"));
}

void loop() {
  PS4.poll();

  if (PS4.connected()) {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS4.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS4.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS4.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS4.getAnalogHat(RightHatY));
    }

    if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
      Serial.print(F("\r\nL2: "));
      Serial.print(PS4.getAnalogButton(L2));
      Serial.print(F("\tR2: "));
      Serial.print(PS4.getAnalogButton(R2));
    }

    if (PS4.getButtonClick(PS))
      Serial.print(F("\r\nPS"));
    if (PS4.getButtonClick(TRIANGLE)) {
      Serial.print(F("\r\nTriangle"));
    }
    if (PS4.getButtonClick(CIRCLE)) {
      Serial.print(F("\r\nCircle"));
    }
    if (PS4.getButtonClick(CROSS)) {
      Serial.print(F("\r\nCross"));
    }
    if (PS4.getButtonClick(SQUARE)) {
      Serial.print(F("\r\nSquare"));
    }

    if (PS4.getButtonClick(UP)) {
      Serial.print(F("\r\nUp"));
    } if (PS4.getButtonClick(RIGHT)) {
      Serial.print(F("\r\nRight"));
    } if (PS4.getButtonClick(DOWN)) {
      Serial.print(F("\r\nDown"));
    } if (PS4.getButtonClick(LEFT)) {
      Serial.print(F("\r\nLeft"));
    }

    if (PS4.getButtonClick(L1))
      Serial.print(F("\r\nL1"));
    if (PS4.getButtonClick(R1))
      Serial.print(F("\r\nR1"));
    if (PS4.getButtonClick(L2))
      Serial.print(F("\r\nL2"));
    if (PS4.getButtonClick(R2))
      Serial.print(F("\r\nR2"));
    if (PS4.getButtonClick(L3))
      Serial.print(F("\r\nL3"));
    if (PS4.getButtonClick(R3))
      Serial.print(F("\r\nR3"));

    if (PS4.getButtonClick(SHARE))
      Serial.print(F("\r\nShare"));
    if (PS4.getButtonClick(OPTIONS)) {
      Serial.print(F("\r\nOptions"));
    }
    if (PS4.getButtonClick(TOUCHPAD)) {
      Serial.print(F("\r\nTouchpad"));
    }
  }
}
