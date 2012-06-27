/*
 * Copyright (c) 2008, Daniel Bolgheroni. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY DANIEL BOLGHERONI ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DANIEL BOLGHERONI OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * DESCRIPTION:
 * Convert data generated by spice3f5 with the print command to a clean
 * file that can be used by gnuplot.
 * 
 * Only tested with outputs generated by spice3f5.
 */

#include <stdio.h>

#define NAME "cirplot"
#define VERSION "0.2"
#define WARNING "Only tested with spice3f5!\n"

#define FILENAME_MAX_WIDTH 32

int main(int argc, char *argv[]) {

  FILE *spice3, *gnuplot;
  char test;
  char spice3_file[FILENAME_MAX_WIDTH];
  char gnuplot_file[FILENAME_MAX_WIDTH];

  if(argc <= 2) {
    printf("missing argument! usage: " NAME " [input_file] [output_file]\n");
    exit(1);
  }

  if(!(spice3 = fopen(argv[1], "r"))) {
    printf("can't open file: %s\n", argv[1]);
    exit(1);
  }

  if(!(gnuplot = fopen(argv[2], "w"))) {
    printf("can't write file: %s\n", argv[2]);
    exit(1);
  }

  while(!feof(spice3)) {
    fscanf(spice3, "%c", &test);

    if(isdigit(test)) {
      while(strncmp(&test, "\n", 1)) {
	fprintf(gnuplot, "%c", test);
	fscanf(spice3, "%c", &test);
      }

      fprintf(gnuplot, "%c", '\n');
    }
  
    if(!isdigit(test))
      while(strncmp(&test, "\n", 1))
	fscanf(spice3, "%c", &test);
  }

  fclose(spice3);
  fclose(gnuplot);

  exit(1);
}
