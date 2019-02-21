EESchema Schematic File Version 4
LIBS:xmobile-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L xmobile-rescue:C-RESCUE-xmobile C10
U 1 1 5A9F1A09
P 5650 1950
F 0 "C10" H 5650 2050 40  0000 L CNN
F 1 "10pF" H 5656 1865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5688 1800 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5500 2475 60  0001 C CNN
F 4 "0402 In" H 5750 1800 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5650 1950 60  0001 C CNN "example"
	1    5650 1950
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C16
U 1 1 5A9F1A10
P 6150 1950
F 0 "C16" H 6150 2050 40  0000 L CNN
F 1 "33pF" H 6156 1865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6175 2125 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6150 1950 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6150 1950 60  0001 C CNN "example"
F 5 "0402 In" H 6250 1800 30  0000 C CNN "case"
	1    6150 1950
	1    0    0    -1  
$EndComp
Text Label 5650 3150 3    60   ~ 0
GND
Text Label 6150 3150 3    60   ~ 0
GND
Text Label 6150 1750 1    60   ~ 0
GND
Text Label 5650 1750 1    60   ~ 0
GND
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D2
U 1 1 5A9F1A3E
P 6725 1900
F 0 "D2" H 6725 2000 50  0000 C CNN
F 1 "LED BLUE" H 6725 1800 50  0000 C CNN
F 2 "LEDs:LED_0402" H 6725 1900 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 6725 1900 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 6725 1900 60  0001 C CNN "example"
F 5 "0402 In" H 6575 2000 30  0000 C CNN "case"
	1    6725 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 2150 5650 2250
Wire Wire Line
	5650 2650 5650 2750
Wire Wire Line
	6150 2650 6150 2750
Wire Wire Line
	6150 2150 6150 2250
Wire Wire Line
	6725 1600 6725 1750
Wire Wire Line
	6725 1600 7100 1600
Wire Wire Line
	7100 1600 7100 1750
Wire Wire Line
	6725 2050 6725 2200
Wire Wire Line
	5650 2200 7500 2200
Wire Wire Line
	6725 2700 6725 2850
Wire Wire Line
	5650 2700 7500 2700
Wire Wire Line
	6725 3150 6725 3300
Wire Wire Line
	6725 3300 7100 3300
Wire Wire Line
	7100 3300 7100 3150
Connection ~ 6150 2200
Connection ~ 5650 2200
Connection ~ 6150 2700
Connection ~ 5650 2700
Connection ~ 6725 2200
Connection ~ 6725 2700
Connection ~ 7100 2200
Connection ~ 7100 2700
Text Label 4025 5700 3    60   ~ 0
GND
Text Label 4525 5700 3    60   ~ 0
GND
Text Label 4525 4300 1    60   ~ 0
GND
Text Label 4025 4300 1    60   ~ 0
GND
Text Label 5900 5700 3    60   ~ 0
GND
Text Label 6400 5700 3    60   ~ 0
GND
Text Label 6400 4300 1    60   ~ 0
GND
Text Label 5900 4300 1    60   ~ 0
GND
Wire Wire Line
	4025 4700 4025 4800
Wire Wire Line
	4025 5200 4025 5300
Wire Wire Line
	4525 5200 4525 5300
Wire Wire Line
	4525 4700 4525 4800
Wire Wire Line
	5900 4700 5900 4800
Wire Wire Line
	5900 5200 5900 5300
Wire Wire Line
	6400 5200 6400 5300
Wire Wire Line
	6400 4700 6400 4800
Wire Wire Line
	6975 4150 6975 4300
Wire Wire Line
	6975 4150 7350 4150
Wire Wire Line
	7350 4150 7350 4300
Wire Wire Line
	6975 4750 6975 4600
Wire Wire Line
	6975 5250 6975 5400
Wire Wire Line
	4025 5250 7650 5250
Wire Wire Line
	6975 5700 6975 5850
Wire Wire Line
	6975 5850 7350 5850
Wire Wire Line
	7350 5850 7350 5700
Connection ~ 6400 4750
Connection ~ 5900 4750
Connection ~ 6400 5250
Connection ~ 5900 5250
Connection ~ 6975 4750
Connection ~ 6975 5250
Connection ~ 7350 4750
Connection ~ 7350 5250
Connection ~ 4525 4750
Connection ~ 4525 5250
Connection ~ 4025 4750
Connection ~ 4025 5250
Text HLabel 5650 2200 0    60   Input ~ 0
AUDIO_MICP
Text HLabel 5650 2700 0    60   Input ~ 0
AUDIO_MICN
Text HLabel 4025 4750 0    60   Input ~ 0
AUDIO_SPKP
Text HLabel 4025 5250 0    60   Input ~ 0
AUDIO_SPKN
Wire Wire Line
	7100 2700 7100 2850
