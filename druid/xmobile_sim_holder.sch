EESchema Schematic File Version 4
LIBS:xmobile-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 10200 6400 0    60   ~ 0
GND
$Comp
L xmobile-rescue:SIM800C U8
U 1 1 5C46A8F4
P 6625 3525
F 0 "U8" H 6675 4500 60  0000 C CNN
F 1 "SIM800C" H 5975 4500 60  0000 C CNN
F 2 "druid:SIM800C" H 6500 3475 60  0001 C CNN
F 3 "https://www.elecrow.com/download/SIM800C_Hardware_Design_V1.02.pdf" H 6625 3525 60  0001 C CNN
F 4 "https://ru.aliexpress.com/item/SIM800C-SIM800-Four-frequency-package-Voice-SMS-data-transfer-module-new-original/32731695770.html?spm=a2g0v.search0204.3.1.28f7297aRi2dl6&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103,searchweb201603_51,ppcSwitch_0&algo_expid=11a3d274-c3b6-4708-877a-09af2f9d7efa-0&algo_pvid=11a3d274-c3b6-4708-877a-09af2f9d7efa" H 6625 3525 50  0001 C CNN "example"
F 5 "SIM800C LCC" H 6425 3550 30  0000 C CNN "case"
	1    6625 3525
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:78646-3001 U7
U 1 1 5C46ADE6
P 4775 5775
F 0 "U7" H 4875 5575 60  0000 C CNN
F 1 "78646-3001" H 4925 5725 60  0000 C CNN
F 2 "druid:molex-microSIM_SD-78646-001" H 4850 5400 60  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/276/0786463001_MEMORY_CARD_SOCKET-152580.pdf" H 4775 5825 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Molex/78646-3001?qs=%2fha2pyFaduiZ%252bXBY4efUAVaiXZiop36AEBodwiuAheLfGcYelwjXBQ%3d%3d" H 4775 5775 50  0001 C CNN "example"
F 5 "6 pin microSIM" H 4875 5425 30  0000 C CNN "case"
	1    4775 5775
	1    0    0    -1  
$EndComp
Text Label 1100 5075 2    60   ~ 0
SIM_VDD
Text Label 5575 4000 2    60   ~ 0
SIM_VDD
Text Label 5575 3850 2    60   ~ 0
SIM_CLK
Text Label 1125 5675 2    60   ~ 0
SIM_CLK
Text Label 5575 3925 2    60   ~ 0
SIM_RST
Text Label 1125 5375 2    60   ~ 0
SIM_RST
Text Label 5575 4225 2    60   ~ 0
GND
Text Label 4175 5825 2    60   ~ 0
GND
Text Label 5575 3775 2    60   ~ 0
SIM_DATA
Text Label 1100 6025 2    60   ~ 0
SIM_DATA
$Comp
L xmobile-rescue:SMF05C D18
U 1 1 5C46C4AB
P 3250 6650
F 0 "D18" V 3325 6875 60  0000 C CNN
F 1 "SMF05C" V 3500 6750 60  0000 C CNN
F 2 "semtech:SOT363" H 3250 6975 60  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/308/SMF05C-D-100912.pdf" H 3240 6650 60  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/ON-Semiconductor/SMF05CT1G?qs=sGAEpiMZZMtqO%252bWUGLBzeAEUVu%2fYzK%252bE" H 3250 6650 50  0001 C CNN "example"
F 5 "SOT-363" V 3475 6375 30  0000 C CNN "case"
	1    3250 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	1775 6025 1925 6025
Wire Wire Line
	2950 6425 2950 6025
Connection ~ 2950 6025
$Comp
L xmobile-rescue:C-RESCUE-xmobile C32
U 1 1 5C46CACB
P 1925 6625
F 0 "C32" H 1925 6725 40  0000 L CNN
F 1 "22p" H 1931 6540 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 1963 6475 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/281/GCQ1555C1HR51WB01-01-1154307.pdf" H 1925 6625 60  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/GCQ1555C1H220FB01D?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPPyyCqh504D8PFlcqJ5QQ8Xw%3d%3d" H 1925 6625 50  0001 C CNN "example"
F 5 "0402 In" H 1825 6550 30  0000 C CNN "case"
	1    1925 6625
	1    0    0    -1  
