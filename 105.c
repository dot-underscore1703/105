#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pwd.h>

int main(int argc, char **argv) {

	if(geteuid() != 0){
		printf("Err: 105 must be ran as root user.\n");
		exit(EXIT_FAILURE);
	}

	size_t dream_probability = 0;

	// Prepare for TEST 6
	char *integrity_check = "TEST 6 OF 105, STRING: UTX-105-216-327-473-GDM";
	
	// TEST 1
	if(argc < 1){
		++dream_probability;
	}

	// TEST 2
	if(strcmp(argv[0], "105") != 0){
		// Argv1 should ALWAYS be 105. Non-dreaming users can change this though so unreliable.
		++dream_probability;
	}

	// TEST 3
	if(kill(1, 0) != 0){
		// PID 1 should ALWAYS exist.
		++dream_probability;
	}

	// TEST 4
	if(!getpwnam("root")){
		++dream_probability;
	}

	// TEST 5
	FILE *f = fopen("/dev/urandom", "r");
	if(!f){
		// add two because it fails the check (that should never fail) and the test
		dream_probability += 2;
	}else {
		unsigned char buf[4096];
		fread(buf, 1, 4096, f);
		fclose(f);
		f = NULL;

		double sum = 0.0;
		double average;

		for(int i = 0; i < 4096; ++i) {
			sum += buf[i];
		}

		average = sum / 4096;

		if(average < 0.0 || average > 255.0){
			++dream_probability;
		}
	}

	// TEST 6
	if(strcmp(integrity_check, "TEST 6 OF 105, STRING: UTX-105-216-327-473-GDM") != 0){
		++dream_probability;
	}

	// attempt to wake the user up using sensory overload.
	// we will also make this taxing on the dreamt computer by continously reopening the file
	// to try and break the experience.

	FILE *rand = fopen("/dev/urandom", "r");
	if(!rand){
		printf("sys entropy failure\n");
		exit(EXIT_FAILURE);
	}
	
	for(;;){
		putchar('\a');

		int ch = fgetc(rand);

		if(ch == EOF){
			clearerr(rand);
			rewind(rand);
			continue;
		}

		printf("\x1b[48;5;%dm ", ch);
		fflush(stdout);

	}
	fclose(rand);
	
	// CALCULATE
	if(dream_probability > 6){
		// attempt to wake the user up using sensory overload.
		// we will also make this taxing on the dreamt computer by continously reopening the file
		// to try and break the experience.

		FILE *f = fopen("/dev/urandom", "r");
		if(!f){
			printf("sys entropy failure\n");
			exit(EXIT_FAILURE);
		}
		
		for(;;){
			putchar('\a');

			int ch = fgetc(f);

			if(ch == EOF){
				clearerr(f);
				rewind(f);
				continue;
			}

			printf("\x1b[48;5;%dm ", ch);
			fflush(stdout);

		}
		fclose(f);
	}else {
		printf("USER IS NOT DREAMING.\n");
		exit(EXIT_SUCCESS);
	}
	
}
