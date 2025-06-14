Hi, we are the CJL team, and this is our GitHub repository, where we will be explaining and providing all the relevant information regarding the development of our autonomous car for the WRO Future Engineers category.






Engineering materials
This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2025.

Arduino UNO R3

Arduino UNO R4

Servomotor MG995

Ultrasonic sensor (3)

9v battery

Pixy CAM 2.1

wheels (4)

Hobby Gearmotor - 140 RPM (2)

H bridge

mini proto board 

jumpers and UTP wires 

4 18650 battteries


## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)

* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` 

* In the picture you can watch how the components that make the car works are conected, without even considering the color detection system.

* `src` contains code of control software for all components which were programmed to participate in the competition

* `other`![image](https://github.com/megasinser/CJL/assets/172218545/e6488643-3f07-460e-a66f-e38325339d0d) ![image](https://github.com/user-attachments/assets/6e243d78-3869-4b53-bc42-f2f5fd387e43) ![image](https://github.com/user-attachments/assets/23edb311-b0f5-40d5-b48f-c3643c94289a) ![image](https://github.com/user-attachments/assets/1b01f0b2-553e-4a33-8957-078d3880ced6)








## Introduction and Project description


For the creation of our autonomous car, I utilized several key components: two Arduino boards, three ultrasonic sensors, an H-bridge, four 18650 batteries, a 3D printed chassis, a reduction motor, and three motor enclosures (one with a motor, two with reduction gears but without motors).

To start, I assembled the chassis, as shown in the photo, and proceeded to connect the two Arduino boards. The three ultrasonic sensors were strategically placed: one on the right side, one on the left, and one in the front. I defined the appropriate pins for each sensor to gather distance data, allowing the robot to detect obstacles and avoid collisions. This data was then used to implement the turning logic, helping the car navigate the track and avoid obstacles.

I also connected a reduction motor to another motor reduction housing via a gearbox, as required by the competition rules. The H-bridge was used to control the motor's direction, allowing it to move forward or backward depending on the signal received from the control system.

For color detection, I integrated the Pixy camera with an Arduino using the PixyMon software. The camera was programmed to detect red, green, orange, and blue colors. Red and green were used to identify blocks or obstacles on the track, while blue and orange  were designated for detecting the track's lines at each corner. The camera’s output was processed by an Arduino, and based on the detected color, the Arduino would send a signal to the second Arduino to control the car's movement. For instance, if the camera detected green, the car would turn left, and if green was detected, it would turn left.

Additionally, the Pixy camera sends information about the color detected (including the X and Y coordinates of the block) to the Arduino, which then sends a HIGH signal to specific pins. This signal is received by the second Arduino to trigger the appropriate response: turning left for red or right for green.

To track the car’s laps, I implemented a counter in the Arduino connected to the Pixy camera. Each time the camera detected a set of four orange lines, one at each corner of the track, it counted as a full lap. After three laps, the Arduino would send a stop signal to the motor Arduino to halt the motors.

The entire system was powered by a total of 8 volts from four 18650 batteries, with a 5-volt regulator used to supply power to the Arduino boards, sensors, and servos.