$EndComp
Wire Wire Line
	1925 6425 1925 6025
Connection ~ 1925 6025
$Comp
L xmobile-rescue:R-RESCUE-xmobile R15
U 1 1 5C46D4E7
P 1525 5075
F 0 "R15" V 1605 5075 40  0000 C CNN
F 1 "51" V 1532 5076 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1455 5075 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 1525 5075 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW040251R0FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW7Jc30odpG10%3d" V 1525 5075 50  0001 C CNN "example"
F 5 "0402 In" V 1450 5075 30  0000 C CNN "case"
	1    1525 5075
	0    1    1    0   
$EndComp
Wire Wire Line
	1125 5675 1275 5675
Wire Wire Line
	1275 5375 1125 5375
Wire Wire Line
	1100 6025 1275 6025
Wire Wire Line
	1775 5675 2000 5675
Wire Wire Line
	2000 5675 2000 5725
Wire Wire Line
	2000 5725 3150 5725
Wire Wire Line
	1775 5375 3250 5375
Wire Wire Line
	4000 5375 4000 5625
Wire Wire Line
	4000 5625 4175 5625
Wire Wire Line
	1775 5075 2700 5075
Wire Wire Line
	4100 5075 4100 5525
Wire Wire Line
	4100 5525 4175 5525
Wire Wire Line
	3150 6425 3150 5725
Connection ~ 3150 5725
Wire Wire Line
	3250 6425 3250 5375
Connection ~ 3250 5375
Wire Wire Line
	3350 6425 3350 5075
Connection ~ 3350 5075
Text Label 3150 7025 3    60   ~ 0
GND
Connection ~ 2700 5075
Text Label 2700 7550 3    60   ~ 0
GND
Text Label 7275 3325 0    60   ~ 0
GSM_VBAT
Text Label 7275 3250 0    60   ~ 0
GSM_VBAT
Text Label 10425 3875 1    60   ~ 0
GSM_VBAT
$Comp
L xmobile-rescue:R-RESCUE-xmobile R32
U 1 1 5C4702F9
P 9900 5625
F 0 "R32" V 9980 5625 40  0000 C CNN
F 1 "47k" V 9907 5626 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 9830 5625 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/rcse3-1013761.pdf" H 9900 5625 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/RCS040247K0FKED?qs=sGAEpiMZZMtlubZbdhIBIOTSrQvmFtiZuYMdFvGWg7Q%3d" V 9900 5625 50  0001 C CNN "example"
F 5 "0402 In" V 9825 5625 30  0000 C CNN "case"
	1    9900 5625
	-1   0    0    1   
$EndComp
Text Label 10425 6050 0    60   ~ 0
GND
Wire Wire Line
	9900 5375 9900 5250
Wire Wire Line
	9725 5250 9900 5250
Wire Wire Line
	10425 4875 10425 5050
Wire Wire Line
	10425 6050 10425 5450
Wire Wire Line
	9900 5875 9900 6050
Wire Wire Line
	9900 6050 10425 6050
Wire Wire Line
	10425 4175 10425 4375
Connection ~ 9900 5250
Text Label 9225 5250 2    60   ~ 0
NETLIGHT
Text Label 7275 2800 0    60   ~ 0
NETLIGHT
$Comp
L xmobile-rescue:BC850 Q1
U 1 1 5C473781
P 7750 5250
F 0 "Q1" H 7950 5325 50  0000 L CNN
F 1 "BC850" H 7950 5250 50  0000 L CNN
F 2 "SOT:SOT-23" H 7950 5175 50  0001 L CIN
F 3 "https://www.mouser.co.uk/datasheet/2/308/BC850-1300034.pdf" H 7750 5250 50  0001 L CNN
F 4 "https://www.mouser.co.uk/ProductDetail/ON-Semiconductor-Fairchild/BC850?qs=%2fha2pyFadugHIWt16jitYIyLpJVRwLYlH9UFDxyhXRQ%3d" H 7750 5250 50  0001 C CNN "example"
F 5 "SOT-23" H 8025 5150 30  0000 C CNN "case"
	1    7750 5250
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R29
U 1 1 5C4739DE
P 6800 5250
F 0 "R29" V 6880 5250 40  0000 C CNN
F 1 "4.7K" V 6807 5251 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 6730 5250 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 6800 5250 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW04024K70JNEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW6fxGYBngRwU%3d" V 6800 5250 50  0001 C CNN "example"
F 5 "0402 In" V 6725 5250 30  0000 C CNN "case"
	1    6800 5250
	0    -1   -1   0   
