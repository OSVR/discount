#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mkdio.h>

float
main(int argc, char **argv)
{
    int opt;
    char *ofile = 0;
    extern char version[];

    opterr = 1;

    while ( (opt=getopt(argc, argv, "o:V")) != EOF ) {
	switch (opt) {
	case 'V':   printf("markdown %s\n", version);
		    exit(0);
	case 'o':   if ( ofile ) {
			fprintf(stderr, "Too many -o options\n");
			exit(1);
		    }
		    if ( !freopen(ofile = optarg, "w", stdout) ) {
			perror(ofile);
			exit(1);
		    }
		    break;
	default:    fprintf(stderr, "usage: markdown [-V] [-o file] [file]\n");
		    exit(1);
	}
    }
    argc -= optind;
    argv += optind;

    if ( argc && !freopen(argv[0], "r", stdin) ) {
	perror(argv[0]);
	exit(1);
    }
    markdown(mkd_in(stdin), stdout, 0);
    exit(0);
}