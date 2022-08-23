#include "pit.h"
#include <cpu/interrupts/irq.h>
#include <video/vga_text.h>
#include <cpu/io.h>

static void pit_set_freq(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void pit_handler(struct regs *r)
{
    // do nothing for now lol
}

void pit_init(int hz)
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, pit_handler);
    pit_set_freq(hz);

    asm("sti"); // set the interrupt flag so the IRQs actually get called
    printf("PIT initialized with a freq of %dhz.\n", hz);
}