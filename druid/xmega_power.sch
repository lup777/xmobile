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
LIBS:sim-holders
LIBS:max7370
LIBS:tp4056
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
L INDUCTOR L2
U 1 1 5A9FD1C0
P 9100 2050
F 0 "L2" V 9025 1925 40  0000 C CNN
F 1 "10u" V 9200 2050 40  0000 C CNN
F 2 "inductor_1210_In:I_1210" H 9100 2050 60  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/product-1022158.pdf" H 9100 2050 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Murata-Electronics/1276AS-H-100M%3dP2?qs=sGAEpiMZZMsg%252by3WlYCkUwoncuxJKc7T%2ffTlu7eSjNI%3d" V 9100 2050 60  0001 C CNN "example"
F 5 "1210 In" V 9025 2100 30  0000 C CNN "case"
	1    9100 2050
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-xmobile C31
U 1 1 5A9FD1C7
P 8600 2600
F 0 "C31" H 8600 2700 40  0000 L CNN
F 1 "0,1p" H 8606 2515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8638 2450 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/c02e-1068346.pdf" H 8600 2600 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GJM1555C1HR10WB01D?qs=sGAEpiMZZMs0AnBnWHyRQNchIam%2fLmo3tiNUbw4QmZU%3d" H 8600 2600 60  0001 C CNN "example"
F 5 "0402 In" H 8625 2450 30  0000 C CNN "case"
	1    8600 2600
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C30
U 1 1 5A9FD1CE
P 8300 2600
F 0 "C30" H 8300 2700 40  0000 L CNN
F 1 "47u" H 8306 2515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8338 2450 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/ZRB18AR60J476ME01-01-1065054.pdf" H 8300 2600 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Murata-Electronics/ZRB18AR60J476ME01L?qs=sGAEpiMZZMs0AnBnWHyRQO9VYadaKTO%252bP4WrvUq8FwyMAQotVEzL0w%3d%3d" H 8300 2600 60  0001 C CNN "example"
F 5 "0603 In" H 8325 2450 30  0000 C CNN "case"
	1    8300 2600
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C29
U 1 1 5A9FD1D5
P 8025 2600
F 0 "C29" H 8025 2700 40  0000 L CNN
F 1 "1u" H 8031 2515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8063 2450 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 8025 2600 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM152R60J105ME15D?qs=sGAEpiMZZMs0AnBnWHyRQFv7x1xn%252bYFdnvIvPkVU8UD1CmfL1E6gmw%3d%3d" H 8025 2600 60  0001 C CNN "example"
F 5 "0402 In" H 8050 2450 30  0000 C CNN "case"
	1    8025 2600
	-1   0    0    1   
$EndComp
$Comp
L GND-RESCUE-xmobile #PWR04
U 1 1 5A9FD1E3
P 5750 3800
F 0 "#PWR04" H 5750 3800 30  0001 C CNN
F 1 "GND" H 5750 3730 30  0001 C CNN
F 2 "" H 5750 3800 60  0001 C CNN
F 3 "" H 5750 3800 60  0001 C CNN
	1    5750 3800
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-xmobile C27
U 1 1 5A9FD1F7
P 8375 5575
F 0 "C27" H 8375 5675 40  0000 L CNN
F 1 "33p" H 8381 5490 40  0000 L CNN
F 2 "" H 8413 5425 30  0000 C CNN
F 3 "https://eu.mouser.com/datasheet/2/212/KEM_C1023_X7R_AUTO_SMD-1093309.pdf" H 8375 5575 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/KEMET/C0402C330J9RACAUTO?qs=sGAEpiMZZMs0AnBnWHyRQB295tntAovfdTfJuYu7h0zCBKUrKoz%252bFQ%3d%3d" H 8375 5575 60  0001 C CNN "example"
F 5 "0402 In" H 8400 5425 30  0000 C CNN "case"
	1    8375 5575
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-xmobile C28
U 1 1 5A9FD1FE
P 8750 5575
F 0 "C28" H 8750 5675 40  0000 L CNN
F 1 "10p" H 8756 5490 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8788 5425 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/C0GNP0-Dielectric-951274.pdf" H 8750 5575 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/AVX/04026A100JAT2A?qs=sGAEpiMZZMs0AnBnWHyRQKJCfzG%2fi9wHQ0Xs5mzrghpcPP2bNIxEUw%3d%3d" H 8750 5575 60  0001 C CNN "example"
F 5 "0402 In" H 8775 5425 30  0000 C CNN "case"
	1    8750 5575
	-1   0    0    1   
