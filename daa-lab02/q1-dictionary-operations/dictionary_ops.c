#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 200

static volatile long g_sink = 0;

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

static int *make_shuffled_keys(int n) {
    int *keys = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) keys[i] = i * 3 + 1;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = keys[i]; keys[i] = keys[j]; keys[j] = t;
    }
    return keys;
}

typedef struct { int *a; int n; } UArr;

static void ua_init(UArr *s, int cap) { s->a = malloc(sizeof(int) * cap); s->n = 0; }
static void ua_insert(UArr *s, int x) { s->a[s->n++] = x; }
static int  ua_search(UArr *s, int k) { for (int i = 0; i < s->n; i++) if (s->a[i] == k) return i; return -1; }
static void ua_delete_idx(UArr *s, int idx) { s->a[idx] = s->a[s->n - 1]; s->n--; }
static int  ua_max(UArr *s) { int m = s->a[0]; for (int i = 1; i < s->n; i++) if (s->a[i] > m) m = s->a[i]; return m; }
static int  ua_min(UArr *s) { int m = s->a[0]; for (int i = 1; i < s->n; i++) if (s->a[i] < m) m = s->a[i]; return m; }

static int ua_predecessor(UArr *s, int key) {
    int best = -1;
    for (int i = 0; i < s->n; i++) if (s->a[i] < key && (best == -1 || s->a[i] > best)) best = s->a[i];
    return best;
}
static int ua_successor(UArr *s, int key) {
    int best = -1;
    for (int i = 0; i < s->n; i++) if (s->a[i] > key && (best == -1 || s->a[i] < best)) best = s->a[i];
    return best;
}

typedef struct { int *a; int n; } SArr;

static void sa_init(SArr *s, int cap) { s->a = malloc(sizeof(int) * cap); s->n = 0; }
static int sa_bsearch(SArr *s, int k) {
    int lo = 0, hi = s->n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s->a[mid] == k) return mid;
        else if (s->a[mid] < k) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
static int sa_lower_bound(SArr *s, int k) {
    int lo = 0, hi = s->n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (s->a[mid] < k) lo = mid + 1; else hi = mid;
    }
    return lo;
}
static void sa_insert(SArr *s, int x) {
    int pos = sa_lower_bound(s, x);
    for (int i = s->n; i > pos; i--) s->a[i] = s->a[i - 1];
    s->a[pos] = x; s->n++;
}
static void sa_delete_idx(SArr *s, int idx) {
    for (int i = idx; i < s->n - 1; i++) s->a[i] = s->a[i + 1];
    s->n--;
}
static int sa_max(SArr *s) { return s->a[s->n - 1]; }
static int sa_min(SArr *s) { return s->a[0]; }
static int sa_predecessor(SArr *s, int idx) { return idx > 0 ? s->a[idx - 1] : -1; }
static int sa_successor(SArr *s, int idx) { return idx < s->n - 1 ? s->a[idx + 1] : -1; }

typedef struct SNode { int key; struct SNode *next; } SNode;
typedef struct { SNode *head; int n; } SList;

