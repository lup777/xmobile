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
Sheet 2 3
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
L MICRO_USB_B P?
U 1 1 59D2121F
P 9000 1525
F 0 "P?" H 9050 1975 60  0000 C CNN
F 1 "MICRO_USB_B" H 8650 1975 60  0000 C CNN
F 2 "" H 9250 1225 60  0000 C CNN
F 3 "" H 9250 1225 60  0000 C CNN
	1    9000 1525
	1    0    0    -1  
$EndComp
Text Label 5450 3600 1    60   ~ 0
USB_MCP_VCC
Text Label 7500 1275 2    60   ~ 0
USB_MCP_VCC
$Comp
L C C?
U 1 1 59D2173F
P 7725 1475
F 0 "C?" H 7725 1575 40  0000 L CNN
F 1 "10mkF" H 7731 1390 40  0000 L CNN
F 2 "" H 7763 1325 30  0000 C CNN
F 3 "" H 7725 1475 60  0000 C CNN
	1    7725 1475
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1275 8450 1275
Connection ~ 7725 1275
$Comp
L C C?
U 1 1 59D21AE1
P 3575 3850
F 0 "C?" H 3575 3950 40  0000 L CNN
F 1 "4.7mkF" H 3581 3765 40  0000 L CNN
F 2 "" H 3613 3700 30  0000 C CNN
F 3 "" H 3575 3850 60  0000 C CNN
	1    3575 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3525 5350 3600
Wire Wire Line
	3300 3525 5350 3525
Wire Wire Line
	3575 3525 3575 3650
Text HLabel 3300 3525 0    60   Output ~ 0
OUT_SystemLoad
Connection ~ 3575 3525
Text HLabel 4550 4600 0    60   Input ~ 0
SEL_InputSourcTypeSelection
Text HLabel 5950 5725 2    60   BiDi ~ 0
VSS
$Comp
L C C?
U 1 1 59D226E0
P 8575 4600
F 0 "C?" H 8575 4700 40  0000 L CNN
F 1 "4.7mkF" H 8581 4515 40  0000 L CNN
F 2 "" H 8613 4450 30  0000 C CNN
F 3 "" H 8575 4600 60  0000 C CNN
	1    8575 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 4400 8750 4400
$Comp
L CONN_3 K?
U 1 1 59D2282D
P 9100 4300
F 0 "K?" V 9050 4300 50  0000 C CNN
F 1 "CONN_3" V 9150 4300 40  0000 C CNN
F 2 "" H 9100 4300 60  0001 C CNN
F 3 "" H 9100 4300 60  0001 C CNN
	1    9100 4300
	1    0    0    -1  
$EndComp
Text Label 5950 5925 0    60   ~ 0
VSS
Wire Wire Line
	5750 5600 5750 5925
Wire Wire Line
	5750 5725 5950 5725
Wire Wire Line
	5750 5925 5950 5925
Connection ~ 5750 5725
Text Label 8750 4300 2    60   ~ 0
VSS
Text Label 8575 4800 3    60   ~ 0
VSS
Text Label 8450 1375 2    60   ~ 0
VSS
Text Label 7350 4600 0    60   ~ 0
VSS
Text HLabel 4550 4700 0    60   Input ~ 0
PROG2_USBPortCurrentRegulationSet
Connection ~ 4225 3525
Connection ~ 4225 4400
Wire Wire Line
	4550 4400 4225 4400
Wire Wire Line
	4225 3525 4225 4500
Wire Wire Line
	4225 4500 4550 4500
Text Label 6550 4800 0    60   ~ 0
VSS
Text Label 7725 1675 3    60   ~ 0
VSS
Text Label 5550 3600 1    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	5750 3600 5750 3525
Wire Wire Line
	5750 3525 6600 3525
Wire Wire Line
	6600 3525 6600 4500
Connection ~ 6600 4400
Wire Wire Line
	6600 4500 6550 4500
