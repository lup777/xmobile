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
$Descr A3 16535 11693
encoding utf-8
Sheet 1 5
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
L SIM800C U2
U 1 1 59667E03
P 10300 9225
F 0 "U2" H 10350 10200 60  0000 C CNN
F 1 "SIM800C" H 9650 10200 60  0000 C CNN
F 2 "SIM800C_lup:SIM800C" H 10125 9425 60  0000 C CNN
F 3 "" H 10300 9225 60  0000 C CNN
	1    10300 9225
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-xmobile R6
U 1 1 5967CB22
P 14375 4725
F 0 "R6" V 14455 4725 40  0000 C CNN
F 1 "10k" V 14382 4726 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14305 4725 30  0001 C CNN
F 3 "" H 14375 4725 30  0000 C CNN
	1    14375 4725
	-1   0    0    1   
$EndComp
Text Label 9250 8950 2    60   ~ 0
GND
Text Label 9250 9325 2    60   ~ 0
GND
Text Label 9250 9775 2    60   ~ 0
GND
Text Label 9250 9925 2    60   ~ 0
GND
Text Label 10950 9100 0    60   ~ 0
GND
Text Label 10950 9325 0    60   ~ 0
GND
Text Label 10950 8800 0    60   ~ 0
GND
Text Label 10950 9025 0    60   ~ 0
3.7V
Text Label 10950 8950 0    60   ~ 0
3.7V
Text Label 10950 9550 0    60   ~ 0
GND
Text Label 10950 9250 0    60   ~ 0
GND
Text Label 14375 4475 2    60   ~ 0
3.3V
$Comp
L CONN_8 P3
U 1 1 5974D7B3
P 14900 1300
F 0 "P3" V 14850 1300 60  0000 C CNN
F 1 "CONN_8" V 14950 1300 60  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-08P-2T_2x04x2.00mm_Straight" H 14900 1300 60  0001 C CNN
F 3 "" H 14900 1300 60  0001 C CNN
F 4 "EPD display connector" V 15075 1300 60  0000 C CNN "description"
	1    14900 1300
	1    0    0    -1  
$EndComp
Text Label 14550 950  2    60   ~ 0
EPD_BUSY
Text Label 14550 1050 2    60   ~ 0
EPD_RST
Text Label 14550 1150 2    60   ~ 0
EPD_DC
Text Label 14550 1250 2    60   ~ 0
EPD_CS
Text Label 14550 1350 2    60   ~ 0
EPD_CLK
Text Label 14550 1450 2    60   ~ 0
EPD_DIN
Text Label 14550 1550 2    60   ~ 0
GND
Text Label 14550 1650 2    60   ~ 0
3.3V
Text Label 10550 4575 0    60   ~ 0
EPD_CS
Text Label 10550 4875 0    60   ~ 0
EPD_CLK
Text Label 10550 4675 0    60   ~ 0
EPD_DIN
Text Label 10550 2575 0    60   ~ 0
EPD_DC
Text Label 10550 2775 0    60   ~ 0
EPD_BUSY
Text Label 10550 2875 0    60   ~ 0
EPD_RST
Text Label 14050 8875 2    60   ~ 0
GSM_AT_TXD
$Comp
L R-RESCUE-xmobile R7
U 1 1 5980DBE0
P 14300 8875
F 0 "R7" V 14380 8875 40  0000 C CNN
F 1 "1KOmh" V 14307 8876 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14230 8875 30  0001 C CNN
F 3 "" H 14300 8875 30  0000 C CNN
	1    14300 8875
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R13
U 1 1 5980DF53
P 14650 6650
F 0 "R13" V 14730 6650 40  0000 C CNN
F 1 "1KOmh" V 14657 6651 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14580 6650 30  0001 C CNN
F 3 "" H 14650 6650 30  0000 C CNN
	1    14650 6650
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R10
U 1 1 5980E098
P 14550 6875
F 0 "R10" V 14630 6875 40  0000 C CNN
F 1 "14KOmh" V 14550 6875 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14480 6875 30  0001 C CNN
F 3 "" H 14550 6875 30  0000 C CNN
	1    14550 6875
	0    1    1    0   
$EndComp
Text Label 14800 6875 0    60   ~ 0
GND
Text Label 14100 6650 2    60   ~ 0
GSM_AT_RXD
$Comp
L R-RESCUE-xmobile R14
U 1 1 5980ECFA
P 14650 7225
F 0 "R14" V 14730 7225 40  0000 C CNN
F 1 "1KOmh" V 14657 7226 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14580 7225 30  0001 C CNN
F 3 "" H 14650 7225 30  0000 C CNN
	1    14650 7225
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R11
U 1 1 5980EDB4
P 14550 7475
F 0 "R11" V 14630 7475 40  0000 C CNN
F 1 "14KOmh" V 14550 7475 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14480 7475 30  0001 C CNN
F 3 "" H 14550 7475 30  0000 C CNN
	1    14550 7475
	0    1    1    0   
