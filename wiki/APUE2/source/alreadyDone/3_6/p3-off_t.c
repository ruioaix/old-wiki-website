#include "apue.h"
#include <errno.h>
#include <limits.h>

static void	pr_sysconf(char *, int);
static void	pr_pathconf(char *, char *, int);

int
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <dirname>");

#ifdef V6_ILP32_OFF32
	printf("V6_ILP32_OFF32 defined to be %d\n", V6_ILP32_OFF32+0);
#else
	printf("no symbol for V6_ILP32_OFF32\n");
#endif
#ifdef _SC_V6_ILP32_OFF32
	pr_sysconf("V6_ILP32_OFF32 =", _SC_V6_ILP32_OFF32);
#else
	printf("no symbol for _SC_V6_ILP32_OFF32\n");
#endif
#ifdef V6_ILP32_OFFBIG
	printf("V6_ILP32_OFFBIG defined to be %d\n", V6_ILP32_OFFBIG+0);
#else
	printf("no symbol for V6_ILP32_OFFBIG\n");
#endif
#ifdef _SC_V6_ILP32_OFFBIG
	pr_sysconf("V6_ILP32_OFFBIG =", _SC_V6_ILP32_OFFBIG);
#else
	printf("no symbol for _SC_V6_ILP32_OFFBIG\n");
#endif
#ifdef V6_LP64_OFF64
	printf("V6_LP64_OFF64 defined to be %d\n", V6_LP64_OFF64+0);
#else
	printf("no symbol for V6_LP64_OFF64\n");
#endif
#ifdef _SC_V6_LP64_OFF64
	pr_sysconf("V6_LP64_OFF64 =", _SC_V6_LP64_OFF64);
#else
	printf("no symbol for _SC_V6_LP64_OFF64\n");
#endif
#ifdef V6_LP64_OFFBIG
	printf("V6_LP64_OFFBIG defined to be %d\n", V6_LP64_OFFBIG+0);
#else
	printf("no symbol for V6_LP64_OFFBIG\n");
#endif
#ifdef _SC_V6_LP64_OFFBIG
	pr_sysconf("V6_LP64_OFFBIG =", _SC_V6_LP64_OFFBIG);
#else
	printf("no symbol for _SC_V6_LP64_OFFBIG\n");
#endif
	exit(0);
}

static void
pr_sysconf(char *mesg, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = sysconf(name)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("sysconf error");
		} else {
			fputs(" (no limit)\n", stdout);
		}
	} else {
		printf(" %ld\n", val);
	}
}

static void
pr_pathconf(char *mesg, char *path, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = pathconf(path, name)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("pathconf error, path = %s", path);
		} else {
			fputs(" (no limit)\n", stdout);
		}
	} else {
		printf(" %ld\n", val);
	}
}
