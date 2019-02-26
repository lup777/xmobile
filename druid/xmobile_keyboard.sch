EESchema Schematic File Version 4
LIBS:xmobile-cache
EELAYER 26 0
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
L xmobile-rescue:MAX7370 U6
U 1 1 5C4B05E9
P 2600 3750
F 0 "U6" H 2600 3600 60  0000 C CNN
F 1 "MAX7370" H 2600 4150 60  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-24-1EP_4x4mm_Pitch0.5mm" H 2575 3100 60  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/256/MAX7370-1514852.pdf" H 3550 3650 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Maxim-Integrated/MAX7370ETG%2b?qs=sGAEpiMZZMsE420DPIasPtOxRlHUUjJIUcrVTuCuU7c%3d" H 2600 3750 60  0001 C CNN "example"
F 5 "TQFN-24" H 2600 3750 30  0000 C CNN "case"
	1    2600 3750
	1    0    0    -1  
$EndComp
Entry Wire Line
	6075 4750 6175 4850
Entry Wire Line
	6075 3925 6175 4025
Entry Wire Line
	6075 3150 6175 3250
Entry Wire Line
	6075 2300 6175 2400
Entry Wire Line
	6075 1450 6175 1550
Text Label 6175 2400 0    60   ~ 0
R1
Text Label 6175 3250 0    60   ~ 0
R2
Text Label 6175 4025 0    60   ~ 0
R3
Text Label 6175 4850 0    60   ~ 0
R4
Text Label 6175 1550 0    60   ~ 0
R0
Entry Wire Line
	9750 5625 9850 5725
Entry Wire Line
	8900 5625 9000 5725
Entry Wire Line
	8050 5625 8150 5725
Entry Wire Line
	7150 5625 7250 5725
Text Label 7150 5600 0    60   ~ 0
C0
Text Label 8050 5625 0    60   ~ 0
C1
Text Label 9750 5600 0    60   ~ 0
C3
Text Label 8900 5600 0    60   ~ 0
C2
Entry Wire Line
	1300 2950 1400 3050
Entry Wire Line
	1300 3050 1400 3150
Entry Wire Line
	1300 3150 1400 3250
Entry Wire Line
	1300 3250 1400 3350
Entry Wire Line
	1300 3350 1400 3450
Text Label 1475 3050 0    60   ~ 0
R0
Text Label 1475 3150 0    60   ~ 0
R1
Text Label 1475 3250 0    60   ~ 0
R2
Text Label 1475 3350 0    60   ~ 0
R3
Text Label 1475 3450 0    60   ~ 0
R4
Entry Wire Line
	3575 3050 3675 3150
Entry Wire Line
	3575 3150 3675 3250
Entry Wire Line
	3575 3250 3675 3350
Entry Wire Line
	3575 3350 3675 3450
Text Label 3350 3050 0    60   ~ 0
C0
Text Label 3350 3150 0    60   ~ 0
C1
Text Label 3350 3250 0    60   ~ 0
C2
Text Label 3350 3350 0    60   ~ 0
C3
Text GLabel 1075 7350 0    60   Input ~ 0
3.3V
Text Label 1075 7350 0    60   ~ 0
3.3V
Text Label 1050 3850 2    60   ~ 0
3.3V
Text GLabel 1075 7550 0    60   Input ~ 0
GND
Text Label 1075 7550 0    60   ~ 0
GND
Text Label 1800 4150 2    60   ~ 0
GND
NoConn ~ 1800 3650
NoConn ~ 1800 3750
NoConn ~ 1800 3550
$Comp
L xmobile-rescue:R-RESCUE-xmobile R12
U 1 1 5C49881F
P 4300 3175
F 0 "R12" V 4380 3175 40  0000 C CNN
F 1 "10k" V 4307 3176 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4230 3175 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sfr-e-1507454.pdf" H 4300 3175 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SFR01MZPJ103?qs=sGAEpiMZZMtlubZbdhIBIIR71ikvQRXLchgEzboAcvI%3d" V 4300 3175 60  0001 C CNN "example"
F 5 "0402 In" V 4225 3175 30  0000 C CNN "case"
	1    4300 3175
	1    0    0    -1  
