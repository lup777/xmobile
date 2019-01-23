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
L R-RESCUE-xmobile R6
U 1 1 5967CB22
P 10025 10100
F 0 "R6" V 10105 10100 40  0000 C CNN
F 1 "10k" V 10032 10101 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9955 10100 30  0001 C CNN
F 3 "" H 10025 10100 30  0000 C CNN
	1    10025 10100
	0    -1   -1   0   
$EndComp
Text Label 10275 10100 0    60   ~ 0
3.3V
$Comp
L CONN_8 P3
U 1 1 5974D7B3
P 15400 1275
F 0 "P3" V 15350 1275 60  0000 C CNN
F 1 "CONN_8" V 15450 1275 60  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-08P-2T_2x04x2.00mm_Straight" H 15400 1275 60  0001 C CNN
F 3 "" H 15400 1275 60  0001 C CNN
F 4 "EPD display connector" V 15575 1275 60  0000 C CNN "description"
	1    15400 1275
	1    0    0    -1  
$EndComp
Text Label 15050 925  2    60   ~ 0
EPD_BUSY
Text Label 15050 1025 2    60   ~ 0
EPD_RST
Text Label 15050 1125 2    60   ~ 0
EPD_DC
Text Label 15050 1225 2    60   ~ 0
EPD_CS
Text Label 15050 1325 2    60   ~ 0
EPD_CLK
Text Label 15050 1425 2    60   ~ 0
EPD_DIN
Text Label 15050 1525 2    60   ~ 0
GND
Text Label 15050 1625 2    60   ~ 0
3.3V
Text Label 29800 12150 0    60   ~ 0
EPD_CS
Text Label 29800 12450 0    60   ~ 0
EPD_CLK
Text Label 29800 12250 0    60   ~ 0
EPD_DIN
Text Label 29800 10150 0    60   ~ 0
EPD_DC
Text Label 29800 10350 0    60   ~ 0
EPD_BUSY
Text Label 29800 10450 0    60   ~ 0
EPD_RST
Text Label 29800 13450 0    60   ~ 0
XMEGA_PE0_GPIO
Text Label 29800 13650 0    60   ~ 0
XMEGA_PE2_RXD0
Text Label 29800 13750 0    60   ~ 0
XMEGA_PE3_TXD0
Text Label 29800 13000 0    60   ~ 0
XMEGA_PD4_GPIO
Text Label 29800 12900 0    60   ~ 0
XMEGA_PD3_GPIO
Text Label 29800 12700 0    60   ~ 0
XMEGA_PD1_GPIO
Text Label 29800 12800 0    60   ~ 0
XMEGA_PD2_GPIO
$Sheet
S 14025 4575 725  575 
U 5A9ED5F5
F0 "audio" 60
F1 "xmobile_audio.sch" 60
F2 "AUDIO_MICP" I L 14025 4675 60 
F3 "AUDIO_MICN" I L 14025 4800 60 
F4 "AUDIO_SPKP" I L 14025 5050 60 
F5 "AUDIO_SPKN" I L 14025 4925 60 
$EndSheet
$Sheet
S 550  10925 500  150 
U 5A9FCB78
F0 "xmega_power" 60
F1 "xmega_power.sch" 60
$EndSheet
$Comp
L AVR-PDI-6 CON1
U 1 1 5AA047A2
P 9650 10650
F 0 "CON1" H 9570 10890 50  0000 C CNN
F 1 "AVR-PDI-6" H 9440 10405 50  0000 L BNN
F 2 "Connectors_JAE:JAE_LY20-06P-2T_2x03x2.00mm_Straight" V 9205 10685 50  0001 C CNN
F 3 "" H 9650 10650 60  0001 C CNN
	1    9650 10650
	0    1    1    0   
