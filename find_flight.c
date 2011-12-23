/* Finds appropriate (closest) flight based on user provided time */

#include <stdio.h>

#define NUM_FLIGHTS 8

struct flight_schedule {
    int dept_time;
    int arrv_time;
};

const struct flight_schedule flight_times[NUM_FLIGHTS] =
  {{480, 616}, {583, 712}, {679, 811}, {767, 900}, {840, 968}, {945, 1075},
   {1140, 1280}, {1305, 1438}};

void find_closest_flight(int desired_time, int *departure_time, 
        int *arrival_time);

int main(void)
{
    int hour, minute, desired_flight_time, departure_time, arrival_time,
        closest_hour, closest_minute;

    for (;;) {
        
        printf("\nPlease enter desired flight time (24-hour time, "
            "enter 0 to quit): ");
        scanf("%2d:%2d", &hour, &minute);
        if (hour == 0) {
            printf("\nExit program: goodbye.\n\n");
            break;
        }

        desired_flight_time = hour * 60 + minute;

        find_closest_flight(desired_flight_time, &departure_time, &arrival_time);

        if (departure_time > 780) {
            if (arrival_time > 780)
                printf("\nClosest departure time is %2d:%02d p.m., arriving, at %2d:%02d p.m.\n\n",
                        (departure_time / 60 - 12), (departure_time % 60),
                        (arrival_time / 60 - 12), (arrival_time % 60));
            else 
                printf("\nClosest departure time is %2d:%02d p.m., arriving at %2d:%02d a.m.\n\n",
                        (departure_time / 60 - 12), (departure_time % 60),
                        (arrival_time / 60), (arrival_time % 60));
        } else if (arrival_time > 780) 
                printf("\nClosest departure time is %2d:%02d a.m., arriving at %2d:%02d p.m.\n\n",
                        (departure_time / 60), (departure_time % 60),
                        (arrival_time / 60 - 12), (arrival_time % 60));
        else 
                printf("\nClosest departure time is %2d:%02d a.m., arriving at %2d:%02d a.m.\n\n",
                        (departure_time / 60), (departure_time % 60),
                        (arrival_time / 60), (arrival_time % 60));
    }

    
    return 0;
}

void find_closest_flight(int desired_time, int *departure_time, 
    int *arrival_time)
{
    int i, min_diff;

    if (flight_times[0].dept_time < desired_time)
        min_diff = desired_time -flight_times[0].dept_time;
    else 
        min_diff = flight_times[0].dept_time - desired_time;
    (*departure_time) = flight_times[0].dept_time;
    (*arrival_time) = flight_times[0].arrv_time;

    for (i = 1; i < NUM_FLIGHTS; i++) {
        if (flight_times[i].dept_time < desired_time) {
            if (desired_time - flight_times[i].dept_time < min_diff) {
                min_diff = desired_time - flight_times[i].dept_time;
                (*departure_time) = flight_times[i].dept_time;
                (*arrival_time) = flight_times[i].arrv_time;
            }
        } else {
            if (flight_times[i].dept_time - desired_time < min_diff) {
                min_diff = flight_times[i].dept_time - desired_time;
                (*departure_time) = flight_times[i].dept_time;
                (*arrival_time) = flight_times[i].arrv_time;
            }
        }
    }
}