$EndComp
Text Label 4600 2550 0    60   ~ 0
3.3V
Text Label 3300 4150 0    60   ~ 0
GND
Text HLabel 4300 3850 2    60   BiDi ~ 0
SDA
Text HLabel 4600 3950 2    60   BiDi ~ 0
SCL
Text HLabel 4900 4050 2    60   Output ~ 0
INT
$Comp
L xmobile-rescue:C 1u1
U 1 1 5C4C0F77
P 1050 4150
F 0 "1u1" H 1075 4250 50  0000 L CNN
F 1 "C" H 1075 4050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1088 4000 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 1050 4150 50  0001 C CNN
F 4 "close to chip" H 1050 4150 60  0001 C CNN "note"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM152R60J105ME15D?qs=sGAEpiMZZMs0AnBnWHyRQFv7x1xn%252bYFdnvIvPkVU8UD1CmfL1E6gmw%3d%3d" H 1050 4150 60  0001 C CNN "example"
F 6 "0402 In" H 950 4075 30  0000 C CNN "case"
	1    1050 4150
	1    0    0    -1  
$EndComp
Text Label 1400 4300 3    60   ~ 0
GND
Text Label 1050 4300 3    60   ~ 0
GND
Text Label 1400 3950 2    60   ~ 0
3.3V
Text Notes 4975 4175 0    60   ~ 0
Active low
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D14
U 1 1 5C4C2FCD
P 2575 5400
F 0 "D14" H 2575 5500 50  0000 C CNN
F 1 "LED BLUE" H 2575 5300 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 2575 5400 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 2575 5400 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SMLP13BC8TT86?qs=sGAEpiMZZMuCm2JlHBGefhkTP7nu0Fg7%2fyfWOmjl5dYVsL3Njh32dw%3d%3d" H 2575 5400 60  0001 C CNN "example"
F 5 "0402 In" H 2425 5500 30  0000 C CNN "case"
	1    2575 5400
	0    -1   -1   0   
$EndComp
Text Label 2575 5250 0    60   ~ 0
3.3V
$Comp
L xmobile-rescue:R-RESCUE-xmobile R8
U 1 1 5C4C321E
P 2575 5950
F 0 "R8" V 2655 5950 40  0000 C CNN
F 1 "1k" V 2582 5951 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2505 5950 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 2575 5950 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 2575 5950 60  0001 C CNN "example"
F 5 "0402 In" V 2500 5950 30  0000 C CNN "case"
	1    2575 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6375 1975 6375 1550
Connection ~ 6375 1550
Wire Wire Line
	7275 1975 7275 1550
Connection ~ 7275 1550
Wire Wire Line
	8125 1975 8125 1550
Connection ~ 8125 1550
Wire Wire Line
	8975 1550 8975 1975
Wire Wire Line
	7150 1975 7150 2775
Wire Wire Line
	8050 1975 8050 2775
Wire Wire Line
	8900 1975 8900 2775
Wire Wire Line
	6375 2775 6375 2400
Connection ~ 6375 2400
Wire Wire Line
	7275 2775 7275 2400
Connection ~ 7275 2400
Wire Wire Line
	6375 3700 6375 3250
Connection ~ 6375 3250
Wire Wire Line
	7275 3700 7275 3250
Connection ~ 7275 3250
Wire Wire Line
	8125 3250 8125 3700
Connection ~ 8125 3250
Wire Wire Line
	8125 2775 8125 2400
Connection ~ 8125 2400
Wire Wire Line
	8975 2400 8975 2775
Wire Wire Line
	8975 3250 8975 3700
Wire Wire Line
	6375 4375 6375 4025
Connection ~ 6375 4025
Wire Wire Line
	7275 4375 7275 4025
Connection ~ 7275 4025
Wire Wire Line
	8125 4375 8125 4025
Connection ~ 8125 4025
Wire Wire Line
	8975 4025 8975 4425
Wire Wire Line
	6375 5175 6375 4850
Connection ~ 6375 4850
Wire Wire Line
	7275 5175 7275 4850