$EndComp
$Comp
L XC6206P332MR U4
U 1 1 5A9FD205
P 7050 2100
F 0 "U4" H 7050 2000 50  0000 C CNN
F 1 "XC6206P332MR" H 7050 2400 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7075 1800 50  0001 C CNN
F 3 "https://www.torexsemi.com/file/xc6206/XC6206.pdf" H 7050 2100 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Torex-Semiconductor/XC6206P332MR-G?qs=%2fha2pyFadujKR1ng7kOnkt2m1eqUI4JxTF4iTczT8BCZBroFPKl6%2fA%3d%3d" H 7050 2100 60  0001 C CNN "example"
F 5 "SOT-23" H 7050 2100 30  0000 C CNN "case"
	1    7050 2100
	1    0    0    -1  
$EndComp
Text Label 5925 3700 0    60   ~ 0
GND
Text Label 7850 2275 3    60   ~ 0
GND
Text Label 8600 3050 3    60   ~ 0
GND
Text Label 8300 3050 3    60   ~ 0
GND
Text Label 8025 3075 3    60   ~ 0
GND
Text Label 7475 5875 2    60   ~ 0
GND
$Comp
L ZENER-RESCUE-xmobile D11
U 1 1 5A9FD218
P 9075 5575
F 0 "D11" V 8975 5650 50  0000 C CNN
F 1 "ZENER" H 9075 5475 40  0000 C CNN
F 2 "Diodes_SMD:SMA_Standard" H 9075 5575 60  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/308/1SMA5913BT3-D-1360201.pdf" H 9075 5575 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ON-Semiconductor/1SMA5918BT3G?qs=sGAEpiMZZMtQ8nqTKtFS%2fJ7m6e1KBCgu1vB5isutOYc%3d" H 9075 5575 60  0001 C CNN "example"
F 5 "SMA 403D" V 9200 5575 30  0000 C CNN "case "
	1    9075 5575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7800 2050 8800 2050
Wire Wire Line
	8600 3050 8600 2800
Wire Wire Line
	8300 2800 8300 3050
Wire Wire Line
	8300 2400 8300 2050
Connection ~ 8300 2050
Connection ~ 8600 2050
Connection ~ 8025 2050
Wire Wire Line
	7800 2150 7850 2150
Wire Wire Line
	7850 2150 7850 2275
Wire Wire Line
	5750 3800 5750 3700
Wire Wire Line
	5600 3700 5925 3700
Wire Wire Line
	8025 2050 8025 2400
Wire Wire Line
	8025 3075 8025 2800
Wire Wire Line
	8600 2400 8600 2050
Wire Wire Line
	3825 5250 9400 5250
Wire Wire Line
	7475 5675 7475 5875
Connection ~ 7475 5875
Wire Wire Line
	7950 5725 7950 5875
Connection ~ 7950 5875
Wire Wire Line
	8375 5875 8375 5775
Connection ~ 8375 5875
Wire Wire Line
	8750 5875 8750 5775
Connection ~ 8750 5875
Wire Wire Line
	7475 5250 7475 5475
Connection ~ 7475 5250
Wire Wire Line
	7950 5250 7950 5425
Connection ~ 7950 5250
Wire Wire Line
	8375 5375 8375 5250
Connection ~ 8375 5250
Wire Wire Line
	8750 5375 8750 5250
Connection ~ 8750 5250
Wire Wire Line
	9075 5250 9075 5375
Wire Wire Line
	9075 5875 9075 5775
Connection ~ 9075 5875
Connection ~ 9075 5250
$Comp
L +BATT #PWR05
U 1 1 5A9FE80A
P 2450 1450
F 0 "#PWR05" H 2450 1400 20  0001 C CNN
F 1 "+BATT" H 2450 1550 30  0000 C CNN
F 2 "" H 2450 1450 60  0001 C CNN
F 3 "" H 2450 1450 60  0001 C CNN
	1    2450 1450
	1    0    0    -1  
