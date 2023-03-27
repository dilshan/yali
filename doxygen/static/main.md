Yet another LCD Interface
=========================

![YALI Hardware Module](../../resources/lcd-cnt-module-small.jpg)

The goal of the YALI (*Yet Another LCD Interface*) project is to provide a universal interface to drive the popular [Hitachi HD44780](https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller) LCD controller. This project offers open hardware module and C/C++ library for the HD44780 controller.

The hardware module of this project consists of a few CMOS logic ICs and a DC boost converter. This module designs to work with 5V and 3.3V DC power sources and logic circuits.

The YALI library is developed using C and is designed to be easily integrated with any C/C++ embedded toolchain. The current version of the YALI library provides built-in interfaces for the following embedded toolchains and platforms:

 - [Arduino](integrate_arduino.md)
 - [STM32 with LibOpenCM3](integrate_stm32.md)
 - [ESP8266 RTOS SDK](integrate_esp8266.md)
 - [Mid-range PIC MCUs with MPLAB XC8](integrate_pic_xc8.md)
 
The PCB of the YALI module can also order from the PCBWay website.

YALI is an open-source project. All the hardware designs and software source codes are available in the YALI project repository.

