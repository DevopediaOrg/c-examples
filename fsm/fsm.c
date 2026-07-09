/*
This code is about a Finite State Machine (FSM). Our goal
is find the steady state probabilities of the given states.

Our FSM has three states. The transition probabilities among
the states are also given. By doing a Monte Carlo simulation,
we estimate the steady state probabilities, that is, the
percentage of time the system will be in each state.

For example, when a day is sunny, 50% of the time the next
day will also be sunny. When a day is rainy, 40% of the time
the next day will be cloudy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_STEPS 10000

typedef enum weather {
    Sunny = 0,
    Cloudy,
    Rainy,
    NUM_STATES
} Weather;

char * WeatherStr[NUM_STATES] = {
    "Sunny", "Cloudy", "Rainy"
};


int main() {
    // FSM transition probability matrix
    float transitions[NUM_STATES][NUM_STATES] = {
        { 0.5, 0.3, 0.2 },
        { 0.1, 0.6, 0.3 },
        { 0.5, 0.4, 0.1 }
    };

    // Make a matrix of cumulative transitions
    float cumulatives[NUM_STATES][NUM_STATES];
    for (int i = 0; i < NUM_STATES; i++) {
        float sum = 0;
        for (int j = 0; j < NUM_STATES; j++) {
            sum += transitions[i][j];
            cumulatives[i][j] = sum;
        }
        if (sum != 1.0) {
            printf("Warning: transitions probabilities from [%s] state "
                   "don't add up to 1.0.\n", WeatherStr[i]);
        }
    }

    srand(time(NULL));

    Weather curr_state = Sunny;
    int counts[NUM_STATES] = {};

    for (int i = 0; i < NUM_STEPS; i++) {
        float rn = (float)(rand()) / RAND_MAX;
        for (int j = 0; j < NUM_STATES; j++) {
            if (rn < cumulatives[curr_state][j]) {
                curr_state = j;
                break;
            }
        }
        counts[curr_state]++;
    }

    for (int j = 0; j < NUM_STATES; j++) {
        printf("%6s: %4.1f %%\n", WeatherStr[j], counts[j] * 100.0 / NUM_STEPS);
    }

    return 0;
}

