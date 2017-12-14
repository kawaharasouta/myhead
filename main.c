#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//!define to use getopt.h
#define _GNU_SOURCE
#include<getopt.h>

#define DEFAULT_N_LINES 10

static struct options[] = {
	{"lines", required_argument, NULL, 'n'},
	{"helop", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[]){
	int opt;
	long nlines = DEFAULT_N_LINES;

	while((otp = getopt_long(argc, argv, "n:", longopts, NULL)) != -1){
		switch(opt){
		case 'n':
			nlines = atol(optarg);
			break;
		case 'h':
			fprintf(stdout, "Usage: %s [in lines] [FILE ...]\n", argv[0]);
			exit(0);
		case '?':
			fprintf(stderr, "Usage: %s [in lines] [FILE ...]\n", argv[0]);
			exit(1)
		}
	}

	/**
	 *if then, 
	 */
	if(optind == argc){
		do_head(stdin, nlines);
	}
	else {
		int i;

		for(i = optind, i < argc, i++){
			FILE *f;

			f = fopen(argv[i], "r");
			if(!f){
				perror(argv[i]);
				exit(1)
			}
			do_head(f, nlines);
			fclose(f);
		}
	}
	exit(0);
}

static void do_head(FILE *f, long nlines){
	int c;

	if(nlines <= 0) return;
	while((c = getc(f)) != EOF){
		if(putchar(c) < 0) exit(1);
		if(c == '\n')	{
			nlines--;
			if(nlines == 0) return;
		}
	}
}
