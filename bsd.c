/*
 * bsd.c - BSD specific definitions and uptime() function.  Should work on
 * all the major BSDs.
 *
 * We subtract the boottime from the current time to get the uptime.  We
 * make a sysctl() to get the boot time.
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
 */

#include <time.h>
#include <sys/sysctl.h>
#include <sys/time.h>

double uptime( void ) {
	int mib[2];
	size_t size;
	struct timeval boottime;
	time_t now = 0;
	time_t uptime = 0;

	mib[0] = CTL_KERN;
	mib[1] = KERN_BOOTTIME;
	size = sizeof( boottime );

	if( sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 && boottime.tv_sec != 0 ) {
		(void)time( &now );
		uptime = now - boottime.tv_sec;

		if( uptime > 60 ) {
			uptime += 30;
		}
	}

	return( uptime );
}