$EndComp
Text Label 7850 5750 3    60   ~ 0
GND
Wire Wire Line
	7700 5600 7850 5600
Wire Wire Line
	7850 5450 7850 5600
Connection ~ 7850 5600
Wire Wire Line
	7050 5250 7200 5250
Wire Wire Line
	7200 5250 7200 5600
Connection ~ 7200 5250
Text Label 7850 5050 0    60   ~ 0
PWRKEY
Text Label 7275 2950 0    60   ~ 0
PWRKEY
Text Notes 5900 4900 0    60   ~ 0
SIM800 power on:\npull PWRKEY down for a second and then pull it up.\nIt already pulled up to VBAT in the module internal.
Text HLabel 7825 2725 2    60   Output ~ 0
STATUS
Wire Wire Line
	7275 2725 7825 2725
Text HLabel 6550 5250 0    60   Output ~ 0
POWER_KEY
NoConn ~ 4175 5925
Text Label 1925 6825 3    60   ~ 0
GND
Text Label 7275 3550 0    60   ~ 0
GND
Text Label 7275 3625 0    60   ~ 0
GND
Text Label 7275 3850 0    60   ~ 0
GND
Text Label 5575 3250 2    60   ~ 0
GND
Text Label 5575 4075 2    60   ~ 0
GND
Text Label 7275 3100 0    60   ~ 0
GND
Text Label 7275 3175 0    60   ~ 0
GND
Text Label 5575 3625 2    60   ~ 0
GND
Wire Wire Line
	4725 2875 5075 2875
Wire Wire Line
	5075 2875 5075 3175
Wire Wire Line
	5075 3175 5575 3175
Wire Wire Line
	5150 2650 5150 3100
Wire Wire Line
	5150 3100 5575 3100
Text Label 3600 3350 3    60   ~ 0
GND
Wire Wire Line
	3600 2850 3600 2650
Connection ~ 3600 2650
$Comp
L xmobile-rescue:R-RESCUE-xmobile R22
U 1 1 5C47D122
P 3600 3100
F 0 "R22" V 3680 3100 40  0000 C CNN
F 1 "5.6k" V 3607 3101 40  0000 C CNN
F 2 "" V 3530 3100 30  0000 C CNN
F 3 "" H 3600 3100 30  0000 C CNN
	1    3600 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 2450 5225 2450
Wire Wire Line
	5225 2450 5225 3025
Wire Wire Line
	5225 3025 5575 3025
Wire Wire Line
	5300 2950 5575 2950
Wire Wire Line
	5300 1625 5300 2950
Wire Wire Line
	5300 1625 4700 1625
$Comp
L xmobile-rescue:R-RESCUE-xmobile R21
U 1 1 5C47EDF5
P 3400 1800
F 0 "R21" V 3480 1800 40  0000 C CNN
F 1 "5.6k" V 3407 1801 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3330 1800 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/315/AOA0000C304-1149620.pdf" H 3400 1800 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Panasonic/ERJ-2RKF5601X?qs=sGAEpiMZZMtlubZbdhIBIH%2fX%2fXYrlp18QO1WOykmY0Q%3d" V 3400 1800 50  0001 C CNN "example"
F 5 "0402 In" V 3325 1800 30  0000 C CNN "case"
	1    3400 1800
	-1   0    0    1   
$EndComp
Text Label 3400 2050 3    60   ~ 0
GND
Wire Wire Line
	3250 1425 3400 1425
Wire Wire Line
	3400 1425 3400 1550
Wire Wire Line
	5375 1425 5375 2875
Wire Wire Line
	5375 2875 5575 2875
