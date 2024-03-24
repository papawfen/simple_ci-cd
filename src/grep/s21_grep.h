#ifndef SRC_S21_GREP_H_  //  SRC_S21_GREP_H_
#define SRC_S21_GREP_H_  //  SRC_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

void grep_flags(int argc, char *argv[]);
int grep_main_flags(char *argv[], FILE *file, regex_t *regex, 
                    int printline, int flagfiles, int i, int regflag);

#endif // SRC_S21_GREP_H_