Connection ~ 7275 4850
Wire Wire Line
	8125 5175 8125 4850
Connection ~ 8125 4850
Wire Wire Line
	8975 4850 8975 5175
Wire Wire Line
	6175 1550 6375 1550
Wire Wire Line
	6175 2400 6375 2400
Wire Wire Line
	6175 3250 6375 3250
Wire Wire Line
	6175 4025 6375 4025
Wire Wire Line
	6175 4850 6375 4850
Wire Bus Line
	1300 1300 6075 1300
Wire Wire Line
	1400 3050 1800 3050
Wire Wire Line
	1400 3150 1800 3150
Wire Wire Line
	1400 3250 1800 3250
Wire Wire Line
	1400 3350 1800 3350
Wire Wire Line
	1400 3450 1800 3450
Wire Wire Line
	3300 3050 3575 3050
Wire Wire Line
	3300 3150 3575 3150
Wire Wire Line
	3300 3250 3575 3250
Wire Wire Line
	3300 3350 3575 3350
Wire Bus Line
	5875 5725 5875 1475
Wire Bus Line
	5875 1475 3675 1475
Wire Wire Line
	1800 4050 1800 4150
Wire Wire Line
	4300 2550 4600 2550
Wire Wire Line
	4300 2550 4300 2925
Wire Wire Line
	4600 2925 4600 2550
Wire Wire Line
	4900 2550 4900 2925
Connection ~ 4600 2550
Wire Wire Line
	4300 3425 4300 3850
Wire Wire Line
	4300 3850 3300 3850
Wire Wire Line
	3300 3950 4600 3950
Wire Wire Line
	4600 3950 4600 3425
Wire Wire Line
	3300 4050 4900 4050
Wire Wire Line
	4900 4050 4900 3425
Wire Wire Line
	1400 4000 1400 3950
Wire Wire Line
	1400 3950 1800 3950
Wire Wire Line
	1050 4000 1050 3850
Wire Wire Line
	1050 3850 1800 3850
Wire Wire Line
	2575 5550 2575 5700
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D15
U 1 1 5C4C4192
P 3050 5400
F 0 "D15" H 3050 5500 50  0000 C CNN
F 1 "LED GREEN" H 3050 5300 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 3050 5400 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 3050 5400 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P13PTT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzN4Th3QTRUboF5qJIQuUKd%2fg%3d%3d" H 3050 5400 60  0001 C CNN "example"
F 5 "0402 In" H 2900 5500 30  0000 C CNN "case"
	1    3050 5400
	0    -1   -1   0   
$EndComp
Text Label 3050 5250 0    60   ~ 0
3.3V
Wire Wire Line
	3050 5550 3050 5700
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D16
U 1 1 5C4C43FA
P 3450 5400
F 0 "D16" H 3450 5500 50  0000 C CNN
F 1 "LED RED" H 3450 5300 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 3450 5400 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sml-p1-e-1139198.pdf" H 3450 5400 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SML-P12U2TT86R?qs=sGAEpiMZZMuCm2JlHBGefsrOrFaWoqzNOGPWK3jFzCB54s8pBFBg3g%3d%3d" H 3450 5400 60  0001 C CNN "example"
F 5 "0402 In" H 3300 5500 30  0000 C CNN "case"
	1    3450 5400
	0    -1   -1   0   
$EndComp
Text Label 3450 5250 0    60   ~ 0
3.3V
Wire Wire Line
	3450 5550 3450 5700
$Comp
L xmobile-rescue:LED-RESCUE-xmobile D17
U 1 1 5C4C4408
P 3925 5400
F 0 "D17" H 3925 5500 50  0000 C CNN
F 1 "LED WHITE" H 3925 5300 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 3925 5400 50  0001 C CNN
F 3 "https://media.osram.info/media/resource/hires/osram-dam-2493126/LW%20QH8G.pdf" H 3925 5400 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/OSRAM-Opto-Semiconductors/LW-QH8G-Q2OO-3K5L?qs=sGAEpiMZZMuCm2JlHBGefutc4sI%252bRg9%2fGvzrBju18VEuEONgNlSGyQ%3d%3d" H 3925 5400 60  0001 C CNN "example"
F 5 "0402 In" H 3775 5500 30  0000 C CNN "case"
	1    3925 5400
	0    -1   -1   0   
