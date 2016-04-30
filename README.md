
Simple digital clock program using RTC.

Program takes around 8 KB program storage on microcontroller. So, ATMega8 could not be used. At least ATMega168/ATMega328 or ATTiny is required.

RTC libraries used:
    1. DS1307RTC: https://github.com/PaulStoffregen/DS1307RTC
    2. Time: https://github.com/PaulStoffregen/Time
Thanks *PaulStoffregen* for these awesome libraries.

These libraries need to be imported in Arduino SDK.

To set time on RTC, 'SetTime' example sketch under DS1307RTC RTC library can be used.