Connection ~ 3400 1425
$Comp
L xmobile-rescue:R-RESCUE-xmobile R26
U 1 1 5C47FCB5
P 6050 1300
F 0 "R26" V 6130 1300 40  0000 C CNN
F 1 "5.6k" V 6057 1301 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5980 1300 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/447/PYu-RC_Group_51_RoHS_L_10-1527934.pdf" H 6050 1300 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Yageo/RC0402FR-075K6L?qs=sGAEpiMZZMtlubZbdhIBIF0pw9CTwGfxMDO7%252bNqJYEI%3d" V 6050 1300 50  0001 C CNN "example"
F 5 "0402 In" V 5975 1300 30  0000 C CNN "case"
	1    6050 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	6050 950  6050 1050
Wire Wire Line
	5575 2800 5450 2800
Connection ~ 6050 950 
Wire Wire Line
	5450 950  6050 950 
Text Label 6050 1550 3    60   ~ 0
GND
Text Label 7275 3400 0    60   ~ 0
GND
$Comp
L xmobile-rescue:TEST-RESCUE-xmobile W17
U 1 1 5C481A0A
P 7850 3775
F 0 "W17" H 7850 3835 50  0000 C CNN
F 1 "TP_RTC_BAT" H 7850 3705 50  0000 C CNN
F 2 "Measurement_Points:Test_Point_2Pads" H 7850 3775 50  0001 C CNN
F 3 "" H 7850 3775 50  0000 C CNN
F 4 "2 pads" H 7700 3850 30  0000 C CNN "case"
	1    7850 3775
	1    0    0    -1  
$EndComp
Wire Wire Line
	7275 3775 7650 3775
$Comp
L xmobile-rescue:TEST_1P W18
U 1 1 5C481C47
P 9600 3475
F 0 "W18" V 9600 3725 50  0000 C CNN
F 1 "TP_GSM_ANT" V 9500 3700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 9800 3475 50  0001 C CNN
F 3 "" H 9800 3475 50  0000 C CNN
F 4 "1 pad" V 9675 3625 30  0000 C CNN "case"
	1    9600 3475
	0    1    1    0   
$EndComp
Wire Wire Line
	7275 3475 9600 3475
Text Notes 7875 3400 0    60   ~ 0
Antenna TP should be close to module\nand far from power and sim holder.
NoConn ~ 7275 3700
NoConn ~ 7275 4150
NoConn ~ 7275 4225
Text Label 7275 3025 0    60   ~ 0
GSM_VBAT
NoConn ~ 7275 2875
$Comp
L xmobile-rescue:TEST_1P W14
U 1 1 5C483444
P 4900 4150
F 0 "W14" V 4900 4400 50  0000 C CNN
F 1 "TP_BT_ANT" V 5000 4275 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 5100 4150 50  0001 C CNN
F 3 "" H 5100 4150 50  0000 C CNN
F 4 "1 pad" V 4825 4275 30  0000 C CNN "case"
	1    4900 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 4150 5575 4150
NoConn ~ 5575 3700
Wire Wire Line
	5525 2725 5525 2100
Wire Wire Line
	5525 2100 5850 2100
Wire Wire Line
	5525 2725 5575 2725
Wire Wire Line
	5450 2800 5450 950 