Text HLabel 5650 3600 1    60   Input ~ 0
CE_ChargeEnable
Text HLabel 3375 7050 0    60   Output ~ 0
LBO_OD_LowBatteryOutput
Text HLabel 3400 6375 0    60   Output ~ 0
STAT2_OD_ChargeStatusIndication
Text HLabel 5650 5600 3    60   Input ~ 0
TE_TimerEnable
Text HLabel 3400 5725 0    60   Output ~ 0
PG_OD_PowerGood
$Comp
L MCP73871 U?
U 1 1 59D21098
P 5550 4600
F 0 "U?" H 5550 4500 50  0000 C CNN
F 1 "MCP73871" H 5550 4700 50  0000 C CNN
F 2 "MODULE" H 5550 4600 50  0001 C CNN
F 3 "DOCUMENTATION" H 5550 4600 50  0001 C CNN
	1    5550 4600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D26160
P 3400 5475
F 0 "R?" V 3480 5475 40  0000 C CNN
F 1 "10 KOhm" V 3407 5476 40  0000 C CNN
F 2 "" V 3330 5475 30  0000 C CNN
F 3 "" H 3400 5475 30  0000 C CNN
	1    3400 5475
	1    0    0    -1  
$EndComp
Text Label 3400 5225 2    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	3400 5725 5350 5725
Wire Wire Line
	5350 5725 5350 5600
$Comp
L R R?
U 1 1 59D263E0
P 3400 6125
F 0 "R?" V 3480 6125 40  0000 C CNN
F 1 "10 KOhm" V 3407 6126 40  0000 C CNN
F 2 "" V 3330 6125 30  0000 C CNN
F 3 "" H 3400 6125 30  0000 C CNN
	1    3400 6125
	1    0    0    -1  
$EndComp
Text Label 3400 5875 2    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	3400 6375 5450 6375
Wire Wire Line
	5450 6375 5450 5600
$Comp
L R R?
U 1 1 59D2657D
P 3375 6800
F 0 "R?" V 3455 6800 40  0000 C CNN
F 1 "10 KOhm" V 3382 6801 40  0000 C CNN
F 2 "" V 3305 6800 30  0000 C CNN
F 3 "" H 3375 6800 30  0000 C CNN
	1    3375 6800
	1    0    0    -1  
$EndComp
Text Label 3375 6550 2    60   ~ 0
USB_MCP_VCC
Wire Wire Line
	3375 7050 5550 7050
Wire Wire Line
	5550 7050 5550 5600
$Comp
L R R?
U 1 1 59D24253
P 7100 4700
F 0 "R?" V 7180 4700 40  0000 C CNN
F 1 "R" V 7107 4701 40  0000 C CNN
F 2 "" V 7030 4700 30  0000 C CNN
F 3 "" H 7100 4700 30  0000 C CNN
	1    7100 4700
	0    1    1    0   
$EndComp
Text Label 7350 4700 0    60   ~ 0
USB_MCP_VCC
$Comp
L R R?
U 1 1 59D2303B
P 7100 4600
F 0 "R?" V 7180 4600 40  0000 C CNN
F 1 "500 Ohm" V 7107 4601 40  0000 C CNN
F 2 "" V 7030 4600 30  0000 C CNN
F 3 "" H 7100 4600 30  0000 C CNN
	1    7100 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6550 4600 6850 4600
Wire Wire Line
	6550 4700 6850 4700
$Comp
L THERMISTOR TH?
U 1 1 59D249BB
P 4250 5050
F 0 "TH?" V 4350 5100 50  0000 C CNN
F 1 "10 kOhm" V 4150 5050 50  0000 C CNN
F 2 "" H 4250 5050 60  0000 C CNN
F 3 "" H 4250 5050 60  0000 C CNN
	1    4250 5050
	1    0    0    -1  
$EndComp
Text Label 4250 5300 3    60   ~ 0
VSS
Wire Wire Line
	4250 4800 4550 4800
Text Notes 6725 6350 0    60   ~ 0
Резистор на PROG1 расчитан на максимальный зарядный то и для USB и для DC-DC на 2А
Text Label 3575 4050 3    60   ~ 0
VSS
$EndSCHEMATC
