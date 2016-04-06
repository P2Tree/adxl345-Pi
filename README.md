# README.md

## Brief

- this project is a c++ project.
- edit in Atom editor.
- compile with g++.
- run in RaspberryPi 3.
- dependency with wiringPi library.
- accelerometer is ADXL345.

## Function

- this project is used to control a accelerometer(ADXL345) to check accelerate.
- we will realize a bangle in arm to check when men wear it moving or steadby.
- It is quite obvious that a RaspberryPi can not wear in arm, and this is a test project. We will transplate it to ARM microcontroller.
- ADXL345 is a excellent accelerometer, it communicate to RaspberryPi with SPI(4 wires).
- This project is realized to check moving or steadby. If a higher than ACTIVITY Threshold accelerate was catched, "activity!" will be showed in terminal. If a lower than INACTIVITY Threshold accelerate was catched and keeping time over Time Threshold, "inactivity!" will be showed in terminal.

## Structure

- Download the project and make it.
- run `sudo ./all`.
- remember the root permission because of the wiringPi library.
- You can change RaspberryPi IO ports and SPI ports in project.
- In ADXL345, INT1 is activity interrupt and INT2 is inactivity interrupt.
- Thresholds can change in project.

## Note

Thanks to the project named adxl345-master, my project is based on this project with some classes and functions. But I am very sorry for it that I can not find this project links anymore.

License: GPLv2. See the LICENSE file for more details.
## Link

You can link me with email: dicksonliuming@gmail.com
My GITHUB is : PWESiberiaBear
