/*
 * up.h - up function declarations and constants
 */

#define VERSION "1.0"

enum { STD, NUM, NOUP };

/* function prototypes */
void disp_version( void );
void disp_usage( char *pn );
void print_uptime( int otype );
double uptime( void );

/*
 * The following lines will determine the host and include the
 * appropriate uptime() function.
 */
/* Linux */
#if defined (__linux__)
#include "utmpx.c"
#endif

/* FreeBSD */
#if defined (__FreeBSD__)
#include "bsd.c"
#endif

/* IRIX */
#if defined (sgi)
#if defined (unix)
#if defined (mips)
#include "utmpx.c"
#endif
#endif
#endif

/* Darwin and MacOS X */
#if defined (__ppc__)
#if defined (__MACH__)
#if defined (__APPLE__)
#include "bsd.c"
#endif
#endif
#endif

/* Solaris */
#if defined (__SVR4)
#if defined (__sun)
#include "utmpx.c"
#endif
#endif