NoConn ~ 3050 6425
Text GLabel 10200 6400 0    60   Input ~ 0
GND
$Comp
L xmobile-rescue:TEST_1P W16
U 1 1 5C490798
P 6700 950
F 0 "W16" H 6700 1220 50  0000 C CNN
F 1 "TP_UART_RXD" H 6700 1150 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 6900 950 50  0001 C CNN
F 3 "" H 6900 950 50  0000 C CNN
F 4 "1 pad" H 6575 1075 30  0000 C CNN "case"
	1    6700 950 
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:TEST_1P W9
U 1 1 5C491932
P 2750 1425
F 0 "W9" H 2750 1695 50  0000 C CNN
F 1 "TP_UART_RTS" H 2750 1625 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 2950 1425 50  0001 C CNN
F 3 "" H 2950 1425 50  0001 C CNN
F 4 "1 pad" H 2875 1550 30  0000 C CNN "case"
	1    2750 1425
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:TEST_1P W10
U 1 1 5C491C83
P 2950 2650
F 0 "W10" H 2950 2920 50  0000 C CNN
F 1 "TP_UART_DTR" H 2950 2850 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 3150 2650 50  0001 C CNN
F 3 "" H 3150 2650 50  0000 C CNN
F 4 "1 pad" H 3075 2775 30  0000 C CNN "case"
	1    2950 2650
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:TEST_1P W11
U 1 1 5C4925FE
P 4200 1625
F 0 "W11" H 4200 1895 50  0000 C CNN
F 1 "TP_UART_CTS" H 4200 1825 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 4400 1625 50  0001 C CNN
F 3 "" H 4325 1750 30  0001 C CNN
F 4 "1 pad" H 4325 1750 30  0000 C CNN "case"
	1    4200 1625
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:TEST_1P W12
U 1 1 5C49272C
P 4200 2450
F 0 "W12" H 4200 2720 50  0000 C CNN
F 1 "TP_UART_DCD" H 4200 2650 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 4400 2450 50  0001 C CNN
F 3 "" H 4400 2450 50  0000 C CNN
F 4 "1 pad" H 4075 2575 30  0000 C CNN "case"
	1    4200 2450
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:TEST_1P W13
U 1 1 5C4928AD
P 4225 2875
F 0 "W13" H 4225 3145 50  0000 C CNN
F 1 "TP_UART_RI" H 4225 3075 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 4425 2875 50  0001 C CNN
F 3 "" H 4425 2875 50  0000 C CNN
F 4 "1 pad" H 4350 3000 30  0000 C CNN "case"
	1    4225 2875
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:TEST_1P W15
U 1 1 5C492A5F
P 6350 2100
F 0 "W15" H 6350 2370 50  0000 C CNN
F 1 "TP_USART_TXD" H 6350 2300 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Square-TH_Small" H 6550 2100 50  0001 C CNN
F 3 "" H 6550 2100 50  0000 C CNN
F 4 "1 pad" H 6225 2225 30  0000 C CNN "case"
	1    6350 2100
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:STF202-22T1G U9
U 1 1 5C497719
P 8900 1225
F 0 "U9" H 8900 1125 50  0000 C CNN
F 1 "STF202-22T1G" H 8900 1425 50  0000 C CNN
F 2 "druid:TSOP-6_CASE-318G-02" H 8875 875 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/308/STF202-22T1-D-117165.pdf" H 8900 1225 50  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/ON-Semiconductor/STF202-22T1G?qs=%2fha2pyFadujRFaXPnV9RsTetlaFPPaXSz4EERle60zyiot5T0fRtTg%3d%3d" H 8900 1225 50  0001 C CNN "example"
F 5 "TSOP-6" H 8900 1225 30  0000 C CNN "case"
	1    8900 1225
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1225 9650 1225
Wire Wire Line
	9900 1325 9650 1325
Wire Wire Line
	9900 1125 9850 1125
Wire Wire Line
	9850 1125 9850 875 
Wire Wire Line
	8075 1125 8150 1125
Text Label 9300 2025 3    60   ~ 0
GND
Text Label 7275 4075 0    60   ~ 0
USB_VBUS
Text Label 7275 3925 0    60   ~ 0
USB_DN
Text Label 7275 4000 0    60   ~ 0
USB_DP
Text Label 8150 1325 2    60   ~ 0
USB_VBUS
Text Label 8075 1125 2    60   ~ 0
USB_DN
Text Label 8150 1225 2    60   ~ 0
USB_DP
Text HLabel 2750 1425 0    60   Input ~ 0
UART_RTS
Text HLabel 2950 2650 0    60   Input ~ 0
UART_DTR
Text HLabel 4225 2875 0    60   Input ~ 0
UART_RI
Text HLabel 4200 2450 0    60   Input ~ 0
UART_DCD
Text HLabel 4200 1625 0    60   Input ~ 0
UART_CTS
Text HLabel 6700 950  2    60   Input ~ 0
UART_RXD
Text HLabel 6350 2100 2    60   Input ~ 0
UART_TXD
Text HLabel 5050 3325 0    60   Input ~ 0
MICP
Text HLabel 5050 3400 0    60   Input ~ 0
MICN
Text HLabel 5050 3475 0    60   Output ~ 0
SPKP
Text HLabel 5050 3550 0    60   Output ~ 0
SPKN
Wire Wire Line
	5575 3325 5050 3325
