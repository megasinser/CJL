Engineering materials
This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2022.

Arduino Mega

Servomotor SG 90

Ultrasonic sensor (3)

9v battery

ESP32 CAM

wheels (4)

Hobby Gearmotor - 140 RPM (2)

L293D dual motor driver 

mini proto board 

jumpers and UTP wires 


## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)

* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition

* `other`![image](https://github.com/megasinser/CJL/assets/172218545/e6488643-3f07-460e-a66f-e38325339d0d) ![image](https://github.com/megasinser/CJL/assets/172218545/60036aba-ae2b-4365-8bf6-343d4149d472) ![image](https://github.com/megasinser/CJL/assets/172218545/1023b9ff-cf79-4327-85df-4dd405180b8e)




## Introduction

In our project, we are using an Arduino Mega as the microcontroller. It controls a servomotor, ultrasonic sensors, and an ESP32 CAM. The ultrasonic sensors, one on each side of the car and one in the front, indicate to the servomotor when the car needs to turn right or left. The sensor in the front works together with an ESP32 CAM to properly detect obstacles on the track. The camera uses OpenCV and HSV color space for image processing and color detection.



