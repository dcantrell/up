/*
 * utmpx.c - utmp method for getting the uptime.  Works on Linux, IRIX,
 * Solaris, and so on.
 *
 * We get the boot time from the utmp file and subtract that from the
 * current time to get the uptime.
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
#include <utmpx.h>

double uptime( void ) {
	double uptime = 0;
	struct utmpx *ent;
	struct utmpx boot_ent;
	time_t now = 0;

	/*
	 * Create a utmpx structure with ut_type defined as BOOT_TIME
	 * so that we can find the boot time.
	 */
	boot_ent.ut_type = BOOT_TIME;

	/*
	 * Get the system boot time.
	 */
	ent = getutxid( &boot_ent );

	/*
	 * Calculate and return uptime.
	 */
	(void)time( &now );
	uptime = now - (ent->ut_tv).tv_sec;
	return( uptime );
}