$EndComp
Connection ~ 5750 3700
Connection ~ 4325 2050
$Comp
L PWR_FLAG #FLG06
U 1 1 5AB7534F
P 2150 4650
F 0 "#FLG06" H 2150 4745 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 4830 50  0000 C CNN
F 2 "" H 2150 4650 50  0000 C CNN
F 3 "" H 2150 4650 50  0000 C CNN
	1    2150 4650
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG07
U 1 1 5AB75478
P 5750 3700
F 0 "#FLG07" H 5750 3795 50  0001 C CNN
F 1 "PWR_FLAG" H 5750 3880 50  0000 C CNN
F 2 "" H 5750 3700 50  0000 C CNN
F 3 "" H 5750 3700 50  0000 C CNN
	1    5750 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3825 2050 6300 2050
Text GLabel 5600 3700 0    60   Input ~ 0
GND
Text GLabel 9400 2050 2    60   Input ~ 0
3.3V
Text GLabel 9400 5250 2    60   Input ~ 0
3.7V
$Comp
L TP4056 U?
U 1 1 5C6A7D13
P 3325 2250
F 0 "U?" H 3275 2100 60  0000 C CNN
F 1 "TP4056" H 3275 2200 60  0000 C CNN
F 2 "SOP8:SOP8" H 3300 2000 60  0001 C CNN
F 3 "https://dlnmh9ip6v2uc.cloudfront.net/datasheets/Prototyping/TP4056.pdf" H 3375 2250 60  0001 C CNN
F 4 "SOP-8" H 3300 2300 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/20-TP4056-TP4056/32965308715.html?spm=a2g0v.search0604.3.19.3b7342ceZ2YQqe&s=p&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=d8dbfd72-123f-4196-8109-e7e6d3afca91&algo_expid=d8dbfd72-123f-4196-8109-e7e6d3afca91-2" H 3325 2250 60  0001 C CNN "example"
	1    3325 2250
	1    0    0    -1  
$EndComp
Text Label 3825 2600 0    60   ~ 0
GND
Wire Wire Line
	4325 2350 4325 2450
Wire Wire Line
	4325 2450 4775 2450
Text Label 5175 2450 0    60   ~ 0
GND
Text Notes 5175 2625 0    60   ~ 0
BAT-
Text Notes 4800 2625 2    60   ~ 0
BAT+\n
$Comp
L LED-RESCUE-xmobile D?
U 1 1 5C6AA662
P 2325 2300
F 0 "D?" H 2325 2400 50  0000 C CNN
F 1 "red" H 2325 2200 50  0000 C CNN
F 2 "LEDs:LED_0402" H 2325 2300 50  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 2325 2300 50  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P12U2TT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzNOGPWK3jFzCB54s8pBFBg3g%3d%3d" H 2325 2300 60  0001 C CNN "example"
F 5 "0402 In" H 2175 2400 30  0000 C CNN "case"
	1    2325 2300
	0    -1   -1   0   
$EndComp
$Comp
L LED-RESCUE-xmobile D?
U 1 1 5C6AA7C8
P 2025 2300
F 0 "D?" H 2025 2400 50  0000 C CNN
F 1 "green" H 2025 2200 50  0000 C CNN
F 2 "LEDs:LED_0402" H 2025 2300 50  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 2025 2300 50  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P12M2TT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzNWFfaRj%2fRvVAAroms6JXrzA%3d%3d" H 2025 2300 60  0001 C CNN "example"
F 5 "0402 In" H 1875 2400 30  0000 C CNN "case"
	1    2025 2300
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5C6AB0B6
P 2175 2700
F 0 "R?" V 2255 2700 50  0000 C CNN
F 1 "1k" V 2175 2700 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2105 2700 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 2175 2700 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 2175 2700 60  0001 C CNN "example"
F 5 "0402 in" V 2100 2700 30  0000 C CNN "case"
	1    2175 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	2325 2150 2775 2150
Wire Wire Line
	2325 2450 2325 2600
