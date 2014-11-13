#include "apue.h"
//#include "apue.h.bak.h"
#include <errno.h>
#include <limits.h>

static void	pr_sysconf(char *, int);
static void	pr_pathconf(char *, char *, int);

int
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <dirname>");

#ifdef CHAR_BIT
	printf("CHAR_BIT defined to be %d\n", CHAR_BIT+0);
#else
	printf("no symbol for CHAR_BIT\n");
#endif
#ifdef _SC_CHAR_BIT
	pr_sysconf("CHAR_BIT =", _SC_CHAR_BIT);
#else
	printf("no symbol for _SC_CHAR_BIT\n");
#endif
#ifdef CHAR_MAX
	printf("CHAR_MAX defined to be %d\n", CHAR_MAX+0);
#else
	printf("no symbol for CHAR_MAX\n");
#endif
#ifdef _SC_CHAR_MAX
	pr_sysconf("CHAR_MAX =", _SC_CHAR_MAX);
#else
	printf("no symbol for _SC_CHAR_MAX\n");
#endif
#ifdef CHAR_MIN
	printf("CHAR_MIN defined to be %d\n", CHAR_MIN+0);
#else
	printf("no symbol for CHAR_MIN\n");
#endif
#ifdef _SC_CHAR_MIN
	pr_sysconf("CHAR_MIN =", _SC_CHAR_MIN);
#else
	printf("no symbol for _SC_CHAR_MIN\n");
#endif
#ifdef SCHAR_MIN
	printf("SCHAR_MIN defined to be %d\n", SCHAR_MIN+0);
#else
	printf("no symbol for SCHAR_MIN\n");
#endif
#ifdef _SC_SCHAR_MIN
	pr_sysconf("SCHAR_MIN =", _SC_SCHAR_MIN);
#else
	printf("no symbol for _SC_SCHAR_MIN\n");
#endif
#ifdef SCHAR_MAX
	printf("SCHAR_MAX defined to be %d\n", SCHAR_MAX+0);
#else
	printf("no symbol for SCHAR_MAX\n");
#endif
#ifdef _SC_SCHAR_MAX
	pr_sysconf("SCHAR_MAX =", _SC_SCHAR_MAX);
#else
	printf("no symbol for _SC_SCHAR_MAX\n");
#endif
#ifdef UCHAR_MAX
	printf("UCHAR_MAX defined to be %d\n", UCHAR_MAX+0);
#else
	printf("no symbol for UCHAR_MAX\n");
#endif
#ifdef _SC_UCHAR_MAX
	pr_sysconf("UCHAR_MAX =", _SC_UCHAR_MAX);
#else
	printf("no symbol for _SC_UCHAR_MAX\n");
#endif
#ifdef INT_MAX
	printf("INT_MAX defined to be %d\n", INT_MAX+0);
#else
	printf("no symbol for INT_MAX\n");
#endif
#ifdef _SC_INT_MAX
	pr_sysconf("INT_MAX =", _SC_INT_MAX);
#else
	printf("no symbol for _SC_INT_MAX\n");
#endif
#ifdef INT_MIN
	printf("INT_MIN defined to be %d\n", INT_MIN+0);
#else
	printf("no symbol for INT_MIN\n");
#endif
#ifdef _SC_INT_MIN
	pr_sysconf("INT_MIN =", _SC_INT_MIN);
#else
	printf("no symbol for _SC_INT_MIN\n");
#endif
#ifdef UINT_MAX
	printf("UINT_MAX defined to be %d\n", UINT_MAX+0);
#else
	printf("no symbol for UINT_MAX\n");
#endif
#ifdef _SC_UINT_MAX
	pr_sysconf("UINT_MAX =", _SC_UINT_MAX);
#else
	printf("no symbol for _SC_UINT_MAX\n");
#endif
#ifdef SHRT_MIN
	printf("SHRT_MIN defined to be %d\n", SHRT_MIN+0);
