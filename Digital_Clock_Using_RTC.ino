/*  Using Arduino/Atmega uC and common anode 7-segment 4 digit display and RTC
    Simple digital clock program.
*/

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// For common anode 7-seg
#define ON LOW
#define OFF HIGH

// Arduino pins
int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
int d4 = 8, d3 = 9, d2 = 10, d1 = 11;

const int digits[]    = {d1, d2, d3, d4};
const int segments[]  = {a, b, c, d, e, f, g};
const int zero[]      = {1, 1, 1, 1, 1, 1, 0};
const int one[]       = {0, 1, 1, 0, 0, 0, 0};
const int two[]       = {1, 1, 0, 1, 1, 0, 1};
const int three[]     = {1, 1, 1, 1, 0, 0, 1};
const int four[]      = {0, 1, 1, 0, 0, 1, 1};
const int five[]      = {1, 0, 1, 1, 0, 1, 1};
const int six[]       = {1, 0, 1, 1, 1, 1, 1};
const int seven[]     = {1, 1, 1, 0, 0, 0, 0};
const int eight[]     = {1, 1, 1, 1, 1, 1, 1};
const int nine[]      = {1, 1, 1, 1, 0, 1, 1};

const int del = 5; // Refresh delay in milliseconds

// Variables
int m1 = 0;
int m2 = 0;
int h1 = 0;
int h2 = 0;

void setup() {
  //  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
  }

  blank();
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    int h = tm.Hour;
    int m = tm.Minute;
    String hh = String(h);
    String mm = String(m);

    if ( h < 10 ) {
      h1 = 0;
      h2 = h;
    } else {
      h1 = hh.substring(0, 1).toInt();
      h2 = hh.substring(1, 2).toInt();
    }

    if ( m < 10 ) {
      m1 = 0;
      m2 = m;
    } else {
      m1 = mm.substring(0, 1).toInt();
      m2 = mm.substring(1, 2).toInt();
    }
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }

  selectDigitAndPrintNum(4, h1);
  delay(del);
  selectDigitAndPrintNum(3, h2);
  delay(del);
  selectDigitAndPrintNum(2, m1);
  delay(del);
  selectDigitAndPrintNum(1, m2);
  delay(del);
}


// Clears all LED segments
void blank() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], OFF);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(digits[i], OFF);
  }
}


// Turns on LED segments to show a number
void printNumber(int digi) {
  switch (digi) {
    case 0:
      for (int z = 0; z < 7; z++)
          if (zero[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 1:
      for (int z = 0; z < 7; z++)
          if (one[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 2:
      for (int z = 0; z < 7; z++)
          if (two[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 3:
      for (int z = 0; z < 7; z++)
          if (three[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 4:
      for (int z = 0; z < 7; z++)
          if (four[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 5:
      for (int z = 0; z < 7; z++)
          if (five[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 6:
      for (int z = 0; z < 7; z++)
          if (six[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 7:
      for (int z = 0; z < 7; z++)
          if (seven[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 8:
      for (int z = 0; z < 7; z++)
          if (eight[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 9:
      for (int z = 0; z < 7; z++)
          if (nine[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    default:
      for (int z = 0; z < 7; z++)
          if (zero[z] == 1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
  }
}

// Selects one of four digits and print a number
void selectDigitAndPrintNum(int digit, int num) {
  if (digit > 4 || digit < 1)
    return;
  if (num > 9 || num < 0)
    return;

  blank();
  for (int i = 0; i < 4; i++) {
    if (i == digit - 1) digitalWrite(digits[i], HIGH); else digitalWrite(digits[i], LOW);
  }
  printNumber(num);
}


