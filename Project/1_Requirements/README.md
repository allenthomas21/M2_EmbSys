# Introduction

An ultrasonic sensor is an electronic device that omits ultrasonic sound waves to measure the distance of the object, and converts the reflected sound into an electrical signal. Ultrasonic waves move faster than  audible sound. Ultrasonic sensors have two major components. The transmitter and  receiver . In this project,  the ultrasound sensor was used in ATMEGA328 to determine the distance  from the sensor. Basic principles of ultrasound distance measurement are based on echo. If the sound wave is sent in the environment, the waves will return to the obstacle to the origin  after  the terms. Therefore, it is only necessary to calculate the travel time of both sounds, that is, the travel time to the origin after hitting an obstacle.

## 4W & 1H 

![4W 1H](https://user-images.githubusercontent.com/99074356/157278017-26030f55-707b-41fa-ac13-f759657973b5.png)

## Requirements

### High Level Requirements:
| ID | Description | Status |
|------| ------| ------|
| HLR1 | Enable ICP Interrupt | Implemented
|HLR2  | Warn the user if any objects are incoming against them | Implemented
|HLR3  | Enable rising edge detection,noise cancellation | Implemented
|HLR4  | Enable internal pullups on PORTC PINS  |	Implemented
|HLR5  |  I2C and LCD |	Implemented


### Low Level Requirements:

| ID | Description | Status |
|-------|------|------|
| LR01 |The Timer count of Timer2 was chosen | Implemented |
| LR02 |Timer2 of ATMEGA328p is used to generate a Trigger pulse of 20uS,  | Implemented |
| LR03 |The prescaler of this unit was chosen, such that the resolution of pulse-width is 16uS. | Implemented |

## SWOT ANALYSIS

![SWOT (1)](https://user-images.githubusercontent.com/99074356/157277682-7f0e49b7-da04-433b-998f-f564582f32d0.png)

## Block Diagram:

![Block Diagram](https://user-images.githubusercontent.com/99074356/157281091-51eea79a-b0a2-4b58-9557-a0283e672d0b.png)