$EndComp
Text Label 9750 10775 3    60   ~ 0
3.3V
Text Label 9550 10775 3    60   ~ 0
GND
Text Label 8600 9900 2    60   ~ 0
GND
$Sheet
S 13175 6900 650  675 
U 5AA512DD
F0 "xmobile_keyboard" 60
F1 "xmobile_keyboard.sch" 60
F2 "in1" I L 13175 7050 60 
F3 "in2" I L 13175 7200 60 
F4 "in3" I L 13175 7350 60 
F5 "out1" O R 13825 7050 60 
F6 "out2" O R 13825 7200 60 
F7 "out3" O R 13825 7350 60 
F8 "GND" B R 13825 7475 60 
$EndSheet
Text Label 13175 7050 2    60   ~ 0
KBD_IN_1
Text Label 29800 13100 0    60   ~ 0
KBD_IN_1
Text Label 29800 13200 0    60   ~ 0
KBD_IN_2
Text Label 13175 7200 2    60   ~ 0
KBD_IN_2
Text Label 29800 13300 0    60   ~ 0
KBD_IN_3
Text Label 13175 7350 2    60   ~ 0
KBD_IN_3
Text Label 29800 11750 0    60   ~ 0
KBD_OUT_1
Text Label 13825 7050 0    60   ~ 0
KBD_OUT_1
Text Label 29800 11850 0    60   ~ 0
KBD_OUT_2
Text Label 13825 7200 0    60   ~ 0
KBD_OUT_2
Text Label 29800 11950 0    60   ~ 0
KBD_OUT_3
Text Label 13825 7350 0    60   ~ 0
KBD_OUT_3
Text Label 29800 12600 0    60   ~ 0
XMEGA_PD0_GSM_POWER
$Comp
L CONN_4 P7
U 1 1 5AA6D87E
P 34550 11400
F 0 "P7" V 34500 11400 50  0000 C CNN
F 1 "CONN_4" V 34600 11400 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-04P-2T_2x02x2.00mm_Straight" H 34550 11400 60  0001 C CNN
F 3 "" H 34550 11400 60  0001 C CNN
	1    34550 11400
	1    0    0    -1  
$EndComp
Text Label 29800 10050 0    60   ~ 0
XMEGA_PA0
Text Label 34200 11250 2    60   ~ 0
XMEGA_PA0
Text Label 29800 10250 0    60   ~ 0
XMEGA_PA2
Text Label 34200 11350 2    60   ~ 0
XMEGA_PA2
Text Label 29800 12350 0    60   ~ 0
XMEGA_PC6
Text Label 34200 11450 2    60   ~ 0
XMEGA_PC6
$Comp
L switch1 U5
U 1 1 5AB790A5
P 8950 10000
F 0 "U5" H 8950 9800 60  0000 C CNN
F 1 "switch1" H 8950 10200 60  0000 C CNN
F 2 "switch1:switch_6x9" H 8950 10000 60  0001 C CNN
F 3 "" H 8950 10000 60  0001 C CNN
	1    8950 10000
	-1   0    0    1   
$EndComp
Text Label 8600 10000 2    60   ~ 0
GND
NoConn ~ 8600 10100
NoConn ~ 9300 9900
Text Label 13825 7475 0    60   ~ 0
GND
NoConn ~ 34200 11550
NoConn ~ 9650 10775
NoConn ~ 9650 10525
Text Label 9975 10325 0    60   ~ 0
PDI_D
Text Label 9550 9950 1    60   ~ 0
PDI_C
$Comp
L ATXMEGA128A1U-A IC1
U 1 1 5AC0F16A
P 28600 12150
F 0 "IC1" H 27550 14450 50  0000 L BNN
F 1 "ATXMEGA128A1U-A" H 29150 9800 50  0000 L BNN
F 2 "tqfp:LQFP-100_14x14mm_Pitch0.5mm" H 28600 12150 50  0000 C CIN
F 3 "" H 28600 12150 50  0000 C CNN
	1    28600 12150
	1    0    0    -1  
$EndComp
$Comp
L C C39
U 1 1 5AC15554
P 30775 9975
F 0 "C39" H 30800 10075 50  0000 L CNN
F 1 "100nF" H 30800 9875 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 30813 9825 50  0000 C CNN
F 3 "" H 30775 9975 50  0000 C CNN
	1    30775 9975
	0    -1   -1   0   
$EndComp
$Comp
L C C38
U 1 1 5AC15849
P 30775 9000
F 0 "C38" H 30800 9100 50  0000 L CNN
F 1 "100nF" H 30800 8900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 30813 8850 50  0000 C CNN
F 3 "" H 30775 9000 50  0000 C CNN
	1    30775 9000
	0    1    1    0   
$EndComp
$Comp
L C C37
U 1 1 5AC15959
P 28975 9375
F 0 "C37" H 29000 9475 50  0000 L CNN
F 1 "100nF" H 29000 9275 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 29013 9225 50  0000 C CNN
F 3 "" H 28975 9375 50  0000 C CNN
	1    28975 9375
	1    0    0    -1  
