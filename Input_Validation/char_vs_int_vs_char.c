#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // USED TO DETECT LETTERS
#include <math.h> // USED FOR 'floor()'
#include <unistd.h> // USED FOR 'sleep()'

#define LENGTH (25)
#define SLEEP_TIMER (3) // GLOBAL SLEEP TIMEER


typedef struct route
{
    int o_station;
    int d_station;
    int s_time;
    int e_time;
    int dur;
    struct route *next;
} t_route;


void read_st(FILE *file, char stations[][LENGTH]);
t_route *read_tr(FILE *file, t_route *routes);
t_route *m_r(int o_station, int d_station, int s_time, int e_time);
t_route *a_r(t_route *routes, t_route *new_route);

bool d_r(t_route *routes, int o_station, int d_station);
t_route *s_t(t_route *routes);
void l_r(t_route *routes, char stations[][LENGTH], int time);
int f_s_nu(int num_stations, char stations[][LENGTH], char search_str[LENGTH]);
void f_s_na(char stations[][LENGTH], int station_num, char station_name[LENGTH]);

int c_t_24(int minute_time);
int c_f_24(int time_24);
int l_c(FILE *file);

int main(int argc, char *argv[])
{
    // SYNTAX CHECK
    if(argc != 3)
    {
        printf("Syntax Error: ./a.out <Station_Data> <Train_Data>\n");
        exit(1);
    }

    // DECLARE VARIABLES
    bool verdict; // 'bool' TYPE VARIABLE FOR 'd_r()'
    FILE *sD = NULL; // FILE POINTER
    FILE *tD = NULL; // FILE POINTER
    int userInput = -1; // THE 'while()' LOOP FLAG
    int tempNum; // VARIABLE TO CONVERT TIME
    int sC; // VARIABLE TO STORE THE TOTAL NUMBER OF STATIONS LISTED IN THE INPUT FILE
    int tC = 0; // VARIABLE TO STORE THE TOTAL NUMBER OF TRAINS LISTED IN THE INPUT FILE
    int sNu; // VARIABLE TO STORE THE CORRECT STATION NUMBER
    int clockTime; // VARIABLE TO SEARCH TRAIN ROUTE TIME TABLES
    int oS; // VARIABLE TO USE IN 'd_r()'
    int dS; // VARIABLE TO USE IN 'd_r()'
    int verifyStatus = 0; // VARIABLE TO HELP SANATIZE VALID INPUT
    int dumpInt = 0; // INTEGER DUMP VARIABLE
    char sNa[LENGTH]; // VARIABLE TO STORE THE STATION NAME IF FOUND WITHIN 'f_s_na()' 
    char dump[100]; // CHARACTER DUMP VARIABLE

    // OPEN FILES
    sD = fopen(argv[1], "r");
    tD = fopen(argv[2], "r");

    // FILE COMPATIBILITY CHECK
    if(sD == NULL || tD == NULL)
    {
        printf("Error: Input file(s) did not open.\n");
        exit(1);
    }
    
    // COUNT THE LINES IN EACH INPUT FILE
    sC = l_c(sD);
    tC = l_c(tD);

    // CHECKING IF INPUT FILES WERE BLANK
    if(sC == 0 || tC == 0)
    {
        printf("Error: One or more input files were blank.\n");
        exit(1);
    }

    // DECLARE 2D STATION ARRAY
    char sL[sC][LENGTH];
    
    // READ STATION FILE
    read_st(sD, sL);

    // DECLARE TRAIN 'struct' ARRAY
    t_route *tL = (t_route*)malloc(sizeof(t_route));

    // READ TRAIN FILE
    tL =  read_tr(tD, tL);

    // CLEAR SCREEN
    system("clear");

    // DISPLAY MENU
    while(userInput != 0)
    {
        // DISPLAY MENU
        printf("\n\n------------------------------------------------------\n%20s to the DOOM %-13s\n------------------------------------------------------\n\n", "Welcome", "Program");
        printf("%4d)  Quit\n%4d)  Find a number with a name\n%4d)  Find a name with a number\n%4d)  Do the numbers connect?\n%4d)  Find shortest time\n%4d)  List all ____ after a time (HHMM)\n\n", 0, 1, 2, 3, 4, 5);
        printf("Please pick an option: ");
        scanf("%d", &userInput); 

        // REMOVE NEWLINE CHARACTER FROM 'stdin'
        scanf("%c", dump);

        // MAIN PROGRAM FUNCTIONING IS HERE IN THESE SWITCH CASES
        // THERE IS A LOT OF INPUT SANITIZATION IN THESE CHOICES
        // CURIOUS IF YOU HAVE ADVICE FOR CLEANING IT UP OR SEE SOMETHING I SHOULD AVOID DOING IN THE FUTURE
        // NOT SURE IF I PLANNED FOR EVERY POSSIBLE INCORRECT INPUT
        switch(userInput)
        {
            case 0:
                {
                    // INTENTIONAL PROGRAM EXIT
                    printf("Goodbye!\n");
                    exit(1);
                }
            case 1:
                {
                    printf("Enter a name: ");
                    scanf("%s", sNa);

                    // REMOVE NEWLINE CHARACTER FROM 'stdin'
                    scanf("%c", dump);

                    if(isdigit(*sNa) == false)
                    {
                        if(atoi(sNa) != 0)
                        {
                            // INPUT IS TYPE INTEGER
                            verifyStatus = 0;
                        }
                        else if(atoi(sNa) == 0)
                        {
                            // INPUT IS TYPE CHARACTER
                            verifyStatus = 1;
                        }
                    }
                    else
                    {
                        while(verifyStatus != 1)
                        {
                            printf("Invalid input, please enter a name: ");
                            scanf("%s", sNa);

                            // REMOVE NEWLINE CHARACTER FROM 'stdin'
                            scanf("%c", dump);
                            if(isdigit(*sNa) == false)
                            {
                                // INPUT IS TYPE CHARACTER
                                verifyStatus = 1;
                            }
                        }
                    }
                    sNu = f_s_nu(sC, sL, sNa);
                    if(sNu != -1)
                    {
                        printf(" %s is number %d\n", sNa, sNu);
                    }
                    else
                    {
                        printf(" %s does not exist.\n Make sure there isn't a typing error.\n", sNu);
                    }
                    
                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;
                    sleep(SLEEP_TIMER);

                    break;
                }
            case 2:
                {
                    printf("Enter a #: ");

                    // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                    verifyStatus = scanf("%d", &sNu);

                    // REMOVE NEWLINE CHARACTER FROM 'stdin'
                    scanf("%c", dump);
                    while(verifyStatus != 1)
                    {
                        printf("Invalid input, please enter a #: ");

                        // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                        verifyStatus = scanf("%d", &sNu);

                        // REMOVE NEWLINE CHARACTER FROM 'stdin'
                        scanf("%c", dump);
                    }
                    f_s_na(sL, sNu, sNa);
                    
                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;
                    
                    break;
                }
            case 3:
                {
                    printf("Enter origin number: ");

                    // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                    verifyStatus = scanf("%d", &oS);

                    // REMOVE NEWLINE CHARACTER FROM 'stdin'
                    scanf("%c", dump);
                    while(verifyStatus != 1)
                    {
                        printf("Invalid input, please enter origin number: ");

                        // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                        verifyStatus = scanf("%d", &oS);

                        // REMOVE NEWLINE CHARACTER FROM 'stdin'
                        scanf("%c", dump);
                    }

                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;
                    printf("Enter destination number: ");

                    // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                    verifyStatus = scanf("%d", &dS);

                    // REMOVE NEWLINE CHARACTER FROM 'stdin'
                    scanf("%c", dump);
                    while(verifyStatus != 1)
                    {
                        printf("Invalid input, please enter destination number: ");

                        // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                        verifyStatus = scanf("%d", &dS);

                        // REMOVE NEWLINE CHARACTER FROM 'stdin'
                        scanf("%c", dump);
                    }
                    
                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;
                    verdict = d_r(tL, oS, dS);
                    if(verdict)
                    {
                        printf("There is a direct path between %d and %d\n", oS, dS);
                    }
                    else
                    {
                        printf("There is NOT a direct path between %d and %d\n", oS, dS);
                    }
                    
                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;
                    sleep(SLEEP_TIMER);
                    
                    break;
                }
            case 4: ; // SEMI-COLON TO SEPARATE THE LABEL FROM THE DECLARATION BELOW
                {
                    // DECLARE VARIABLES
                    t_route *shortNode = (t_route*)malloc(sizeof(t_route));
                    
                    shortNode = s_t(tL);

                    // TOTAL MINUTES CONVERTED TO MILITARY TIME
                    oS = c_t_24(shortNode->s_time);
                    dS = c_t_24(shortNode->e_time);

                    printf("The shortest route is from\n %2d: %s @ %d\n", shortNode->o_station, sL[shortNode->o_station], oS);
                    printf("%7s\n %2d: %s @ %d\n", "to", shortNode->d_station, sL[shortNode->d_station], dS);

                    // RELEASE HEAP STACK FROM 'shortNode'
                    free(shortNode);
                    sleep(SLEEP_TIMER);
                    
                    break;
                }
            case 5:
                {
                    printf("Enter earliest starting time in 24-hour format (hhmm): ");
                    //scanf("%d", &clockTime);

                    // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                    verifyStatus = scanf("%d", &clockTime);

                    // REMOVE NEWLINE CHARACTER FROM 'stdin'
                    scanf("%c", dump);

                    // CHECKING RANGE OF MILITARY TIME BEFORE CHECKING VERIFICATION STATUS
                    while(clockTime < 0 || clockTime >= 2401 || verifyStatus != 1)
                    {
                        printf("Invalid input, please enter earliest starting time in 24-hour format (hhmm): ");

                        // 'verifyStatus' FLAG IS SET BASED ON USER INPUT
                        verifyStatus = scanf("%d", &clockTime);

                        // REMOVE NEWLINE CHARACTER FROM 'stdin'
                        scanf("%c", dump);
                    }

                    l_r(tL, sL, clockTime);

                    // RESET 'verifyStatus' FLAG
                    verifyStatus = 0;

                    break;
                }
            default:
                {
                    // RESET TO LOOP IF NO APPROPRIATE SELECTION IS MADE
                    printf("Please choose from the menu [0-5].\n");

                    // RESET 'userInput'
                    if(isalpha(userInput))
                    {
                        userInput = -1;
                    }

                    // PAUSE BEFORE CLEARING SCREEN AND PRINTING THE MENU AGAIN
                    sleep(SLEEP_TIMER);
                    system("clear");

                    break;
                }
            }
        // ADD AN EXTRA LINE TO COPY EXAMPLE LAYOUT EXACTLY
        printf("\n");
    }

    // CLOSE FILES
    fclose(sD);
    fclose(tD);


    return 0;
}


