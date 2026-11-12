#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 100010
#define MAXL 12
#define TSIZE 262144

static char words[MAXN][MAXL];
static int table[TSIZE];
static int cnt = 0;
static int L = 0;
static int alpha = 26;
static int distF[MAXN], distB[MAXN], bufF[MAXN], bufB[MAXN], nxtbuf[MAXN];

static unsigned state = 2463534242u;

unsigned rng(void) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

unsigned hash_word(const char *s) {
    unsigned h = 5381;
    while (*s) h = h * 33 + (unsigned char)*s++;
    return h;
}

void reset_dict(int len) {
    cnt = 0;
    L = len;
    memset(table, -1, sizeof(table));
}

int find_word(const char *s) {
    unsigned h = hash_word(s) & (TSIZE - 1);
    while (table[h] != -1) {
        if (strcmp(words[table[h]], s) == 0) return table[h];
        h = (h + 1) & (TSIZE - 1);
    }
    return -1;
}

int add_word(const char *s) {
    unsigned h = hash_word(s) & (TSIZE - 1);
    while (table[h] != -1) {
        if (strcmp(words[table[h]], s) == 0) return table[h];
        h = (h + 1) & (TSIZE - 1);
    }
    strcpy(words[cnt], s);
    table[h] = cnt;
    return cnt++;
}

int bidirectional(int src, int dst, int *visited) {
    if (src == dst) {
        *visited = 1;
        return 0;
    }
    for (int i = 0; i < cnt; i++) distF[i] = distB[i] = -1;
    int sizeF = 1, sizeB = 1, vis = 2;
    bufF[0] = src;
    distF[src] = 0;
    bufB[0] = dst;
    distB[dst] = 0;
    while (sizeF > 0 && sizeB > 0) {
        int forward = sizeF <= sizeB;
        int *front = forward ? bufF : bufB;
        int *size = forward ? &sizeF : &sizeB;
        int *dThis = forward ? distF : distB;
        int *dOther = forward ? distB : distF;
        int ns = 0;
        for (int i = 0; i < *size; i++) {
            int u = front[i];
            char w[MAXL];
            strcpy(w, words[u]);
            for (int pos = 0; pos < L; pos++) {
                char orig = w[pos];
                for (char c = 'a'; c < 'a' + 26; c++) {
                    if (c == orig) continue;
                    w[pos] = c;
                    int v = find_word(w);
                    if (v < 0) continue;
                    if (dOther[v] != -1) {
                        *visited = vis;
                        return dThis[u] + 1 + dOther[v];
                    }
                    if (dThis[v] == -1) {
                        dThis[v] = dThis[u] + 1;
                        nxtbuf[ns++] = v;
                        vis++;
                    }
                }
                w[pos] = orig;
            }
        }
        memcpy(front, nxtbuf, ns * sizeof(int));
        *size = ns;
    }
    *visited = vis;
    return -1;
}

int unidirectional(int src, int dst, int *visited) {
    if (src == dst) {
        *visited = 1;
        return 0;
    }
    for (int i = 0; i < cnt; i++) distF[i] = -1;
    int head = 0, tail = 0, vis = 1;
    bufF[tail++] = src;
    distF[src] = 0;
    while (head < tail) {
        int u = bufF[head++];
        char w[MAXL];
        strcpy(w, words[u]);
        for (int pos = 0; pos < L; pos++) {
            char orig = w[pos];
            for (char c = 'a'; c < 'a' + 26; c++) {
                if (c == orig) continue;
                w[pos] = c;
                int v = find_word(w);
                if (v < 0 || distF[v] != -1) continue;
                distF[v] = distF[u] + 1;
                vis++;
                if (v == dst) {
                    *visited = vis;
                    return distF[v];
                }
                bufF[tail++] = v;
            }
            w[pos] = orig;
        }
    }
    *visited = vis;
    return -1;
}

int differ_by_one(const char *a, const char *b) {
    int d = 0;
    for (int i = 0; i < L; i++) if (a[i] != b[i]) d++;
    return d == 1;
}