$EndComp
$Comp
L C C36
U 1 1 5AC15B5B
P 28850 9100
F 0 "C36" H 28875 9200 50  0000 L CNN
F 1 "100nF" H 28875 9000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28888 8950 50  0000 C CNN
F 3 "" H 28850 9100 50  0000 C CNN
	1    28850 9100
	1    0    0    -1  
$EndComp
$Comp
L C C35
U 1 1 5AC15C67
P 28725 9375
F 0 "C35" H 28750 9475 50  0000 L CNN
F 1 "100nF" H 28750 9275 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28763 9225 50  0000 C CNN
F 3 "" H 28725 9375 50  0000 C CNN
	1    28725 9375
	1    0    0    -1  
$EndComp
$Comp
L C C34
U 1 1 5AC15D7C
P 28600 9100
F 0 "C34" H 28625 9200 50  0000 L CNN
F 1 "100nF" H 28625 9000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28638 8950 50  0000 C CNN
F 3 "" H 28600 9100 50  0000 C CNN
	1    28600 9100
	1    0    0    -1  
$EndComp
$Comp
L C C33
U 1 1 5AC15E90
P 28475 9375
F 0 "C33" H 28500 9475 50  0000 L CNN
F 1 "100nF" H 28500 9275 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28513 9225 50  0000 C CNN
F 3 "" H 28475 9375 50  0000 C CNN
	1    28475 9375
	1    0    0    -1  
$EndComp
$Comp
L C C32
U 1 1 5AC15FC5
P 28350 9100
F 0 "C32" H 28375 9200 50  0000 L CNN
F 1 "100nF" H 28375 9000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28388 8950 50  0000 C CNN
F 3 "" H 28350 9100 50  0000 C CNN
	1    28350 9100
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AC178F7
P 28225 9375
F 0 "C3" H 28250 9475 50  0000 L CNN
F 1 "100nF" H 28250 9275 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28263 9225 50  0000 C CNN
F 3 "" H 28225 9375 50  0000 C CNN
	1    28225 9375
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AC17A8A
P 28100 9100
F 0 "C2" H 28125 9200 50  0000 L CNN
F 1 "100nF" H 28125 9000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 28138 8950 50  0000 C CNN
F 3 "" H 28100 9100 50  0000 C CNN
	1    28100 9100
	1    0    0    -1  
$EndComp
Text Label 28850 8950 1    60   ~ 0
GND
Text Label 28600 8950 1    60   ~ 0
GND
Text Label 28350 8950 1    60   ~ 0
GND
Text Label 28100 8950 1    60   ~ 0
GND
Text Label 28975 8950 1    60   ~ 0
GND
Text Label 28725 8950 1    60   ~ 0
GND
Text Label 28475 8950 1    60   ~ 0
GND
Text Label 28225 8950 1    60   ~ 0
GND
Text Label 29000 14550 3    60   ~ 0
GND
Text Label 28900 14550 3    60   ~ 0
GND
Text Label 28800 14550 3    60   ~ 0
GND
Text Label 28700 14550 3    60   ~ 0
GND
Text Label 28600 14550 3    60   ~ 0
GND
Text Label 28500 14550 3    60   ~ 0
GND
Text Label 28400 14550 3    60   ~ 0
GND
Text Label 28300 14550 3    60   ~ 0
GND
Text Label 28200 14550 3    60   ~ 0
GND
Text Label 28100 14550 3    60   ~ 0
GND
Text Label 27400 10050 2    60   ~ 0
PDI_C
Text Label 27400 10150 2    60   ~ 0
PDI_D
$Comp
L CP1-RESCUE-xmobile C41
U 1 1 5AC1E9E1
P 30825 9675
F 0 "C41" H 30875 9775 50  0000 L CNN
F 1 "10mk" H 30825 9575 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.3" H 30825 9675 60  0001 C CNN
F 3 "" H 30825 9675 60  0000 C CNN
	1    30825 9675
	0    -1   -1   0   
$EndComp
Text Label 31025 9975 3    60   ~ 0
GND
$Comp
L CP1-RESCUE-xmobile C40
U 1 1 5AC202D3
P 30825 9300
F 0 "C40" H 30875 9400 50  0000 L CNN
F 1 "10mk" H 30825 9200 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.3" H 30825 9300 60  0001 C CNN
F 3 "" H 30825 9300 60  0000 C CNN
	1    30825 9300
	0    -1   -1   0   
