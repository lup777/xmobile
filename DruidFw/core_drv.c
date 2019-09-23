// core_drv.c
#include <avr/io.h>

#include "global.h"

#include "core_drv.h"

void WriteEBI(uint32_t Address, uint8_t Val);
uint8_t ReadEBI(uint32_t Address);
void sram_read_enable(void);
void sram_write_enable(void);

inline void clk_init(void) {
    //OSC_PLLCTRL = 0x16;  // 2 * 16 = 32MGz
  OSC_CTRL = OSC_RC32MEN_bm;

  while( !( OSC_STATUS & OSC_RC32MRDY_bm ) ); // waite while 32MGXz osc ready

  CCP = CCP_IOREG_gc;
  CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
}

void int_init(void) {
  //clear_global_interrupt();

    CCP = CCP_IOREG_gc;

    PMIC.CTRL = (PMIC_LOLVLEN_bm | PMIC_HILVLEN_bm);

    PMIC.INTPRI = 0x00;
}

inline void sram_write_enable(void) {
  /*PORTH.OUTSET =
    //| PIN1_bm   // OE
    //| PIN0_bm  // WE
    ;*/
  PORTH.OUTCLR =
    //| PIN1_bm   // OE
    PIN0_bm  // WE
    ;
}

inline void sram_read_enable(void) {
  PORTH.OUTSET =
    //| PIN1_bm   // OE
    PIN0_bm  // WE
    ;
  PORTH.OUTCLR =
    PIN1_bm   // OE
    //PIN0_bm  // WE
    ;
}

void sram_init(void) {
  /* EXAMPLE
    PORTCFG.EBIOUT = PORTCFG_EBIADROUT_PF_gc | PORTCFG_EBICSOUT_PH_gc;
    EBI.CTRL = EBI_SRMODE_NOALE_gc | EBI_IFMODE_4PORT_gc;

    EBI.CS2.BASEADDR = 0x0000;
    EBI.CS2.CTRLB = EBI_CS_SRWS_1CLK_gc;   // 62,5ns R/W cycle @ 32MHz - you have to meet your SRAM's speed specification
    EBI.CS2.CTRLA = EBI_CS_ASPACE_128KB_gc | EBI_CS_MODE_SRAM_gc;

  */

  // NEED PORT CONFIGURATION
  // PK - A0 .. A7
  // PF - A8 .. A15
  // PH - A16.. A19, CE1, CE2, OE, WE
  // PJ - D0 .. D7
  // PH2 - CE1
  // PH3 - CE2
  //   PH0 - WE
  //   PH1 - OE (RE)
  //   PH2 - CE1
  //   PH3 - CE2
  //   PH4 .. PH7 - A16 .. A19
  PORTK.DIRSET = 0xFF; // A0 .. A7
  PORTF.DIRSET = 0xFF; // A8 .. A15
  PORTH.DIRSET = 0xFF; // A16.. A19, CE1, CE2, OE, WE
  PORTJ.DIRCLR = 0xFF; // D0 .. D7

  PORTH.OUTSET =
    PIN4_bm | PIN6_bm | PIN6_bm | PIN7_bm // A16 - A19
    | PIN2_bm   // CE1
    | PIN3_bm   // CE2
    //| PIN1_bm   // OE
    //| PIN0_bm  // WE
    ;

  PORTH.OUTCLR =
    //PIN4_bm | PIN6_bm | PIN6_bm | PIN7_bm // (in real A18..A21) A16 - A19 
    //PIN2_bm   // CE1 (in real A16)
    //| PIN3_bm // CE2 (in real A17)
    PIN1_bm   // OE
    | PIN0_bm   // WE
    ;
  
  

  PORTCFG.EBIOUT = PORTCFG_EBIADROUT_PF_gc | PORTCFG_EBICSOUT_PH_gc;

  EBI.CTRL = EBI_SRMODE_NOALE_gc // do not use address multiplexing
    | EBI_IFMODE_4PORT_gc;       // 4 port mode. This mode reserved
                                 // IFMODE[1:0] = 1 0 (bits)

  //EBI.CS0.CTRLA = EBI_CS_MODE_DISABLED_gc;
  //EBI.CS1.CTRLA = EBI_CS_MODE_DISABLED_gc;
  //EBI.CS2.CTRLA = EBI_CS_MODE_DISABLED_gc;

  
  EBI.CS3.CTRLA = EBI_CS_ASPACE_128KB_gc  // size of the block above the base address
    | EBI_CS_MODE_SRAM_gc;              // SRAM mode

  EBI.CS3.CTRLB = EBI_CS_SRWS_1CLK_gc;  // One Clk per 2 cycles wait state

  // lowest a]ddress in the address space enabled by chip select
  //EBI.CS3.BASEADDR = (uint16_t)((0x100000 >> 8) & 0xFFFFF);
  //EBI.CS3.BASEADDR = (uint16_t)0x100000;
  EBI.CS3.BASEADDR = (uint16_t)0x0;
}


