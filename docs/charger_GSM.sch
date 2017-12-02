EESchema Schematic File Version 2
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
LIBS:zakadc
LIBS:vw2500m
LIBS:usb-b
LIBS:uprojects-msp430
LIBS:uprojects-maxim-integrated
LIBS:tps79530
LIBS:tps63001
LIBS:tps61040dbv
LIBS:tact_sw
LIBS:str751fr0t6
LIBS:stm32f103cb
LIBS:stm32f101cbt6
LIBS:stm32f030f4
LIBS:stm32f20x_LQFP64
LIBS:sn54ac04
LIBS:smf05c
LIBS:sim_holder
LIBS:sim900
LIBS:sim800c
LIBS:reset_supervisor
LIBS:quectel
LIBS:psl-ecg_12md_ads1298
LIBS:pl2303
LIBS:pcf8563_rtc
LIBS:opa333_sot23-5
LIBS:nrf8001
LIBS:ncp3020
LIBS:mt3608
LIBS:molex_sim_holder_47553
LIBS:micro_usb_b
LIBS:microsd_socket
LIBS:md1506_gsm_ant
LIBS:mcp73833
LIBS:mcp73831
LIBS:mb6s
LIBS:max669
LIBS:ltc4120
LIBS:ltc3533
LIBS:lt1370
LIBS:lpc1313
LIBS:lp2951
LIBS:lm2931cdr2g
LIBS:lm809
LIBS:lis3dh
LIBS:led_couple
LIBS:l6984
LIBS:itg3200
LIBS:irfh9310
LIBS:irfh5300
LIBS:ir2110l4
LIBS:hmc5883
LIBS:hlk-rm04
LIBS:hc735-oscillator
LIBS:gl850g_usb_hub
LIBS:esp-07
LIBS:dpak-diode
LIBS:cstce_crystal
LIBS:conn15
LIBS:cc3100mod
LIBS:bmp180
LIBS:ble112
LIBS:alt_symbols
LIBS:ads1298_ecg_adc
LIBS:ad8542
LIBS:ad8495
LIBS:ad8054
LIBS:ad8051
LIBS:3225_4p_quartz
LIBS:74lvc02
LIBS:XC6206P332MR
LIBS:STF202-22T1G
LIBS:MCP73871
LIBS:xmobile-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L MCP73871 U?
U 1 1 59D2974A
P 6325 4775
F 0 "U?" H 6325 4675 50  0000 C CNN
F 1 "MCP73871" H 6325 4875 50  0000 C CNN
F 2 "MODULE" H 6325 4775 50  0001 C CNN
F 3 "DOCUMENTATION" H 6325 4775 50  0001 C CNN
	1    6325 4775
	1    0    0    -1  
$EndComp
$Comp
L MICRO_USB_B P?
U 1 1 59D29792
P 9150 1800
F 0 "P?" H 9200 2250 60  0000 C CNN
F 1 "MICRO_USB_B" H 8800 2250 60  0000 C CNN
F 2 "" H 9400 1500 60  0000 C CNN
F 3 "" H 9400 1500 60  0000 C CNN
	1    9150 1800
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K?
U 1 1 59D2983F
P 9650 4475
F 0 "K?" V 9600 4475 50  0000 C CNN
F 1 "CONN_3" V 9700 4475 40  0000 C CNN
F 2 "" H 9650 4475 60  0001 C CNN
F 3 "" H 9650 4475 60  0001 C CNN
	1    9650 4475
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D2999A
P 8050 4875
F 0 "R?" V 8130 4875 40  0000 C CNN
F 1 "R" V 8057 4876 40  0000 C CNN
F 2 "" V 7980 4875 30  0000 C CNN
F 3 "" H 8050 4875 30  0000 C CNN
	1    8050 4875
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D29C29
P 8050 4775
F 0 "R?" V 8130 4775 40  0000 C CNN
F 1 "500 kOhm" V 8057 4776 40  0000 C CNN
F 2 "" V 7980 4775 30  0000 C CNN
F 3 "" H 8050 4775 30  0000 C CNN
	1    8050 4775
	0    1    1    0   
$EndComp
Text Label 7325 4975 0    60   ~ 0
VSS
Text Label 8300 4775 0    60   ~ 0
VSS
Text Label 6525 5900 0    60   ~ 0
VSS
Text HLabel 6525 6000 2    60   BiDi ~ 0
VSS
Wire Wire Line
	6525 5775 6525 6000
Wire Wire Line
	7325 4775 7800 4775
Wire Wire Line
	7325 4875 7800 4875
$Comp
L C C?
U 1 1 59D29D69
P 7450 1750
F 0 "C?" H 7450 1850 40  0000 L CNN
F 1 "10 mkF" H 7456 1665 40  0000 L CNN
F 2 "" H 7488 1600 30  0000 C CNN
F 3 "" H 7450 1750 60  0000 C CNN
	1    7450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1550 8600 1550