void read_st(FILE *file, char stations[][LENGTH])
{

    // DECLARE VARIABLES
    int loopCount = 0;
    int sNu; // LISTED IN 'file'
    char lineDump[100]; // DUMP FOR TEXT LINES
    char charDump[LENGTH]; // DUMP FOR CHARACTERS

    while(fgets(lineDump, sizeof(lineDump), file) != NULL)
    {
        sscanf(lineDump, "%d %s", &sNu, charDump);

        if(sNu == loopCount)
        {
            // POPULATE 'stations' SINCE THE STATION'S NUMBER MATCHES 'loopCount'
            sscanf(charDump, "%s", stations[loopCount]);
            loopCount++;
        }
        else
        {
            // POPULATE 'stations' IN THE ORDER OF THE STATION'S NUMBER LISTED IN 'file'
            int tempCount = 0;
            while(sNu != tempCount)
            {
                tempCount++;
            }
            sscanf(charDump, "%s", stations[tempCount]);
            loopCount++;
        }
    }
}

t_route *read_tr(FILE *file, t_route *routes)
{

    // DECLARE VARIABLES
    int tempO; // TEMP VARIABLE TO SEND TO 'm_r()'
    int tempD; // TEMP VARIABLE TO SEND TO 'm_r()'
    int tempS; // TEMP VARIABLE TO SEND TO 'm_r()'
    int tempE; // TEMP VARIABLE TO SEND TO 'm_r()'
    char lineDump[100]; // DUMP FOR TEXT LINES
    t_route *newNode = (t_route*)malloc(sizeof(t_route));
    
    // POPULATE FIRST NODE
    fgets(lineDump, sizeof(lineDump), file);
    sscanf(lineDump, "%d %d %d %d", &routes->o_station, &routes->d_station, &routes->s_time, &routes->e_time);
    routes->dur = (routes->e_time - routes->s_time);
    
    // POPULATE THE REST OF THE LINKEDLIST THROUGH 'm_r()'
    while(fgets(lineDump, sizeof(lineDump), file) != NULL)
    {
        sscanf(lineDump, "%d %d %d %d", &tempO, &tempD, &tempS, &tempE);

        newNode = m_r(tempO, tempD, tempS, tempE);
        newNode = a_r(routes, newNode);
    }
    
    // ADDING A FILLER NODE TO THE END IN ORDER TO PRINT ALL ENTRIES BY FINISHING INPUT AT THE SECOND-BEFORE-LAST ARRAY INDEX POSITION
    // THIS IS MY SOLUTION TO A STRANGE DATA CORRUPTION I ENCOUNTERED ON REPL AFTER PASSING THE LINKEDLIST AROUND TO DIFFERENT FUNCTIONS
    newNode = m_r(-1, -1, -1, -1);
    newNode = a_r(routes, newNode);


    return routes;
}

