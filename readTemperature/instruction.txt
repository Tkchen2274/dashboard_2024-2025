1. Read in voltage at serial port A0 (or any A* port, just change line 59 respectively)
2. Voltage is read in and displayed in maximum 5V and minimum 0V
3. Using V1/V2 = R1/R2
4. Temperature formula derived from https://www.amphenol-sensors.com/hubfs/Documents/AAS-920-657F-Thermometrics-GE1935-103020-web.pdf?Itemid=8484%20' using logrithmic
5. Output temperature in console

To connect the thermistor, connect the thermistor with another resistant (e.g. 10000 Ohm) in series, and a voltmeter (in our case, the arduino) in parallel, and connect the whole set to a power supply (in our case, just connect arduino with your computer)