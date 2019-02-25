EESchema Schematic File Version 4
LIBS:xmobile-cache
EELAYER 26 0
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
L xmobile-rescue:R-RESCUE-xmobile R1
U 1 1 5967CB22
P 10025 10100
F 0 "R1" V 10105 10100 40  0000 C CNN
F 1 "10k" V 10032 10101 40  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9955 10100 30  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/348/sfr-e-1507454.pdf" V 10200 9750 30  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/ROHM-Semiconductor/SFR01MZPJ103?qs=sGAEpiMZZMtlubZbdhIBIIR71ikvQRXLchgEzboAcvI%3d" V 10025 10100 60  0001 C CNN "example"
F 5 "0402 In" V 9950 10100 30  0000 C CNN "case"
	1    10025 10100
	0    -1   -1   0   
$EndComp
Text Label 10275 10100 0    60   ~ 0
3.3V
$Comp
L xmobile-rescue:CONN_8 P1
U 1 1 5974D7B3
P 13525 7500
F 0 "P1" V 13475 7500 60  0000 C CNN
F 1 "CONN_8" V 13575 7500 60  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x08_P1.00mm_Vertical" V 13700 7450 60  0001 C CNN
F 3 "" H 13525 7500 60  0001 C CNN
F 4 "EPD display connector" V 13700 7500 60  0001 C CNN "description"
F 5 "pin header 1.00mm" V 13675 7500 30  0000 C CNN "case"
	1    13525 7500
	1    0    0    -1  
$EndComp
Text Label 13175 7150 2    60   ~ 0
EPD_BUSY
Text Label 13175 7250 2    60   ~ 0
EPD_RST
Text Label 13175 7350 2    60   ~ 0
EPD_DC
Text Label 13175 7450 2    60   ~ 0
EPD_CS
Text Label 13175 7550 2    60   ~ 0
EPD_CLK
Text Label 13175 7650 2    60   ~ 0
EPD_DIN
Text Label 13175 7750 2    60   ~ 0
GND
Text Label 13175 7850 2    60   ~ 0
3.3V
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
S 14400 9675 500  150 
U 5A9FCB78
F0 "xmega_power" 60
F1 "xmega_power.sch" 60
$EndSheet
Text Label 9725 10700 0    60   ~ 0
3.3V
Text Label 9325 10700 2    60   ~ 0
GND
Text Label 8700 10100 2    60   ~ 0
GND
$Sheet
S 13125 6125 525  400 
U 5AA512DD
F0 "xmobile_keyboard" 60
F1 "xmobile_keyboard.sch" 60
F2 "SDA" B L 13125 6200 60 
F3 "SCL" B L 13125 6300 60 
F4 "INT" O L 13125 6400 60 
$EndSheet
Text Label 10100 10350 0    60   ~ 0
PDI_D
Text Label 9550 9950 1    60   ~ 0
PDI_C
$Comp
L xmobile-rescue:CY62158EV30LL-45BVXI U1
U 1 1 5C118522
P 4250 5200
F 0 "U1" H 4250 5000 60  0000 C CNN
F 1 "CY62158EV30LL-45BVXI" H 4250 5150 39  0000 C CNN
F 2 "druid:48-ball_VFBGA_6x8x1mm_BV48BZ48" H 4475 3925 60  0001 C CNN
F 3 "https://www.cypress.com/file/43811/download" H 4300 4250 60  0001 C CNN
F 4 "VFBGA48" H 4250 5250 30  0000 C CNN "case"
F 5 "https://eu.mouser.com/ProductDetail/Cypress-Semiconductor/CY62158EV30LL-45BVXI?qs=sGAEpiMZZMt9mBA6nIyysIT6PXTPi%2fj%2fhnigerrGPws%3d" H 4250 5200 60  0001 C CNN "example"
	1    4250 5200
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:XMega128A1U_BGA100 U2
U 1 1 5C19D697
P 9300 5600
F 0 "U2" H 9300 4450 60  0000 C CNN
F 1 "XMega128A1U_BGA100" H 9350 4900 60  0000 C CNN
F 2 "druid:BGA100_9x9x1.2_pitch-0.80mm" H 9400 5150 60  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/268/Atmel-8385-8-and-16-bit-AVR-Microcontroller-ATxmeg-1315775.pdf" H 9700 7400 60  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Microchip-Technology-Atmel/ATXMEGA128A1U-C7U?qs=sGAEpiMZZMvqv2n3s2xjsVQIURldyCCHGWx9j4DhqLs%3d" H 9300 5600 60  0001 C CNN "example"
F 5 "VFBGA100" H 9300 5600 30  0000 C CNN "case"
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
3.3V
Text Label 3950 4350 1    60   ~ 0
3.3V
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
Text GLabel 14675 9425 0    60   Input ~ 0
3.3V
Text Label 14675 9425 0    60   ~ 0
3.3V
Wire Wire Line
	9300 10100 9550 10100
