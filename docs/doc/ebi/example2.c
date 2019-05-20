#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <QA/uart/uart.h>
#include <Q/osc/osc.h>

#include <Q/color_lcd/SSD1289.h>
#include <Q/color_lcd/SSD1289_types.h>

#ifndef F_USB
#include <avr/iox128a1u.h>
#endif

#include "cfg/Qssd1289_cfg.h"

#include <Q/Qcopy/memcopy.c>

volatile bool draw_ready = false;

void init_ebi(void) __attribute__ ((naked)) \
    __attribute__ ((section (".init0")));

void init_ebi(void)
{
    PORTCFG.EBIOUT = 0b00000001; //0b00000000
    EBI.CTRL = EBI_SRMODE_NOALE_gc | EBI_IFMODE_4PORT_gc;

    EBI.CS0.CTRLA = EBI_CS_MODE_DISABLED_gc;
    EBI.CS1.CTRLA = EBI_CS_MODE_DISABLED_gc;
    EBI.CS2.CTRLA = EBI_CS_MODE_DISABLED_gc;
    PORTH.OUT = 0xFF;
    PORTH.DIR = 0xFF;
    PORTF.DIR = 0xFF;
    PORTK.DIR = 0xFF;
    
    EBI.CS3.CTRLA = EBI_CS_ASPACE_512KB_gc | EBI_CS_MODE_SRAM_gc;
    EBI.CS3.CTRLB = EBI_CS_SRWS_1CLK_gc;
    
    EBI.CS3.BASEADDR = 0;
}


typedef __int24 int24_t;

uint8_t ReadEBI(uint32_t Address)
{
 uint8_t Seg = (uint8_t)(Address >> 16);
 uint16_t Off = (uint16_t)Address;
 uint8_t Value;
 __asm__ __volatile__
 (
   "in __tmp_reg__,%3"          "\n\t"  /* store RAMPZ */
   "out %3,%1"                  "\n\t"  /* load new RAMPZ */
   "ld %0,%a2"                  "\n\t"  /* load Ret */
   "out %3,__tmp_reg__"         "\n\t"  /* restore RAMPZ */
   :  "=&r" (Value)                     /* %0 */
   :  "r"   (Seg),                      /* %1 */
      "z"   (Off),                      /* a2 */
      "I"   _SFR_IO_ADDR(RAMPZ)         /* %3 */
  );

  return( Value );
}

void WriteEBI(uint32_t Address, uint8_t Val)
{
  uint8_t Seg = (uint8_t)(Address >>16);
  uint16_t Off = (uint16_t)Address;
 __asm__ __volatile__
 (
   "in __tmp_reg__,%3"          "\n\t"  /* store RAMPZ */
   "out %3,%1"                  "\n\t"  /* load new RAMPZ */
   "st %a2,%0"                  "\n\t"  /* write byte */
   "out %3,__tmp_reg__"         "\n\t"  /* restore RAMPZ */
   :
   :  "r"  (Val),                       /* %0 */
      "r"  (Seg),                       /* %1 */
      "z"  (Off),                       /* %2 (Z) */
      "I"  _SFR_IO_ADDR(RAMPZ)          /* %3 */
 );
}

void writeSampleImage(__int24 adr)
{
	__int24 adr2 = adr + (320L * 240L);
	for(uint16_t y = 0; y < 320; y++)
	{
		for(uint16_t x = 0; x < 240; x++)
		{
			WriteEBI(adr, y);
			WriteEBI(adr2, x);
			adr++;
			adr2++;
		}
	}
}