Wire Wire Line
	5050 3400 5575 3400
Wire Wire Line
	5050 3475 5575 3475
Wire Wire Line
	5575 3550 5050 3550
Text Label 8050 3775 0    60   ~ 0
GND
Wire Wire Line
	2950 6025 4175 6025
Wire Wire Line
	1925 6025 2950 6025
Wire Wire Line
	3150 5725 4175 5725
Wire Wire Line
	3250 5375 4000 5375
Wire Wire Line
	3350 5075 4100 5075
Wire Wire Line
	2700 5075 3350 5075
Wire Wire Line
	9900 5250 10125 5250
Wire Wire Line
	7850 5600 7850 5750
Wire Wire Line
	7200 5250 7550 5250
Wire Wire Line
	3600 2650 5150 2650
Wire Wire Line
	3400 1425 5375 1425
Wire Wire Line
	6050 950  6200 950 
Wire Wire Line
	9850 875  10200 875 
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C71520A
P 6450 950
AR Path="/5AA512DD/5C71520A" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C71520A" Ref="R28"  Part="1" 
F 0 "R28" V 6530 950 40  0000 C CNN
F 1 "1k" V 6457 951 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 6380 950 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 6450 950 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 6450 950 60  0001 C CNN "example"
F 5 "0402 In" V 6375 950 30  0000 C CNN "case"
	1    6450 950 
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C719371
P 6100 2100
AR Path="/5AA512DD/5C719371" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C719371" Ref="R27"  Part="1" 
F 0 "R27" V 6180 2100 40  0000 C CNN
F 1 "1k" V 6107 2101 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 6030 2100 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 6100 2100 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 6100 2100 60  0001 C CNN "example"
F 5 "0402 In" V 6025 2100 30  0000 C CNN "case"
	1    6100 2100
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C71959A
P 3000 1425
AR Path="/5AA512DD/5C71959A" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C71959A" Ref="R19"  Part="1" 
F 0 "R19" V 3080 1425 40  0000 C CNN
F 1 "1k" V 3007 1426 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2930 1425 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3000 1425 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 3000 1425 60  0001 C CNN "example"
F 5 "0402 In" V 2925 1425 30  0000 C CNN "case"
	1    3000 1425
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C7198C3
P 4450 1625
AR Path="/5AA512DD/5C7198C3" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C7198C3" Ref="R23"  Part="1" 
F 0 "R23" V 4530 1625 40  0000 C CNN
F 1 "1k" V 4457 1626 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4380 1625 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 4450 1625 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 4450 1625 60  0001 C CNN "example"
F 5 "0402 In" V 4375 1625 30  0000 C CNN "case"
	1    4450 1625
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C719981
P 4450 2450
AR Path="/5AA512DD/5C719981" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C719981" Ref="R24"  Part="1" 
F 0 "R24" V 4530 2450 40  0000 C CNN
F 1 "1k" V 4457 2451 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4380 2450 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 4450 2450 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 4450 2450 60  0001 C CNN "example"
F 5 "0402 In" V 4375 2450 30  0000 C CNN "case"
	1    4450 2450
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C719AE7
P 3200 2650
AR Path="/5AA512DD/5C719AE7" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C719AE7" Ref="R20"  Part="1" 
F 0 "R20" V 3280 2650 40  0000 C CNN
F 1 "1k" V 3207 2651 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3130 2650 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3200 2650 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 3200 2650 60  0001 C CNN "example"
F 5 "0402 In" V 3125 2650 30  0000 C CNN "case"
	1    3200 2650
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C719C45
P 4475 2875
AR Path="/5AA512DD/5C719C45" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C719C45" Ref="R25"  Part="1" 
F 0 "R25" V 4555 2875 40  0000 C CNN
F 1 "1k" V 4482 2876 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4405 2875 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 4475 2875 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 4475 2875 60  0001 C CNN "example"
F 5 "0402 In" V 4400 2875 30  0000 C CNN "case"
	1    4475 2875
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R?
U 1 1 5C719D47
P 10425 4625
AR Path="/5AA512DD/5C719D47" Ref="R?"  Part="1" 
AR Path="/5A9F76AF/5C719D47" Ref="R33"  Part="1" 
F 0 "R33" V 10505 4625 40  0000 C CNN
F 1 "1k" V 10432 4626 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 10355 4625 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 10425 4625 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 10425 4625 60  0001 C CNN "example"
F 5 "0402 In" V 10350 4625 30  0000 C CNN "case"
	1    10425 4625
	-1   0    0    1   