$Comp
L xmobile-rescue:TEST-RESCUE-xmobile W?
U 1 1 5C6D0927
P 7500 2450
AR Path="/5C6D0927" Ref="W?"  Part="1" 
AR Path="/5A9ED5F5/5C6D0927" Ref="W?"  Part="1" 
F 0 "W?" H 7500 2510 50  0000 C CNN
F 1 "MIC" H 7500 2380 50  0000 C CNN
F 2 "Measurement_Points:Test_Point_2Pads" H 7450 2600 50  0001 C CNN
F 3 "" H 7500 2450 50  0000 C CNN
F 4 "2 pads" H 7500 2550 30  0000 C CNN "case"
	1    7500 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 2200 7100 2050
Wire Wire Line
	7500 2700 7500 2650
Wire Wire Line
	7500 2200 7500 2250
$Comp
L xmobile-rescue:TEST-RESCUE-xmobile W?
U 1 1 5C6D0EE0
P 7650 5000
AR Path="/5C6D0EE0" Ref="W?"  Part="1" 
AR Path="/5A9ED5F5/5C6D0EE0" Ref="W?"  Part="1" 
F 0 "W?" H 7650 5060 50  0000 C CNN
F 1 "SPK" H 7650 4930 50  0000 C CNN
F 2 "Measurement_Points:Test_Point_2Pads" H 7600 5150 50  0001 C CNN
F 3 "" H 7650 5000 50  0000 C CNN
F 4 "2 pads" H 7650 5100 30  0000 C CNN "case"
	1    7650 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 5250 7650 5200
Wire Wire Line
	7350 5400 7350 5250
Wire Wire Line
	7650 4750 7650 4800
Wire Wire Line
	7350 4750 7350 4600
Wire Wire Line
	4025 4750 7650 4750
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D694B
P 5650 2450
F 0 "C?" H 5650 2550 40  0000 L CNN
F 1 "10pF" H 5656 2365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5688 2300 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5500 2975 60  0001 C CNN
F 4 "0402 In" H 5750 2300 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5650 2450 60  0001 C CNN "example"
	1    5650 2450
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6A3D
P 5650 2950
F 0 "C?" H 5650 3050 40  0000 L CNN
F 1 "10pF" H 5656 2865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5688 2800 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5500 3475 60  0001 C CNN
F 4 "0402 In" H 5750 2800 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5650 2950 60  0001 C CNN "example"
	1    5650 2950
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6B0E
P 6150 2450
F 0 "C?" H 6150 2550 40  0000 L CNN
F 1 "33pF" H 6156 2365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6175 2625 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6150 2450 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6150 2450 60  0001 C CNN "example"
F 5 "0402 In" H 6250 2300 30  0000 C CNN "case"
	1    6150 2450
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6B9B
P 6150 2950
F 0 "C?" H 6150 3050 40  0000 L CNN
F 1 "33pF" H 6156 2865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6175 3125 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6150 2950 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6150 2950 60  0001 C CNN "example"
F 5 "0402 In" H 6250 2800 30  0000 C CNN "case"
	1    6150 2950
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6CC6
P 5900 4500
F 0 "C?" H 5900 4600 40  0000 L CNN
F 1 "10pF" H 5906 4415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5938 4350 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5750 5025 60  0001 C CNN
F 4 "0402 In" H 6000 4350 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5900 4500 60  0001 C CNN "example"
	1    5900 4500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6D99
P 6400 4500
F 0 "C?" H 6400 4600 40  0000 L CNN
F 1 "33pF" H 6406 4415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6425 4675 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6400 4500 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6400 4500 60  0001 C CNN "example"
F 5 "0402 In" H 6500 4350 30  0000 C CNN "case"
	1    6400 4500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6EE0
P 5900 5000
F 0 "C?" H 5900 5100 40  0000 L CNN
F 1 "10pF" H 5906 4915 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5938 4850 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5750 5525 60  0001 C CNN
F 4 "0402 In" H 6000 4850 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5900 5000 60  0001 C CNN "example"
	1    5900 5000
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D6F6B
P 5900 5500
F 0 "C?" H 5900 5600 40  0000 L CNN
F 1 "10pF" H 5906 5415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5938 5350 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 5750 6025 60  0001 C CNN
F 4 "0402 In" H 6000 5350 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 5900 5500 60  0001 C CNN "example"
	1    5900 5500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D7042
P 6400 5000
F 0 "C?" H 6400 5100 40  0000 L CNN
F 1 "33pF" H 6406 4915 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6425 5175 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6400 5000 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6400 5000 60  0001 C CNN "example"
F 5 "0402 In" H 6500 4850 30  0000 C CNN "case"
	1    6400 5000
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D70D1
P 6400 5500
F 0 "C?" H 6400 5600 40  0000 L CNN
F 1 "33pF" H 6406 5415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6425 5675 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 6400 5500 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 6400 5500 60  0001 C CNN "example"
F 5 "0402 In" H 6500 5350 30  0000 C CNN "case"
	1    6400 5500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D7206