$EndComp
Text Label 14800 7475 0    60   ~ 0
GND
Text Label 14175 7225 2    60   ~ 0
GSM_AT_RTS
$Comp
L R-RESCUE-xmobile R8
U 1 1 5980F251
P 14300 9100
F 0 "R8" V 14380 9100 40  0000 C CNN
F 1 "1KOmh" V 14307 9101 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14230 9100 30  0001 C CNN
F 3 "" H 14300 9100 30  0000 C CNN
	1    14300 9100
	0    1    1    0   
$EndComp
Text Label 14050 9100 2    60   ~ 0
GSM_AT_DCD
$Comp
L R-RESCUE-xmobile R15
U 1 1 5980F44E
P 14650 7800
F 0 "R15" V 14575 7800 40  0000 C CNN
F 1 "1KOmh" V 14657 7801 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14580 7800 30  0001 C CNN
F 3 "" H 14650 7800 30  0000 C CNN
	1    14650 7800
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R12
U 1 1 5980FA7D
P 14575 8050
F 0 "R12" V 14655 8050 40  0000 C CNN
F 1 "14KOmh" V 14575 8050 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14505 8050 30  0001 C CNN
F 3 "" H 14575 8050 30  0000 C CNN
	1    14575 8050
	0    -1   -1   0   
$EndComp
Text Label 14825 8050 0    60   ~ 0
GND
Text Label 14125 7800 2    60   ~ 0
GSM_AT_DTR
Text Label 15025 7225 0    60   ~ 0
XMEGA_PE0_GPIO
Text Label 10550 5875 0    60   ~ 0
XMEGA_PE0_GPIO
Text Label 9250 8575 2    60   ~ 0
GSM_AT_RTS
Text Label 9250 8425 2    60   ~ 0
GSM_AT_TXD
Text Label 14550 8875 0    60   ~ 0
XMEGA_PE2_RXD0
Text Label 10550 6075 0    60   ~ 0
XMEGA_PE2_RXD0
Text Label 14900 6650 0    60   ~ 0
XMEGA_PE3_TXD0
Text Label 10550 6175 0    60   ~ 0
XMEGA_PE3_TXD0
Text Label 14550 9100 0    60   ~ 0
XMEGA_PD2_GPIO
Text Label 10550 5425 0    60   ~ 0
XMEGA_PD4_GPIO
Text Label 14900 7800 0    60   ~ 0
XMEGA_PD3_GPIO
Text Label 10550 5325 0    60   ~ 0
XMEGA_PD3_GPIO
Text Label 9250 8725 2    60   ~ 0
GSM_AT_DCD
Text Label 9250 8500 2    60   ~ 0
GSM_AT_RXD
$Comp
L R-RESCUE-xmobile R16
U 1 1 5981CEE9
P 14650 8325
F 0 "R16" V 14575 8325 40  0000 C CNN
F 1 "1KOmh" V 14657 8326 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14580 8325 30  0001 C CNN
F 3 "" H 14650 8325 30  0000 C CNN
	1    14650 8325
	0    1    1    0   
$EndComp
Text Label 14100 8325 2    60   ~ 0
GSM_AT_CTS
Text Label 14900 8325 0    60   ~ 0
XMEGA_PD4_GPIO
$Comp
L R-RESCUE-xmobile R9
U 1 1 59820A06
P 14300 9325
F 0 "R9" V 14380 9325 40  0000 C CNN
F 1 "1KOmh" V 14307 9326 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 14230 9325 30  0001 C CNN
F 3 "" H 14300 9325 30  0000 C CNN
	1    14300 9325
	0    1    1    0   
$EndComp
Text Label 14050 9325 2    60   ~ 0
GSM_AT_RI
Text Label 14550 9325 0    60   ~ 0
XMEGA_PD1_GPIO
Text Label 9250 8650 2    60   ~ 0
GSM_AT_CTS
Text Label 9250 8800 2    60   ~ 0
GSM_AT_DTR
Text Label 9250 8875 2    60   ~ 0
GSM_AT_RI
Text Label 10550 5125 0    60   ~ 0
XMEGA_PD1_GPIO
Text Label 10550 5225 0    60   ~ 0
XMEGA_PD2_GPIO
$Comp
L STF202-22T1G U1
U 1 1 598237D5
P 2750 4850
F 0 "U1" H 2750 4750 50  0000 C CNN
F 1 "STF202-22T1G" H 2750 5075 50  0000 C CNN
F 2 "semiconductor:TSOP-6" H 2750 4850 50  0001 C CNN
F 3 "DOCUMENTATION" H 2750 4850 50  0001 C CNN
	1    2750 4850
	1    0    0    -1  
