#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "defs.h"
#include "io.h"
#include "keyboard.h"
#include "kernel.h"

void int_08();
void int_09();
void int_80(int sysCallNumber, void ** args);

#endif