void setup_transfer(void)
{
	EVSYS.CH0MUX                     = EVSYS_CHMUX_TCC0_CCD_gc; //Route Timer through eventcontroller for clearing timer interrupt
	EVSYS.CH0CTRL                    = 0;

	DMA.CTRL                         = DMA_PRIMODE_CH0123_gc | DMA_ENABLE_bm; //Enable in Priority mode 0->1->2->3
  
  DMA.CH0.CTRLB                    = DMA_CH_TRNINTLVL_OFF_gc | DMA_CH_TRNIF_bm;                   

  DMA.CH0.ADDRCTRL                 = DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc;

  DMA.CH0.TRIGSRC                  = DMA_CH_TRIGSRC_EVSYS_CH0_gc;  //Set eventcontroller as trigger.
  
  DMA.CH0.DESTADDR0                = (uint8_t) (uint16_t) &SSD_HPORT.OUT; //Set target.
  DMA.CH0.DESTADDR1                = (uint8_t) ((uint16_t) &SSD_HPORT.OUT >> 8) & 0xFF;
  DMA.CH0.DESTADDR2                = 0;

  DMA.CH1.CTRLB                    = DMA_CH_TRNINTLVL_OFF_gc   | DMA_CH_TRNIF_bm;
  DMA.CH1.ADDRCTRL                 = DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc;
  DMA.CH1.TRIGSRC                  = DMA_CH_TRIGSRC_EVSYS_CH0_gc;
  
  DMA.CH1.DESTADDR0                = (uint8_t) (uint16_t) (&SSD_LPORT.OUT) & 0xFF;
  DMA.CH1.DESTADDR1                = (uint8_t) ((uint16_t) (&SSD_LPORT.OUT) >> 8) & 0xFF;
  DMA.CH1.DESTADDR2                = 0;
	
	//Set up one shot
  DMA.CH2.CTRLB                    = DMA_CH_TRNINTLVL_LO_gc   | DMA_CH_TRNIF_bm;
  DMA.CH2.ADDRCTRL                 = DMA_CH_SRCRELOAD_NONE_gc | DMA_CH_SRCDIR_FIXED_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc;
  DMA.CH2.TRIGSRC                  = DMA_CH_TRIGSRC_EVSYS_CH0_gc;


	//Set static byte so it will remain in memory as DMA source
	static uint8_t cc_skip = 2;
  DMA.CH2.SRCADDR0                = (uint8_t) (uint16_t) (&cc_skip) & 0xFF;
  DMA.CH2.SRCADDR1                = (uint8_t) ((uint16_t) (&cc_skip) >> 8) & 0xFF;
  DMA.CH2.SRCADDR2                = 0;
	
	DMA.CH2.DESTADDR0                = (uint8_t) (uint16_t) (&TCC2.LCNT) & 0xFF;
  DMA.CH2.DESTADDR1                = (uint8_t) ((uint16_t) (&TCC2.LCNT) >> 8) & 0xFF;
  DMA.CH2.DESTADDR2                = 0;
	
	TCC2.CTRLE = TC2_BYTEM_SPLITMODE_gc;

	TCC2.LCMPD = 2;
	TCC2.LCMPC = 100;
	TCC2.LCMPB = 100;
	TCC2.LCMPA = 100;
	TCC2.LPER = 1;             //The resets every 17 cycles
	
	TCC2.CTRLA = TC_CLKSEL_DIV1_gc; //Disable the timer for now
	TCC2.CTRLB = 0; //Singleslope mode
// 	TCC2.INTCTRLB = TC2_LCMPDINTLVL_LO_gc | TC2_LCMPBINTLVL_LO_gc;  //Interrupts disable possible because we use event system.
	
}

