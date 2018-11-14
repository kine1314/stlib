#include <stdio.h>
#include <sys/types.h>
#include <assert.h>

#define MAXSIZE 99999
#define YES 1
#define NO 0
#define HK(key) ((key)%(MAXSIZE))

typedef struct uid_e {
    uid_t uid;
    unsigned int njobs;
} uid_e_t;

typedef struct uid_hash {
    uid_e_t elem[MAXSIZE];
    int used[MAXSIZE];
} uid_hash_t;

void init_uid_hash (uid_hash_t *H) {
    assert (H != NULL);
    int i = 0;
    for (i = 0; i < MAXSIZE; i++) {
        H->elem[i].uid = 0;
        H->elem[i].njobs = 0;
        H->used[i] = NO;
    }
}
int insert_uid_hash(uid_hash_t *H, const uid_e_t *e) {
    assert (H != NULL);
    assert (e != NULL);

    unsigned int key = HK(e->uid);
    int di = 1;
    if (H->elem[key].uid == e->uid && H->used[key] == YES ) {
        return -1;
    }
    while (H->used[key] == YES) {
        //这里输出key
        printf ("%u\n", key);
        if (di > MAXSIZE/2) {
            return -1;
        }
        else if (di > 0) {
            key= HK(HK(e->uid) + (di*di));
            di = -di;
            if (key < 0) key = MAXSIZE + key;
        } else {
            key= HK(HK(e->uid) - (di*di));
            di = -di;
            di ++;
            if (key < 0) key = MAXSIZE + key;
        }

    }
    if (key <= MAXSIZE) {
        H->elem[key] = *e;
        H->used[key] = YES;
        return key;
    }
    return -1;
}
int getpos (const uid_hash_t *H, uid_t uid, uid_e_t *e) {
    unsigned int key = HK(uid);
    int di = 1;
    if (H->used[key] == NO) {
        return -1;
    } else {
        while (H->used[key] == NO || H->elem[key].uid != uid) {
            if (di > MAXSIZE/2) {
                return -1;
            }
            else if (di > 0) {
                key = HK(HK(uid) + (di*di));
                di = -di;
                if (key < 0) key = MAXSIZE + key;
            } else {
                key = HK(HK(uid) - (di*di));
                if (key < 0) key = MAXSIZE + key;
                di = -di;
                di ++;
            }
        }
    }
    *e = H->elem[key];
    return key;
}
int main ()
{
    int i = 0;
    uid_hash_t H;
    //设置所有位置已经使用
    for (i = 0; i < MAXSIZE; i ++) {
        H.used[i] = YES;
    }
    uid_e_t e1 = {1, 1};
    insert_uid_hash(&H, &e1);

    return 0;
}
