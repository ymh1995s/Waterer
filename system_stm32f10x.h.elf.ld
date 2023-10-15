
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\Users\Linux\Downloads\8주차\Project\(USART)자가통신")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
STARTUP("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM\crt0_STM32x.o")
INPUT("C:\Users\Linux\Downloads\8주차\Project\(USART)자가통신\system_stm32f10x.h.elf")
EXTERN( __io_putchar )
EXTERN( _write )
GROUP(
"STM32x_io_putchar_thumb.a"
"std_sbrk_thumb.lib"
"smallprintf_thumb.a"
"STM32F10x_thumb.lib"
"libc.a"
"libm.a"

)
INCLUDE "C:\Users\Linux\Downloads\8주차\Project\(USART)자가통신\STM32F103_32K_20K_FLASH.ld"
OUTPUT("C:\Users\Linux\Downloads\8주차\Project\(USART)자가통신\system_stm32f10x.h.elf")
