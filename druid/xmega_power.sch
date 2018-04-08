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
Sheet 4 5
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
L +BATT #PWR03
U 1 1 5A9FD1BA
P 4625 5250
F 0 "#PWR03" H 4625 5200 20  0001 C CNN
F 1 "+BATT" H 4625 5350 30  0000 C CNN
F 2 "" H 4625 5250 60  0001 C CNN
F 3 "" H 4625 5250 60  0001 C CNN
	1    4625 5250
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L2
U 1 1 5A9FD1C0
P 7750 2250
F 0 "L2" V 7700 2250 40  0000 C CNN
F 1 "10mk" V 7850 2250 40  0000 C CNN
F 2 "Inductors:Inductor_1212" H 7750 2250 60  0000 C CNN
F 3 "" H 7750 2250 60  0000 C CNN
	1    7750 2250
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C31
U 1 1 5A9FD1C7
P 7250 2800
F 0 "C31" H 7250 2900 40  0000 L CNN
F 1 "100n" H 7256 2715 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7288 2650 30  0000 C CNN
F 3 "" H 7250 2800 60  0000 C CNN
	1    7250 2800
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C30
U 1 1 5A9FD1CE
P 6950 2800
F 0 "C30" H 6950 2900 40  0000 L CNN
F 1 "47mk" H 6956 2715 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6988 2650 30  0000 C CNN
F 3 "" H 6950 2800 60  0000 C CNN
	1    6950 2800
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C29
U 1 1 5A9FD1D5
P 6675 2800
F 0 "C29" H 6675 2900 40  0000 L CNN
F 1 "1mk (ceramic)" H 6681 2715 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6713 2650 30  0000 C CNN
F 3 "" H 6675 2800 60  0000 C CNN
	1    6675 2800
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C24
U 1 1 5A9FD1DC
P 4775 2450
F 0 "C24" H 4775 2550 40  0000 L CNN
F 1 "1mk (ceramic)" H 4781 2365 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4813 2300 30  0000 C CNN
F 3 "" H 4775 2450 60  0000 C CNN
	1    4775 2450
	-1   0    0    1   
$EndComp
$Comp
L GND-RESCUE-xmobile #PWR04
U 1 1 5A9FD1E3
P 5650 4125
F 0 "#PWR04" H 5650 4125 30  0001 C CNN
F 1 "GND" H 5650 4055 30  0001 C CNN
F 2 "" H 5650 4125 60  0001 C CNN
F 3 "" H 5650 4125 60  0001 C CNN
	1    5650 4125
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-xmobile C25
U 1 1 5A9FD1E9
P 4950 5575
F 0 "C25" H 4950 5675 40  0000 L CNN
F 1 "100mk (tantal)" H 4800 5450 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4988 5425 30  0000 C CNN
F 3 "" H 4950 5575 60  0000 C CNN
	1    4950 5575
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C26
U 1 1 5A9FD1F0
P 5425 5575
F 0 "C26" H 5425 5675 40  0000 L CNN
F 1 "10mk (ceramic)" H 5225 5500 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5463 5425 30  0000 C CNN
F 3 "" H 5425 5575 60  0000 C CNN
	1    5425 5575
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C27
U 1 1 5A9FD1F7
P 5850 5575
F 0 "C27" H 5850 5675 40  0000 L CNN
F 1 "33p" H 5856 5490 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5888 5425 30  0000 C CNN
F 3 "" H 5850 5575 60  0000 C CNN
	1    5850 5575
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C28
U 1 1 5A9FD1FE
P 6225 5575
F 0 "C28" H 6225 5675 40  0000 L CNN
F 1 "10p" H 6231 5490 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6263 5425 30  0000 C CNN
F 3 "" H 6225 5575 60  0000 C CNN
	1    6225 5575
	-1   0    0    1   
$EndComp
$Comp
L XC6206P332MR U4
U 1 1 5A9FD205
P 5700 2300
F 0 "U4" H 5700 2200 50  0000 C CNN
F 1 "XC6206P332MR" H 5700 2600 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5700 2300 50  0001 C CNN
F 3 "DOCUMENTATION" H 5700 2300 50  0001 C CNN
	1    5700 2300
	1    0    0    -1  
$EndComp
Text Label 5825 4025 0    60   ~ 0
GND
Text Label 6500 2475 3    60   ~ 0
GND
Text Label 7250 3250 3    60   ~ 0
GND
Text Label 6950 3250 3    60   ~ 0
GND
Text Label 6675 3275 3    60   ~ 0
GND
Text Label 4775 2900 3    60   ~ 0
GND
Text Label 4650 5875 2    60   ~ 0
GND
$Comp
L ZENER-RESCUE-xmobile D11
U 1 1 5A9FD218
P 6550 5575
F 0 "D11" H 6550 5675 50  0000 C CNN
F 1 "ZENER" H 6550 5475 40  0000 C CNN
F 2 "Diodes_SMD:SMA_Handsoldering" H 6550 5575 60  0000 C CNN
F 3 "" H 6550 5575 60  0000 C CNN
	1    6550 5575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 2250 7450 2250
