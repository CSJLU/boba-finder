#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Earth's radius in kilometers
#define EARTH_RADIUS 6371.0

// Function to convert degrees to radians
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Haversine formula function
double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c;
}

int main() {
    FILE *file;
    char filename[100];
    double lat1, lon1, lat2, lon2;

    printf("Enter the input file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    double prevLat, prevLon;
    int isFirstLine = 1;

    printf("Distances between consecutive points:\n");

    while (fscanf(file, "%lf %lf", &lat1, &lon1) == 2) {
        if (!isFirstLine) {
            double distance = haversine(prevLat, prevLon, lat1, lon1);
            printf("From (%.6f, %.6f) to (%.6f, %.6f): %.2f km\n",
                   prevLat, prevLon, lat1, lon1, distance);
        }
        prevLat = lat1;
        prevLon = lon1;
        isFirstLine = 0;
    }

    fclose(file);
    return 0;
}