Wire Wire Line
	2625 2600 2775 2600
Wire Wire Line
	2775 2700 2325 2700
Wire Wire Line
	2025 2700 2025 2450
Wire Wire Line
	2025 2050 2775 2050
Wire Wire Line
	2025 2050 2025 2150
Wire Wire Line
	2325 2150 2325 2050
Connection ~ 2325 2050
$Comp
L C C?
U 1 1 5C6AB784
P 2150 1600
F 0 "C?" H 2175 1700 50  0000 L CNN
F 1 "10u" H 2175 1500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2188 1450 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 2150 1600 50  0001 C CNN
F 4 "0402 In" H 2050 1675 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM155C80J106ME11J?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPP8PNgAVsimC2C1etn3MYH0g%3d%3d" H 2150 1600 60  0001 C CNN "example"
	1    2150 1600
	1    0    0    -1  
$EndComp
Text Label 2150 1750 3    60   ~ 0
GND
Wire Wire Line
	2150 1450 2650 1450
Wire Wire Line
	2650 1325 2650 2050
Connection ~ 2650 2050
Text Label 3325 3000 3    60   ~ 0
GND
$Comp
L R R?
U 1 1 5C6AC8FB
P 3950 2950
F 0 "R?" V 4030 2950 50  0000 C CNN
F 1 "1.2k" V 3950 2950 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3880 2950 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3950 2950 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K20FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWRBT%2frAKZHAM%3d" V 3950 2950 60  0001 C CNN "example"
F 5 "0402 In" V 3875 2950 30  0000 C CNN "case"
	1    3950 2950
	-1   0    0    1   
$EndComp
Text Label 3950 3100 3    60   ~ 0
GND
Wire Wire Line
	3825 2700 3950 2700
Wire Wire Line
	3950 2700 3950 2800
Connection ~ 2450 1450
Wire Wire Line
	7475 5875 9075 5875
$Comp
L +BATT #PWR?
U 1 1 5C6B0901
P 2450 4650
F 0 "#PWR?" H 2450 4600 20  0001 C CNN
F 1 "+BATT" H 2450 4750 30  0000 C CNN
F 2 "" H 2450 4650 60  0001 C CNN
F 3 "" H 2450 4650 60  0001 C CNN
	1    2450 4650
	1    0    0    -1  
$EndComp
Connection ~ 4325 5250
Text Label 3825 5800 0    60   ~ 0
GND
Wire Wire Line
	4325 5550 4325 5650
Wire Wire Line
	4325 5650 4775 5650
Text Label 5175 5650 0    60   ~ 0
GND
Text Notes 5175 5825 0    60   ~ 0
BAT-
Text Notes 4825 5825 2    60   ~ 0
BAT+\n
Wire Wire Line
	2325 5350 2775 5350
Wire Wire Line
	2325 5650 2325 5800
Wire Wire Line
	2625 5800 2775 5800
Wire Wire Line
	2775 5900 2325 5900
Wire Wire Line
	2025 5900 2025 5650
Wire Wire Line
	2025 5250 2775 5250
Wire Wire Line
	2025 5250 2025 5350
Wire Wire Line
	2325 5350 2325 5250
Connection ~ 2325 5250
Text Label 2150 4950 3    60   ~ 0
GND
Wire Wire Line
	2150 4650 2650 4650
Wire Wire Line
	2650 4525 2650 5250
Connection ~ 2650 5250
Text Label 3325 6200 3    60   ~ 0
GND
Text Label 3950 6300 3    60   ~ 0
GND
Wire Wire Line
	3825 5900 3950 5900
Wire Wire Line
	3950 5900 3950 6000
Connection ~ 2450 4650
$Comp
L PWR_FLAG #FLG?
U 1 1 5C6B204A
P 2150 1450
F 0 "#FLG?" H 2150 1545 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 1630 50  0000 C CNN
F 2 "" H 2150 1450 50  0000 C CNN
F 3 "" H 2150 1450 50  0000 C CNN
	1    2150 1450
	1    0    0    -1  
