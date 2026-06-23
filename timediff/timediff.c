/*
Takes two times in HH:MM:SS 24-hour format. Both times  belong to the same day.
Finds the absolute difference of the two times in seconds.
*/

#include <stdio.h>
#include <math.h>

/*
Take time in HH:MM:SS 24-hour format.
Return the number of seconds since midnight (00:00:00).
*/
int time2secs(char *time) {
    int hour, min, sec;
    sscanf(time, "%02d:%02d:%02d", &hour, &min, &sec);
    return hour*60*60 + min*60 + sec;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: expecting exactly 2 program arguments. Quitting...\n");
        return 1;
    }

    int t1 = time2secs(argv[1]);
    int t2 = time2secs(argv[2]);

    printf("Time difference is %d secs\n", abs(t1 - t2));

    return 0;
}
