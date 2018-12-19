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
LIBS:SRAM
LIBS:xmega128a1u_bga100
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
P 6250 2950
F 0 "U3" H 6300 3400 60  0000 C CNN
F 1 "MOLEX_SIM_HOLDER_47553" H 6275 3275 60  0000 C CNN
F 2 "molex:MOLEX_SIM_HOLDER_47553" H 6225 2925 60  0000 C CNN
F 3 "" H 6225 2925 60  0000 C CNN
	1    6250 2950
	1    0    0    -1  
$EndComp
$Comp
L SMF05C D10
U 1 1 5A9F7A85
P 5225 4000
F 0 "D10" H 5325 4225 60  0000 C CNN
F 1 "SMF05C" H 5050 4225 60  0000 C CNN
F 2 "semtech:SOT363" H 5215 4000 60  0000 C CNN
F 3 "" H 5215 4000 60  0000 C CNN
	1    5225 4000
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R18
U 1 1 5A9F7A8D
P 4525 3425
F 0 "R18" V 4605 3425 40  0000 C CNN
F 1 "51Omh" V 4532 3426 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4455 3425 30  0000 C CNN
F 3 "" H 4525 3425 30  0000 C CNN
	1    4525 3425
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C22
U 1 1 5A9F7A94
P 4100 3750
F 0 "C22" H 4100 3850 40  0000 L CNN
F 1 "22pF" H 4106 3665 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4138 3600 30  0000 C CNN
F 3 "" H 4100 3750 60  0000 C CNN
	1    4100 3750
	1    0    0    -1  
$EndComp
NoConn ~ 6825 2900
$Comp
L R-RESCUE-xmobile R19
U 1 1 5A9F7AA1
P 4775 3000
F 0 "R19" V 4855 3000 40  0000 C CNN
F 1 "51Omh" V 4782 3001 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4705 3000 30  0000 C CNN
F 3 "" H 4775 3000 30  0000 C CNN
	1    4775 3000
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R20
U 1 1 5A9F7AA8
P 4975 2900
F 0 "R20" V 4925 2700 40  0000 C CNN
F 1 "51Omh" V 4982 2901 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4905 2900 30  0000 C CNN
F 3 "" H 4975 2900 30  0000 C CNN
	1    4975 2900
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R17
U 1 1 5A9F7AB2
P 2400 2925
F 0 "R17" V 2480 2925 40  0000 C CNN
F 1 "4.7KOmh" V 2407 2926 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2330 2925 30  0000 C CNN
F 3 "" H 2400 2925 30  0000 C CNN
	1    2400 2925
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C23
U 1 1 5A9F7AB9
P 5625 4200
F 0 "C23" H 5625 4300 40  0000 L CNN
F 1 "22pF" H 5631 4115 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5663 4050 30  0000 C CNN
F 3 "" H 5625 4200 60  0000 C CNN
	1    5625 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3425 4775 3425
Wire Wire Line
	4925 3425 4925 3775
Wire Wire Line
	4000 3425 4275 3425
Wire Wire Line
	4100 3425 4100 3550
Connection ~ 4100 3425
Connection ~ 4925 3425
Wire Wire Line
	6825 3000 7100 3000
Wire Wire Line
	3950 3100 5725 3100
Wire Wire Line
	5025 3775 5025 3200
Connection ~ 5025 3200
Wire Wire Line
	5325 3775 5325 2800
Connection ~ 5325 2800
Wire Wire Line
	5125 3775 5125 3000
Connection ~ 5125 3000
Wire Wire Line
	5150 2800 5725 2800
Wire Wire Line
	5225 2900 5725 2900
Wire Wire Line
	5025 3000 5725 3000
Wire Wire Line
	2650 2925 2700 2925
Wire Wire Line
	2700 2925 2700 3200
Connection ~ 2700 3200
Wire Wire Line
	5625 4000 5625 2800
Connection ~ 5625 2800
Text HLabel 5150 2800 0    60   Input ~ 0
SIM_VCC
Text HLabel 4725 2900 0    60   Input ~ 0
SIM_RST
Text HLabel 4525 3000 0    60   Input ~ 0
SIM_CLK
Text HLabel 5200 2100 0    60   BiDi ~ 0
GND
Text HLabel 2150 2925 0    60   Input ~ 0
GSM_VDD
Text HLabel 2200 3200 0    60   Output ~ 0
SIM_DET
Text HLabel 4000 3425 0    60   BiDi ~ 0
SIM_DATA
Text Label 5200 2100 0    60   ~ 0
GND
Text Label 6825 3100 0    60   ~ 0
GND
Text Label 5625 4400 3    60   ~ 0
GND
Text Label 5125 4375 3    60   ~ 0
GND
Text Label 4100 3950 3    60   ~ 0
GND
$Comp
L R-RESCUE-xmobile R27
U 1 1 5AB7668E
P 3175 3200
F 0 "R27" V 3255 3200 40  0000 C CNN
F 1 "0Omh" V 3182 3201 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3105 3200 30  0000 C CNN
F 3 "" H 3175 3200 30  0000 C CNN
	1    3175 3200
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R28
U 1 1 5AB7B1D6
P 3700 3100
F 0 "R28" V 3780 3100 40  0000 C CNN
F 1 "0Omh" V 3707 3101 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3630 3100 30  0000 C CNN
F 3 "" H 3700 3100 30  0000 C CNN
	1    3700 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3100 2825 3100
Wire Wire Line
	2825 3100 2825 3200
Connection ~ 2825 3200
Wire Wire Line
	5725 3200 3425 3200
Wire Wire Line
	2200 3200 2925 3200
NoConn ~ 5225 3775
Text Label 6825 2800 0    60   ~ 0
GND
Wire Wire Line
	7100 3000 7100 3425
$EndSCHEMATC