$EndComp
$Comp
L TEST-RESCUE-xmobile W?
U 1 1 5C6B9CD1
P 4975 2450
AR Path="/5C6B9CD1" Ref="W?"  Part="1" 
AR Path="/5A9FCB78/5C6B9CD1" Ref="W?"  Part="1" 
F 0 "W?" H 4975 2510 50  0000 C CNN
F 1 "TEST_BAT_1" H 4975 2380 50  0000 C CNN
F 2 "Measurement_Points:Test_Point_2Pads" H 5225 2600 50  0001 C CNN
F 3 "" H 4975 2450 50  0000 C CNN
F 4 "2 pads" H 4975 2575 30  0000 C CNN "case"
	1    4975 2450
	1    0    0    -1  
$EndComp
$Comp
L TEST-RESCUE-xmobile W?
U 1 1 5C6BA4AE
P 4975 5650
AR Path="/5C6BA4AE" Ref="W?"  Part="1" 
AR Path="/5A9FCB78/5C6BA4AE" Ref="W?"  Part="1" 
F 0 "W?" H 4975 5710 50  0000 C CNN
F 1 "TEST_BAT2" H 4975 5580 50  0000 C CNN
F 2 "Measurement_Points:Test_Point_2Pads" H 5275 5800 50  0001 C CNN
F 3 "" H 4975 5650 50  0000 C CNN
F 4 "2 pads" H 4975 5775 30  0000 C CNN "case"
	1    4975 5650
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P W?
U 1 1 5C6C9437
P 2650 1325
F 0 "W?" H 2650 1595 50  0000 C CNN
F 1 "TEST_BAT_1_CHARGE" H 2650 1525 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 2700 1675 50  0001 C CNN
F 3 "" H 2850 1325 50  0000 C CNN
F 4 "1 pad" H 2775 1450 30  0000 C CNN "case"
	1    2650 1325
	1    0    0    -1  
$EndComp
Connection ~ 2650 1450
$Comp
L TEST_1P W?
U 1 1 5C6C9C6E
P 2650 4525
F 0 "W?" H 2650 4795 50  0000 C CNN
F 1 "TEST_BAT_2_CHARGE" H 2650 4725 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 2700 4875 50  0001 C CNN
F 3 "" H 2850 4525 50  0000 C CNN
F 4 "1 pad" H 2800 4650 30  0000 C CNN "case"
	1    2650 4525
	1    0    0    -1  
$EndComp
Connection ~ 2650 4650
$Comp
L LED-RESCUE-xmobile D?
U 1 1 5C6CA596
P 2025 5500
F 0 "D?" H 2025 5600 50  0000 C CNN
F 1 "green" H 2025 5400 50  0000 C CNN
F 2 "LEDs:LED_0402" H 2025 5500 50  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 2025 5500 50  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P12M2TT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzNWFfaRj%2fRvVAAroms6JXrzA%3d%3d" H 2025 5500 60  0001 C CNN "example"
F 5 "0402 In" H 1875 5600 30  0000 C CNN "case"
	1    2025 5500
	0    -1   -1   0   
$EndComp
$Comp
L LED-RESCUE-xmobile D?
U 1 1 5C6CB16E
P 2325 5500
F 0 "D?" H 2325 5600 50  0000 C CNN
F 1 "red" H 2325 5400 50  0000 C CNN
F 2 "LEDs:LED_0402" H 2325 5500 50  0001 C CNN
F 3 "https://ru.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 2325 5500 50  0001 C CNN
F 4 "https://ru.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P12U2TT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzNOGPWK3jFzCB54s8pBFBg3g%3d%3d" H 2325 5500 60  0001 C CNN "example"
F 5 "0402 In" H 2175 5600 30  0000 C CNN "case"
	1    2325 5500
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5C6D036E
P 2150 4800
F 0 "C?" H 2175 4900 50  0000 L CNN
F 1 "10u" H 2175 4700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2188 4650 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 2150 4800 50  0001 C CNN
F 4 "0402 In" H 2050 4875 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM155C80J106ME11J?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPP8PNgAVsimC2C1etn3MYH0g%3d%3d" H 2150 4800 60  0001 C CNN "example"
	1    2150 4800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5C6D0763