$EndComp
Text Label 3925 5250 0    60   ~ 0
3.3V
Wire Wire Line
	3925 5550 3925 5700
Text Label 2575 6200 0    60   ~ 0
LED1
Text Label 3050 6200 0    60   ~ 0
LED2
Text Label 3450 6200 0    60   ~ 0
LED3
Text Label 3925 6200 0    60   ~ 0
LED4
Text Label 3300 3450 0    60   ~ 0
LED1
Text Label 3300 3550 0    60   ~ 0
LED2
Text Label 3300 3650 0    60   ~ 0
LED3
Text Label 3300 3750 0    60   ~ 0
LED4
$Comp
L xmobile-rescue:SW_PUSH SW2
U 1 1 5C4FFA32
P 6675 1975
F 0 "SW2" H 6825 2085 50  0000 C CNN
F 1 "SW_PUSH" H 6675 1895 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 6675 2175 50  0001 C CNN
F 3 "" H 6675 1975 50  0000 C CNN
F 4 "4x4x0,8" H 6675 1975 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 6675 1975 60  0001 C CNN "example"
	1    6675 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	6975 1975 7150 1975
Wire Wire Line
	7875 1975 8050 1975
Wire Wire Line
	8725 1975 8900 1975
Wire Wire Line
	9750 1975 9575 1975
Wire Wire Line
	6975 3700 7150 3700
Connection ~ 7150 3700
Wire Wire Line
	7875 3700 8050 3700
Connection ~ 8050 3700
Wire Wire Line
	8725 3700 8900 3700
Connection ~ 8900 3700
Wire Wire Line
	9575 3700 9750 3700
Connection ~ 9750 3700
Wire Wire Line
	9575 2775 9750 2775
Connection ~ 9750 2775
Wire Wire Line
	8725 2775 8900 2775
Connection ~ 8900 2775
Wire Wire Line
	7875 2775 8050 2775
Connection ~ 8050 2775
Wire Wire Line
	6975 2775 7150 2775
Connection ~ 7150 2775
Wire Wire Line
	9575 4425 9750 4425
Connection ~ 9750 4425
Wire Wire Line
	8725 4375 8900 4375
Connection ~ 8900 4375
Wire Wire Line
	7875 4375 8050 4375
Connection ~ 8050 4375
Wire Wire Line
	6975 4375 7150 4375
Connection ~ 7150 4375
Wire Wire Line
	6975 5175 7150 5175
Connection ~ 7150 5175
Wire Wire Line
	7875 5175 8050 5175
Connection ~ 8050 5175
Wire Wire Line
	8725 5175 8900 5175
Connection ~ 8900 5175
Wire Wire Line
	9575 5175 9750 5175
Connection ~ 9750 5175
Wire Wire Line
	9750 1975 9750 2775