$EndComp
Text Label 10950 9625 0    60   ~ 0
GSM_USB_DN
Text Label 2000 4850 2    60   ~ 0
GSM_USB_DN
Text Label 10950 9700 0    60   ~ 0
GSM_USB_DP
Text Label 2000 4950 2    60   ~ 0
GSM_USB_DP
Text Label 3500 4750 0    60   ~ 0
GND
Text Label 2925 4125 3    60   ~ 0
GND
$Comp
L C-RESCUE-xmobile C1
U 1 1 59826142
P 1550 4125
F 0 "C1" H 1550 4225 40  0000 L CNN
F 1 "C" H 1556 4040 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 1588 3975 30  0001 C CNN
F 3 "" H 1550 4125 60  0000 C CNN
	1    1550 4125
	0    1    1    0   
$EndComp
Text Label 1350 4125 2    60   ~ 0
GND
Text Label 10950 9775 0    60   ~ 0
GSM_USB_VBUS
Text Label 2000 4750 2    60   ~ 0
GSM_USB_VBUS
Text Label 10950 8500 0    60   ~ 0
GSM_NETLIGHT
$Comp
L R-RESCUE-xmobile R3
U 1 1 5A91626C
P 5450 8375
F 0 "R3" V 5530 8375 40  0000 C CNN
F 1 "4.7KOmh" V 5457 8376 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5380 8375 30  0001 C CNN
F 3 "" H 5450 8375 30  0000 C CNN
	1    5450 8375
	0    1    1    0   
$EndComp
$Comp
L BC850 Q2
U 1 1 5A916427
P 6000 8375
F 0 "Q2" H 6000 8226 40  0000 R CNN
F 1 "A2SHB" H 6000 8525 40  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5900 8477 29  0000 C CNN
F 3 "" H 6000 8375 60  0000 C CNN
	1    6000 8375
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-xmobile D1
U 1 1 5A916783
P 6100 7275
F 0 "D1" H 6100 7375 50  0000 C CNN
F 1 "LED" H 6100 7175 50  0000 C CNN
F 2 "LEDs:LED_0603" H 6100 7275 60  0001 C CNN
F 3 "" H 6100 7275 60  0000 C CNN
	1    6100 7275
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R5
U 1 1 5A916BF7
P 6100 7825
F 0 "R5" V 6180 7825 40  0000 C CNN
F 1 "470Ом" V 6107 7826 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6030 7825 30  0001 C CNN
F 3 "" H 6100 7825 30  0000 C CNN
	1    6100 7825
	1    0    0    -1  
$EndComp
Text Label 6100 7075 0    60   ~ 0
3.7V
$Comp
L R-RESCUE-xmobile R4
U 1 1 5A9180D4
P 5750 8700
F 0 "R4" V 5830 8700 40  0000 C CNN
F 1 "4.7KOmh" V 5757 8701 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5680 8700 30  0001 C CNN
F 3 "" H 5750 8700 30  0000 C CNN
	1    5750 8700
	1    0    0    -1  
$EndComp
Text Label 6175 9000 0    60   ~ 0
GND
$Comp
L BC850 Q1
U 1 1 5A91C159
P 3125 6950
F 0 "Q1" H 3125 6801 40  0000 R CNN
F 1 "A2SHB" H 3125 7100 40  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3025 7052 29  0000 C CNN
F 3 "" H 3125 6950 60  0000 C CNN
	1    3125 6950
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-xmobile R2
U 1 1 5A91C5A8
P 2975 7350
F 0 "R2" V 3055 7350 40  0000 C CNN
F 1 "4.7KOmh" V 2982 7351 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2905 7350 30  0001 C CNN
F 3 "" H 2975 7350 30  0000 C CNN
	1    2975 7350
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-xmobile R1
U 1 1 5A91C857
P 2350 6950
F 0 "R1" V 2430 6950 40  0000 C CNN
F 1 "4.7KOmh" V 2357 6951 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2280 6950 30  0001 C CNN
F 3 "" H 2350 6950 30  0000 C CNN
	1    2350 6950
	0    1    1    0   