static void sl_init(SList *s) { s->head = NULL; s->n = 0; }
static void sl_push_front(SList *s, int x) {
    SNode *nd = malloc(sizeof(SNode)); nd->key = x; nd->next = s->head; s->head = nd; s->n++;
}
static void sl_insert_sorted(SList *s, int x) {
    SNode *nd = malloc(sizeof(SNode)); nd->key = x;
    if (!s->head || s->head->key >= x) { nd->next = s->head; s->head = nd; }
    else {
        SNode *cur = s->head;
        while (cur->next && cur->next->key < x) cur = cur->next;
        nd->next = cur->next; cur->next = nd;
    }
    s->n++;
}
static SNode *sl_search(SList *s, int k) { SNode *cur = s->head; while (cur && cur->key != k) cur = cur->next; return cur; }
static void sl_delete(SList *s, int k) {
    SNode *cur = s->head, *prev = NULL;
    while (cur && cur->key != k) { prev = cur; cur = cur->next; }
    if (!cur) return;
    if (!prev) s->head = cur->next; else prev->next = cur->next;
    free(cur); s->n--;
}
static int sl_max(SList *s) { int m = s->head->key; for (SNode *c = s->head; c; c = c->next) if (c->key > m) m = c->key; return m; }
static int sl_min_unsorted(SList *s) { int m = s->head->key; for (SNode *c = s->head; c; c = c->next) if (c->key < m) m = c->key; return m; }
static int sl_min_sorted(SList *s) { return s->head->key; }
static int sl_successor_sorted(SList *s, int k) { SNode *cur = sl_search(s, k); return (cur && cur->next) ? cur->next->key : -1; }
static int sl_predecessor_scan(SList *s, int k) {
    SNode *cur = s->head, *prev = NULL;
    while (cur && cur->key != k) { prev = cur; cur = cur->next; }
    return prev ? prev->key : -1;
}
static int sl_successor_unsorted(SList *s, int key) {
    int best = -1;
    for (SNode *c = s->head; c; c = c->next) if (c->key > key && (best == -1 || c->key < best)) best = c->key;
    return best;
}
static int sl_predecessor_unsorted(SList *s, int key) {
    int best = -1;
    for (SNode *c = s->head; c; c = c->next) if (c->key < key && (best == -1 || c->key > best)) best = c->key;
    return best;
}

typedef struct DNode { int key; struct DNode *prev, *next; } DNode;
typedef struct { DNode *head, *tail; int n; } DList;

static void dl_init(DList *s) { s->head = s->tail = NULL; s->n = 0; }
static void dl_push_front(DList *s, int x) {
    DNode *nd = malloc(sizeof(DNode)); nd->key = x; nd->prev = NULL; nd->next = s->head;
    if (s->head) s->head->prev = nd; s->head = nd;
    if (!s->tail) s->tail = nd;
    s->n++;
}
static void dl_insert_sorted(DList *s, int x) {
    DNode *nd = malloc(sizeof(DNode)); nd->key = x;
    if (!s->head || s->head->key >= x) {
        nd->prev = NULL; nd->next = s->head;
        if (s->head) s->head->prev = nd; s->head = nd;
        if (!s->tail) s->tail = nd;
    } else {
        DNode *cur = s->head;
        while (cur->next && cur->next->key < x) cur = cur->next;
        nd->next = cur->next; nd->prev = cur;
        if (cur->next) cur->next->prev = nd; else s->tail = nd;
        cur->next = nd;
    }
    s->n++;
}
static DNode *dl_search(DList *s, int k) { DNode *cur = s->head; while (cur && cur->key != k) cur = cur->next; return cur; }
static void dl_delete_node(DList *s, DNode *nd) {
    if (nd->prev) nd->prev->next = nd->next; else s->head = nd->next;
    if (nd->next) nd->next->prev = nd->prev; else s->tail = nd->prev;
    free(nd); s->n--;
}
static int dl_max_unsorted(DList *s) { int m = s->head->key; for (DNode *c = s->head; c; c = c->next) if (c->key > m) m = c->key; return m; }
static int dl_min_unsorted(DList *s) { int m = s->head->key; for (DNode *c = s->head; c; c = c->next) if (c->key < m) m = c->key; return m; }
static int dl_max_sorted(DList *s) { return s->tail->key; }
static int dl_min_sorted(DList *s) { return s->head->key; }
static int dl_successor_sorted(DNode *nd) { return nd->next ? nd->next->key : -1; }
static int dl_predecessor_sorted(DNode *nd) { return nd->prev ? nd->prev->key : -1; }
static int dl_successor_unsorted(DList *s, int key) {
    int best = -1;
    for (DNode *c = s->head; c; c = c->next) if (c->key > key && (best == -1 || c->key < best)) best = c->key;
    return best;
}
static int dl_predecessor_unsorted(DList *s, int key) {
    int best = -1;
    for (DNode *c = s->head; c; c = c->next) if (c->key < key && (best == -1 || c->key > best)) best = c->key;
    return best;
}