$EndComp
Text Label 31025 9000 1    60   ~ 0
GND
Text Label 27600 9575 2    60   ~ 0
3.3V
$Comp
L CONN_01X08 P10
U 1 1 5AC3E445
P 26850 13900
F 0 "P10" H 26850 14350 50  0000 C CNN
F 1 "CONN_01X08" V 26950 13900 50  0000 C CNN
F 2 "Connectors_JAE:JAE_LY20-08P-2T_2x04x2.00mm_Straight" H 26850 13900 50  0000 C CNN
F 3 "" H 26850 13900 50  0000 C CNN
	1    26850 13900
	-1   0    0    1   
$EndComp
NoConn ~ 27400 10550
NoConn ~ 27400 10650
NoConn ~ 27400 10750
NoConn ~ 27400 10850
NoConn ~ 27400 11000
NoConn ~ 27400 11100
NoConn ~ 27400 11200
NoConn ~ 27400 11300
NoConn ~ 27400 11400
NoConn ~ 27400 11500
NoConn ~ 27400 11600
NoConn ~ 27400 11700
NoConn ~ 27400 11850
NoConn ~ 27400 11950
NoConn ~ 27400 12050
NoConn ~ 27400 12150
NoConn ~ 27400 12250
NoConn ~ 27400 12350
NoConn ~ 27400 12450
NoConn ~ 27400 12550
NoConn ~ 27400 12700
NoConn ~ 27400 12800
NoConn ~ 27400 12900
NoConn ~ 27400 13000
NoConn ~ 27400 13100
NoConn ~ 27400 13200
NoConn ~ 27400 13300
NoConn ~ 27400 13400
NoConn ~ 29800 14150
NoConn ~ 29800 14050
NoConn ~ 29800 13950
NoConn ~ 29800 13850
NoConn ~ 29800 13550
NoConn ~ 29800 11300
NoConn ~ 29800 11400
NoConn ~ 29800 11500
NoConn ~ 29800 11600
$Comp
L INDUCTOR L1
U 1 1 5AC20B29
P 29300 9225
F 0 "L1" V 29250 9225 40  0000 C CNN
F 1 "120m" V 29400 9225 40  0001 C CNN
F 2 "Inductors:Inductor_1212" H 29300 9225 60  0001 C CNN
F 3 "" H 29300 9225 60  0000 C CNN
F 4 "ferrite bead" V 29425 9200 60  0000 C CNN "details"
	1    29300 9225
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 5AC483E4
P 30625 8925
F 0 "#FLG02" H 30625 9020 50  0001 C CNN
F 1 "PWR_FLAG" H 30625 9105 50  0000 C CNN
F 2 "" H 30625 8925 50  0000 C CNN
F 3 "" H 30625 8925 50  0000 C CNN
	1    30625 8925
	1    0    0    -1  
$EndComp
NoConn ~ 29800 10650
NoConn ~ 29800 10550
NoConn ~ 29800 11100
NoConn ~ 29800 11200
NoConn ~ 29800 10750
NoConn ~ 29800 10900
NoConn ~ 29800 11000
NoConn ~ 27400 10300
NoConn ~ 27400 10400
NoConn ~ 29800 12050
$Comp
L CY62158EV30LL-45BVXI U?
U 1 1 5C118522
P 4250 5200
F 0 "U?" H 4250 5000 60  0000 C CNN
F 1 "CY62158EV30LL-45BVXI" H 4250 5150 39  0000 C CNN
F 2 "" H 4300 4250 60  0000 C CNN
F 3 "" H 4300 4250 60  0000 C CNN
	1    4250 5200
	1    0    0    -1  
$EndComp
$Comp
L XMega128A1U_BGA100 U?
U 1 1 5C19D697
P 9300 5600
F 0 "U?" H 9300 4450 60  0000 C CNN
F 1 "XMega128A1U_BGA100" H 9350 4900 60  0000 C CNN
F 2 "" H 9700 7400 60  0000 C CNN
F 3 "" H 9700 7400 60  0000 C CNN
	1    9300 5600
	1    0    0    -1  