$EndComp
Text Label 3225 7525 3    60   ~ 0
GND
Text Label 10950 8650 0    60   ~ 0
GSM_POWER_KEY
Text Label 3225 6750 0    60   ~ 0
GSM_POWER_KEY
Text Label 2100 6950 2    60   ~ 0
XMEGA_PD0_GSM_POWER
Text Label 9250 9400 2    60   ~ 0
SIM_DET
Text Label 9250 9475 2    60   ~ 0
SIM_DATA
Text Label 9250 9550 2    60   ~ 0
SIM_CLK
Text Label 9250 9625 2    60   ~ 0
SIM_RST
Text Label 9250 9700 2    60   ~ 0
SIM_VDD
NoConn ~ 10950 8725
Text Label 10950 9175 0    60   ~ 0
GSM_ANT
Text Label 3450 975  2    60   ~ 0
GSM_ANT
Text Label 9250 9025 2    60   ~ 0
GSM_MICP
Text Label 9250 9100 2    60   ~ 0
GSM_MICN
Text Label 9250 9175 2    60   ~ 0
GSM_SPKP
Text Label 9250 9250 2    60   ~ 0
GSM_SPKN
$Sheet
S 6850 10225 1425 450 
U 5A9ED5F5
F0 "audio" 60
F1 "xmobile_audio.sch" 60
F2 "AUDIO_MICP" I R 8275 10325 60 
F3 "AUDIO_MICN" I R 8275 10475 60 
F4 "AUDIO_SPKP" I L 6850 10325 60 
F5 "AUDIO_SPKN" I L 6850 10475 60 
$EndSheet
Text Label 6850 10325 2    60   ~ 0
GSM_SPKP
Text Label 6850 10475 2    60   ~ 0
GSM_SPKN
Text Label 8275 10325 0    60   ~ 0
GSM_MICP
Text Label 8275 10475 0    60   ~ 0
GSM_MICN
$Sheet
S 2225 9125 1050 475 
U 5A9F76AF
F0 "xmobile_sim_holder" 60
F1 "xmobile_sim_holder.sch" 60
F2 "SIM_VCC" I L 2225 9225 60 
F3 "SIM_RST" I L 2225 9325 60 
F4 "SIM_CLK" I R 3275 9225 60 
F5 "GND" B R 3275 9325 60 
F6 "GSM_VDD" I R 3275 9425 60 
F7 "SIM_DET" O R 3275 9525 60 
F8 "SIM_DATA" B L 2225 9425 60 
$EndSheet
Text Label 5200 8375 2    60   ~ 0
GSM_NETLIGHT
$Sheet
S 725  1025 800  425 
U 5A9FCB78
F0 "xmega_power" 60
F1 "xmega_power.sch" 60
F2 "3.3V" O R 1525 1100 60 
F3 "3.7V" O R 1525 1225 60 
F4 "GND" O R 1525 1350 60 
$EndSheet
Text Label 1525 1100 0    60   ~ 0
3.3V
Text Label 1525 1225 0    60   ~ 0
3.7V
Text Label 1525 1350 0    60   ~ 0
GND
$Comp
L AVR-PDI-6 CON1
U 1 1 5AA047A2
P 14925 5100
F 0 "CON1" H 14845 5340 50  0000 C CNN
F 1 "AVR-PDI-6" H 14715 4855 50  0000 L BNN
F 2 "Connectors_JAE:JAE_LY20-06P-2T_2x03x2.00mm_Straight" V 14480 5135 50  0001 C CNN
F 3 "" H 14925 5100 60  0001 C CNN
	1    14925 5100
	1    0    0    -1  
$EndComp
Text Label 15050 5000 0    60   ~ 0
3.3V
Text Label 15050 5200 0    60   ~ 0
GND
Text Label 14175 6150 3    60   ~ 0
GND
$Sheet
S 4000 2075 650  675 
U 5AA512DD
F0 "xmobile_keyboard" 60
F1 "xmobile_keyboard.sch" 60
F2 "in1" I L 4000 2225 60 
F3 "in2" I L 4000 2375 60 
F4 "in3" I L 4000 2525 60 
F5 "out1" O R 4650 2225 60 
F6 "out2" O R 4650 2375 60 
F7 "out3" O R 4650 2525 60 
F8 "GND" B R 4650 2650 60 
$EndSheet
Text Label 4000 2225 2    60   ~ 0
KBD_IN_1
Text Label 10550 5525 0    60   ~ 0
KBD_IN_1
Text Label 10550 5625 0    60   ~ 0
KBD_IN_2
Text Label 4000 2375 2    60   ~ 0
KBD_IN_2
Text Label 10550 5725 0    60   ~ 0
KBD_IN_3
Text Label 4000 2525 2    60   ~ 0
KBD_IN_3
Text Label 10550 4175 0    60   ~ 0
KBD_OUT_1
Text Label 4650 2225 0    60   ~ 0
KBD_OUT_1
Text Label 10550 4275 0    60   ~ 0
KBD_OUT_2
Text Label 4650 2375 0    60   ~ 0
KBD_OUT_2
Text Label 10550 4375 0    60   ~ 0
KBD_OUT_3
Text Label 4650 2525 0    60   ~ 0
KBD_OUT_3
Text Label 10550 5025 0    60   ~ 0
XMEGA_PD0_GSM_POWER
$Comp
L CONN_4 P7
U 1 1 5AA6D87E
P 15300 3825
F 0 "P7" V 15250 3825 50  0000 C CNN
F 1 "CONN_4" V 15350 3825 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-04P-2T_2x02x2.00mm_Straight" H 15300 3825 60  0001 C CNN
F 3 "" H 15300 3825 60  0001 C CNN
	1    15300 3825
	1    0    0    -1  
