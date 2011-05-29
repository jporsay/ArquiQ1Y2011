#ifndef _command_
#define _command_

#include "defs.h"
#include "shell.h"
#include "video.h"
#include "math.h"
#include "cpu.h"

int echo_cmd(int argc, char *argv[]);
int restart_cmd(int argc, char *argv[]);
int clear_cmd(int argc, char *argv[]);
int help_cmd(int argc, char *argv[]);
int setPit_cmd(int argc, char *argv[]);
int resetPit_cmd(int argc, char *argv[]);
int countDown_cmd(int argc, char *argv[]);
int CPUspeed_cmd(int argc, char *argv[]);
int random_cmd(int argc, char *argv[]);
int test_cmd(int argc, char *argv[]);
int asd_cmd(int argc, char *argv[]);

#endif
