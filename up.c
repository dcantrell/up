/*
 * up.c - by: David L. Cantrell Jr. (david@burdell.org)
 * Displays the uptime of system, accounting for the following:
 *
 *   o Decades
 *   o Years
 *   o Weeks
 *   o Days
 *   o Hours
 *   o Minutes
 *
 * It can also display uptime in the standard for quick comparison
 * with other systems ( XX day(s), HH:MM )
 *
 * Copyright (C) 2002, David L. Cantrell Jr., Atlanta, GA, USA.
 * All rights reserved.
 * 
 * Redistribution and use of this software, with or without modification,
 * is permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of this software must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Last modified 03-Jul-2002 by David L. Cantrell Jr.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "up.h"

/*
 * disp_version() - Display program version information.
 */
void disp_version( void ) {
	printf( "up v" );
	printf( VERSION );
	printf( " -- by: David L. Cantrell Jr. <david@burdell.org>\n" );
}

/*
 * disp_usage() - Display program usage screen.
 */
void disp_usage( char *pn ) {
	printf( "A robust uptime display utility for many operating systems.\n\n" );
	printf( "Usage: %s [option]\n", pn );

	printf( "  --compare | -c   Display uptime in standard uptime format, for quick\n" );
	printf( "                   comparison with other systems.\n" );

	printf( "  --numbers | -n   Output numbers only (useful for scripts).  They\n" );
	printf( "                   are in this order:  decades, years, weeks, days,\n" );
	printf( "                   hours, minutes.  Zero values are no eliminated.\n" );

	printf( "  --noup    | -u   Displays the default uptime format without the\n" );
	printf( "                   preceeding 'up'.\n" );

	printf( "  --version | -V   Return the version number and author information.\n" );

	printf( "  --help    | -h   Display this screen.\n" );
}

/*
 * print_uptime() - Displays the system uptime in the desired format.
 */
void print_uptime( int otype ) {
	/*
 	 * This routine calculates the uptime and displays it in the
	 * desired format (the unique anal format of this program, or
	 * the traditional format of 'uptime'). I wrote this routine
	 * from scratch (most of the others are hacked from procps...
	 * well, except main) and it's not the most pretty thing in
	 * the world, but DAMMIT it works!
	 */

	int uptimes[6];
	int idx;
	double upseconds;
	char *upstrs[6];
	const char * const words[6] = {"decade", "year", "week", "day", "hour", "minute"};

	upseconds = uptime();

	if( otype == STD ) {
		/* calculate uptime values */
		uptimes[3] = (int) upseconds / (60*60*24);
		uptimes[4] = ((int) upseconds / (60*60)) % 24;
		uptimes[5] = ((int) upseconds / 60) % 60;
	} else {
		/* calculate the uptime values */
		uptimes[0] = (int) upseconds / (60*60*24*365*10);
		uptimes[1] = ((int) upseconds / (60*60*24*365)) % 10;
		uptimes[2] = ((int) upseconds / (60*60*24*7)) % 52;
		uptimes[3] = ((int) upseconds / (60*60*24)) % 7;
		uptimes[4] = ((int) upseconds / (60*60)) % 24;
		uptimes[5] = ((int) upseconds / 60) % 60;
	}

	/* fixup the plurals */
	for( idx=0; idx <= 5; idx++ ) {
		upstrs[idx] = ( uptimes[idx] != 1 ) ? "s" : "";
	}

	/* print the uptime string, eliminating zero values */
	if( otype == STD ) {
		printf( " uptime:  up %d %s%s, ", uptimes[3], words[3], upstrs[3] );
		printf( "%2d:%02d", uptimes[4], uptimes[5] );
	} else if( otype == NUM ) {
		for( idx=0; idx<=5; idx++ ) {
			printf( "%d ", uptimes[idx] );
		}
	} else {
		if( otype != NOUP ) {
			printf( " up" );
		}

		for( idx=0; idx<=5; idx++ ) {
			if( uptimes[idx] != 0 ) {
				printf( " %d %s%s", uptimes[idx], words[idx], upstrs[idx] );
			}
		}
	}
 
	printf("\n");
}

/* MAIN */
int main( int argc, char **argv ) {
	int ret = EXIT_SUCCESS;
	char *o = NULL;

	if( argc == 1 ) {
		print_uptime( -1 );
	} else if( argc == 2 ) {
		o = argv[1];

		if( strncmp(o, "--version", 9) == 0 || strncmp(o, "-V", 2) == 0 ) {
			disp_version();
		} else if( strncmp(o, "--help", 6) == 0 || strncmp(o, "-h", 2) == 0 ) {
			disp_version();
			disp_usage( argv[0] );
		} else if( strncmp(o, "--compare", 9) == 0 || strncmp(o, "-c", 2) == 0 ) {
			print_uptime( STD );
		} else if( strncmp(o, "--numbers", 9) == 0 || strncmp(o, "-n", 2) == 0 ) {
			print_uptime( NUM );
		} else if( strncmp(o, "--noup", 6) == 0 || strncmp(o, "-u", 2) == 0 ) {
			print_uptime( NOUP );
		} else {
			printf( "Invalid command line argument.  Type %s --help for help.\n", argv[0] );
			ret = EXIT_FAILURE;
		}
	}

	return( ret );
}
