// sander.h

#pragma once

#ifdef SANDER


#  include <stdio.h>
#  define _log printf


void raw_log(char* path, u8 len);

#endif