$EndComp
Text Label 7800 6300 2    60   ~ 0
A0
Text Label 7800 6400 2    60   ~ 0
A1
Text Label 7800 6500 2    60   ~ 0
A2
Text Label 7800 6600 2    60   ~ 0
A3
Text Label 7800 6700 2    60   ~ 0
A4
Text Label 7800 6800 2    60   ~ 0
A5
Text Label 7800 6900 2    60   ~ 0
A6
Text Label 7800 7000 2    60   ~ 0
A7
Text Label 7800 3600 2    60   ~ 0
A8
Text Label 7800 3700 2    60   ~ 0
A9
Text Label 7800 3900 2    60   ~ 0
A11
Text Label 7800 4000 2    60   ~ 0
A12
Text Label 7800 4100 2    60   ~ 0
A13
Text Label 7800 4200 2    60   ~ 0
A14
Text Label 7800 4300 2    60   ~ 0
A15
Text Label 7800 4900 2    60   ~ 0
A16
Text Label 7800 5000 2    60   ~ 0
A17
Text Label 7800 5100 2    60   ~ 0
A18
Text Label 7800 5200 2    60   ~ 0
A19
Text Label 3400 5650 2    60   ~ 0
A18
Text Label 3400 5550 2    60   ~ 0
A19
Text Label 7800 5400 2    60   ~ 0
D0
Text Label 7800 5500 2    60   ~ 0
D1
Text Label 7800 5600 2    60   ~ 0
D2
Text Label 7800 5700 2    60   ~ 0
D3
Text Label 7800 5800 2    60   ~ 0
D4
Text Label 7800 5900 2    60   ~ 0
D5
Text Label 7800 6000 2    60   ~ 0
D6
Text Label 7800 6100 2    60   ~ 0
D7
Text Label 7800 4500 2    60   ~ 0
WE
Text Label 4150 4350 1    60   ~ 0
WE
Text Label 4050 4350 1    60   ~ 0
OE
Text Label 7800 4600 2    60   ~ 0
OE
Text Label 7800 3800 2    60   ~ 0
A10
Text Label 8400 8500 3    60   ~ 0
GND
Text Label 8500 8500 3    60   ~ 0
GND
Text Label 8600 8500 3    60   ~ 0
GND
Text Label 8700 8500 3    60   ~ 0
GND
Text Label 8800 8500 3    60   ~ 0
GND
Text Label 8900 8500 3    60   ~ 0
GND
Text Label 9000 8500 3    60   ~ 0
GND
Text Label 9100 8500 3    60   ~ 0
GND
Text Label 9200 8500 3    60   ~ 0
GND
Text Label 9300 8500 3    60   ~ 0
GND
Text Label 9600 8500 3    60   ~ 0
PDI_C
Text Label 9500 8500 3    60   ~ 0
PDI_D
Text Label 3850 4350 1    60   ~ 0
+3.3V_filtered
Text Label 3950 4350 1    60   ~ 0
+3.3V_filtered
Text Label 4550 4350 1    60   ~ 0
GND
Text Label 4450 4350 1    60   ~ 0
GND
Text Label 4250 4350 1    60   ~ 0
CE1
Text Label 4350 4350 1    60   ~ 0
CE2
Text Label 7800 4700 2    60   ~ 0
CE1
Text Label 7800 4800 2    60   ~ 0
CE2
$Sheet
S 12225 3475 650  1725
U 5A9F76AF
F0 "xmobile_GSM" 60
F1 "xmobile_sim_holder.sch" 60
F2 "STATUS" O R 12875 3550 60 
F3 "POWER_KEY" O R 12875 3675 60 
F4 "UART_RTS" I R 12875 3800 60 
F5 "UART_DTR" I R 12875 3925 60 
F6 "UART_RI" I R 12875 4050 60 
F7 "UART_DCD" I R 12875 4175 60 
F8 "UART_CTS" I R 12875 4300 60 
F9 "UART_RXD" I R 12875 4425 60 
F10 "UART_TXD" I R 12875 4550 60 
F11 "MICP" I R 12875 4675 60 
F12 "MICN" I R 12875 4800 60 
F13 "SPKP" O R 12875 4925 60 
F14 "SPKN" O R 12875 5050 60 
$EndSheet
Text Label 12875 3800 0    60   ~ 0
GSM_RTS
Text Label 10800 8100 0    60   ~ 0
GSM_RTS
Text Label 12875 3925 0    60   ~ 0
GSM_DTR
Text Label 10800 3900 0    60   ~ 0
GSM_DTR
Text Label 12875 4050 0    60   ~ 0
GSM_RI
Text Label 10800 3700 0    60   ~ 0
GSM_RI
Text Label 12875 4175 0    60   ~ 0
GSM_DCD
Text Label 10800 3800 0    60   ~ 0
GSM_DCD
Text Label 12875 4300 0    60   ~ 0
GSM_CTS
Text Label 10800 4000 0    60   ~ 0
GSM_CTS
Text Label 12875 4425 0    60   ~ 0
GSM_RXD
Text Label 10800 7800 0    60   ~ 0
GSM_RXD
Text Label 12875 4550 0    60   ~ 0
GSM_TXD
Text Label 10800 7900 0    60   ~ 0
GSM_TXD
Text Label 12875 3675 0    60   ~ 0
GSM_PWRKEY
Text Label 10800 3600 0    60   ~ 0
GSM_PWRKEY
Entry Wire Line
	7500 5300 7600 5400