Connection ~ 9550 10100
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
	3100 5550 3100 5450
Wire Wire Line
	8600 3100 8700 3100
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
Text Label 10800 6600 0    60   ~ 0
EPD_RST
Text Label 10800 6700 0    60   ~ 0
EPD_BUSY
Text Label 10800 6900 0    60   ~ 0
EPD_DC
Text Label 10800 4800 0    60   ~ 0
EPD_CS
Text Label 10800 4700 0    60   ~ 0
EPD_CLK
Text Label 10800 4500 0    60   ~ 0
EPD_DIN
Text Label 13125 6200 2    60   ~ 0
KBD_SDA
Text Label 13125 6300 2    60   ~ 0
KBD_SCL
Text Label 13125 6400 2    60   ~ 0
KBD_INT
Text Label 10800 5100 0    60   ~ 0
KBD_SCL
Text Label 10800 5200 0    60   ~ 0
KBD_SDA
Text Label 10800 7000 0    60   ~ 0
KBD_INT
$Comp
L xmobile-rescue:TEST_1P J3
U 1 1 5C4B9CCC
P 11625 4600
F 0 "J3" H 11625 4870 50  0000 C CNN
F 1 "TEST_DISP_DATA_OUT" H 11625 4800 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_1.0x1.0mm_Drill0.5mm" H 11650 4925 50  0001 C CNN
F 3 "" H 11825 4600 50  0001 C CNN
F 4 "1 pad" H 11625 4925 30  0000 C CNN "case"
	1    11625 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	10800 4600 11625 4600
Text GLabel 15500 9425 0    60   Input ~ 0
GND
Text Label 15500 9425 0    60   ~ 0
GND
Text Label 12875 3550 0    60   ~ 0
GSM_STATUS
Text Label 10800 6800 0    60   ~ 0
GSM_STATUS
$Comp
L xmobile-rescue:Micro_SD_Card J1
U 1 1 5C4DB2CD
P 4075 8950
F 0 "J1" H 3425 9550 50  0000 C CNN
F 1 "Micro_SD_Card" H 4725 9550 50  0000 R CNN
F 2 "Connector_Card:microSD_HC_Wuerth_693072010801" H 4075 8200 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/445/693072010801-336093.pdf" H 4075 8950 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/Wurth-Electronics/693072010801?qs=sGAEpiMZZMuJakaoiLiBpiVYNV8REXtFk03jtifiNMv8wsb977CC%2fA%3d%3d" H 4075 8950 50  0001 C CNN "example"
F 5 "8 pin microSD" H 4350 8925 30  0000 C CNN "case"
	1    4075 8950
	1    0    0    -1  
$EndComp
Text Label 3175 9150 2    60   ~ 0
GND
Text Label 3175 9050 2    60   ~ 0
microSD_SCLK
Text Label 1650 8950 2    60   ~ 0
3.3V
Text Label 3175 9250 2    60   ~ 0
microSD_DO
Text Label 3175 8750 2    60   ~ 0
microSD_CS
Text Label 3175 8850 2    60   ~ 0
microSD_DI
NoConn ~ 3175 8650
NoConn ~ 3175 9350
Text Label 1825 9250 3    60   ~ 0
GND
$Comp
L xmobile-rescue:C C2
U 1 1 5C4DFD85
P 1825 9100
F 0 "C2" H 1850 9200 50  0000 L CNN
F 1 "0.1u" H 1950 9100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2025 9375 50  0001 C CNN
F 3 "https://eu.mouser.com/datasheet/2/40/cx5r-776519.pdf" H 1825 9100 50  0001 C CNN
F 4 "https://eu.mouser.com/ProductDetail/AVX/04026D104KAT4A?qs=sGAEpiMZZMs0AnBnWHyRQPg4iYkCw7IMED%2f4kpqgf7w%3d" H 1825 9100 60  0001 C CNN "example"
F 5 "0402 In" H 1950 9025 30  0000 C CNN "case"
	1    1825 9100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 8950 1825 8950