#else
	printf("no symbol for SHRT_MIN\n");
#endif
#ifdef _SC_SHRT_MIN
	pr_sysconf("SHRT_MIN =", _SC_SHRT_MIN);
#else
	printf("no symbol for _SC_SHRT_MIN\n");
#endif
#ifdef SHRT_MAX
	printf("SHRT_MAX defined to be %d\n", SHRT_MAX+0);
#else
	printf("no symbol for SHRT_MAX\n");
#endif
#ifdef _SC_SHRT_MAX
	pr_sysconf("SHRT_MAX =", _SC_SHRT_MAX);
#else
	printf("no symbol for _SC_SHRT_MAX\n");
#endif
#ifdef USHRT_MAX
	printf("USHRT_MAX defined to be %d\n", USHRT_MAX+0);
#else
	printf("no symbol for USHRT_MAX\n");
#endif
#ifdef _SC_USHRT_MAX
	pr_sysconf("USHRT_MAX =", _SC_USHRT_MAX);
#else
	printf("no symbol for _SC_USHRT_MAX\n");
#endif
#ifdef LONG_MAX
	printf("LONG_MAX defined to be %d\n", LONG_MAX+0);
#else
	printf("no symbol for LONG_MAX\n");
#endif
#ifdef _SC_LONG_MAX
	pr_sysconf("LONG_MAX =", _SC_LONG_MAX);
#else
	printf("no symbol for _SC_LONG_MAX\n");
#endif
#ifdef LONG_MIN
	printf("LONG_MIN defined to be %d\n", LONG_MIN+0);
#else
	printf("no symbol for LONG_MIN\n");
#endif
#ifdef _SC_LONG_MIN
	pr_sysconf("LONG_MIN =", _SC_LONG_MIN);
#else
	printf("no symbol for _SC_LONG_MIN\n");
#endif
#ifdef ULONG_MAX
	printf("ULONG_MAX defined to be %d\n", ULONG_MAX+0);
#else
	printf("no symbol for ULONG_MAX\n");
#endif
#ifdef _SC_ULONG_MAX
	pr_sysconf("ULONG_MAX =", _SC_ULONG_MAX);
#else
	printf("no symbol for _SC_ULONG_MAX\n");
#endif
#ifdef LLONG_MAX
	printf("LLONG_MAX defined to be %d\n", LLONG_MAX+0);
#else
	printf("no symbol for LLONG_MAX\n");
#endif
#ifdef _SC_LLONG_MAX
	pr_sysconf("LLONG_MAX =", _SC_LLONG_MAX);
#else
	printf("no symbol for _SC_LLONG_MAX\n");
#endif
#ifdef LLONG_MIN
	printf("LLONG_MIN defined to be %d\n", LLONG_MIN+0);
#else
	printf("no symbol for LLONG_MIN\n");
#endif
#ifdef _SC_LLONG_MIN
	pr_sysconf("LLONG_MIN =", _SC_LLONG_MIN);
#else
	printf("no symbol for _SC_LLONG_MIN\n");
#endif
#ifdef ULLONG_MAX
	printf("ULLONG_MAX defined to be %d\n", ULLONG_MAX+0);
#else
	printf("no symbol for ULLONG_MAX\n");
#endif
#ifdef _SC_ULLONG_MAX
	pr_sysconf("ULLONG_MAX =", _SC_ULLONG_MAX);
#else
	printf("no symbol for _SC_ULLONG_MAX\n");
#endif
#ifdef MB_LEN_MAX
	printf("MB_LEN_MAX defined to be %d\n", MB_LEN_MAX+0);
#else
	printf("no symbol for MB_LEN_MAX\n");
#endif
#ifdef _SC_MB_LEN_MAX
	pr_sysconf("MB_LEN_MAX =", _SC_MB_LEN_MAX);
#else
	printf("no symbol for _SC_MB_LEN_MAX\n");