$Comp
L xmobile-rescue:SW_PUSH SW7
U 1 1 5C6DCE7B
P 7575 1975
F 0 "SW7" H 7725 2085 50  0000 C CNN
F 1 "SW_PUSH" H 7575 1895 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 7575 2175 50  0001 C CNN
F 3 "" H 7575 1975 50  0000 C CNN
F 4 "4x4x0,8" H 7575 1975 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 7575 1975 60  0001 C CNN "example"
	1    7575 1975
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW12
U 1 1 5C6DCF38
P 8425 1975
F 0 "SW12" H 8575 2085 50  0000 C CNN
F 1 "SW_PUSH" H 8425 1895 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8425 2175 50  0001 C CNN
F 3 "" H 8425 1975 50  0000 C CNN
F 4 "4x4x0,8" H 8425 1975 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 8425 1975 60  0001 C CNN "example"
	1    8425 1975
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW3
U 1 1 5C6DD084
P 6675 2775
F 0 "SW3" H 6825 2885 50  0000 C CNN
F 1 "SW_PUSH" H 6675 2695 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 6675 2975 50  0001 C CNN
F 3 "" H 6675 2775 50  0000 C CNN
F 4 "4x4x0,8" H 6675 2775 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 6675 2775 60  0001 C CNN "example"
	1    6675 2775
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW8
U 1 1 5C6DD126
P 7575 2775
F 0 "SW8" H 7725 2885 50  0000 C CNN
F 1 "SW_PUSH" H 7575 2695 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 7575 2975 50  0001 C CNN
F 3 "" H 7575 2775 50  0000 C CNN
F 4 "4x4x0,8" H 7575 2775 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 7575 2775 60  0001 C CNN "example"
	1    7575 2775
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW13
U 1 1 5C6DD1D1
P 8425 2775
F 0 "SW13" H 8575 2885 50  0000 C CNN
F 1 "SW_PUSH" H 8425 2695 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8425 2975 50  0001 C CNN
F 3 "" H 8425 2775 50  0000 C CNN
F 4 "4x4x0,8" H 8425 2775 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 8425 2775 60  0001 C CNN "example"
	1    8425 2775
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW17
U 1 1 5C6DD300
P 9275 1975
F 0 "SW17" H 9425 2085 50  0000 C CNN
F 1 "SW_PUSH" H 9275 1895 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 9275 2175 50  0001 C CNN
F 3 "" H 9275 1975 50  0000 C CNN
F 4 "4x4x0,8" H 9275 1975 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9275 1975 60  0001 C CNN "example"
	1    9275 1975
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW18
U 1 1 5C6DD3BD
P 9275 2775
F 0 "SW18" H 9425 2885 50  0000 C CNN
F 1 "SW_PUSH" H 9275 2695 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 9275 2975 50  0001 C CNN
F 3 "" H 9275 2775 50  0000 C CNN
F 4 "4x4x0,8" H 9275 2775 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9275 2775 60  0001 C CNN "example"
	1    9275 2775
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW4
U 1 1 5C6DD583
P 6675 3700
F 0 "SW4" H 6825 3810 50  0000 C CNN
F 1 "SW_PUSH" H 6675 3620 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 6675 3900 50  0001 C CNN
F 3 "" H 6675 3700 50  0000 C CNN
F 4 "4x4x0,8" H 6675 3700 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 6675 3700 60  0001 C CNN "example"
	1    6675 3700
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW5
U 1 1 5C6DD636
P 6675 4375
F 0 "SW5" H 6825 4485 50  0000 C CNN
F 1 "SW_PUSH" H 6675 4295 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 6675 4575 50  0001 C CNN
F 3 "" H 6675 4375 50  0000 C CNN
F 4 "4x4x0,8" H 6675 4375 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 6675 4375 60  0001 C CNN "example"
	1    6675 4375
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW10
U 1 1 5C6DD6E4
P 7575 4375
F 0 "SW10" H 7725 4485 50  0000 C CNN
F 1 "SW_PUSH" H 7575 4295 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 7575 4575 50  0001 C CNN
F 3 "" H 7575 4375 50  0000 C CNN
F 4 "4x4x0,8" H 7575 4375 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 7575 4375 60  0001 C CNN "example"
	1    7575 4375
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW9
U 1 1 5C6DD787
P 7575 3700
F 0 "SW9" H 7725 3810 50  0000 C CNN
F 1 "SW_PUSH" H 7575 3620 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 7575 3900 50  0001 C CNN
F 3 "" H 7575 3700 50  0000 C CNN
F 4 "4x4x0,8" H 7575 3700 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 7575 3700 60  0001 C CNN "example"
	1    7575 3700
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW14
U 1 1 5C6DD88C
P 8425 3700
F 0 "SW14" H 8575 3810 50  0000 C CNN
F 1 "SW_PUSH" H 8425 3620 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8425 3900 50  0001 C CNN
F 3 "" H 8425 3700 50  0000 C CNN
F 4 "4x4x0,8" H 8425 3700 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 8425 3700 60  0001 C CNN "example"
	1    8425 3700
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW15
U 1 1 5C6DD941
P 8425 4375
F 0 "SW15" H 8575 4485 50  0000 C CNN
F 1 "SW_PUSH" H 8425 4295 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8425 4575 50  0001 C CNN
F 3 "" H 8425 4375 50  0000 C CNN
F 4 "4x4x0,8" H 8425 4375 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 8425 4375 60  0001 C CNN "example"
	1    8425 4375
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW19
U 1 1 5C6DDA70
P 9275 3700
F 0 "SW19" H 9425 3810 50  0000 C CNN
F 1 "SW_PUSH" H 9275 3620 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 9275 3900 50  0001 C CNN
F 3 "" H 9275 3700 50  0000 C CNN
F 4 "4x4x0,8" H 9275 3700 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9275 3700 60  0001 C CNN "example"
	1    9275 3700
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW20
U 1 1 5C6DDB57
P 9275 4425
F 0 "SW20" H 9425 4535 50  0000 C CNN
F 1 "SW_PUSH" H 9275 4345 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 9275 4625 50  0001 C CNN
F 3 "" H 9275 4425 50  0000 C CNN
F 4 "4x4x0,8" H 9275 4425 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9275 4425 60  0001 C CNN "example"
	1    9275 4425
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW6
U 1 1 5C6DDCFE
P 6675 5175
F 0 "SW6" H 6825 5285 50  0000 C CNN
F 1 "SW_PUSH" H 6675 5095 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 6675 5375 50  0001 C CNN
F 3 "" H 6675 5175 50  0000 C CNN
F 4 "4x4x0,8" H 6675 5175 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 6675 5175 60  0001 C CNN "example"
	1    6675 5175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW11