$EndComp
Text Label 10550 2475 0    60   ~ 0
XMEGA_PA0
Text Label 14950 3675 2    60   ~ 0
XMEGA_PA0
Text Label 10550 2675 0    60   ~ 0
XMEGA_PA2
Text Label 14950 3775 2    60   ~ 0
XMEGA_PA2
Text Label 10550 4775 0    60   ~ 0
XMEGA_PC6
Text Label 14950 3875 2    60   ~ 0
XMEGA_PC6
$Comp
L switch1 U5
U 1 1 5AB790A5
P 14275 5800
F 0 "U5" H 14275 5600 60  0000 C CNN
F 1 "switch1" H 14275 6000 60  0000 C CNN
F 2 "switch1:switch_6x9" H 14275 5800 60  0001 C CNN
F 3 "" H 14275 5800 60  0001 C CNN
	1    14275 5800
	0    1    1    0   
$EndComp
Text Label 14275 6150 3    60   ~ 0
GND
NoConn ~ 14375 6150
NoConn ~ 14175 5450
$Comp
L USB_B P1
U 1 1 5AB7B7B5
P 2825 3825
F 0 "P1" H 3025 3625 50  0000 C CNN
F 1 "USB_B" H 2775 4025 50  0000 C CNN
F 2 "usb:Conn_USBmicro-B_ebay-side_TH" V 2775 3725 50  0000 C CNN
F 3 "" V 2775 3725 50  0000 C CNN
	1    2825 3825
	1    0    0    -1  
$EndComp
Text Label 3125 3725 0    60   ~ 0
GND
Text Label 4650 2650 0    60   ~ 0
GND
NoConn ~ 14950 3975
NoConn ~ 15050 5100
NoConn ~ 14800 5100
Text Label 14800 5000 2    60   ~ 0
PDI_D
Text Label 14225 5200 2    60   ~ 0
PDI_C
$Comp
L PWR_FLAG #FLG01
U 1 1 5AB82AA2
P 1850 1100
F 0 "#FLG01" H 1850 1195 50  0001 C CNN
F 1 "PWR_FLAG" H 1850 1280 50  0000 C CNN
F 2 "" H 1850 1100 50  0000 C CNN
F 3 "" H 1850 1100 50  0000 C CNN
	1    1850 1100
	1    0    0    -1  
$EndComp
NoConn ~ 10950 8425
Text Label 10950 8875 0    60   ~ 0
GND
NoConn ~ 10950 9400
NoConn ~ 10950 9475
NoConn ~ 10950 9850
NoConn ~ 10950 9925
NoConn ~ 9250 9850
Text Label 3275 9525 0    60   ~ 0
SIM_DET
Text Label 2225 9425 2    60   ~ 0
SIM_DATA
Text Label 3275 9225 0    60   ~ 0
SIM_CLK
Text Label 2225 9325 2    60   ~ 0
SIM_RST
Text Label 2225 9225 2    60   ~ 0
SIM_VDD
Text Label 3275 9325 0    60   ~ 0
GND
Text Label 10950 8575 0    60   ~ 0
SIM_HOLDER_VDD_EXT
Text Label 3275 9425 0    60   ~ 0
SIM_HOLDER_VDD_EXT
$Comp
L CONN_01X02 P2
U 1 1 5AB8506D
P 3650 1025
F 0 "P2" H 3650 1175 50  0000 C CNN
F 1 "CONN_01X02" V 3750 1025 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-04P-2T_2x02x2.00mm_Straight" H 3650 1025 50  0000 C CNN
F 3 "" H 3650 1025 50  0000 C CNN
	1    3650 1025
	1    0    0    -1  