Entry Wire Line
	7500 5400 7600 5500
Entry Wire Line
	7500 5500 7600 5600
Entry Wire Line
	7500 5600 7600 5700
Entry Wire Line
	7500 5700 7600 5800
Entry Wire Line
	7500 5800 7600 5900
Entry Wire Line
	7500 5900 7600 6000
Entry Wire Line
	7500 6000 7600 6100
Entry Wire Line
	7500 6200 7600 6300
Entry Wire Line
	7500 6300 7600 6400
Entry Wire Line
	7500 6400 7600 6500
Entry Wire Line
	7500 6500 7600 6600
Entry Wire Line
	7500 6600 7600 6700
Entry Wire Line
	7500 6700 7600 6800
Entry Wire Line
	7500 6800 7600 6900
Entry Wire Line
	7500 6900 7600 7000
Entry Wire Line
	7500 5100 7600 5200
Entry Wire Line
	7500 5000 7600 5100
Entry Wire Line
	7500 4900 7600 5000
Entry Wire Line
	7500 4800 7600 4900
Entry Wire Line
	7500 4200 7600 4300
Entry Wire Line
	7500 4100 7600 4200
Entry Wire Line
	7500 4000 7600 4100
Entry Wire Line
	7500 3900 7600 4000
Entry Wire Line
	7500 3800 7600 3900
Entry Wire Line
	7500 3700 7600 3800
Entry Wire Line
	7500 3600 7600 3700
Entry Wire Line
	7500 3500 7600 3600
Text Label 7500 6150 2    60   ~ 0
ADDR_SRAM
Text Label 7500 4800 2    60   ~ 0
ADDR_SRAM
Text Label 7500 3500 2    60   ~ 0
ADDR_SRAM
Entry Wire Line
	5225 4800 5325 4900
Entry Wire Line
	5225 4900 5325 5000
Entry Wire Line
	5225 5000 5325 5100
Entry Wire Line
	5225 5100 5325 5200
Entry Wire Line
	5225 5200 5325 5300
Entry Wire Line
	5225 5300 5325 5400
Entry Wire Line
	5225 5400 5325 5500
Entry Wire Line
	5225 5500 5325 5600
Entry Wire Line
	5225 5600 5325 5700
Entry Wire Line
	4650 6250 4750 6350
Entry Wire Line
	4550 6250 4650 6350
Entry Wire Line
	4450 6250 4550 6350
Entry Wire Line
	4350 6250 4450 6350
Entry Wire Line
	4250 6250 4350 6350
Entry Wire Line
	4150 6250 4250 6350
Entry Wire Line
	4050 6250 4150 6350
Entry Wire Line
	3950 6250 4050 6350
Entry Wire Line
	3850 6250 3950 6350
Entry Wire Line
	3100 5450 3200 5550
Entry Wire Line
	3100 5550 3200 5650
Entry Wire Line
	3100 5350 3200 5450
Entry Wire Line
	3100 5250 3200 5350
Entry Wire Line
	3100 5150 3200 5250
Entry Wire Line
	3100 5050 3200 5150
Entry Wire Line
	3100 4950 3200 5050
Entry Wire Line
	3100 4850 3200 4950
Entry Wire Line
	3100 4750 3200 4850
Entry Wire Line
	3100 4650 3200 4750
