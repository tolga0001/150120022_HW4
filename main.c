#include <stdio.h>
#include <string.h>
#include <math.h>

# define SIZE 10

typedef struct MetroStation {
    char name[20];
    double x, y;
} MetroStation;


typedef struct MetroLine {
    char color[20];
    MetroStation MetroStations[SIZE];

} MetroLine;

typedef struct MetroSystem {
    char name[20];
    MetroLine MetroLines[SIZE];

} MetroSystem;
MetroSystem istanbul = {"İstanbul"};

void duplicatePath(struct MetroStation pStation[10], MetroStation *pStation1);

void addStartStation(MetroStation station, struct MetroStation pStation[10]);

int getIndexOfLastStation(MetroStation *pStation);

void printPath(struct MetroStation pStation[10]);

int equals(MetroStation s1, MetroStation s2) {
    if (strcmp(s1.name, s2.name) == 0) {
        return 1;
    }
    return 0;
}

int getLastStationIndex(MetroLine line) {
    int i = 0;
    do {
        if (line.MetroStations[i].name[0] == '\0') {
            break;
        }
        i++;
    } while (i < SIZE);
    return i - 1;
}

void addStation(MetroLine *metroLinePtr, MetroStation metroStation) {
    int i = 0;
    do {
        if (metroLinePtr->MetroStations[i].name[0] == '\0') {
            break;
        }
        i++;
    } while (i < SIZE);

    metroLinePtr->MetroStations[i] = metroStation;
}

int hasStation(MetroLine metroLine, MetroStation metroStation) {
    int i;
    MetroStation currentStation;
    for (i = 0; i < SIZE; ++i) {
        currentStation = metroLine.MetroStations[i];
        if (equals(currentStation, metroStation)) {
            return 1;
        }
    }
    return 0;
}

MetroStation getFirstStop(MetroLine metroLine) {
    if (metroLine.MetroStations[0].name[0] == '\0') {
        MetroStation empty;
        return empty;
    }
    return metroLine.MetroStations[0];

}

MetroStation getPreviousStop(MetroLine metroLine, MetroStation metroStation) {
    MetroStation empty;

    if (equals(metroStation, metroLine.MetroStations[0]))
        return empty;
    // int currentIndex = 1;
    int i;
    for (i = 1; i < SIZE; ++i) {
        if (equals(metroStation, metroLine.MetroStations[i])) {
            return metroLine.MetroStations[i - 1];
        }
    }
    return empty;
}


MetroStation getNextStop(MetroLine metroLine, MetroStation metroStation) {
    MetroStation empty;
    int i;
    char name[SIZE];
    int lastStIndex = getLastStationIndex(metroLine);
    if (equals(metroStation, metroLine.MetroStations[lastStIndex]))
        return empty;

    for (i = 0; i < SIZE - 1; ++i) {
        if (equals(metroStation, metroLine.MetroStations[i])) {
            return metroLine.MetroStations[i + 1];
        }
    }
    return empty;
}

void addLine(MetroSystem *metroSystemPtr, MetroLine metroLine) {
    int i;
    for (i = 0; i < SIZE; ++i) {
        if (metroSystemPtr->MetroLines[i].color[0] == '\0') {
            break;
        }
    }
    metroSystemPtr->MetroLines[i] = metroLine;
}

void printLine(MetroLine metroLine) {
    printf("Metroline %s:  ", metroLine.color);
    int i;
    int lastIndex = getLastStationIndex(metroLine);
    for (i = 0; i < lastIndex; i++) {
        printf("%s, ", metroLine.MetroStations[i].name);
    }
    printf("%s.", metroLine.MetroStations[lastIndex].name);
    printf("\n");
}


int getlength(MetroLine metroLine) {
    return getLastStationIndex(metroLine) + 1;
}

double getdistance(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

int getstationslength(MetroStation *pStation) {
    int i;
    int length = 0;
    for (i = 0; pStation[i].name[0] != '\0'; i++) {
        length++;
    }
    return length;
}

double getDistanceTravelled(MetroStation metroStations[]) {
    int len = getstationslength(metroStations);
    if (len > 2) {
        int index;
        double totaldistance = 0;
        double x0, y0, x1, y1;
        for (index = 0; index < SIZE - 1; index++) {
            x0 = metroStations[index].x;
            y0 = metroStations[index].y;
            x1 = metroStations[index + 1].x;
            y1 = metroStations[index + 1].y;
            totaldistance += getdistance(x0, y0, x1, y1);
        }
        return totaldistance;

    }


    return 0;
}


MetroStation findNearestStation(MetroSystem metroSystem, double x, double y) {
    MetroStation nearestSt = getFirstStop(metroSystem.MetroLines[0]);
    double nearestX = nearestSt.x;
    double nearestY = nearestSt.y;
    double nearestDistance = getdistance(x, y, nearestX, nearestY);

    int i, j;
    MetroStation currentstation;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; ++j) {
            currentstation = metroSystem.MetroLines[i].MetroStations[j];
            double distance = getdistance(x, y, currentstation.x, currentstation.y);
            if (distance < nearestDistance) {
                nearestDistance = distance;
                nearestSt = currentstation;
            }
        }
    }
    return nearestSt;


}