$EndComp
NoConn ~ 3450 1075
$Comp
L ATXMEGA128A1U-A IC1
U 1 1 5AC0F16A
P 9350 4575
F 0 "IC1" H 8300 6875 50  0000 L BNN
F 1 "ATXMEGA128A1U-A" H 9900 2225 50  0000 L BNN
F 2 "tqfp:LQFP-100_14x14mm_Pitch0.5mm" H 9350 4575 50  0000 C CIN
F 3 "" H 9350 4575 50  0000 C CNN
	1    9350 4575
	1    0    0    -1  
$EndComp
$Comp
L C C39
U 1 1 5AC15554
P 11525 2400
F 0 "C39" H 11550 2500 50  0000 L CNN
F 1 "100nF" H 11550 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 11563 2250 50  0000 C CNN
F 3 "" H 11525 2400 50  0000 C CNN
	1    11525 2400
	0    -1   -1   0   
$EndComp
$Comp
L C C38
U 1 1 5AC15849
P 11525 1425
F 0 "C38" H 11550 1525 50  0000 L CNN
F 1 "100nF" H 11550 1325 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 11563 1275 50  0000 C CNN
F 3 "" H 11525 1425 50  0000 C CNN
	1    11525 1425
	0    1    1    0   
$EndComp
$Comp
L C C37
U 1 1 5AC15959
P 9725 1800
F 0 "C37" H 9750 1900 50  0000 L CNN
F 1 "100nF" H 9750 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9763 1650 50  0000 C CNN
F 3 "" H 9725 1800 50  0000 C CNN
	1    9725 1800
	1    0    0    -1  
$EndComp
$Comp
L C C36
U 1 1 5AC15B5B
P 9600 1525
F 0 "C36" H 9625 1625 50  0000 L CNN
F 1 "100nF" H 9625 1425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9638 1375 50  0000 C CNN
F 3 "" H 9600 1525 50  0000 C CNN
	1    9600 1525
	1    0    0    -1  
$EndComp
$Comp
L C C35
U 1 1 5AC15C67
P 9475 1800
F 0 "C35" H 9500 1900 50  0000 L CNN
F 1 "100nF" H 9500 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9513 1650 50  0000 C CNN
F 3 "" H 9475 1800 50  0000 C CNN
	1    9475 1800
	1    0    0    -1  
$EndComp
$Comp
L C C34
U 1 1 5AC15D7C
P 9350 1525
F 0 "C34" H 9375 1625 50  0000 L CNN
F 1 "100nF" H 9375 1425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9388 1375 50  0000 C CNN
F 3 "" H 9350 1525 50  0000 C CNN
	1    9350 1525
	1    0    0    -1  
$EndComp
$Comp
L C C33
U 1 1 5AC15E90
P 9225 1800
F 0 "C33" H 9250 1900 50  0000 L CNN
F 1 "100nF" H 9250 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9263 1650 50  0000 C CNN
F 3 "" H 9225 1800 50  0000 C CNN
	1    9225 1800
	1    0    0    -1  
$EndComp
$Comp
L C C32
U 1 1 5AC15FC5
P 9100 1525
F 0 "C32" H 9125 1625 50  0000 L CNN
F 1 "100nF" H 9125 1425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9138 1375 50  0000 C CNN
F 3 "" H 9100 1525 50  0000 C CNN
	1    9100 1525
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AC178F7
P 8975 1800
F 0 "C3" H 9000 1900 50  0000 L CNN
F 1 "100nF" H 9000 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9013 1650 50  0000 C CNN
F 3 "" H 8975 1800 50  0000 C CNN
	1    8975 1800
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AC17A8A
P 8850 1525
F 0 "C2" H 8875 1625 50  0000 L CNN
F 1 "100nF" H 8875 1425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8888 1375 50  0000 C CNN
F 3 "" H 8850 1525 50  0000 C CNN
	1    8850 1525
	1    0    0    -1  
$EndComp
Text Label 9600 1375 1    60   ~ 0
GND
Text Label 9350 1375 1    60   ~ 0
GND
Text Label 9100 1375 1    60   ~ 0
GND
Text Label 8850 1375 1    60   ~ 0
GND
Text Label 9725 1375 1    60   ~ 0
GND
Text Label 9475 1375 1    60   ~ 0
GND
Text Label 9225 1375 1    60   ~ 0
GND
Text Label 8975 1375 1    60   ~ 0
GND
Text Label 9750 6975 3    60   ~ 0
GND
Text Label 9650 6975 3    60   ~ 0
GND
Text Label 9550 6975 3    60   ~ 0
GND
Text Label 9450 6975 3    60   ~ 0
GND
Text Label 9350 6975 3    60   ~ 0
GND
Text Label 9250 6975 3    60   ~ 0
GND
Text Label 9150 6975 3    60   ~ 0
GND
Text Label 9050 6975 3    60   ~ 0
GND
Text Label 8950 6975 3    60   ~ 0
GND
Text Label 8850 6975 3    60   ~ 0
GND
Text Label 8150 2475 2    60   ~ 0
PDI_C
Text Label 8150 2575 2    60   ~ 0
PDI_D
$Comp
L CP1-RESCUE-xmobile C41
U 1 1 5AC1E9E1
P 11575 2100
F 0 "C41" H 11625 2200 50  0000 L CNN
F 1 "10mk" H 11575 2000 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.3" H 11575 2100 60  0001 C CNN
F 3 "" H 11575 2100 60  0000 C CNN
	1    11575 2100
	0    -1   -1   0   