Connection ~ 4775 2250
Wire Wire Line
	4775 2900 4775 2650
Wire Wire Line
	7250 3250 7250 3000
Wire Wire Line
	6950 3000 6950 3250
Wire Wire Line
	6950 2600 6950 2250
Connection ~ 6950 2250
Connection ~ 7250 2250
Connection ~ 6675 2250
Wire Wire Line
	6450 2350 6500 2350
Wire Wire Line
	6500 2350 6500 2475
Wire Wire Line
	5650 4125 5650 4025
Wire Wire Line
	5500 4025 5825 4025
Wire Wire Line
	6675 2250 6675 2600
Wire Wire Line
	6675 3275 6675 3000
Wire Wire Line
	7250 2600 7250 2250
Wire Wire Line
	3900 5250 6875 5250
Wire Wire Line
	4950 5775 4950 5875
Connection ~ 4950 5875
Wire Wire Line
	5425 5875 5425 5775
Connection ~ 5425 5875
Wire Wire Line
	5850 5875 5850 5775
Connection ~ 5850 5875
Wire Wire Line
	6225 5875 6225 5775
Connection ~ 6225 5875
Wire Wire Line
	4950 5375 4950 5250
Connection ~ 4950 5250
Wire Wire Line
	5425 5375 5425 5250
Connection ~ 5425 5250
Wire Wire Line
	5850 5375 5850 5250
Connection ~ 5850 5250
Wire Wire Line
	6225 5375 6225 5250
Connection ~ 6225 5250
Wire Wire Line
	6550 5250 6550 5375
Wire Wire Line
	6550 5875 6550 5775
Connection ~ 6550 5875
Connection ~ 6550 5250
Wire Wire Line
	4650 5875 6550 5875
$Comp
L +BATT #PWR05
U 1 1 5A9FE80A
P 4500 2250
F 0 "#PWR05" H 4500 2200 20  0001 C CNN
F 1 "+BATT" H 4500 2350 30  0000 C CNN
F 2 "" H 4500 2250 60  0001 C CNN
F 3 "" H 4500 2250 60  0001 C CNN
	1    4500 2250
	1    0    0    -1  
$EndComp
Text HLabel 8050 2250 2    60   Output ~ 0
3.3V
Text HLabel 6875 5250 2    60   Output ~ 0
3.7V
Text HLabel 5500 4025 0    60   Output ~ 0
GND
Connection ~ 5650 4025
Connection ~ 4500 2250
$Comp
L PWR_FLAG #FLG06
U 1 1 5AB7534F
P 4375 5250
F 0 "#FLG06" H 4375 5345 50  0001 C CNN
F 1 "PWR_FLAG" H 4375 5430 50  0000 C CNN
F 2 "" H 4375 5250 50  0000 C CNN
F 3 "" H 4375 5250 50  0000 C CNN
	1    4375 5250
	1    0    0    -1  
$EndComp
Connection ~ 4625 5250
$Comp
L PWR_FLAG #FLG07
U 1 1 5AB75478
P 5650 4025
F 0 "#FLG07" H 5650 4120 50  0001 C CNN
F 1 "PWR_FLAG" H 5650 4205 50  0000 C CNN
F 2 "" H 5650 4025 50  0000 C CNN
F 3 "" H 5650 4025 50  0000 C CNN
	1    5650 4025
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2250 4950 2250
Connection ~ 4375 5250
$Comp
L CONN_01X02 P9
U 1 1 5AB7EB32
P 3650 2650
F 0 "P9" H 3650 2800 50  0000 C CNN
F 1 "CONN_01X02" V 3750 2650 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-04P-2T_2x02x2.00mm_Straight" H 3650 2650 50  0000 C CNN
F 3 "" H 3650 2650 50  0000 C CNN
	1    3650 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 2600 4050 2600
Wire Wire Line
	4050 2600 4050 2250
Wire Wire Line
	3850 2700 4775 2700
Connection ~ 4775 2700
$Comp
L CONN_01X02 P8
U 1 1 5AB7ED0D
P 3575 5550
F 0 "P8" H 3575 5700 50  0000 C CNN
F 1 "CONN_01X02" V 3675 5550 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-04P-2T_2x02x2.00mm_Straight" H 3575 5550 50  0000 C CNN
F 3 "" H 3575 5550 50  0000 C CNN
	1    3575 5550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3775 5500 3900 5500
Wire Wire Line
	3900 5500 3900 5250
Wire Wire Line
	3775 5600 4700 5600
Wire Wire Line
	4700 5600 4700 5875
Connection ~ 4700 5875
$EndSCHEMATC
