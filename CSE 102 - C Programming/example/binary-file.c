#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIN_FILE "binary-file.bin"

typedef struct Point2D {
	double x, y;
} Point2D;


int main (void) {
	FILE * fid;
	int i;
	const int size = 30;
	Point2D p[size], tmp;

	srand(time(NULL));

	for (i = 0; i < size; ++i) {
		p[i].x = rand() % 100; 
		p[i].y = rand() % 100; 
	}

	fid = fopen(BIN_FILE, "wb");
	if (fid != NULL) {

		fwrite(p, sizeof(Point2D), size, fid);
		fclose(fid);

		fid = fopen(BIN_FILE, "rb");
		if (fid != NULL) {
			for (i = 0; i < size; ++i) {
				fread(&tmp, sizeof(Point2D), 1, fid);
				printf("p: %2f %2f\n", tmp.x, tmp.y);
			}
			putchar('\n');
			fclose(fid);
		}
	}
}