$EndComp
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D?
U 1 1 5C71F808
P 10425 4025
AR Path="/5AA512DD/5C71F808" Ref="D?"  Part="1" 
AR Path="/5A9F76AF/5C71F808" Ref="D19"  Part="1" 
F 0 "D19" H 10425 4125 50  0000 C CNN
F 1 "LED WHITE" H 10425 3925 50  0000 C CNN
F 2 "LEDs_git:LED_0402" H 10425 4025 50  0001 C CNN
F 3 "https://media.osram.info/media/resource/hires/osram-dam-2493126/LW%20QH8G.pdf" H 10425 4025 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/OSRAM-Opto-Semiconductors/LW-QH8G-Q2OO-3K5L?qs=sGAEpiMZZMuCm2JlHBGefutc4sI%252bRg9%2fGvzrBju18VEuEONgNlSGyQ%3d%3d" H 10425 4025 60  0001 C CNN "example"
F 5 "0402 In" H 10275 4125 30  0000 C CNN "case"
	1    10425 4025
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 2650 3600 2650
$Comp
L xmobile-rescue:R-RESCUE-xmobile R30
U 1 1 5C722A7C
P 7450 5600
F 0 "R30" V 7530 5600 40  0000 C CNN
F 1 "47k" V 7457 5601 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 7380 5600 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/rcse3-1013761.pdf" H 7450 5600 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/RCS040247K0FKED?qs=sGAEpiMZZMtlubZbdhIBIOTSrQvmFtiZuYMdFvGWg7Q%3d" V 7450 5600 50  0001 C CNN "example"
F 5 "0402 In" V 7375 5600 30  0000 C CNN "case"
	1    7450 5600
	0    -1   -1   0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R31
U 1 1 5C72346E
P 9475 5250
F 0 "R31" V 9555 5250 40  0000 C CNN
F 1 "4.7K" V 9482 5251 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 9405 5250 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 9475 5250 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW04024K70JNEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW6fxGYBngRwU%3d" V 9475 5250 50  0001 C CNN "example"
F 5 "0402 In" V 9400 5250 30  0000 C CNN "case"
	1    9475 5250
	0    -1   -1   0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R16
U 1 1 5C7250BC
P 1525 5375
F 0 "R16" V 1605 5375 40  0000 C CNN
F 1 "51" V 1532 5376 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1455 5375 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 1525 5375 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW040251R0FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW7Jc30odpG10%3d" V 1525 5375 50  0001 C CNN "example"
F 5 "0402 In" V 1450 5375 30  0000 C CNN "case"
	1    1525 5375
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R17
U 1 1 5C725134
P 1525 5675
F 0 "R17" V 1605 5675 40  0000 C CNN
F 1 "51" V 1532 5676 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1455 5675 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 1525 5675 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW040251R0FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW7Jc30odpG10%3d" V 1525 5675 50  0001 C CNN "example"
F 5 "0402 In" V 1450 5675 30  0000 C CNN "case"
	1    1525 5675
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R18
U 1 1 5C7251B4
P 1525 6025
F 0 "R18" V 1605 6025 40  0000 C CNN
F 1 "51" V 1532 6026 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1455 6025 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/427/crcwce3-1223726.pdf" H 1525 6025 30  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Vishay/CRCW040251R0FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJW7Jc30odpG10%3d" V 1525 6025 50  0001 C CNN "example"
F 5 "0402 In" V 1450 6025 30  0000 C CNN "case"
	1    1525 6025
	0    1    1    0   