t_route *m_r(int o_station, int d_station, int s_time, int e_time)
{

    // DECLARE VARIABLES
    t_route *newNode = (t_route*)malloc(sizeof(t_route));

    // POPULATE 'newNode' DATA MEMBERS
    newNode->o_station = o_station;
    newNode->d_station = d_station;
    newNode->s_time = s_time;
    newNode->e_time = e_time;
    newNode->dur = (newNode->e_time - newNode->s_time);
    newNode->next = NULL;

    
    return newNode;
}

t_route *a_r(t_route *routes, t_route *new_route)
{

    // DECLARE VARIABLES
    t_route *tmp = routes;

    if(routes == NULL)
    {
        // CHECK FOR 'NULL' VALUE ON 'routes'
        routes = new_route;
    }
    else
    {
        // CYCLE TO END OF LIST THROUGH SECONDARY POINTER
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
    }
    
    // LINK THE NEXT NODE THROUGH SECONDARY POINTER
    tmp->next = new_route;

    
    return routes;
}

bool d_r(t_route *routes, int o_station, int d_station)
{

    // DECLARE VARIABLES
    t_route *tmp = routes;

    while(tmp->next != NULL)
    {
        if(tmp->o_station == o_station && tmp->d_station == d_station)
        {
            // A DIRECT ROUTE BETWEEN 'o_station' AND 'd_station' WAS FOUND
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    // NO DIRECT ROUTE BETWEEN 'o_station' AND 'd_station' WAS FOUND
    return false;
}

t_route *s_t(t_route *routes)
{

    // DECLARE VARIABLES
    t_route *newNode = (t_route*)malloc(sizeof(t_route));
    t_route *tmp = routes;
    int *shortestDuration = (int*)malloc(sizeof(int));

    // INITIALIZING 'shortestDuration'
    shortestDuration = &tmp->dur;

    while(tmp->next != NULL)
    {
        // CHANGE 'shortestDuration'
        if(tmp->dur <= *shortestDuration)
        {
            *shortestDuration = tmp->dur;
            newNode = tmp;
        }
        
        // LINK THE NEXT NODE THROUGH SECONDARY POINTER
        tmp = tmp->next;
    }


    return newNode;
}

void l_r(t_route *routes, char stations[][LENGTH], int time)
{

    // DECLARE VARIABLES
    t_route *tmp = routes;
    int convertedStart;
    int convertedEnd;

    while(tmp->next != NULL)
    {
        convertedStart = c_t_24(tmp->s_time);
        convertedEnd = c_t_24(tmp->e_time);
        
        if(convertedStart >= time && tmp->next != NULL)
        {
            printf("%2d: %-15s@ %4d  to%4d: %-15s@ %4d\n", tmp->o_station, stations[tmp->o_station], convertedStart, tmp->d_station, stations[tmp->d_station], convertedEnd);
        }
        
        // LINK THE NEXT NODE THROUGH SECONDARY POINTER        
        tmp = tmp->next;
    }
    sleep(SLEEP_TIMER);
}

int f_s_nu(int num_stations, char stations[][LENGTH], char search_str[LENGTH])
{

    for(int i = 0; i < num_stations; ++i)
    {
        if(strcmp(stations[i], search_str) == 0)
        {
            // MATCH FOR 'search_str' FOUND
            return i;
        }
        else
        {
            continue;
        }
    }

    // NO MATCH FOR 'search_str' FOUND
    return -1;
}

void f_s_na(char stations[][LENGTH], int station_num, char station_name[LENGTH])
{

    // INITIALIZE 'station_name' VARIABLE
    station_name = stations[station_num];
    
    if(strlen(station_name) > 0)
    {
        // 'station_name' FOUND
        printf("Station %d is %s\n", station_num, station_name);
        sleep(SLEEP_TIMER);
    }
    else
    {
        // 'station_name' NOT FOUND
        printf("Station does not exist\n");
        sleep(SLEEP_TIMER);
    }
}


int c_t_24(int minute_time)
{

    // DECLARE VARIABLES
    int intHour = 0;
    int intMin = 0;
    int convertedTime;
    char charHour[100];
    char charMin[100];

    intMin = minute_time;

    // IF CONVERSION IS WITHOUT REMAINDERS
    if((minute_time % 60) == 0)
    {
        convertedTime = (minute_time / 60);
        convertedTime *= 100;
    }
    // IF CONVERSION IS WITH REMAINDERS
    else
    {
        // DIVIDE TOTAL MINUTES BY 1 HOUR (60 MINUTES)
        while(intMin > 60)
        {
            intHour++;
            intMin -= 60;
        }
    
        // CONVERT HOURS AND MINUTES TO STRINGS TO CONCATENATE TO 'HHMM' MILITARY TIME FORMAT
        sprintf(charHour, "%02d", intHour);
        sprintf(charMin, "%02d", intMin);
        strcat(charHour, charMin);

        // CONVERT CONCATENATED STRING TO INTEGER TYPE
        convertedTime = atoi(charHour);
    }


    return convertedTime;
}

int c_f_24(int time_24)
{

    // DECLARE VARIABLES
    int intHour = 0;
    int intMin = 0;
    int totalMinutes = 0;
    char dump[100];
    char charHour[100];
    char charMin[100];

    // CONVERT 'time_24' TO STRING
    snprintf(dump, sizeof(dump), "%d", time_24);

    for(int i = 0; i < 4; ++i)
    {
        if(i < 2)
        {
            // SEPARATE HOUR DIGITS (1st TWO DIGITS) TO 'hours'
            charHour[i] = dump[i];
        }
        else if(i >= 2)
        {
            // SEPARATE MINUTE DIGITS (LAST TWO DIGITS) TO 'minutes'
            charMin[i - 2] = dump[i];
        }
    }

    // FORCE THE NULL TERMINATORS TO THE END OF EACH C-STRING
    charHour[2] = '\0';
    charMin[2] = '\0';

    // CONVERT STRING TO INT
    intHour = atoi(charHour);
    intMin = atoi(charMin);

    // TOTAL UP THE MINUTES
    totalMinutes += intHour * 60;
    totalMinutes += intMin;


    return totalMinutes;
}

int l_c(FILE *file)
{

    // DECLARE VARIALBES
    int loopCount = 0;
    char dump[100];

    while(fgets(dump, sizeof(dump), file) != NULL)
    {
        loopCount++;
    }

    // RESETTING CURSOR POSITION
    rewind(file);


    return loopCount;
}