// 128KB: 0x0000 - 0x1F400
#ifndef DISABLE_LOGS
#if 0
bool check_sram(void) {
  volatile uint32_t ptr_start = 0x4000;
  volatile uint32_t ptr_end = 0x100000; // 128KB
  volatile uint32_t ptr;
  
  volatile uint8_t data = 0xAA;
  uint8_t step = 0xFF;
  bool result = true;;
  volatile uint8_t value;

  for (;ptr_start + step < ptr_end; ptr_start += step) {

    sram_write_enable();
    for (data = 0, ptr = ptr_start;
	 ptr <= ptr_start + step;
	 ptr++, data++) {
      WriteEBI(ptr, data);
      //_log("write: 0x%02X", data);
    }

    sram_read_enable();
    for (data = 0, ptr = ptr_start;
	 ptr <= ptr_start + step;
	 ptr++, data ++) {
      value = ReadEBI(ptr);
      //_log("read: 0x%02X", value);
      if (value != data) {
	uint16_t tmpl = (uint16_t)(ptr & 0xFFFF);
	uint16_t tmph = (uint16_t)(ptr >> 16) & 0xFFFF;
	_log("addr: 0x%04X%04X failed", tmph, tmpl);
	result = false;
	break;
      }
    }

    if (result == false) break;

    if (result == true) {
      uint16_t tmpl = (uint16_t)(ptr & 0xFFFF);
      uint16_t tmph = (uint16_t)(ptr >> 16) & 0xFFFF;

      _log("addr: 0x%04X%04X success", tmph, tmpl);
    }
  }

  _log("test done.");
  return true;
}
#else
bool check_sram(void) {
  volatile uint16_t ptr_start = 0x4000;
  volatile uint16_t ptr_end = 0xFFFF; // 128KB
  volatile uint16_t ptr;
  
  volatile uint8_t data = 0xAA;
  uint8_t step = 0xFF;
  bool result = true;;
  volatile uint8_t value;

  for (;ptr_start + step < ptr_end; ptr_start += step) {

    sram_write_enable();
    for (data = 0, ptr = ptr_start;
	 ptr <= ptr_start + step;
	 ptr++, data++) {
      //WriteEBI(ptr, data);
      *((uint16_t*)ptr) = data;
      //_log("write: 0x%02X", data);
    }

    sram_read_enable();
    for (data = 0, ptr = ptr_start;
	 ptr <= ptr_start + step;
	 ptr++, data ++) {
      //value = ReadEBI(ptr);
      value = *((uint16_t*)ptr);
      //_log("read: 0x%02X", value);
      if (value != data) {
	uint16_t tmpl = (uint16_t)(ptr & 0xFFFF);
	uint16_t tmph = 0;
	_log("addr: 0x%04X%04X failed", tmph, tmpl);
	result = false;
	break;
      }
    }

    if (result == false) break;

    if (result == true) {
      uint16_t tmpl = (uint16_t)(ptr & 0xFFFF);
      uint16_t tmph = 0;

      _log("addr: 0x%04X%04X success", tmph, tmpl);
    }
  }

  _log("test done.");
  return true;
}
#endif
#endif

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