U 1 1 5C6DDDAF
P 7575 5175
F 0 "SW11" H 7725 5285 50  0000 C CNN
F 1 "SW_PUSH" H 7575 5095 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 7575 5375 50  0001 C CNN
F 3 "" H 7575 5175 50  0000 C CNN
F 4 "4x4x0,8" H 7575 5175 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 7575 5175 60  0001 C CNN "example"
	1    7575 5175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW16
U 1 1 5C6DDEF8
P 8425 5175
F 0 "SW16" H 8575 5285 50  0000 C CNN
F 1 "SW_PUSH" H 8425 5095 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8425 5375 50  0001 C CNN
F 3 "" H 8425 5175 50  0000 C CNN
F 4 "4x4x0,8" H 8425 5175 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 8425 5175 60  0001 C CNN "example"
	1    8425 5175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:SW_PUSH SW21
U 1 1 5C6DDFAF
P 9275 5175
F 0 "SW21" H 9425 5285 50  0000 C CNN
F 1 "SW_PUSH" H 9275 5095 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 9275 5375 50  0001 C CNN
F 3 "" H 9275 5175 50  0000 C CNN
F 4 "4x4x0,8" H 9275 5175 30  0000 C CNN "case"
F 5 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9275 5175 60  0001 C CNN "example"
	1    9275 5175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:C 1u2
U 1 1 5C6E6190
P 1400 4150
F 0 "1u2" H 1425 4250 50  0000 L CNN
F 1 "C" H 1425 4050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1438 4000 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/281/murata_03052018_GRM_Series_1-1310166.pdf" H 1400 4150 50  0001 C CNN
F 4 "close to chip" H 1400 4150 60  0001 C CNN "note"
F 5 "https://eu.mouser.com/ProductDetail/Murata-Electronics/GRM152R60J105ME15D?qs=sGAEpiMZZMs0AnBnWHyRQFv7x1xn%252bYFdnvIvPkVU8UD1CmfL1E6gmw%3d%3d" H 1400 4150 60  0001 C CNN "example"
F 6 "0402 In" H 1300 4075 30  0000 C CNN "case"
	1    1400 4150
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R9
U 1 1 5C6E6DE1
P 3050 5950
F 0 "R9" V 3130 5950 40  0000 C CNN
F 1 "1k" V 3057 5951 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2980 5950 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3050 5950 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 3050 5950 60  0001 C CNN "example"
F 5 "0402 In" V 2975 5950 30  0000 C CNN "case"
	1    3050 5950
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R10
U 1 1 5C6E6E9E
P 3450 5950
F 0 "R10" V 3530 5950 40  0000 C CNN
F 1 "1k" V 3457 5951 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3380 5950 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3450 5950 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 3450 5950 60  0001 C CNN "example"
F 5 "0402 In" V 3375 5950 30  0000 C CNN "case"
	1    3450 5950
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R13
U 1 1 5C6E7B9A
P 4600 3175
F 0 "R13" V 4680 3175 40  0000 C CNN
F 1 "10k" V 4607 3176 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4530 3175 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sfr-e-1507454.pdf" H 4600 3175 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SFR01MZPJ103?qs=sGAEpiMZZMtlubZbdhIBIIR71ikvQRXLchgEzboAcvI%3d" V 4600 3175 60  0001 C CNN "example"
F 5 "0402 In" V 4525 3175 30  0000 C CNN "case"
	1    4600 3175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R14