Text Label 7500 5300 2    60   ~ 0
DATA_SRAM
Text Label 5325 5700 0    60   ~ 0
ADDR_SRAM
Text Label 4750 6350 0    60   ~ 0
ADDR_SRAM
Text Label 3100 5450 2    60   ~ 0
ADDR_SRAM
Text Label 3100 4650 2    60   ~ 0
DATA_SRAM
Text Label 5075 4800 0    60   ~ 0
A0
Text Label 5075 4900 0    60   ~ 0
A1
Text Label 5075 5000 0    60   ~ 0
A2
Text Label 5075 5100 0    60   ~ 0
A3
Text Label 5075 5200 0    60   ~ 0
A4
Text Label 5075 5300 0    60   ~ 0
A5
Text Label 5075 5400 0    60   ~ 0
A6
Text Label 5075 5500 0    60   ~ 0
A7
Text Label 5075 5600 0    60   ~ 0
A8
Text Label 3850 6000 3    60   ~ 0
A17
Text Label 3950 6000 3    60   ~ 0
A16
Text Label 4050 6000 3    60   ~ 0
A15
Text Label 4150 6000 3    60   ~ 0
A14
Text Label 4250 6000 3    60   ~ 0
A13
Text Label 4350 6000 3    60   ~ 0
A12
Text Label 4450 6000 3    60   ~ 0
A11
Text Label 4550 6000 3    60   ~ 0
A10
Text Label 4650 6000 3    60   ~ 0
A9
Text Label 3400 4750 2    60   ~ 0
D7
Text Label 3400 4850 2    60   ~ 0
D6
Text Label 3400 4950 2    60   ~ 0
D5
Text Label 3400 5050 2    60   ~ 0
D4
Text Label 3400 5150 2    60   ~ 0
D3
Text Label 3400 5250 2    60   ~ 0
D2
Text Label 3400 5350 2    60   ~ 0
D1
Text Label 3400 5450 2    60   ~ 0
D0
Text GLabel 825  10675 0    60   Input ~ 0
3.3V
Text Label 825  10675 0    60   ~ 0
3.3V
Wire Wire Line
	9300 10100 9775 10100
Wire Wire Line
	9550 9950 9550 10525
Connection ~ 9550 10100
Wire Wire Line
	28350 9575 28350 9250
Wire Wire Line
	28975 9225 28975 8950
Wire Wire Line
	28725 9225 28725 8950
Wire Wire Line
	28475 9225 28475 8950
Wire Wire Line
	28225 9225 28225 8950
Wire Wire Line
	31025 9300 31025 9000
Wire Wire Line
	31025 9000 30925 9000
Wire Wire Line
	31025 9675 31025 9975
Wire Wire Line
	31025 9975 30925 9975
Connection ~ 30625 9000
Connection ~ 30625 9975
Connection ~ 30625 9300
Connection ~ 30625 9675
Wire Wire Line
	28100 9575 28100 9250
Wire Wire Line
	28225 9575 28225 9525
Connection ~ 28225 9575
Connection ~ 28350 9575
Wire Wire Line
	28475 9575 28475 9525
Connection ~ 28475 9575
Wire Wire Line
	28725 9575 28725 9525
Connection ~ 28725 9575
Wire Wire Line
	28975 9575 28975 9525
Connection ~ 28975 9575
Wire Wire Line
	28850 9575 28850 9250
Connection ~ 28850 9575
Wire Wire Line
	28900 9575 28900 9750
Connection ~ 28900 9575
Wire Wire Line
	28800 9575 28800 9750
Connection ~ 28800 9575
Wire Wire Line
	28700 9575 28700 9750
Connection ~ 28700 9575
Wire Wire Line
	28600 9250 28600 9750
Connection ~ 28600 9575
Wire Wire Line
	28400 9575 28400 9750
Connection ~ 28400 9575
Wire Wire Line
	28500 9575 28500 9750
Connection ~ 28500 9575
Wire Wire Line
	28300 9575 28300 9750
Connection ~ 28300 9575
Wire Wire Line
	28200 9575 28200 9750
Connection ~ 28200 9575
Connection ~ 28100 9575
Wire Wire Line
	27050 13550 27400 13550
Wire Wire Line
	27400 13650 27050 13650
Wire Wire Line
	27050 13750 27400 13750
Wire Wire Line
	27400 13850 27050 13850
Wire Wire Line
	27400 13950 27050 13950
Wire Wire Line
	27050 14050 27400 14050
Wire Wire Line
	27400 14150 27050 14150
Wire Wire Line
	27050 14250 27400 14250
Wire Wire Line
	27600 9575 29300 9575
Wire Wire Line
	29300 9575 29300 9525
Wire Wire Line
	29050 9750 29050 9625
Wire Wire Line
	29150 9750 29150 9675
Wire Wire Line
	30625 8925 30625 9975
Wire Wire Line
	29050 9625 30100 9625
Wire Wire Line
	30100 9625 30100 9300