int getIndex(MetroStation station, MetroLine line) {
    int i;
    //int condition= strcmp(station.)
    for (i = 0; line.MetroStations[i].name[0] != '\0'; i++) {
        if (equals(station, line.MetroStations[i])) {
            return i;
        }
    }
    return -1;
}

void fillArray(MetroStation metroStation, MetroStation neighboringStations[], int *k, MetroLine currentline) {
    int index = getIndex((metroStation), (currentline));
    if (index == 0) {
        neighboringStations[*k] = getNextStop(currentline, metroStation);
        (*k)++;

    } else if (index == getLastStationIndex((currentline))) {
        neighboringStations[*k] = getPreviousStop(currentline, metroStation);
        (*k)++;

    } else {
        neighboringStations[(*k)++] = getPreviousStop(currentline, metroStation);
        neighboringStations[(*k)++] = getNextStop(currentline, metroStation);

    }
}

void getNeighboringStations(MetroSystem metroSystem, MetroStation metroStation, MetroStation neighboringStations[]) {
    int i;
    int nIndex = 0;
    MetroLine currentline;
    //int len= strcmp()
    // int i = 0;
    //int isLineExist = (metroSystem.MetroLines[i].color[0] != '\0');

    for (i = 0; (metroSystem.MetroLines[i].color[0] != '\0'); i++) {
        currentline = metroSystem.MetroLines[i];
        if (hasStation(currentline, metroStation)) {

            fillArray(metroStation, neighboringStations, &nIndex, currentline);
        }


    }
    //fillArray(stationIndex, neighboringStations, currentline);
    // break;
}

int doescontains(MetroStation station, MetroStation *pStation) {
    int i = 0;
    for (i = 0; i < SIZE; i++) {
        if (equals(pStation[i], station)) {
            return 1;
        }
    }
    return 0;
}

void recursiveFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[], MetroStation bestPath[]) {
    if (doescontains(start, partialPath)) {
        return;
    }
    if (equals(start, finish)) {
        partialPath = bestPath;
        return;
    }
    MetroStation neighbors[SIZE] = {};
    getNeighboringStations(istanbul, start, neighbors);
    MetroStation duplicatedPath[SIZE] = {};
    duplicatePath(duplicatedPath, partialPath);
    addStartStation(start, neighbors);

    static index = 0;

    if (partialPath != NULL) {
        if (getDistanceTravelled(partialPath) < getDistanceTravelled(bestPath)) {
            bestPath = partialPath;
        }
    }
    recursiveFindPath(neighbors[index++], finish, duplicatedPath, partialPath);

}

void addStartStation(MetroStation start, MetroStation pStation[10]) {
    int lastIndex = getIndexOfLastStation(pStation);
    pStation[lastIndex + 1] = start;


}

int getIndexOfLastStation(MetroStation *pStation) {
    int i, lastIndex;
    int indexCount = 0;
    for (i = 0; strlen(pStation->name) != 0; i++) {
        indexCount++;
    };
    lastIndex = indexCount - 1;
    return lastIndex;
}

void duplicatePath(struct MetroStation destination[10], MetroStation *source) {
    int i;
    for (i = 0; i < getstationslength(destination); i++) {
        strcpy(destination[i].name, source[i].name);
        destination[i].x = source[i].x;
        destination[i].y = source[i].y;
    }

}

void findPath(MetroStation start, MetroStation finish, MetroStation path[]) {
    MetroStation partialPath[SIZE] = {};
    recursiveFindPath(start, finish, path, partialPath);
}