int main(void) {
    srand(42);
    int sizes[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *f = fopen("results_q1.csv", "w");
    fprintf(f, "structure,operation,n,avg_time_us\n");

    for (int si = 0; si < num_sizes; si++) {
        int n = sizes[si];
        int *keys = make_shuffled_keys(n);

        {
            UArr s; ua_init(&s, n);
            for (int i = 0; i < n; i++) ua_insert(&s, keys[i]);
            double t0, t1;
            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) g_sink += (long)ua_search(&s, keys[rand() % n]);
            t1 = now_seconds();
            fprintf(f, "unsorted_array,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) { ua_insert(&s, 999999); s.n--; }
            t1 = now_seconds();
            fprintf(f, "unsorted_array,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) { int idx = rand() % s.n; int val = s.a[idx]; ua_delete_idx(&s, idx); ua_insert(&s, val); }
            t1 = now_seconds();
            fprintf(f, "unsorted_array,delete,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)ua_max(&s); t1 = now_seconds();
            fprintf(f, "unsorted_array,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)ua_min(&s); t1 = now_seconds();
            fprintf(f, "unsorted_array,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)ua_predecessor(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "unsorted_array,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)ua_successor(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "unsorted_array,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            free(s.a);
        }

        {
            SArr s; sa_init(&s, n + TRIALS + 1);
            int *sorted_keys = malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) sorted_keys[i] = keys[i];
            for (int i = 0; i < n; i++) sorted_keys[i] = keys[i];
            for (int i = 0; i < n; i++) sa_insert(&s, keys[i]);

            double t0, t1;
            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) g_sink += (long)sa_bsearch(&s, keys[rand() % n]);
            t1 = now_seconds();
            fprintf(f, "sorted_array,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) { sa_insert(&s, -1 - t); sa_delete_idx(&s, 0); }
            t1 = now_seconds();
            fprintf(f, "sorted_array,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds();
            for (int t = 0; t < TRIALS; t++) { int idx = rand() % s.n; int val = s.a[idx]; sa_delete_idx(&s, idx); sa_insert(&s, val); }
            t1 = now_seconds();
            fprintf(f, "sorted_array,delete,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);

            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sa_max(&s); t1 = now_seconds();
            fprintf(f, "sorted_array,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sa_min(&s); t1 = now_seconds();
            fprintf(f, "sorted_array,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { int idx = sa_bsearch(&s, keys[rand() % n]); g_sink += (long)sa_predecessor(&s, idx); } t1 = now_seconds();
            fprintf(f, "sorted_array,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { int idx = sa_bsearch(&s, keys[rand() % n]); g_sink += (long)sa_successor(&s, idx); } t1 = now_seconds();
            fprintf(f, "sorted_array,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            free(s.a); free(sorted_keys);
        }

        {
            SList s; sl_init(&s);
            for (int i = 0; i < n; i++) sl_push_front(&s, keys[i]);
            double t0, t1;
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_search(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_unsorted,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { sl_push_front(&s, 999999); sl_delete(&s, 999999); } t1 = now_seconds();
            fprintf(f, "sll_unsorted,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { int k = keys[rand() % n]; sl_delete(&s, k); sl_push_front(&s, k); } t1 = now_seconds();
            fprintf(f, "sll_unsorted,delete,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_max(&s); t1 = now_seconds();
            fprintf(f, "sll_unsorted,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_min_unsorted(&s); t1 = now_seconds();
            fprintf(f, "sll_unsorted,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_predecessor_unsorted(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_unsorted,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_successor_unsorted(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_unsorted,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            SNode *c = s.head; while (c) { SNode *nx = c->next; free(c); c = nx; }
        }

        {
            SList s; sl_init(&s);
            for (int i = 0; i < n; i++) sl_insert_sorted(&s, keys[i]);
            double t0, t1;
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_search(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_sorted,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { sl_insert_sorted(&s, -1 - t); sl_delete(&s, -1 - t); } t1 = now_seconds();
            fprintf(f, "sll_sorted,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { int k = keys[rand() % n]; sl_delete(&s, k); sl_insert_sorted(&s, k); } t1 = now_seconds();
            fprintf(f, "sll_sorted,delete,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_max(&s); t1 = now_seconds();
            fprintf(f, "sll_sorted,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_min_sorted(&s); t1 = now_seconds();
            fprintf(f, "sll_sorted,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_predecessor_scan(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_sorted,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)sl_successor_sorted(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "sll_sorted,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            SNode *c = s.head; while (c) { SNode *nx = c->next; free(c); c = nx; }
        }

        {
            DList s; dl_init(&s);
            for (int i = 0; i < n; i++) dl_push_front(&s, keys[i]);
            double t0, t1;
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) dl_search(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "dll_unsorted,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { dl_push_front(&s, 999999); dl_delete_node(&s, s.head); } t1 = now_seconds();
            fprintf(f, "dll_unsorted,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            {
                int trial_n = TRIALS < n ? TRIALS : n;
                DNode **victims = malloc(sizeof(DNode*) * trial_n);
                int *vkeys = malloc(sizeof(int) * trial_n);
                for (int t = 0; t < trial_n; t++) { vkeys[t] = keys[t]; victims[t] = dl_search(&s, vkeys[t]); }
                t0 = now_seconds();
                for (int t = 0; t < trial_n; t++) dl_delete_node(&s, victims[t]);
                t1 = now_seconds();
                for (int t = 0; t < trial_n; t++) dl_push_front(&s, vkeys[t]);
                fprintf(f, "dll_unsorted,delete,%d,%f\n", n, (t1 - t0) / trial_n * 1e6);
                free(victims); free(vkeys);
            }
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_max_unsorted(&s); t1 = now_seconds();
            fprintf(f, "dll_unsorted,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_min_unsorted(&s); t1 = now_seconds();
            fprintf(f, "dll_unsorted,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_predecessor_unsorted(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "dll_unsorted,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_successor_unsorted(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "dll_unsorted,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            DNode *c = s.head; while (c) { DNode *nx = c->next; free(c); c = nx; }
        }

        {
            DList s; dl_init(&s);
            for (int i = 0; i < n; i++) dl_insert_sorted(&s, keys[i]);
            double t0, t1;
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) dl_search(&s, keys[rand() % n]); t1 = now_seconds();
            fprintf(f, "dll_sorted,search,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { dl_insert_sorted(&s, -1 - t); dl_delete_node(&s, s.head); } t1 = now_seconds();
            fprintf(f, "dll_sorted,insert,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            {
                int trial_n = TRIALS < n ? TRIALS : n;
                DNode **victims = malloc(sizeof(DNode*) * trial_n);
                int *vkeys = malloc(sizeof(int) * trial_n);
                for (int t = 0; t < trial_n; t++) { vkeys[t] = keys[t]; victims[t] = dl_search(&s, vkeys[t]); }
                t0 = now_seconds();
                for (int t = 0; t < trial_n; t++) dl_delete_node(&s, victims[t]);
                t1 = now_seconds();
                for (int t = 0; t < trial_n; t++) dl_insert_sorted(&s, vkeys[t]);
                fprintf(f, "dll_sorted,delete,%d,%f\n", n, (t1 - t0) / trial_n * 1e6);
                free(victims); free(vkeys);
            }
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_max_sorted(&s); t1 = now_seconds();
            fprintf(f, "dll_sorted,max,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) g_sink += (long)dl_min_sorted(&s); t1 = now_seconds();
            fprintf(f, "dll_sorted,min,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { DNode *nd = dl_search(&s, keys[rand() % n]); g_sink += (long)dl_predecessor_sorted(nd); } t1 = now_seconds();
            fprintf(f, "dll_sorted,predecessor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            t0 = now_seconds(); for (int t = 0; t < TRIALS; t++) { DNode *nd = dl_search(&s, keys[rand() % n]); g_sink += (long)dl_successor_sorted(nd); } t1 = now_seconds();
            fprintf(f, "dll_sorted,successor,%d,%f\n", n, (t1 - t0) / TRIALS * 1e6);
            DNode *c = s.head; while (c) { DNode *nx = c->next; free(c); c = nx; }
        }

        free(keys);
        printf("Finished n = %d\n", n);
    }

    fclose(f);
    printf("Done. Results written to results_q1.csv (checksum=%ld)\n", g_sink);
    return 0;
}
