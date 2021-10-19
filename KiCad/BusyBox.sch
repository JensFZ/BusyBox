EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "BusyBoy"
Date "2021-10-19"
Rev "Rev 1"
Comp "JensFZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D1
U 1 1 6168C071
P 7000 2150
F 0 "D1" H 6993 1895 50  0000 C CNN
F 1 "LED" H 6993 1986 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 7000 2150 50  0001 C CNN
F 3 "~" H 7000 2150 50  0001 C CNN
	1    7000 2150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 6168E919
P 7500 2150
F 0 "R1" V 7293 2150 50  0000 C CNN
F 1 "R" V 7384 2150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 2150 50  0001 C CNN
F 3 "~" H 7500 2150 50  0001 C CNN
	1    7500 2150
	0    1    1    0   
$EndComp
Text GLabel 3000 4650 1    50   Input ~ 0
SW1
Text GLabel 3300 2250 2    50   Input ~ 0
SW3
Wire Wire Line
	7150 2150 7350 2150
$Comp
L kicad-library:GND #PWR07
U 1 1 616A1C9A
P 7650 2150
F 0 "#PWR07" H 7650 1900 50  0001 C CNN
F 1 "GND" V 7655 2022 50  0000 R CNN
F 2 "" H 7650 2150 50  0000 C CNN
F 3 "" H 7650 2150 50  0000 C CNN
	1    7650 2150
	0    -1   -1   0   
$EndComp
Text GLabel 3300 2550 2    50   Input ~ 0
LED_Gruen
Text GLabel 6600 2150 0    50   Input ~ 0
LED_Gruen
$Comp
L Device:LED D2
U 1 1 616A5B70
P 7000 2600
F 0 "D2" H 6993 2345 50  0000 C CNN
F 1 "LED" H 6993 2436 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 7000 2600 50  0001 C CNN
F 3 "~" H 7000 2600 50  0001 C CNN
	1    7000 2600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 616A60EB
P 7500 2600
F 0 "R2" V 7293 2600 50  0000 C CNN
F 1 "R" V 7384 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 2600 50  0001 C CNN
F 3 "~" H 7500 2600 50  0001 C CNN
	1    7500 2600
	0    1    1    0   
$EndComp
$Comp
L kicad-library:GND #PWR08
U 1 1 616A66AF
P 7650 2600
F 0 "#PWR08" H 7650 2350 50  0001 C CNN
F 1 "GND" V 7655 2472 50  0000 R CNN
F 2 "" H 7650 2600 50  0000 C CNN
F 3 "" H 7650 2600 50  0000 C CNN
	1    7650 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7150 2600 7350 2600
Wire Wire Line
	6600 2150 6850 2150
Text GLabel 3300 2650 2    50   Input ~ 0
LED_Rot
Text GLabel 6600 2600 0    50   Input ~ 0
LED_Rot
Wire Wire Line
	6600 2600 6850 2600
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 616F1231
P 7400 4000
F 0 "J1" H 7372 3882 50  0000 R CNN
F 1 "Conn_01x04_Male" H 7372 3973 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7400 4000 50  0001 C CNN
F 3 "~" H 7400 4000 50  0001 C CNN
	1    7400 4000
	-1   0    0    1   
$EndComp
Text GLabel 7200 4000 0    50   Input ~ 0
5V
Text GLabel 7200 4100 0    50   Input ~ 0
GND
Text GLabel 7200 3900 0    50   Input ~ 0
SDA
Text GLabel 7200 3800 0    50   Input ~ 0
SCL
Text GLabel 3300 1950 2    50   Input ~ 0
SCL
Text GLabel 3300 2050 2    50   Input ~ 0
SDA
$Comp
L nodemcu:NodeMCU_LUA_Amica_V2 U1
U 1 1 616FFE69
P 2850 2550
F 0 "U1" H 2850 3475 50  0000 C CNN
F 1 "NodeMCU_LUA_Amica_V2" H 2850 3384 50  0000 C CNN
F 2 "ESP8266:NodeMCU-LoLinV3" H 3100 2550 50  0001 C CNN
F 3 "" H 3100 2550 50  0000 C CNN
	1    2850 2550
	1    0    0    -1  