int main() {
    /* MetroLine metroLine = {"red"};
     MetroLine metroLine1 = {"blue"};
     MetroLine metroLine2 = {"yellow"};
     MetroStation m1 = {"goztepe", 10, 20};
     MetroStation m2 = {"haydarpasa", 10, 20};
     MetroStation m3 = {"kadikoy", 10, 20};
     MetroStation m4 = {"Avcilar", 10, 20};
     MetroStation m5 = {"BostancÄ±", 10, 20};
     addStation(&metroLine, m1);
     addStation(&metroLine, m2);
     addStation(&metroLine, m3);
     addStation(&metroLine, m4);
     addStation(&metroLine, m5);
     addStation(&metroLine, m2);

     addStation(&metroLine1, m1);
     addStation(&metroLine1, m4);
     addStation(&metroLine1, m5);
     addStation(&metroLine1, m3);

     addStation(&metroLine2, m4);
     addStation(&metroLine2, m3);
     addStation(&metroLine2, m1);
     addStation(&metroLine2, m5);
     addStation(&metroLine2, m2);
     addLine(&istanbul, metroLine);
     addLine(&istanbul, metroLine1);
     addLine(&istanbul, metroLine2);
     // printf("%i", metroLine.MetroStations[0].name[0] == '\0');


     MetroStation neighbourstations[] = {};
     getNeighboringStations(istanbul, m3, neighbourstations);

     int i;
     for (i = 0; neighbourstations[i].name[0] != '\0'; ++i) {
         printf("neighbours[%d]: %s\n", i, neighbourstations[i].name);
         // printf("%d. line[%d] %s\n", i + 1, i, metroLine.MetroStations[i].name);
     }
     //addStation(&metroLine, m2);
     //printf("%s", getPreviousStop(metroLine, m2).name);
     //printf("%s", getNextStop(metroLine, m1).name);
     //printLine(metroLine);
     int x = getLastStationIndex(metroLine);
     // printf("%d", x);
     // printf("%i", getFirstStop(metroLine).name[0] == '\0');
     // printf("%i", hasStation(metroLine,m1));
     //printf("%i", hasStation(metroLine,m2));
     //printf("%s %s",metroLine.MetroStations[0].name,metroLine.MetroStations[1].name);*/
    int i;
    double myX = 1, myY = 2;
    double goalX = 62, goalY = 45;

    // define 3 metro lines, 9 metro stations, and an empty myPath
    MetroLine red = {'\0'}, blue = {'\0'}, green = {'\0'};
    MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
    MetroStation myPath[SIZE] = {'\0'};

    strcpy(red.color, "red");
    strcpy(blue.color, "blue");
    strcpy(green.color, "green");


    strcpy(s1.name, "Haydarpasa");
    s1.x = 0;
    s1.y = 0;
    strcpy(s2.name, "Sogutlucesme");
    s2.x = 10;
    s2.y = 5;
    strcpy(s3.name, "Goztepe");
    s3.x = 20;
    s3.y = 10;
    strcpy(s4.name, "Kozyatagi");
    s4.x = 30;
    s4.y = 35;
    strcpy(s5.name, "Bostanci");
    s5.x = 45;
    s5.y = 20;
    strcpy(s6.name, "Kartal");
    s6.x = 55;
    s6.y = 20;
    strcpy(s7.name, "Samandira");
    s7.x = 60;
    s7.y = 40;
    strcpy(s8.name, "Icmeler");
    s8.x = 70;
    s8.y = 15;

    //Add several metro stations to the given metro lines.
    addStation(&red, s1);
    addStation(&red, s2);
    addStation(&red, s3);
    addStation(&red, s4);
    addStation(&red, s5);
    addStation(&red, s8);

    addStation(&blue, s2);
    addStation(&blue, s3);
    addStation(&blue, s4);
    addStation(&blue, s6);
    addStation(&blue, s7);

    addStation(&green, s2);
    addStation(&green, s3);
    addStation(&green, s5);
    addStation(&green, s6);
    addStation(&green, s8);

    // Add red, blue, green metro lines to the Istanbul metro system.
    addLine(&istanbul, red);
    addLine(&istanbul, blue);
    addLine(&istanbul, green);

    // print the content of the red, blue, green metro lines
    printLine(red);
    printLine(blue);
    printLine(green);


    // find the nearest stations to the current and target locations
    MetroStation nearMe = findNearestStation(istanbul, myX, myY);
    MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

    printf("\n");

    printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

    // if the nearest current and target stations are the same, then print a message and exit.
    if (equals(nearMe, nearGoal)) {
        printf("It is better to walk!\n");
        return 0;
    }

    // Calculate and print the myPath with the minimum distance travelled from start to target stations.
    findPath(nearMe, nearGoal, myPath);

    if (strlen(myPath[0].name) == 0)
        printf("There is no path on the metro!\n");
    else {
        printPath(myPath);
    }

    return 0;


}

void printPath(MetroStation *stations) { //prints the stations on given path.
    int i;
    for (i = 0; strlen(stations[i].name) != 0; i++) {
        printf("%d. %s\n", i + 1, stations[i].name);
    }
}
