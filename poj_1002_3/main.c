#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4',
                '5', '5', '5', '6', '6', '6', '7', 0, '7', '7', '8', '8', '8', '9', '9', '9', 0};

char ph[100000][9];
int nph;


int main() {
   int a1,a2,seq,num;
   char buf[1000];

    memset( ph, 0, sizeof(ph) );
    scanf( " %d", &nph );
    for( a1 = 0; a1 < nph; a1++ ) {
        scanf( " %s", buf );
        seq = 0;
        for( a2 = 0; buf[a2]; a2++ ) {
            if( buf[a2] == '-' ) continue;
            if( buf[a2] >= 'A' && buf[a2] <= 'Z' ) buf[a2] = map[buf[a2]-'A'];
            ph[a1][seq++] = buf[a2];
            if( seq == 3 ) ph[a1][seq++] = '-';
        }
    }
    qsort( ph, nph, 9, strcmp);
    seq = 1; num = 0;
    for( a1 = 1; a1 < nph; a1++ ) {
        if( strcmp( ph[a1-1], ph[a1] ) ) {  // always return 0 or 1,since ph[a1 - 1] >= ph[a1]
            if( seq > 1 ) {
                printf( "%s %d\n", ph[a1-1], seq );
                num = 1;
            }
            seq = 1;
        } else {
            seq++;
        }
    }
    if( seq > 1 ) { // output the last possible same str
        printf( "%s %d\n", ph[a1-1], seq );
        num = 1;
    }
    if( !num ) printf( "No duplicates.\n" );

    return 0;
}
