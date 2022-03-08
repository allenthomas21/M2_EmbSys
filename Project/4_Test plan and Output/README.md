

### High Level Test Plan:
| ID | Description | Status | Type of Test |
|------| ------| ------| -------- |
| HLR1 | Enable ICP Interrupt | PASS | Technical |
|HLR2  | Enable rising edge detection,noise cancellation | PASS | Technical |
|HLR3 | Enable internal pullups on PORTC PINS  |	PASS | Technical |
|HLR4 |  I2C and LCD |	PASS | Technical |



### Low Level Test Plan:

| ID | Description | Status | Type of Test |
|-------|------|------| ------ |
| LR01 |The Timer count of Timer2 was chosen | PASS | Technical |
| LR02 |Timer2 of ATMEGA328p is used to generate a Trigger pulse of 20uS,  | PASS | Technical |
| LR03 |The prescaler of this unit was chosen, such that the resolution of pulse-width is 16uS. | PASS | Technical |
