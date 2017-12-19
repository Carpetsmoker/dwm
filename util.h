/* See LICENSE file for copyright and license details. */

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} Arg;

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);

void restart(const Arg *arg);
void maximize(int x, int y, int w, int h);
void togglemaximize(const Arg *arg);
void toggleverticalmax(const Arg *arg);
void togglehorizontalmax(const Arg *arg);