$EndComp
Text Label 11775 2400 3    60   ~ 0
GND
$Comp
L CP1-RESCUE-xmobile C40
U 1 1 5AC202D3
P 11575 1725
F 0 "C40" H 11625 1825 50  0000 L CNN
F 1 "10mk" H 11575 1625 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.3" H 11575 1725 60  0001 C CNN
F 3 "" H 11575 1725 60  0000 C CNN
	1    11575 1725
	0    -1   -1   0   
$EndComp
Text Label 11775 1425 1    60   ~ 0
GND
Text Label 8350 2000 2    60   ~ 0
3.3V
$Comp
L CONN_01X08 P10
U 1 1 5AC3E445
P 7600 6325
F 0 "P10" H 7600 6775 50  0000 C CNN
F 1 "CONN_01X08" V 7700 6325 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-08P-2T_2x04x2.00mm_Straight" H 7600 6325 50  0000 C CNN
F 3 "" H 7600 6325 50  0000 C CNN
	1    7600 6325
	-1   0    0    1   
$EndComp
NoConn ~ 8150 2975
NoConn ~ 8150 3075
NoConn ~ 8150 3175
NoConn ~ 8150 3275
NoConn ~ 8150 3425
NoConn ~ 8150 3525
NoConn ~ 8150 3625
NoConn ~ 8150 3725
NoConn ~ 8150 3825
NoConn ~ 8150 3925
NoConn ~ 8150 4025
NoConn ~ 8150 4125
NoConn ~ 8150 4275
NoConn ~ 8150 4375
NoConn ~ 8150 4475
NoConn ~ 8150 4575
NoConn ~ 8150 4675
NoConn ~ 8150 4775
NoConn ~ 8150 4875
NoConn ~ 8150 4975
NoConn ~ 8150 5125
NoConn ~ 8150 5225
NoConn ~ 8150 5325
NoConn ~ 8150 5425
NoConn ~ 8150 5525
NoConn ~ 8150 5625
NoConn ~ 8150 5725
NoConn ~ 8150 5825
NoConn ~ 10550 6575
NoConn ~ 10550 6475
NoConn ~ 10550 6375
NoConn ~ 10550 6275
NoConn ~ 10550 5975
NoConn ~ 10550 3725
NoConn ~ 10550 3825
NoConn ~ 10550 3925
NoConn ~ 10550 4025
$Comp
L INDUCTOR L1
U 1 1 5AC20B29
P 10050 1650
F 0 "L1" V 10000 1650 40  0000 C CNN
F 1 "120m" V 10150 1650 40  0001 C CNN
F 2 "Inductors:Inductor_1212" H 10050 1650 60  0001 C CNN
F 3 "" H 10050 1650 60  0000 C CNN
F 4 "ferrite bead" V 10175 1625 60  0000 C CNN "details"
	1    10050 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	14175 7225 14400 7225
Wire Wire Line
	14900 7225 15025 7225
Wire Wire Line
	14250 7475 14300 7475
Wire Wire Line
	14250 7475 14250 7225
Connection ~ 14250 7225
Wire Wire Line
	14100 6650 14400 6650
Wire Wire Line
	14300 6875 14250 6875
Wire Wire Line
	14250 6875 14250 6650
Connection ~ 14250 6650
Wire Wire Line
	14125 7800 14400 7800
Wire Wire Line
	14325 8050 14250 8050
Wire Wire Line
	14250 8050 14250 7800
Connection ~ 14250 7800
Wire Wire Line
	14100 8325 14400 8325
Wire Wire Line
	2000 4125 2000 4750
Wire Wire Line
	1750 4125 2625 4125
Wire Wire Line
	3500 4850 3775 4850
Wire Wire Line
	2725 4450 3775 4450
Wire Wire Line
	2725 4450 2725 4125
Wire Wire Line
	3500 4950 3875 4950
Wire Wire Line
	2825 4350 3875 4350
Wire Wire Line
	2825 4350 2825 4125
Wire Wire Line
	3775 4450 3775 4850
