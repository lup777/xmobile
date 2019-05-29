// core_drv.h

#pragma once

void int_init(void);
void clk_init(void);
void sram_init(void);

#ifndef DISABLE_LOGS
bool check_sram(void);
#endif
