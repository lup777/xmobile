EESchema Schematic File Version 2
LIBS:xmobile-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:XC6206P332MR
LIBS:STF202-22T1G
LIBS:MCP73871
LIBS:switch1
LIBS:xmobile-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOLEX_SIM_HOLDER_47553 U3
U 1 1 5A9F7A7E
P 6150 2950
F 0 "U3" H 6200 3400 60  0000 C CNN
F 1 "MOLEX_SIM_HOLDER_47553" H 6175 3275 60  0000 C CNN
F 2 "molex:MOLEX_SIM_HOLDER_47553" H 6125 2925 60  0000 C CNN
F 3 "" H 6125 2925 60  0000 C CNN
	1    6150 2950
	1    0    0    -1  
$EndComp
$Comp
L SMF05C D10
U 1 1 5A9F7A85
P 5125 4000
F 0 "D10" H 5225 4225 60  0000 C CNN
F 1 "SMF05C" H 4950 4225 60  0000 C CNN
F 2 "semtech:SOT363" H 5115 4000 60  0000 C CNN
F 3 "" H 5115 4000 60  0000 C CNN
	1    5125 4000
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R18
U 1 1 5A9F7A8D
P 4425 3425
F 0 "R18" V 4505 3425 40  0000 C CNN
F 1 "51Omh" V 4432 3426 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4355 3425 30  0000 C CNN
F 3 "" H 4425 3425 30  0000 C CNN
	1    4425 3425
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C22
U 1 1 5A9F7A94
P 4000 3750
F 0 "C22" H 4000 3850 40  0000 L CNN
F 1 "22pF" H 4006 3665 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4038 3600 30  0000 C CNN
F 3 "" H 4000 3750 60  0000 C CNN
	1    4000 3750
	1    0    0    -1  
$EndComp
NoConn ~ 6725 2900
$Comp
L R-RESCUE-xmobile R19
U 1 1 5A9F7AA1
P 4675 3000
F 0 "R19" V 4755 3000 40  0000 C CNN
F 1 "51Omh" V 4682 3001 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4605 3000 30  0000 C CNN
F 3 "" H 4675 3000 30  0000 C CNN
	1    4675 3000
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R20
U 1 1 5A9F7AA8
P 4875 2900
F 0 "R20" V 4825 2700 40  0000 C CNN
F 1 "51Omh" V 4882 2901 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4805 2900 30  0000 C CNN
F 3 "" H 4875 2900 30  0000 C CNN
	1    4875 2900
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R17
U 1 1 5A9F7AB2
P 3450 2925
F 0 "R17" V 3530 2925 40  0000 C CNN
F 1 "4.7KOmh" V 3457 2926 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3380 2925 30  0000 C CNN
F 3 "" H 3450 2925 30  0000 C CNN
	1    3450 2925
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C23
U 1 1 5A9F7AB9
P 5525 4200
F 0 "C23" H 5525 4300 40  0000 L CNN
F 1 "22pF" H 5531 4115 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5563 4050 30  0000 C CNN
F 3 "" H 5525 4200 60  0000 C CNN
	1    5525 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3425 4675 3425
Wire Wire Line
	4825 3425 4825 3775
Wire Wire Line
	3900 3425 4175 3425
Wire Wire Line
	4000 3425 4000 3550
Connection ~ 4000 3425
Connection ~ 4825 3425
Wire Wire Line
	6725 3000 7000 3000
Wire Wire Line
	7000 2800 7000 3425
Wire Wire Line
	3250 3200 5625 3200
Wire Wire Line
	5625 3100 5425 3100
Wire Wire Line
	5425 3100 5425 3200
Connection ~ 5425 3200
Wire Wire Line
	6725 2800 7000 2800
Connection ~ 7000 3000
Wire Wire Line
	4925 3775 4925 3200
Connection ~ 4925 3200
Wire Wire Line
	5225 3775 5225 2800
Connection ~ 5225 2800
Wire Wire Line
	5025 3775 5025 3000
Connection ~ 5025 3000
Wire Wire Line
	5050 2800 5625 2800
Wire Wire Line
	5125 2900 5625 2900
Wire Wire Line
	4925 3000 5625 3000
Wire Wire Line
	3700 2925 3750 2925
Wire Wire Line
	3750 2925 3750 3200
Connection ~ 3750 3200
Wire Wire Line
	5525 4000 5525 2800
Connection ~ 5525 2800
Text HLabel 5050 2800 0    60   Input ~ 0
SIM_VCC
Text HLabel 4625 2900 0    60   Input ~ 0
SIM_RST
Text HLabel 4425 3000 0    60   Input ~ 0
SIM_CLK
Text HLabel 5100 2100 0    60   BiDi ~ 0
GND
Text HLabel 3200 2925 0    60   Input ~ 0
GSM_VDD
Text HLabel 3250 3200 0    60   Output ~ 0
SIM_DET
Text HLabel 3900 3425 0    60   BiDi ~ 0
SIM_DATA
Text Label 5100 2100 0    60   ~ 0
GND_
Text Label 6725 3100 0    60   ~ 0
GND_
Text Label 5525 4400 3    60   ~ 0
GND_
Text Label 5025 4375 3    60   ~ 0
GND_
Text Label 4000 3950 3    60   ~ 0
GND_
$EndSCHEMATC