P 4325 5400
F 0 "C?" H 4350 5500 50  0000 L CNN
F 1 "10u" H 4350 5300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4363 5250 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 4325 5400 50  0001 C CNN
F 4 "0402 In" H 4225 5475 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM155C80J106ME11J?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPP8PNgAVsimC2C1etn3MYH0g%3d%3d" H 4325 5400 60  0001 C CNN "example"
	1    4325 5400
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5C6D0925
P 4325 2200
F 0 "C?" H 4350 2300 50  0000 L CNN
F 1 "10u" H 4350 2100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4363 2050 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 4325 2200 50  0001 C CNN
F 4 "0402 In" H 4225 2275 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM155C80J106ME11J?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPP8PNgAVsimC2C1etn3MYH0g%3d%3d" H 4325 2200 60  0001 C CNN "example"
	1    4325 2200
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5C6D24E8
P 7950 5575
F 0 "C?" H 7975 5675 50  0000 L CNN
F 1 "10u" H 7975 5475 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 7988 5425 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 7950 5575 50  0001 C CNN
F 4 "0402 In" H 7850 5650 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM155C80J106ME11J?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPP8PNgAVsimC2C1etn3MYH0g%3d%3d" H 7950 5575 60  0001 C CNN "example"
	1    7950 5575
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C?
U 1 1 5C6D2D36
P 7475 5575
F 0 "C?" H 7485 5645 50  0000 L CNN
F 1 "100u (tantal)" H 7275 5500 50  0000 L CNN
F 2 "0603_In_tantalum:C_0603" H 7475 5575 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/f98-775787.pdf" H 7475 5575 50  0001 C CNN
F 4 "0603 In Polar" H 7450 5700 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/AVX/F980J107MMAAXE?qs=OIhlmDO%252boa7CbJsh7hWANA%3d%3d" H 7475 5575 60  0001 C CNN "example"
	1    7475 5575
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5C6E4482
P 2475 2600
F 0 "R?" V 2555 2600 50  0000 C CNN
F 1 "1k" V 2475 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2405 2600 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 2475 2600 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 2475 2600 60  0001 C CNN "example"
F 5 "0402 in" V 2400 2600 30  0000 C CNN "case"
	1    2475 2600
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5C6E463E
P 2175 5900
F 0 "R?" V 2255 5900 50  0000 C CNN
F 1 "1k" V 2175 5900 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2105 5900 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 2175 5900 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 2175 5900 60  0001 C CNN "example"
F 5 "0402 in" V 2100 5900 30  0000 C CNN "case"
	1    2175 5900
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5C6E49C1
P 2475 5800
F 0 "R?" V 2555 5800 50  0000 C CNN
F 1 "1k" V 2475 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2405 5800 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 2475 5800 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 2475 5800 60  0001 C CNN "example"
F 5 "0402 in" V 2400 5800 30  0000 C CNN "case"
	1    2475 5800
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5C6E5065
P 3950 6150
F 0 "R?" V 4030 6150 50  0000 C CNN
F 1 "1.2k" V 3950 6150 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3880 6150 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3950 6150 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K20FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWRBT%2frAKZHAM%3d" V 3950 6150 60  0001 C CNN "example"
F 5 "0402 In" V 3875 6150 30  0000 C CNN "case"
	1    3950 6150
	-1   0    0    1   
$EndComp
$Comp
L TP4056 U?
U 1 1 5C6E5C3E
P 3325 5450
F 0 "U?" H 3275 5300 60  0000 C CNN
F 1 "TP4056" H 3275 5400 60  0000 C CNN
F 2 "SOP8:SOP8" H 3300 5200 60  0001 C CNN
F 3 "https://dlnmh9ip6v2uc.cloudfront.net/datasheets/Prototyping/TP4056.pdf" H 3375 5450 60  0001 C CNN
F 4 "SOP-8" H 3300 5500 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/20-TP4056-TP4056/32965308715.html?spm=a2g0v.search0604.3.19.3b7342ceZ2YQqe&s=p&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=d8dbfd72-123f-4196-8109-e7e6d3afca91&algo_expid=d8dbfd72-123f-4196-8109-e7e6d3afca91-2" H 3325 5450 60  0001 C CNN "example"
	1    3325 5450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
