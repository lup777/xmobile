// core_drv.c
#include "global.h"

#include "core_drv.h"

inline void run_on_32mgz(void) {
    //OSC_PLLCTRL = 0x16;  // 2 * 16 = 32MGz
  OSC_CTRL = OSC_RC32MEN_bm;

  while( !( OSC_STATUS & OSC_RC32MRDY_bm ) ); // waite while 32MGXz osc ready

  CCP = CCP_IOREG_gc;
  CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
}

void interrupts_init(void) {
  //clear_global_interrupt();

    CCP = CCP_IOREG_gc;

    PMIC.CTRL = (PMIC_LOLVLEN_bm | PMIC_HILVLEN_bm);

    PMIC.INTPRI = 0x00;
}