$EndComp
Text GLabel 2400 3250 0    50   Input ~ 0
5V
$Comp
L Switch:SW_DIP_x03 SW1
U 1 1 6170F6DB
P 2700 5250
F 0 "SW1" H 2700 5717 50  0000 C CNN
F 1 "SW_DIP_x03" H 2700 5626 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DIP_SPSTx03_Slide_9.78x9.8mm_W7.62mm_P2.54mm" H 2700 5250 50  0001 C CNN
F 3 "~" H 2700 5250 50  0001 C CNN
	1    2700 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 61712C79
P 3550 5050
F 0 "R3" V 3343 5050 50  0000 C CNN
F 1 "R" V 3434 5050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3480 5050 50  0001 C CNN
F 3 "~" H 3550 5050 50  0001 C CNN
	1    3550 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 617133DF
P 3850 5250
F 0 "R5" V 3643 5250 50  0000 C CNN
F 1 "R" V 3734 5250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3780 5250 50  0001 C CNN
F 3 "~" H 3850 5250 50  0001 C CNN
	1    3850 5250
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 61713DD6
P 3700 5150
F 0 "R4" V 3493 5150 50  0000 C CNN
F 1 "R" V 3584 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3630 5150 50  0001 C CNN
F 3 "~" H 3700 5150 50  0001 C CNN
	1    3700 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 5050 3400 5050
Wire Wire Line
	3550 5150 3100 5150
Wire Wire Line
	3000 5250 3200 5250
Text GLabel 4300 5250 2    50   Input ~ 0
GND
Wire Wire Line
	4000 5250 4150 5250
Wire Wire Line
	3850 5150 4150 5150
Wire Wire Line
	4150 5150 4150 5250
Connection ~ 4150 5250
Wire Wire Line
	4150 5250 4300 5250
Wire Wire Line
	3700 5050 4150 5050
Wire Wire Line
	4150 5050 4150 5150
Connection ~ 4150 5150
Wire Wire Line
	3000 4650 3000 5050
Connection ~ 3000 5050
Text GLabel 3300 2850 2    50   Input ~ 0
SW1
Text GLabel 3100 4650 1    50   Input ~ 0
SW2
Wire Wire Line
	3100 4650 3100 5150
Connection ~ 3100 5150
Wire Wire Line
	3100 5150 3000 5150
Text GLabel 3200 4650 1    50   Input ~ 0
SW3
Wire Wire Line
	3200 4650 3200 5250
Connection ~ 3200 5250
Wire Wire Line
	3200 5250 3700 5250
Text GLabel 3300 3250 2    50   Input ~ 0
3V3
Text GLabel 2400 5050 0    50   Input ~ 0
3V3
Text GLabel 2400 5150 0    50   Input ~ 0
3V3
Text GLabel 2400 5250 0    50   Input ~ 0
3V3
NoConn ~ 3300 1850
NoConn ~ 3300 2150
NoConn ~ 3300 2350
NoConn ~ 3300 2950
NoConn ~ 3300 3050
NoConn ~ 2400 1850
NoConn ~ 2400 1950
NoConn ~ 2400 2150
NoConn ~ 2400 2250
NoConn ~ 2400 2350
NoConn ~ 2400 2450
NoConn ~ 2400 2550
NoConn ~ 2400 2650
NoConn ~ 2400 2750
NoConn ~ 2400 2850
NoConn ~ 2400 2950
NoConn ~ 2400 3050
Text GLabel 3300 2750 2    50   Input ~ 0
SW2
NoConn ~ 3300 2450
Text GLabel 3300 3150 2    50   Input ~ 0
GND
NoConn ~ 2400 3150
NoConn ~ 2400 2050
$EndSCHEMATC