#endif
#ifdef FOPEN_MAX
	printf("FOPEN_MAX defined to be %d\n", FOPEN_MAX+0);
#else
	printf("no symbol for FOPEN_MAX\n");
#endif
#ifdef _SC_FOPEN_MAX
	pr_sysconf("FOPEN_MAX =", _SC_FOPEN_MAX);
#else
	printf("no symbol for _SC_FOPEN_MAX\n");
#endif
#ifdef STREAM_MAX
	printf("STREAM_MAX defined to be %d\n", STREAM_MAX+0);
#else
	printf("no symbol for STREAM_MAX\n");
#endif
#ifdef _SC_STREAM_MAX
	pr_sysconf("STREAM_MAX =", _SC_STREAM_MAX);
#else
	printf("no symbol for _SC_STREAM_MAX\n");
#endif
#ifdef TMP_MAX
	printf("TMP_MAX defined to be %d\n", TMP_MAX+0);
#else
	printf("no symbol for TMP_MAX\n");
#endif
#ifdef _SC_TMP_MAX
	pr_sysconf("TMP_MAX =", _SC_TMP_MAX);
#else
	printf("no symbol for _SC_TMP_MAX\n");
#endif
#ifdef FILENAME_MAX
	printf("FILENAME_MAX defined to be %d\n", FILENAME_MAX+0);
#else
	printf("no symbol for FILENAME_MAX\n");
#endif
#ifdef _SC_FILENAME_MAX
	pr_sysconf("FILENAME_MAX =", _SC_FILENAME_MAX);
#else
	printf("no symbol for _SC_FILENAME_MAX\n");
#endif
#ifdef ARG_MAX
	printf("ARG_MAX defined to be %d\n", ARG_MAX+0);