P 4025 4500
F 0 "C?" H 4025 4600 40  0000 L CNN
F 1 "10pF" H 4031 4415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4063 4350 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 3875 5025 60  0001 C CNN
F 4 "0402 In" H 4125 4350 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 4025 4500 60  0001 C CNN "example"
	1    4025 4500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D72FB
P 4025 5000
F 0 "C?" H 4025 5100 40  0000 L CNN
F 1 "10pF" H 4031 4915 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4063 4850 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 3875 5525 60  0001 C CNN
F 4 "0402 In" H 4125 4850 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 4025 5000 60  0001 C CNN "example"
	1    4025 5000
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D7388
P 4025 5500
F 0 "C?" H 4025 5600 40  0000 L CNN
F 1 "10pF" H 4031 5415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4063 5350 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 3875 6025 60  0001 C CNN
F 4 "0402 In" H 4125 5350 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 4025 5500 60  0001 C CNN "example"
	1    4025 5500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D77F5
P 4525 4500
F 0 "C?" H 4525 4600 40  0000 L CNN
F 1 "33pF" H 4531 4415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4550 4675 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 4525 4500 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 4525 4500 60  0001 C CNN "example"
F 5 "0402 In" H 4625 4350 30  0000 C CNN "case"
	1    4525 4500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D78F0
P 4525 5000
F 0 "C?" H 4525 5100 40  0000 L CNN
F 1 "33pF" H 4531 4915 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4550 5175 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 4525 5000 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 4525 5000 60  0001 C CNN "example"
F 5 "0402 In" H 4625 4850 30  0000 C CNN "case"
	1    4525 5000
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C?
U 1 1 5C6D7979
P 4525 5500
F 0 "C?" H 4525 5600 40  0000 L CNN
F 1 "33pF" H 4531 5415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4550 5675 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 4525 5500 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 4525 5500 60  0001 C CNN "example"
F 5 "0402 In" H 4625 5350 30  0000 C CNN "case"
	1    4525 5500
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C7622
P 7100 1900
F 0 "D?" H 7100 2000 50  0000 C CNN
F 1 "LED BLUE" H 7100 1800 50  0000 C CNN
F 2 "LEDs:LED_0402" H 7100 1900 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 7100 1900 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 7100 1900 60  0001 C CNN "example"
F 5 "0402 In" H 6950 2000 30  0000 C CNN "case"
	1    7100 1900
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C77F4
P 7100 3000
F 0 "D?" H 7100 3100 50  0000 C CNN
F 1 "LED BLUE" H 7100 2900 50  0000 C CNN
F 2 "LEDs:LED_0402" H 7100 3000 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 7100 3000 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 7100 3000 60  0001 C CNN "example"
F 5 "0402 In" H 6950 3100 30  0000 C CNN "case"
	1    7100 3000
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C796F
P 6725 3000
F 0 "D?" H 6725 3100 50  0000 C CNN
F 1 "LED BLUE" H 6725 2900 50  0000 C CNN
F 2 "LEDs:LED_0402" H 6725 3000 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 6725 3000 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 6725 3000 60  0001 C CNN "example"
F 5 "0402 In" H 6575 3100 30  0000 C CNN "case"
	1    6725 3000
	0    -1   -1   0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C7BA9
P 6975 4450
F 0 "D?" H 6975 4550 50  0000 C CNN
F 1 "LED BLUE" H 6975 4350 50  0000 C CNN
F 2 "LEDs:LED_0402" H 6975 4450 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 6975 4450 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 6975 4450 60  0001 C CNN "example"
F 5 "0402 In" H 6825 4550 30  0000 C CNN "case"
	1    6975 4450
	0    -1   -1   0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C7D73
P 7350 4450
F 0 "D?" H 7350 4550 50  0000 C CNN
F 1 "LED BLUE" H 7350 4350 50  0000 C CNN
F 2 "LEDs:LED_0402" H 7350 4450 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 7350 4450 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 7350 4450 60  0001 C CNN "example"
F 5 "0402 In" H 7200 4550 30  0000 C CNN "case"
	1    7350 4450
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C7FDB
P 7350 5550
F 0 "D?" H 7350 5650 50  0000 C CNN
F 1 "LED BLUE" H 7350 5450 50  0000 C CNN
F 2 "LEDs:LED_0402" H 7350 5550 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 7350 5550 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 7350 5550 60  0001 C CNN "example"
F 5 "0402 In" H 7200 5650 30  0000 C CNN "case"
	1    7350 5550
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C6C809E
P 6975 5550
F 0 "D?" H 6975 5650 50  0000 C CNN
F 1 "LED BLUE" H 6975 5450 50  0000 C CNN
F 2 "LEDs:LED_0402" H 6975 5550 60  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 6975 5550 60  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 6975 5550 60  0001 C CNN "example"
F 5 "0402 In" H 6825 5650 30  0000 C CNN "case"
	1    6975 5550
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