int brute_force(int src, int dst) {
    for (int i = 0; i < cnt; i++) distF[i] = -1;
    int head = 0, tail = 0;
    bufF[tail++] = src;
    distF[src] = 0;
    while (head < tail) {
        int u = bufF[head++];
        for (int j = 0; j < cnt; j++) {
            if (distF[j] == -1 && differ_by_one(words[u], words[j])) {
                distF[j] = distF[u] + 1;
                bufF[tail++] = j;
            }
        }
    }
    return distF[dst];
}

int transform(const char *A, const char *B) {
    int b = find_word(B);
    if (b < 0) return -1;
    if (strcmp(A, B) == 0) return 0;
    int a = add_word(A);
    int vis;
    return bidirectional(a, b, &vis);
}

void random_word(char *w) {
    for (int i = 0; i < L; i++) w[i] = 'a' + rng() % alpha;
    w[L] = '\0';
}

int main() {
    const char *dict[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    reset_dict(3);
    for (int i = 0; i < 6; i++) add_word(dict[i]);
    printf("Dictionary: hot dot dog lot log cog\n");
    printf("hit -> cog : %d\n", transform("hit", "cog"));
    printf("hot -> cog : %d\n", transform("hot", "cog"));
    printf("cog -> cog : %d\n", transform("cog", "cog"));
    reset_dict(3);
    const char *dict2[] = {"hot", "dot", "dog", "lot", "log"};
    for (int i = 0; i < 5; i++) add_word(dict2[i]);
    printf("Dictionary: hot dot dog lot log (cog missing)\n");
    printf("hit -> cog : %d\n", transform("hit", "cog"));
    reset_dict(3);
    const char *dict3[] = {"hot", "dot", "cog"};
    for (int i = 0; i < 3; i++) add_word(dict3[i]);
    printf("Dictionary: hot dot cog (no bridge)\n");
    printf("hit -> cog : %d\n", transform("hit", "cog"));

    int passed = 0, tests = 500;
    for (int t = 0; t < tests; t++) {
        int len = 2 + rng() % 3;
        reset_dict(len);
        alpha = 3;
        int n = 5 + rng() % 40;
        char w[MAXL];
        for (int i = 0; i < n; i++) {
            random_word(w);
            add_word(w);
        }
        int dst = rng() % cnt;
        random_word(w);
        int src = add_word(w);
        int v1, v2, v3 = brute_force(src, dst);
        int r1 = bidirectional(src, dst, &v1);
        int r2 = unidirectional(src, dst, &v2);
        if (r1 == r2 && r2 == v3) passed++;
    }
    printf("\nValidation against pairwise-Hamming BFS: %d / %d random tests passed\n", passed, tests);

    FILE *fp = fopen("results.csv", "w");
    fprintf(fp, "words,length,bidirectional_ms,unidirectional_ms,bidirectional_visited,unidirectional_visited,avg_distance\n");
    printf("\nwords    bi(ms)    uni(ms)   bi_visited  uni_visited  avg_dist\n");
    alpha = 26;
    int Q = 5;
    for (int N = 10000; N <= 100000; N += 10000) {
        reset_dict(10);
        char w[MAXL];
        random_word(w);
        add_word(w);
        while (cnt < N) {
            strcpy(w, words[rng() % cnt]);
            w[rng() % L] = 'a' + rng() % alpha;
            add_word(w);
        }
        double tb = 0, tu = 0, vb = 0, vu = 0, dsum = 0;
        int found = 0, mismatch = 0;
        for (int q = 0; q < Q; q++) {
            int a = rng() % cnt, b = rng() % cnt;
            int v1, v2;
            clock_t t0 = clock();
            int r1 = bidirectional(a, b, &v1);
            tb += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
            t0 = clock();
            int r2 = unidirectional(a, b, &v2);
            tu += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
            if (r1 != r2) mismatch++;
            vb += v1;
            vu += v2;
            if (r1 >= 0) {
                dsum += r1;
                found++;
            }
        }
        double avg_d = found ? dsum / found : -1;
        printf("%-8d %-9.3f %-9.3f %-11.0f %-12.0f %.2f%s\n", N, tb / Q, tu / Q, vb / Q, vu / Q, avg_d, mismatch ? "  MISMATCH" : "");
        fprintf(fp, "%d,10,%.4f,%.4f,%.1f,%.1f,%.2f\n", N, tb / Q, tu / Q, vb / Q, vu / Q, avg_d);
    }
    fclose(fp);
    return 0;
}