NoConn ~ 4875 9550
Text Label 10800 4100 0    60   ~ 0
microSD_DI
Text Label 10800 4300 0    60   ~ 0
microSD_SCLK
Text Label 10800 4200 0    60   ~ 0
microSD_DO
Text Label 10800 8000 0    60   ~ 0
microSD_CS
$Comp
L xmobile-rescue:SW_PUSH SW1
U 1 1 5C505516
P 9000 10100
F 0 "SW1" H 9150 10210 50  0000 C CNN
F 1 "SW_PUSH" H 9000 10020 50  0000 C CNN
F 2 "druid:button_4pin_7,5x5" H 8975 9950 50  0001 C CNN
F 3 "" H 9000 10100 50  0000 C CNN
F 4 "https://ru.aliexpress.com/item/100-4-4-0-8/32909011951.html?spm=a2g0v.search0604.3.313.5a9f5cbe3LNMTR&ws_ab_test=searchweb0_0%2Csearchweb201602_6_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_10301_537_536_10902_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=b432da11-c10a-421f-96ee-7905deee8d06&algo_expid=b432da11-c10a-421f-96ee-7905deee8d06-45" H 9000 10100 60  0001 C CNN "example"
F 5 "4x4x0,8" H 9000 10100 30  0000 C CNN "case"
	1    9000 10100
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:TEST_2P J2
U 1 1 5C561693
P 7300 7200
F 0 "J2" H 7300 7260 50  0000 C CNN
F 1 "TEST_VIBRO" H 7300 7130 50  0000 C CNN
F 2 "TestPoint:TestPoint_2Pads_Pitch2.54mm_Drill0.8mm" H 6925 7025 50  0001 C CNN
F 3 "" H 7300 7200 50  0001 C CNN
F 4 "2 pads" H 7300 7075 30  0000 C CNN "case"
	1    7300 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 7200 7800 7200
Text Label 7100 7200 2    60   ~ 0
GND
$Comp
L xmobile-rescue:TEST-RESCUE-xmobile W2
U 1 1 5C6C0FE4
P 9900 10350
F 0 "W2" H 9900 10410 50  0000 C CNN
F 1 "TEST_PDI" H 9900 10280 50  0000 C CNN
F 2 "TestPoint:TestPoint_2Pads_Pitch2.54mm_Drill0.8mm" H 10150 10200 50  0001 C CNN
F 3 "" H 9900 10350 50  0000 C CNN
F 4 "2 pads" H 9900 10225 30  0000 C CNN "case"
	1    9900 10350
	1    0    0    -1  
$EndComp
$Comp
L xmobile-rescue:TEST-RESCUE-xmobile W1
U 1 1 5C6C18FA
P 9525 10700
F 0 "W1" H 9525 10760 50  0000 C CNN
F 1 "TEST_XMEGA_PWR" H 9525 10630 50  0000 C CNN
F 2 "TestPoint:TestPoint_2Pads_Pitch2.54mm_Drill0.8mm" H 9625 10550 50  0001 C CNN
F 3 "" H 9525 10700 50  0000 C CNN
F 4 "2 pads" H 9525 10575 30  0000 C CNN "case"
	1    9525 10700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 10350 9700 10350
Wire Wire Line
	9550 9950 9550 10100
NoConn ~ 10800 4900
NoConn ~ 10800 5000
NoConn ~ 10800 5400
NoConn ~ 10800 5500
NoConn ~ 10800 5600
NoConn ~ 10800 5700
NoConn ~ 10800 5800
NoConn ~ 10800 5900
NoConn ~ 10800 6000
NoConn ~ 10800 6100
NoConn ~ 10800 6300
NoConn ~ 10800 6400
NoConn ~ 10800 6500
NoConn ~ 10800 7400
NoConn ~ 10800 7500
NoConn ~ 10800 7600
NoConn ~ 10800 7700
NoConn ~ 7800 7300
NoConn ~ 7800 7400
NoConn ~ 7800 7500
NoConn ~ 7800 7700
NoConn ~ 7800 7800
Wire Wire Line
	9550 10100 9775 10100
Wire Wire Line
	9550 10100 9550 10350
Wire Wire Line
	8700 3100 8800 3100
Wire Wire Line
	8800 3100 8900 3100
Wire Wire Line
	8900 3100 9000 3100
Wire Wire Line
	9000 3100 9100 3100
Wire Wire Line
	9100 3100 9200 3100
Wire Wire Line
	9200 3100 9300 3100
Wire Wire Line
	9300 3100 9400 3100
Wire Wire Line
	9400 3100 9500 3100
$Comp
L xmobile-rescue:PWR_FLAG #FLG0101
U 1 1 5C7368D2
P 14975 9425
F 0 "#FLG0101" H 14975 9520 50  0001 C CNN
F 1 "PWR_FLAG" H 14975 9649 50  0000 C CNN
F 2 "" H 14975 9425 50  0000 C CNN
F 3 "" H 14975 9425 50  0000 C CNN
	1    14975 9425
	1    0    0    -1  
$EndComp
Wire Wire Line
	14675 9425 14975 9425
Wire Bus Line
	7500 4800 7500 5125
Wire Bus Line
	7500 5300 7500 6000
Wire Bus Line
	7500 3500 7500 4200
Wire Bus Line
	3100 4650 3100 5350
Wire Bus Line
	7500 6150 7500 6900
Wire Bus Line
	5325 4900 5325 5700
Wire Bus Line
	3950 6350 4750 6350
Connection ~ 1825 8950
Wire Wire Line
	1825 8950 3175 8950
$EndSCHEMATC