U 1 1 5C6E7C9E
P 4900 3175
F 0 "R14" V 4980 3175 40  0000 C CNN
F 1 "10k" V 4907 3176 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4830 3175 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sfr-e-1507454.pdf" H 4900 3175 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SFR01MZPJ103?qs=sGAEpiMZZMtlubZbdhIBIIR71ikvQRXLchgEzboAcvI%3d" V 4900 3175 60  0001 C CNN "example"
F 5 "0402 In" V 4825 3175 30  0000 C CNN "case"
	1    4900 3175
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:R-RESCUE-xmobile R11
U 1 1 5C6E62AB
P 3925 5950
F 0 "R11" V 4005 5950 40  0000 C CNN
F 1 "1k" V 3932 5951 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3855 5950 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/427/crcwce3-1223726.pdf" H 3925 5950 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Vishay/CRCW04021K00FKEDC?qs=sGAEpiMZZMtlubZbdhIBIIZe04wfiaJWtbhT4BxhiTc%3d" V 3925 5950 60  0001 C CNN "example"
F 5 "0402 In" V 3850 5950 30  0000 C CNN "case"
	1    3925 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6375 1550 7275 1550
Wire Wire Line
	7275 1550 8125 1550
Wire Wire Line
	8125 1550 8975 1550
Wire Wire Line
	6375 2400 7275 2400
Wire Wire Line
	7275 2400 8125 2400
Wire Wire Line
	6375 3250 7275 3250
Wire Wire Line
	7275 3250 8125 3250
Wire Wire Line
	8125 3250 8975 3250
Wire Wire Line
	8125 2400 8975 2400
Wire Wire Line
	6375 4025 7275 4025
Wire Wire Line
	7275 4025 8125 4025
Wire Wire Line
	8125 4025 8975 4025
Wire Wire Line
	6375 4850 7275 4850
Wire Wire Line
	7275 4850 8125 4850
Wire Wire Line
	8125 4850 8975 4850
Wire Wire Line
	4600 2550 4900 2550
Wire Wire Line
	7150 3700 7150 4375
Wire Wire Line
	8050 3700 8050 4375
Wire Wire Line
	8900 3700 8900 4375
Wire Wire Line
	9750 3700 9750 4425
Wire Wire Line
	9750 2775 9750 3700
Wire Wire Line
	8900 2775 8900 3700
Wire Wire Line
	8050 2775 8050 3700
Wire Wire Line
	7150 2775 7150 3700
Wire Wire Line
	9750 4425 9750 5175
Wire Wire Line
	8900 4375 8900 5175
Wire Wire Line
	8050 4375 8050 5175
Wire Wire Line
	7150 4375 7150 5175
Wire Wire Line
	7150 5175 7150 5625
Wire Wire Line
	8050 5175 8050 5625
Wire Wire Line
	8900 5175 8900 5625
Wire Wire Line
	9750 5175 9750 5625
Wire Bus Line
	5875 5725 9850 5725
Wire Bus Line
	3675 1475 3675 3450
Wire Bus Line
	1300 1300 1300 3350
Wire Bus Line
	6075 1300 6075 4750
$EndSCHEMATC
