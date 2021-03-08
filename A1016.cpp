#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Call {
    char name[21];
    int MM;
    int time;
    bool on;
} calls[1000];

struct {
    char name[21];
    int on, off;
    int MM;
} trueCalls[500];

int time2int(int dd, int hh, int mm) {
    return mm + hh * 60 + dd * 1440;
}

int getdd(int time) {
    return time / 1440;
}
int gethh(int time) {
    return time % 1440 / 60;
}
int getmm(int time) {
    return time % 60;
}

bool compare(Call a, Call b) {
    int minus = strcmp(a.name, b.name);
    if (minus < 0) {
        return true;
    }
    else if (minus > 0) {
        return false;
    }
    else {
        return a.time < b.time;
    }
}

int main(void) {
    int price[24];
    for (int i = 0; i < 24; i++) {
        scanf("%d", price + i);
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int dd, hh, mm;
        char status[10];
        scanf("%s %d:%d:%d:%d %s", calls[i].name, &calls[i].MM, &dd, &hh, &mm, status);
        calls[i].time = time2int(dd, hh, mm);
        if (status[1] == 'n') {
            calls[i].on = true;
        }
        else {
            calls[i].on = false;
        }
    }
    sort( calls, calls + n, compare );
    // make a true call list
    int count = 0;
    for (int i = 1; i < n; i++) {
        if ( calls[i - 1].on == true && calls[i].on == false && strcmp( calls[i - 1].name, calls[i].name ) == 0 ) {
            strcpy(trueCalls[count].name, calls[i].name);
            trueCalls[count].on = calls[i - 1].time;
            trueCalls[count].off = calls[i].time;
            trueCalls[count].MM = calls[i].MM;
            count++;
        }
    }
    for (int i = 0; i < count; i++) {
        int total;
        if ( i == 0 || strcmp( trueCalls[ i - 1 ].name, trueCalls[ i ].name ) != 0 ) {
            // the first record of this user
            total = 0;
            printf("%s %02d\n", trueCalls[i].name, trueCalls[i].MM);
        }
        // caculate the charge of the call
        int sum = 0;
        int on = trueCalls[i].on;
        int off = trueCalls[i].off;
        printf("%02d:%02d:%02d %02d:%02d:%02d %d", 
                getdd(on), gethh(on), getmm(on), getdd(off), gethh(off), getmm(off), off - on );
        while (on < off) {
            sum += price[gethh(on++)];
        }
        total += sum;
        printf(" $%d.%02d\n", sum / 100, sum % 100);
        if ( i == count - 1 || strcmp( trueCalls[ i + 1 ].name, trueCalls[ i ].name ) != 0 ) {
            // the last record of this user
            printf("Total amount: $%d.%02d\n", total / 100, total % 100);
        }
    }
    return 0;
}