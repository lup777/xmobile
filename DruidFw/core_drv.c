// core_drv.c
#include <avr/io.h>

#include "global.h"

#include "core_drv.h"

void WriteEBI(uint32_t Address, uint8_t Val);
uint8_t ReadEBI(uint32_t Address);


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

  PORTK.DIRSET = 0xFF;
  PORTF.DIRSET = 0xFF;
  PORTH.DIRSET = 0xFF;
  PORTH.OUTSET = 0xFF & (~PIN2_bm);

  PORTH.OUTCLR = PIN2_bm; // CE1
  //PORTH.OUTSET = PIN3_bm; // CE2

  PORTCFG.EBIOUT = PORTCFG_EBIADROUT_PF_gc | PORTCFG_EBICSOUT_PH_gc;

  EBI.CTRL = EBI_SRMODE_NOALE_gc // do not use address multiplexing
    | EBI_IFMODE_4PORT_gc;       // 4 port mode. This mode reserved
                                 // IFMODE[1:0] = 1 0 (bits)

  EBI.CS0.CTRLA = EBI_CS_MODE_DISABLED_gc;
  EBI.CS1.CTRLA = EBI_CS_MODE_DISABLED_gc;
  EBI.CS2.CTRLA = EBI_CS_MODE_DISABLED_gc;

  
  EBI.CS3.CTRLA = EBI_CS_ASPACE_1MB_gc  // size of the block above the base address
    | EBI_CS_MODE_SRAM_gc;              // SRAM mode

  EBI.CS3.CTRLB = EBI_CS_SRWS_0CLK_gc;  // One Clk per 2 cycles wait state

  EBI.CS3.BASEADDR = (uint16_t)((0x100000 >> 8) & 0xFFFFF); // lowest address in the address space enabled by chip select
}

#ifndef DISABLE_LOGS
bool check_sram(void) {
  //_log("start check_sram");
  /*uint32_t i  = 0;
  uint8_t data = 0xAA;

  uint8_t result;
  
  for (i = 0x4000; i < 0x400F; i++) {
    WriteEBI(i, data);
    _log("write: 0x%02X", data);
  }

  WriteEBI((uint32_t)0x401F, 0xAB);
  
  for (i = 0x4000; i < 0x400F; i ++) {
    result = ReadEBI(i);
    _log("read: 0x%02X", result);
    //if (*(uint8_t*)ptr != 0xAA)
    //if (result != data)
    //return false;
    }*/

  volatile int32_t ptr = 0x4000;
  volatile int32_t ptr_end = 0x10400F;
  
  uint8_t data = 0xAA;
  uint8_t result;
  
  for (ptr = 0x104000; ptr < ptr_end; ptr++, data++) {
    //*(uint8_t*)ptr = data;
    WriteEBI(ptr, data);
    _log("write: 0x%02X", data);
  }

  for (ptr = 0x104000; ptr < ptr_end + 1; ptr++) {
    //result = *(uint8_t*)ptr;
    result = ReadEBI(ptr);
    _log("read: 0x%02X", result);
  }

  //CHECK(0);
  return true;
}
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