Wire Wire Line
	30100 9300 30625 9300
Wire Wire Line
	29150 9675 30625 9675
Wire Wire Line
	29300 8925 30625 8925
Wire Wire Line
	9750 10525 9750 10325
Wire Wire Line
	9750 10325 9975 10325
Wire Wire Line
	12875 4675 14025 4675
Wire Wire Line
	14025 4800 12875 4800
Wire Wire Line
	12875 4925 14025 4925
Wire Wire Line
	14025 5050 12875 5050
Wire Wire Line
	7800 5400 7600 5400
Wire Wire Line
	7800 5500 7600 5500
Wire Wire Line
	7800 5600 7600 5600
Wire Wire Line
	7800 5700 7600 5700
Wire Wire Line
	7800 5800 7600 5800
Wire Wire Line
	7800 5900 7600 5900
Wire Wire Line
	7800 6000 7600 6000
Wire Wire Line
	7800 6100 7600 6100
Wire Bus Line
	7500 5300 7500 6000
Wire Wire Line
	7800 6300 7600 6300
Wire Wire Line
	7800 6400 7600 6400
Wire Wire Line
	7800 6500 7600 6500
Wire Wire Line
	7800 6700 7600 6700
Wire Wire Line
	7800 6600 7600 6600
Wire Wire Line
	7800 6800 7600 6800
Wire Wire Line
	7800 6900 7600 6900
Wire Wire Line
	7800 7000 7600 7000
Wire Bus Line
	7500 6150 7500 6900
Wire Wire Line
	7800 5200 7600 5200
Wire Wire Line
	7800 5100 7600 5100
Wire Wire Line
	7800 5000 7600 5000
Wire Wire Line
	7800 4900 7600 4900
Wire Wire Line
	7800 4300 7600 4300
Wire Wire Line
	7800 4200 7600 4200
Wire Wire Line
	7800 4100 7600 4100
Wire Wire Line
	7800 4000 7600 4000
Wire Wire Line
	7800 3900 7600 3900
Wire Wire Line
	7800 3800 7600 3800
Wire Wire Line
	7800 3700 7600 3700
Wire Wire Line
	7800 3600 7600 3600
Wire Bus Line
	7500 4800 7500 5125
Wire Bus Line
	7500 3500 7500 4200
Wire Wire Line
	3400 5450 3200 5450
Wire Wire Line
	3400 5350 3200 5350
Wire Wire Line
	3400 5250 3200 5250
Wire Wire Line
	3200 5150 3400 5150
Wire Wire Line
	3400 5050 3200 5050
Wire Wire Line
	3400 4950 3200 4950
Wire Wire Line
	3400 4850 3200 4850
Wire Wire Line
	3400 4750 3200 4750
Wire Wire Line
	5050 4800 5225 4800
Wire Wire Line
	5050 4900 5225 4900
Wire Wire Line
	5050 5000 5225 5000
Wire Wire Line
	5050 5100 5225 5100
Wire Wire Line
	5050 5200 5225 5200
Wire Wire Line
	5050 5300 5225 5300
Wire Wire Line
	5050 5400 5225 5400
Wire Wire Line
	5050 5500 5225 5500
Wire Wire Line
	5050 5600 5225 5600
Wire Wire Line
	4650 6000 4650 6250
Wire Wire Line
	4550 6000 4550 6250
Wire Wire Line
	4450 6000 4450 6250
Wire Wire Line
	4350 6000 4350 6250
Wire Wire Line
	4250 6000 4250 6250
Wire Wire Line
	4150 6000 4150 6250
Wire Wire Line
	4050 6000 4050 6250
Wire Wire Line
	3950 6000 3950 6250
Wire Wire Line
	3850 6000 3850 6250
Wire Wire Line
	3400 5550 3200 5550
Wire Wire Line
	3400 5650 3200 5650
Wire Bus Line
	5325 4900 5325 5700
Wire Bus Line
	3950 6350 4750 6350
Wire Bus Line
	3100 5350 3100 4650
Wire Bus Line
	3100 5550 3100 5450
Wire Wire Line
	8600 3100 9500 3100
Connection ~ 8700 3100
Connection ~ 8800 3100
Connection ~ 8900 3100
Connection ~ 9000 3100
Connection ~ 9100 3100
Connection ~ 9200 3100
Connection ~ 9300 3100
Connection ~ 9400 3100
Text Label 9500 3100 0    60   ~ 0
3.3V
$EndSCHEMATC