Text Label 7450 1550 2    60   ~ 0
USB_MCP_VCC
Text Label 7450 1950 3    60   ~ 0
VSS
Text Label 8600 1650 2    60   ~ 0
VSS
Text Label 8300 4875 0    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	7325 4575 9300 4575
$Comp
L C C?
U 1 1 59D2A04F
P 9175 4875
F 0 "C?" H 9175 4975 40  0000 L CNN
F 1 "4.7 kmF" H 9181 4790 40  0000 L CNN
F 2 "" H 9213 4725 30  0000 C CNN
F 3 "" H 9175 4875 60  0000 C CNN
	1    9175 4875
	1    0    0    -1  
$EndComp
Text Label 9175 5075 3    60   ~ 0
VSS
Wire Wire Line
	9175 4675 9175 4575
Connection ~ 9175 4575
Text Label 9300 4475 2    60   ~ 0
VSS
Wire Wire Line
	7400 4675 7325 4675
Wire Wire Line
	7400 3725 7400 4675
Connection ~ 7400 4575
Wire Wire Line
	7400 3725 6525 3725
Wire Wire Line
	6525 3725 6525 3775
Wire Wire Line
	6125 3725 6125 3775
Wire Wire Line
	4850 3725 6125 3725
Wire Wire Line
	5275 3725 5275 4675
Wire Wire Line
	5275 4575 5325 4575
Wire Wire Line
	5275 4675 5325 4675
Connection ~ 5275 4575
$Comp
L C C?
U 1 1 59D2A4B7
P 4850 3925
F 0 "C?" H 4850 4025 40  0000 L CNN
F 1 "4.7 mkF" H 4856 3840 40  0000 L CNN
F 2 "" H 4888 3775 30  0000 C CNN
F 3 "" H 4850 3925 60  0000 C CNN
	1    4850 3925
	1    0    0    -1  
$EndComp
Connection ~ 5275 3725
$Comp
L THERMISTOR TH?
U 1 1 59D2A859
P 4750 5225
F 0 "TH?" V 4850 5275 50  0000 C CNN
F 1 "10 kOhm" V 4650 5225 50  0000 C CNN
F 2 "" H 4750 5225 60  0000 C CNN
F 3 "" H 4750 5225 60  0000 C CNN
	1    4750 5225
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 4975 5325 4975
Text Label 4750 5475 3    60   ~ 0
VSS
Text Label 4475 5625 2    60   ~ 0
USB_MCP_VCC
$Comp
L R R?
U 1 1 59D2AB6B
P 4475 5875
F 0 "R?" V 4555 5875 40  0000 C CNN
F 1 "10 KOhm" V 4482 5876 40  0000 C CNN
F 2 "" V 4405 5875 30  0000 C CNN
F 3 "" H 4475 5875 30  0000 C CNN
	1    4475 5875
	1    0    0    -1  
$EndComp
Wire Wire Line
	4475 6125 6125 6125
Wire Wire Line
	6125 6125 6125 5775
$Comp
L R R?
U 1 1 59D2AC0D
P 3350 6325
F 0 "R?" V 3430 6325 40  0000 C CNN
F 1 "10 KOhm" V 3357 6326 40  0000 C CNN
F 2 "" V 3280 6325 30  0000 C CNN
F 3 "" H 3350 6325 30  0000 C CNN
	1    3350 6325
	1    0    0    -1  
$EndComp
Text Label 3350 6075 2    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	6225 6575 3350 6575
Wire Wire Line
	6225 5775 6225 6575
$Comp
L R R?
U 1 1 59D2ACFA
P 4500 6975
F 0 "R?" V 4580 6975 40  0000 C CNN
F 1 "10 KOhm" V 4507 6976 40  0000 C CNN
F 2 "" V 4430 6975 30  0000 C CNN
F 3 "" H 4500 6975 30  0000 C CNN
	1    4500 6975
	1    0    0    -1  
$EndComp
Text Label 4500 6725 2    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	6325 7225 6325 5775
Text HLabel 4850 3725 0    60   Output ~ 0
OUT_SystemLoad
Text HLabel 5325 4775 0    60   Input ~ 0
SEL_InputSourceTypeSelection
Text HLabel 5325 4875 0    60   Input ~ 0
PROG2_USBPortCurrentRegationSet
Text Label 6225 3775 1    60   ~ 0
USB_MCP_VCC
Text Label 6325 3775 1    60   ~ 0
USB_MCP_VCC
Text HLabel 6425 3775 1    60   Input ~ 0
CE_ChargeEnable
Text HLabel 4475 6125 0    60   Output ~ 0
PG_OD_PowerGood
Text HLabel 3350 6575 0    60   Output ~ 0
STAT2_OD_ChargeStatusIndication
Wire Wire Line
	4500 7225 6325 7225
Text HLabel 4500 7225 0    60   Output ~ 0
LBO_OD_LowBatteryOutput
Text HLabel 6425 5775 3    60   Input ~ 0
TE_TimerEnable
$EndSCHEMATC
