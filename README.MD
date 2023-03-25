Yet another LCD Interface
=========================

The goal of the YALI (Yet Another LCD Interface) project is to provide a universal interface to drive the popular Hitachi HD44780 LCD controller. This project offers open hardware module and C/C++ library for the HD44780 controller.

The hardware module of this project consists of a few CMOS logic ICs and a DC boost converter. This module designs to work with 5V and 3.3V DC power sources and logic circuits.

The YALI library is developed using C and is designed to be easily integrated with any C/C++ embedded toolchain. The current version of the YALI library provides built-in interfaces for the following embedded toolchains and platforms:

 - Arduino
 - STM32 with LibOpenCM3
 - ESP8266 RTOS SDK
 - Mid-range PIC MCUs with MPLAB XC C

YALI is an open-source project. All the hardware designs and software source codes are available in the YALI project repository.