#else
	printf("no symbol for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
	pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
#else
	printf("no symbol for _SC_ARG_MAX\n");
#endif
#ifdef CHILD_MAX
	printf("CHILD_MAX defined to be %d\n", CHILD_MAX+0);
#else
	printf("no symbol for CHILD_MAX\n");
#endif
#ifdef _SC_CHILD_MAX
	pr_sysconf("CHILD_MAX =", _SC_CHILD_MAX);
#else
	printf("no symbol for _SC_CHILD_MAX\n");
#endif
#ifdef HOST_NAME_MAX
	printf("HOST_NAME_MAX defined to be %d\n", HOST_NAME_MAX+0);
#else
	printf("no symbol for HOST_NAME_MAX\n");
#endif
#ifdef _SC_HOST_NAME_MAX
	pr_sysconf("HOST_NAME_MAX =", _SC_HOST_NAME_MAX);
#else
	printf("no symbol for _SC_HOST_NAME_MAX\n");
#endif
#ifdef LINK_MAX
	printf("LINK_MAX defined to be %d\n", LINK_MAX+0);
#else
	printf("no symbol for LINK_MAX\n");
#endif
#ifdef _SC_LINK_MAX
	pr_sysconf("LINK_MAX =", _SC_LINK_MAX);
#else
	printf("no symbol for _SC_LINK_MAX\n");
#endif
#ifdef LOGIN_NAME_MAX
	printf("LOGIN_NAME_MAX defined to be %d\n", LOGIN_NAME_MAX+0);
#else
	printf("no symbol for LOGIN_NAME_MAX\n");
#endif
#ifdef _SC_LOGIN_NAME_MAX
	pr_sysconf("LOGIN_NAME_MAX =", _SC_LOGIN_NAME_MAX);
#else
	printf("no symbol for _SC_LOGIN_NAME_MAX\n");
#endif
#ifdef MAX_CANON
	printf("MAX_CANON defined to be %d\n", MAX_CANON+0);
#else
	printf("no symbol for MAX_CANON\n");
#endif
#ifdef _SC_MAX_CANON
	pr_sysconf("MAX_CANON =", _SC_MAX_CANON);
#else
	printf("no symbol for _SC_MAX_CANON\n");
#endif
#ifdef MAX_INPUT
	printf("MAX_INPUT defined to be %d\n", MAX_INPUT+0);
#else
	printf("no symbol for MAX_INPUT\n");
#endif
#ifdef _SC_MAX_INPUT
	pr_sysconf("MAX_INPUT =", _SC_MAX_INPUT);
#else
	printf("no symbol for _SC_MAX_INPUT\n");
#endif
#ifdef NAME_MAX
	printf("NAME_MAX defined to be %d\n", NAME_MAX+0);
#else
	printf("no symbol for NAME_MAX\n");
#endif
#ifdef _SC_NAME_MAX
	pr_sysconf("NAME_MAX =", _SC_NAME_MAX);
#else
	printf("no symbol for _SC_NAME_MAX\n");
#endif
#ifdef NGROUPS_MAX
	printf("NGROUPS_MAX defined to be %d\n", NGROUPS_MAX+0);
#else
	printf("no symbol for NGROUPS_MAX\n");
#endif
#ifdef _SC_NGROUPS_MAX
	pr_sysconf("NGROUPS_MAX =", _SC_NGROUPS_MAX);
#else
	printf("no symbol for _SC_NGROUPS_MAX\n");
#endif
#ifdef OPEN_MAX
	printf("OPEN_MAX defined to be %d\n", OPEN_MAX+0);
#else
	printf("no symbol for OPEN_MAX\n");
#endif
#ifdef _SC_OPEN_MAX
	pr_sysconf("OPEN_MAX =", _SC_OPEN_MAX);
#else
	printf("no symbol for _SC_OPEN_MAX\n");
#endif
#ifdef PATH_MAX
	printf("PATH_MAX defined to be %d\n", PATH_MAX+0);
#else
	printf("no symbol for PATH_MAX\n");
#endif
#ifdef _SC_PATH_MAX
	pr_sysconf("PATH_MAX =", _SC_PATH_MAX);
#else
	printf("no symbol for _SC_PATH_MAX\n");
#endif
#ifdef PIPE_BUF
	printf("PIPE_BUF defined to be %d\n", PIPE_BUF+0);
#else
	printf("no symbol for PIPE_BUF\n");
#endif
#ifdef _SC_PIPE_BUF
	pr_sysconf("PIPE_BUF =", _SC_PIPE_BUF);
#else
	printf("no symbol for _SC_PIPE_BUF\n");
#endif
#ifdef RE_DUP_MAX
	printf("RE_DUP_MAX defined to be %d\n", RE_DUP_MAX+0);
#else
	printf("no symbol for RE_DUP_MAX\n");
#endif
#ifdef _SC_RE_DUP_MAX
	pr_sysconf("RE_DUP_MAX =", _SC_RE_DUP_MAX);
#else
	printf("no symbol for _SC_RE_DUP_MAX\n");
#endif
#ifdef SSIZE_MAX
	printf("SSIZE_MAX defined to be %d\n", SSIZE_MAX+0);
#else
	printf("no symbol for SSIZE_MAX\n");
#endif
#ifdef _SC_SSIZE_MAX
	pr_sysconf("SSIZE_MAX =", _SC_SSIZE_MAX);
#else
	printf("no symbol for _SC_SSIZE_MAX\n");
#endif
#ifdef SYMLINK_MAX
	printf("SYMLINK_MAX defined to be %d\n", SYMLINK_MAX+0);
#else
	printf("no symbol for SYMLINK_MAX\n");
#endif
#ifdef _SC_SYMLINK_MAX
	pr_sysconf("SYMLINK_MAX =", _SC_SYMLINK_MAX);
#else
	printf("no symbol for _SC_SYMLINK_MAX\n");
#endif
#ifdef SYMLOOP_MAX
	printf("SYMLOOP_MAX defined to be %d\n", SYMLOOP_MAX+0);
#else
	printf("no symbol for SYMLOOP_MAX\n");
#endif
#ifdef _SC_SYMLOOP_MAX
	pr_sysconf("SYMLOOP_MAX =", _SC_SYMLOOP_MAX);
#else
	printf("no symbol for _SC_SYMLOOP_MAX\n");
#endif
#ifdef TTY_NAME_MAX
	printf("TTY_NAME_MAX defined to be %d\n", TTY_NAME_MAX+0);
#else
	printf("no symbol for TTY_NAME_MAX\n");
#endif
#ifdef _SC_TTY_NAME_MAX
	pr_sysconf("TTY_NAME_MAX =", _SC_TTY_NAME_MAX);
#else
	printf("no symbol for _SC_TTY_NAME_MAX\n");
#endif
#ifdef TZNAME_MAX
	printf("TZNAME_MAX defined to be %d\n", TZNAME_MAX+0);
#else
	printf("no symbol for TZNAME_MAX\n");
#endif
#ifdef _SC_TZNAME_MAX
	pr_sysconf("TZNAME_MAX =", _SC_TZNAME_MAX);
#else
	printf("no symbol for _SC_TZNAME_MAX\n");
#endif
#ifdef NL_ARGMAX
	printf("NL_ARGMAX defined to be %d\n", NL_ARGMAX+0);
#else
	printf("no symbol for NL_ARGMAX\n");
#endif
#ifdef _SC_NL_ARGMAX
	pr_sysconf("NL_ARGMAX =", _SC_NL_ARGMAX);
#else
	printf("no symbol for _SC_NL_ARGMAX\n");
#endif
#ifdef NL_LANGMAX
	printf("NL_LANGMAX defined to be %d\n", NL_LANGMAX+0);
#else
	printf("no symbol for NL_LANGMAX\n");
#endif
#ifdef _SC_NL_LANGMAX
	pr_sysconf("NL_LANGMAX =", _SC_NL_LANGMAX);
#else
	printf("no symbol for _SC_NL_LANGMAX\n");
#endif
#ifdef NL_MSGMAX
	printf("NL_MSGMAX defined to be %d\n", NL_MSGMAX+0);
#else
	printf("no symbol for NL_MSGMAX\n");
#endif
#ifdef _SC_NL_MSGMAX
	pr_sysconf("NL_MSGMAX =", _SC_NL_MSGMAX);
#else
	printf("no symbol for _SC_NL_MSGMAX\n");
#endif
#ifdef NL_NMAX
	printf("NL_NMAX defined to be %d\n", NL_NMAX+0);
#else
	printf("no symbol for NL_NMAX\n");
#endif
#ifdef _SC_NL_NMAX
	pr_sysconf("NL_NMAX =", _SC_NL_NMAX);
#else
	printf("no symbol for _SC_NL_NMAX\n");
#endif
#ifdef NL_SETMAX
	printf("NL_SETMAX defined to be %d\n", NL_SETMAX+0);
#else
	printf("no symbol for NL_SETMAX\n");
#endif
#ifdef _SC_NL_SETMAX
	pr_sysconf("NL_SETMAX =", _SC_NL_SETMAX);
#else
	printf("no symbol for _SC_NL_SETMAX\n");
#endif
#ifdef NL_TEXTMAX
	printf("NL_TEXTMAX defined to be %d\n", NL_TEXTMAX+0);
#else
	printf("no symbol for NL_TEXTMAX\n");
#endif
#ifdef _SC_NL_TEXTMAX
	pr_sysconf("NL_TEXTMAX =", _SC_NL_TEXTMAX);
#else
	printf("no symbol for _SC_NL_TEXTMAX\n");
#endif
#ifdef NZERO
	printf("NZERO defined to be %d\n", NZERO+0);
#else
	printf("no symbol for NZERO\n");
#endif
#ifdef _SC_NZERO
	pr_sysconf("NZERO =", _SC_NZERO);
#else
	printf("no symbol for _SC_NZERO\n");
#endif
#ifdef IOV_MAX
	printf("IOV_MAX defined to be %d\n", IOV_MAX+0);
#else
	printf("no symbol for IOV_MAX\n");
#endif
#ifdef _SC_IOV_MAX
	pr_sysconf("IOV_MAX =", _SC_IOV_MAX);
#else
	printf("no symbol for _SC_IOV_MAX\n");
#endif
#ifdef NAME_MAX
	printf("NAME_MAX defined to be %d\n", NAME_MAX+0);
#else
	printf("no symbol for NAME_MAX\n");
#endif
#ifdef _SC_NAME_MAX
	pr_sysconf("NAME_MAX =", _SC_NAME_MAX);
#else
	printf("no symbol for _SC_NAME_MAX\n");
#endif
#ifdef PATH_MAX
	printf("PATH_MAX defined to be %d\n", PATH_MAX+0);
#else
	printf("no symbol for PATH_MAX\n");
#endif
#ifdef _SC_PATH_MAX
	pr_sysconf("PATH_MAX =", _SC_PATH_MAX);
#else
	printf("no symbol for _SC_PATH_MAX\n");
#endif
#ifdef ATEXIT_MAX
	printf("ATEXIT_MAX defined to be %d\n", ATEXIT_MAX+0);
#else
	printf("no symbol for ATEXIT_MAX\n");
#endif
#ifdef _SC_ATEXIT_MAX
	pr_sysconf("ATEXIT_MAX =", _SC_ATEXIT_MAX);
#else
	printf("no symbol for _SC_ATEXIT_MAX\n");
#endif
#ifdef CLK_TCK
	printf("CLK_TCK defined to be %d\n", CLK_TCK+0);
#else
	printf("no symbol for CLK_TCK\n");
#endif
#ifdef _SC_CLK_TCK
	pr_sysconf("CLK_TCK =", _SC_CLK_TCK);
#else
	printf("no symbol for _SC_CLK_TCK\n");
#endif
#ifdef HOST_NAME_MAX
	printf("HOST_NAME_MAX defined to be %d\n", HOST_NAME_MAX+0);
#else
	printf("no symbol for HOST_NAME_MAX\n");
#endif
#ifdef _SC_HOST_NAME_MAX
	pr_sysconf("HOST_NAME_MAX =", _SC_HOST_NAME_MAX);
#else
	printf("no symbol for _SC_HOST_NAME_MAX\n");
#endif
#ifdef LINE_MAX
	printf("LINE_MAX defined to be %d\n", LINE_MAX+0);
#else
	printf("no symbol for LINE_MAX\n");
#endif
#ifdef _SC_LINK_MAX
	pr_sysconf("LINE_MAX =", _SC_LINK_MAX);
#else
	printf("no symbol for _SC_LINK_MAX\n");
#endif
#ifdef PAGESIZE
	printf("PAGESIZE defined to be %d\n", PAGESIZE+0);
#else
	printf("no symbol for PAGESIZE\n");
#endif
#ifdef _SC_PAGESIZE
	pr_sysconf("PAGESIZE =", _SC_PAGESIZE);
#else
	printf("no symbol for _SC_PAGESIZE\n");
#endif
#ifdef PAGE_SIZE
	printf("PAGE_SIZE defined to be %d\n", PAGE_SIZE+0);
#else
	printf("no symbol for PAGE_SIZE\n");
#endif
#ifdef _SC_PAGE_SIZE
	pr_sysconf("PAGE_SIZE =", _SC_PAGE_SIZE);
#else
	printf("no symbol for _SC_PAGE_SIZE\n");
#endif
#ifdef RE_DUP_MAX
	printf("RE_DUP_MAX defined to be %d\n", RE_DUP_MAX+0);
#else
	printf("no symbol for RE_DUP_MAX\n");
#endif
#ifdef _SC_RE_DUP_MAX
	pr_sysconf("RE_DUP_MAX =", _SC_RE_DUP_MAX);
#else
	printf("no symbol for _SC_RE_DUP_MAX\n");
#endif
#ifdef COLL_WEIGHTS_MAX
	printf("COLL_WEIGHTS_MAX defined to be %d\n", COLL_WEIGHTS_MAX+0);
#else
	printf("no symbol for COLL_WEIGHTS_MAX\n");
#endif
#ifdef _SC_COLL_WEIGHTS_MAX
	pr_sysconf("COLL_WEIGHTS_MAX =", _SC_COLL_WEIGHTS_MAX);
#else
	printf("no symbol for _SC_COLL_WEIGHTS_MAX\n");
#endif
#ifdef FILESIZEBITS
	printf("FILESIZEBITS defined to be %d\n", FILESIZEBITS+0);
#else
	printf("no symbol for FILESIZEBITS\n");
#endif
#ifdef _PC_FILESIZEBITS
	pr_pathconf("FILESIZEBITS =", argv[1], _PC_FILESIZEBITS);
#else
	printf("no symbol for _PC_FILESIZEBITS\n");
#endif
#ifdef LINK_MAX
	printf("LINK_MAX defined to be %d\n", LINK_MAX+0);
#else
	printf("no symbol for LINK_MAX\n");
#endif
#ifdef _PC_LINK_MAX
	pr_pathconf("LINK_MAX =", argv[1], _PC_LINK_MAX);
#else
	printf("no symbol for _PC_LINK_MAX\n");
#endif
#ifdef MAX_CANON
	printf("MAX_CANON defined to be %d\n", MAX_CANON+0);
#else
	printf("no symbol for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
	pr_pathconf("MAX_CANON =", argv[1], _PC_MAX_CANON);
#else
	printf("no symbol for _PC_MAX_CANON\n");
#endif
#ifdef MAX_INPUT
	printf("MAX_INPUT defined to be %d\n", MAX_INPUT+0);
#else
	printf("no symbol for MAX_INPUT\n");
#endif
#ifdef _PC_MAX_INPUT
	pr_pathconf("MAX_INPUT =", argv[1], _PC_MAX_INPUT);
#else
	printf("no symbol for _PC_MAX_INPUT\n");
#endif
#ifdef NAME_MAX
	printf("NAME_MAX defined to be %d\n", NAME_MAX+0);
#else
	printf("no symbol for NAME_MAX\n");
#endif
#ifdef _PC_NAME_MAX
	pr_pathconf("NAME_MAX =", argv[1], _PC_NAME_MAX);
#else
	printf("no symbol for _PC_NAME_MAX\n");
#endif
#ifdef PATH_MAX
	printf("PATH_MAX defined to be %d\n", PATH_MAX+0);
#else
	printf("no symbol for PATH_MAX\n");
#endif
#ifdef _PC_PATH_MAX
	pr_pathconf("PATH_MAX =", argv[1], _PC_PATH_MAX);
#else
	printf("no symbol for _PC_PATH_MAX\n");
#endif
#ifdef PIPE_BUF
	printf("PIPE_BUF defined to be %d\n", PIPE_BUF+0);
#else
	printf("no symbol for PIPE_BUF\n");
#endif
#ifdef _PC_PIPE_BUF
	pr_pathconf("PIPE_BUF =", argv[1], _PC_PIPE_BUF);
#else
	printf("no symbol for _PC_PIPE_BUF\n");
#endif
#ifdef SYMLINK_MAX
	printf("SYMLINK_MAX defined to be %d\n", SYMLINK_MAX+0);
#else
	printf("no symbol for SYMLINK_MAX\n");
#endif
#ifdef _PC_SYMLINK_MAX
	pr_pathconf("SYMLINK_MAX =", argv[1], _PC_SYMLINK_MAX);
#else
	printf("no symbol for _PC_SYMLINK_MAX\n");
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