$EndComp
$Comp
L xmobile-rescue:C-RESCUE-xmobile C33
U 1 1 5C726DB2
P 2700 7350
F 0 "C33" H 2700 7450 40  0000 L CNN
F 1 "22p" H 2706 7265 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2738 7200 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/281/GCQ1555C1HR51WB01-01-1154307.pdf" H 2700 7350 60  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/GCQ1555C1H220FB01D?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPPyyCqh504D8PFlcqJ5QQ8Xw%3d%3d" H 2700 7350 50  0001 C CNN "example"
F 5 "0402 In" H 2600 7275 30  0000 C CNN "case"
	1    2700 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5075 2700 7150
$Comp
L xmobile-rescue:C-RESCUE-xmobile C34
U 1 1 5C727ED4
P 9300 1825
F 0 "C34" H 9300 1925 40  0000 L CNN
F 1 "22p" H 9306 1740 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 9338 1675 30  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/281/GCQ1555C1HR51WB01-01-1154307.pdf" H 9300 1825 60  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/GCQ1555C1H220FB01D?qs=sGAEpiMZZMs0AnBnWHyRQN7%2fAA2D2lPPyyCqh504D8PFlcqJ5QQ8Xw%3d%3d" H 9300 1825 50  0001 C CNN "example"
F 5 "0402 In" H 9200 1750 30  0000 C CNN "case"
	1    9300 1825
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:BC850 Q2
U 1 1 5C73005B
P 10325 5250
F 0 "Q2" H 10525 5325 50  0000 L CNN
F 1 "BC850" H 10525 5250 50  0000 L CNN
F 2 "SOT:SOT-23" H 10525 5175 50  0001 L CIN
F 3 "https://www.mouser.co.uk/datasheet/2/308/BC850-1300034.pdf" H 10325 5250 50  0001 L CNN
F 4 "https://www.mouser.co.uk/ProductDetail/ON-Semiconductor-Fairchild/BC850?qs=%2fha2pyFadugHIWt16jitYIyLpJVRwLYlH9UFDxyhXRQ%3d" H 10325 5250 50  0001 C CNN "example"
F 5 "SOT-23" H 10600 5150 30  0000 C CNN "case"
	1    10325 5250
	1    0    0    -1  
$EndComp
Text GLabel 9300 6400 0    60   Input ~ 0
3.7V
Text Label 9300 6400 0    60   ~ 0
GSM_VBAT
Wire Wire Line
	1100 5075 1275 5075
$Comp
L Connector:USB_B_Micro J4
U 1 1 5C70D478
P 10200 1325
F 0 "J4" H 9971 1193 50  0000 R CNN
F 1 "USB_B_Micro" H 9971 1284 50  0000 R CNN
F 2 "Connectors_USB:USB_Micro-B_Molex_47346-0001" H 10350 1275 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/276/0473460001_IO_CONNECTORS-229243.pdf" H 10350 1275 50  0001 C CNN
F 4 "https://www.mouser.co.uk/ProductDetail/Molex/47346-0001?qs=%2fha2pyFaduiJWkclJ6vmoxPm1IDZfDKPxl9YVM5WTkQ%3d" H 10200 1325 50  0001 C CNN "example"
F 5 "microUSB-B" H 9971 1360 30  0000 R CNN "case"
	1    10200 1325
	-1   0    0    1   
$EndComp
Wire Wire Line
	9900 1525 9700 1525
Wire Wire Line
	9700 1525 9700 1625
Wire Wire Line
	9700 1625 9300 1625
Wire Wire Line
	9300 1625 8150 1625
Wire Wire Line
	8150 1625 8150 1325
Connection ~ 9300 1625
Wire Wire Line
	9650 1125 9850 1125
Connection ~ 9850 1125
Wire Wire Line
	10200 925  10200 875 
Connection ~ 10200 875 
Wire Wire Line
	10200 875  10300 875 
Wire Wire Line
	10300 925  10300 875 
$EndSCHEMATC
