#include "../include/timer.h"

void setPitInterval(size_t frequency) {
	// Since what we send to the PIT is a divisor, generate a
	// number which, when divided by the pit's original frequency
	// generates the required freq.
	size_t divisor;
	if (frequency == 0) {
		divisor = 1;
	} else {
		divisor = BASE_FREQUENCY / frequency;
	}
	
	/* 
	 * Setting PIT's command
	 * Data: 00 11 010 0
	 * 0 Binary Mode: 16b binary
	 * 010 Mode: 2 (rate generator)
	 * 11 Access mode: low byte - high byte
	 */
	outb(0x43, 0x34);
	
	// Set PIT frequency
	byte low = (byte)(divisor & 0xFF);
	byte high = (byte)(divisor >> 8 & 0xFF);
	
	outb(0x40, low);
	outb(0x40, high);
	
	return;
}
