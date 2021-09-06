# Pawaro
 Pet automatic Feeder using Arduino

## Circuit

### Modules required
| Quantity 	| Module      	| Reference       	|
|----------	|-------------	|-----------------	|
| 1        	| LED RGB     	| Common Anode  	|
| 1        	| Servo Motor 	| SG90            	|
| 1        	| Switch      	| toggle switch   	|
| 2        	| Button      	| Normally closed 	|
| 1        	| RTC         	| DS13207 module  	|
| 1        	| Battery *   	| 3V CR2032       	|
| 1        	| Arduino     	| Any             	|
| 1        	| Resistance   	| 10kΩ            	|
| 3        	| Resistance   	| 220Ω          	|

\* Battery for the RTC module is optional
### Arduino connections
* Using an Arduino Pro Mini (ATmega328P, 5V 16MHz)
| Arduino 	| Module                       	|
|---------	|------------------------------	|
| VCC0    	| Source 5V                    	|
| VCC1    	| Servo(VCC), RTC(VCC), Button 	|
| GND     	| Ground                       	|
| 2       	| 10K resistor to ground       	|
| 3~       	| Reserved for update           |
| 5~      	| RGB Red                      	|
| 6~      	| RGB Green                    	|
| 9~      	| RGB Blue                     	|
| 10~      	| Servo(SIG)                   	|
| RST     	| Button to ground             	|

~ stands for PWM