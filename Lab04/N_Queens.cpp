#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cilk.h>
#include <cilk-lib.h>
#include <cilk-compat.h>
int safe(char *config, int i, int j)
{
	int r, s;
	for (r=0; r<i; r++) {
		s = config[r];
		if (j==s || i-r==j-s || i-r==s-j)
			return 0;
}
	return 1;
}
cilk char *nqueens(char *config, int n, int i)
{
	char *new_config;
	char *done = NULL;
	int j;
	inlet void catch(char *res)
	{
		if (res != NULL) {
			if (done == NULL)
				done = res;
			abort;
		}
	}
	if (i==n) {
		char *result;
		/* put this good solution in heap,
			and return a pointer to it */
		result = malloc(n*sizeof(char));
		memcpy(result, config, n*sizeof(char));
		return result;
	}
	/* try each possible position for queen <i> */
	for (j=0; j<n; j++) {
		/* allocate a temporary array and
		* copy the config into it */
		new_config = Cilk_alloca((i + 1) * sizeof(char));
		memcpy(new_config, config, i*sizeof(char));
		if (safe(new_config, i, j)) {
			new_config[i] = j;
			catch(spawn nqueens(new_config, n, i+1));
		}
		if (done != NULL)
			break;
	}
	sync;
	return done;
}
cilk int main(int argc, char *argv[])
{
	int n, i;
	char *config;
	char *result;
	if (argc < 2) {
		printf("%s: number of queens required\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	config = Cilk_alloca(n * sizeof(char));
	printf("running queens %d\n", n);
	result = spawn nqueens(config, n, 0);
	sync;
	if (result != NULL) {
		printf("Solution: ");
		for (i=0; i<n; i++)
			printf("%2d ", result[i]);
			printf("\n");
	}
	else
		printf("No solutions!\n");
	return 0;
}