Wire Wire Line
	3875 4350 3875 4950
Connection ~ 2000 4125
Wire Wire Line
	5700 8375 5800 8375
Wire Wire Line
	5750 8375 5750 8450
Connection ~ 5750 8375
Wire Wire Line
	6100 8075 6100 8175
Wire Wire Line
	6100 8575 6100 9000
Wire Wire Line
	6100 7575 6100 7475
Wire Wire Line
	5750 9000 6175 9000
Wire Wire Line
	5750 9000 5750 8950
Connection ~ 6100 9000
Wire Wire Line
	3225 7150 3225 7525
Connection ~ 3225 7350
Wire Wire Line
	2600 6950 2925 6950
Wire Wire Line
	2725 7350 2725 6950
Connection ~ 2725 6950
Wire Wire Line
	14375 4975 14375 5450
Wire Wire Line
	14225 5200 14800 5200
Connection ~ 14375 5200
Wire Wire Line
	1525 1100 1850 1100
Wire Wire Line
	9100 1675 9100 2000
Wire Wire Line
	9725 1650 9725 1375
Wire Wire Line
	9475 1650 9475 1375
Wire Wire Line
	9225 1650 9225 1375
Wire Wire Line
	8975 1650 8975 1375
Wire Wire Line
	11775 1725 11775 1425
Wire Wire Line
	11775 1425 11675 1425
Wire Wire Line
	11775 2100 11775 2400
Wire Wire Line
	11775 2400 11675 2400
Connection ~ 11375 1425
Connection ~ 11375 2400
Connection ~ 11375 1725
Connection ~ 11375 2100
Wire Wire Line
	8850 2000 8850 1675
Wire Wire Line
	8975 1950 8975 2000
Connection ~ 8975 2000
Connection ~ 9100 2000
Wire Wire Line
	9225 1950 9225 2000
Connection ~ 9225 2000
Wire Wire Line
	9475 1950 9475 2000
Connection ~ 9475 2000
Wire Wire Line
	9725 1950 9725 2000
Connection ~ 9725 2000
Wire Wire Line
	9600 1675 9600 2000
Connection ~ 9600 2000
Wire Wire Line
	9650 2175 9650 2000
Connection ~ 9650 2000
Wire Wire Line
	9550 2175 9550 2000
Connection ~ 9550 2000
Wire Wire Line
	9450 2175 9450 2000
Connection ~ 9450 2000
Wire Wire Line
	9350 1675 9350 2175
Connection ~ 9350 2000
Wire Wire Line
	9150 2175 9150 2000
Connection ~ 9150 2000
Wire Wire Line
	9250 2175 9250 2000
Connection ~ 9250 2000
Wire Wire Line
	9050 2175 9050 2000
Connection ~ 9050 2000
Wire Wire Line
	8950 2175 8950 2000
Connection ~ 8950 2000
Connection ~ 8850 2000
Wire Wire Line
	7800 5975 8150 5975
Wire Wire Line
	8150 6075 7800 6075
Wire Wire Line
	7800 6175 8150 6175
Wire Wire Line
	8150 6275 7800 6275
Wire Wire Line
	8150 6375 7800 6375
Wire Wire Line
	7800 6475 8150 6475
Wire Wire Line
	8150 6575 7800 6575
Wire Wire Line
	7800 6675 8150 6675
Wire Wire Line
	8350 2000 10050 2000
Wire Wire Line
	10050 2000 10050 1950
Wire Wire Line
	9800 2175 9800 2050
Wire Wire Line
	9900 2175 9900 2100
Wire Wire Line
	11375 1350 11375 2400
Wire Wire Line
	9800 2050 10850 2050
Wire Wire Line
	10850 2050 10850 1725
Wire Wire Line
	10850 1725 11375 1725
Wire Wire Line
	9900 2100 11375 2100
Wire Wire Line
	10050 1350 11375 1350
$Comp
L PWR_FLAG #FLG02
U 1 1 5AC483E4
P 11375 1350
F 0 "#FLG02" H 11375 1445 50  0001 C CNN
F 1 "PWR_FLAG" H 11375 1530 50  0000 C CNN
F 2 "" H 11375 1350 50  0000 C CNN
F 3 "" H 11375 1350 50  0000 C CNN
	1    11375 1350
	1    0    0    -1  
$EndComp
NoConn ~ 10550 3075
NoConn ~ 10550 2975
NoConn ~ 10550 3525
NoConn ~ 10550 3625
NoConn ~ 10550 3175
NoConn ~ 10550 3325
NoConn ~ 10550 3425
NoConn ~ 8150 2725
NoConn ~ 8150 2825
NoConn ~ 10550 4475
$EndSCHEMATC