void transfer_data2(__int24 src, uint8_t width, uint16_t height)
{
	//The memory need to be in two dived area high/lowbyte
	//E.g. uint8_t picture[2][height][width] where 2 means highbyte/lowbyte.

	//All 3 DMA Channels Are Triggered by a TC2 Timer.
	//Two of them are for the data for the port outputs.
	//One of them is copy a value into the counter register(TCx2.CNT) of the timer.
	//This is generating a single pulse after each dma transfer.
	//The priority is very important. First the two data channels need
	//to make there work. Then the timer DMA may start for generating
	//the pulse.
	//When the PWM pin (RW) is connected to the Timer(CCx). It will be set to high
	//and the data lines will be connected to the display memory.
	//After the DMA transfer is complete it will be CLR one more time.
	//That means one more pulse is generated then we need. This will
	//overdraw a pixel outside the range.
	//For compensate this we could set the transfer count for the
	//timer dma to size - 1. But since we want to be able to transfer
	//more then 2^16 words (64KB * 2). We need to use repeat count
	//which is an multiplier for the count.
	//Example: If we want to transfer 6(lines)*8(cols) = 48 words
	//we need to transfer 47 Timer pulses. But 47 is a prime. So its
	//impossible to find an other multiplier than 1 for the transfer.
	//In this example its fine because 47 < 2^16. But there will be
	//cases where no transfer is possible. And it would take lot of time.
	//So we starting a dummy transfer without having the timer connected to
	//the WR pin.
	
	//Setup the Timer DMA
	DMA.CH2.CTRLA                    = DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm;
	DMA.CH2.TRIGSRC                  = DMA_CH_TRIGSRC_OFF_gc; //Trigger source software trigger only, because it would trigger it self.
	DMA.CH2.TRFCNT                   = height;
	DMA.CH2.REPCNT                   = width;
	DMA.CH2.CTRLA                   |= DMA_CH_ENABLE_bm;

	//##### Dummy trigger ######
// 	SET_CS; //Deselect the Display
// 	
	DMA.CH2.CTRLA |= DMA_CH_TRFREQ_bm; //Trigger a transfer
	//There is no way to check if a burst is completed so we just need to wait
	//before connecting the CCx to the wr pin.

	
	

	draw_ready = false;
	DMA.CH0.CTRLA                    = DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm;
	DMA.CH1.CTRLA                    = DMA_CH_BURSTLEN_1BYTE_gc | DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm;
	
	//As the PORT OUT registers are not sequential in the memory we need to cheat.
	//Every channel is allways transfering two bytes to the same PORT (BURST SIZE 2).
	//This allows to skip one byte while every transfer
	DMA.CH0.SRCADDR0                 = (uint8_t) (uint16_t) src;
	DMA.CH0.SRCADDR1                 = (uint8_t)  *(((uint8_t *)&(src)) + 1);
	DMA.CH0.SRCADDR2                 = (uint8_t)  *(((uint8_t *)&(src)) + 2);
	DMA.CH0.TRFCNT                   = height;
	DMA.CH0.REPCNT                   = width;
	
	
// 	printf("source[3] = %d\n", (uint8_t)  *(((uint8_t *)&(src)) + 2));
	//We dont need the byte as *(src-1) but the source byte *(src) is needed.
	//But the first byte will be skipped. So this is fine.
	src += width * height;
	DMA.CH1.SRCADDR0                 = (uint8_t) (uint16_t) src;
	DMA.CH1.SRCADDR1                 = (uint8_t)  *(((uint8_t *)&(src)) + 1);
	DMA.CH1.SRCADDR2                 = (uint8_t)  *(((uint8_t *)&(src)) + 2);
	DMA.CH1.TRFCNT                   = height;
	DMA.CH1.REPCNT                   = width;
	
	

	TCC2.CTRLB = TC2_LCMPDEN_bm; //The first transfer should now be done and the timer counted down
	//So we can now connect the CCx to the wr pin and enable the data DMAs.
	DMA.CH2.TRIGSRC                  = DMA_CH_TRIGSRC_EVSYS_CH0_gc;
	DMA.CH0.CTRLA                   |= DMA_CH_ENABLE_bm;
	DMA.CH1.CTRLA                   |= DMA_CH_ENABLE_bm;
	
	//Trigger first transfer.
	DMA.CH0.CTRLA |= DMA_CH_TRFREQ_bm;
	DMA.CH1.CTRLA |= DMA_CH_TRFREQ_bm;
	DMA.CH2.CTRLA |= DMA_CH_TRFREQ_bm;
	
}

void draw_pictuer(__int24 src, uint8_t posx, uint16_t posy, uint8_t width, uint16_t height)
{
	SET_AREA(posx, posx, posx + width - 1, posy + height - 1);
	transfer_data2(src, 240, 320);
}

void wait_for_ready(void)
{
	while(!draw_ready)
		;
}



int main(void)
{
	CCPWrite(&(MCU.MCUCR), MCU_JTAGD_bm);

	int2x_USB48(9);
	uart_init(&USARTD0, 1000000, USART_RXCINTLVL_OFF_gc, NULL, true, true); //Connect printf to uart.
	
	HW_INIT();
	SW_INIT();
	
	setup_transfer();
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
	printf("start\n");
	

	writeSampleImage(0x10000);

	DRAW_RECT(0,0,239,319,RED);
	for(uint16_t i = 0; i < 1000; i++)
	{
		draw_pictuer(0x10000, 0, 0, 240, 320);
		printf("i: %d\n", i);
		while(!draw_ready)
			;
	}
	
	while(true)
		;

	return 0;
}

ISR(DMA_CH2_vect)
{

	DMA.INTFLAGS = DMA_CH2TRNIF_bm; //Clear DMA IF nesseary!

	TCC2.CTRLB = 0; //Disconnect WR Pin from timer

	draw_ready = true; //Set ready
}


