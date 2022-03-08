# Introduction

This circuit was developed by connecting the ultrasonic sensor to an AVR microcontroller. This sensor uses a technique called "echo" that is obtained when the sound bounces after hitting a surface. We know that sound vibrations cannot penetrate  solids. Therefore, when  sound sources generate vibrations, they move in the air at a speed of 220 meters per second. These vibrations are called sounds when they hit your ears. As mentioned earlier, these vibrations can not pass firmly throughout. The ultrasound sensor "HCSR04" provides an output signal proportional to an echo-based distance. Here, the sensor creates sound vibration in the ultrasonic range, and when it brings a trigger, the sound vibration is waiting to return. The purpose of this is, it is fitted in vehicles to prevent collision and assist in self parking.

## High Level Requirements:
| ID | Description | Status |
|------| ------| ------|
| HLR1 | Enable ICP Interrupt | Implemented
|HLR2  | Warn the user if any objects are incoming against them | Implemented
|HLR3  | Enable rising edge detection,noise cancellation | Implemented
|HLR4  | Enable internal pullups on PORTC PINS  |	Implemented
|HLR5  |  I2C and LCD |	Implemented


## Low Level Requirements:

| ID | Description | Status |
|-------|------|------|
| LR01 |The Timer count of Timer2 was chosen | Implemented |
| LR02 |Timer2 of ATMEGA328p is used to generate a Trigger pulse of 20uS,  | Implemented |
| LR03 |The prescaler of this unit was chosen, such that the resolution of pulse-width is 16uS. | Implemented |

### SWOT ANALYSIS
