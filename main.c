#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Airport *linePrint(char line[],FILE *fp, struct Airport *airports, int i);
void loadData(struct Airport *airports, int numAirports);
void searchAirport(struct Airport *airports, struct Airport *selectedAirport, int numAirports);
void dispCurrentMenu(int currentMenu);
struct traveller *addTraveller(struct traveller *pT, int *numTravellers);
struct flight *addFlight(struct flight *pF, int *numFlights, struct Airport *airports, int numAirports, int *eventID);
struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation, int *eventID);
struct insurance *addInsurance(struct insurance *pI, int *numInsurance);
struct Date {
    int year;
    int month;
    int day;
};
void printPreview(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance, struct Date *dates);
void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance);
int length(char *arr);

struct Date *allocateDays(struct flight*pF, struct accommodation *pA, int numFlights, int numAccommodation, struct Date *dates);

void day2Date(char inpDate[], struct Date *date);
//Itinerary
/*
day 1 - 23/10/2023
flight EMA->PMI
Check In at Test Hotel
Activity 1
day 2...

*/



struct Airport {
    char name[60];
    char city[40];
    char country[200];
    char code[10];
    char code2[10];
};

struct traveller{
    char name[30];
    int age;
    char phoneNumber[18];
};

struct flight{
    char type[13];
    char depApt[44];
    char arrApt[44];
    char depTime[5];
    char arrTime[5];
    char date[11];
    char airline[30];
    char flightNumber[20];
    int day;
    int tag;
};

struct accommodation{
    char address[100];
    char name [30];
    char dateCI[11];
    char dateCO[11];
    int dayCI;
    int dayCO;
    int tag;
};

struct insurance{
    char name[30];
    char reference[30];
    char number[18];
};

int main()
{
    int numTravellers = 0;
    int numFlights = 0;
    int numAccommodation = 0;
    int numInsurance = 0;
    int numAirports = 7698; //Numbers in data file are not complete, skips many numbers
    int eventID = 0;


    //Allocate memory to structures
    struct traveller *pT = (struct traveller *)malloc(numTravellers*sizeof(struct traveller));
    struct flight *pF = (struct flight *)malloc(numFlights*sizeof(struct flight));
    struct accommodation *pA = (struct accommodation *)malloc(numAccommodation*sizeof(struct accommodation));
    struct insurance *pI = (struct insurance *)malloc(numInsurance*sizeof(struct insurance));
    struct Airport *airports = (struct Airport*)malloc(numAirports*sizeof(struct Airport));
    struct Date *dates = NULL;

    char option, dum;
    int currentMenu = 0, finish = 0;

    loadData(airports,numAirports);


    while(finish==0){

        dispCurrentMenu(currentMenu);//day2Date("03/12/1998", dates);  //For testing
        printf("%d\n",eventID);
        printf("Press a to add item, w or s to navigate menu, p to print preview, q to print. Please Enter an Option:\n");
        scanf(" %c", &option);
        switch(option){
            case 'a':
                switch(currentMenu){
                case 0:
                    pT = addTraveller(pT,&numTravellers);
                    break;
                case 1:
                    pF = addFlight(pF, &numFlights, airports, numAirports, &eventID);
                    break;
                case 2:
                    pA = addAccommodation(pA, &numAccommodation, &eventID);
                    break;
                case 3:
                    pI = addInsurance(pI, &numInsurance);
                    break;
                }
                system("cls");
                break;
            case 'w':
                currentMenu -= 1;
                if(currentMenu==-1){
                    currentMenu = 3;
                }
                system("cls");
                break;
            case 's':
                currentMenu += 1;
                if(currentMenu==4){
                    currentMenu = 0;
                }
                system("cls");
                break;
            case 'p':
                system("cls");
                dates = allocateDays(pF,pA,numFlights,numAccommodation,dates);
                printPreview(pT, pF, pA, pI, numTravellers, numFlights, numAccommodation, numInsurance, dates);
                printf("\n\nEnter any character to continue:\n");
                scanf(" %c",&dum);
                break;

            case 'q':
                finish = 1;

                break;

            default:
                printf("Type one of the above options.\n");

        }
    }
    createDoc(pT, pF, pA, pI, numTravellers, numFlights, numAccommodation, numInsurance);
    free(pT);
    free(pF);
    free(pA);
    free(pI);
    free(airports);


    return 0;
}

void day2Date(char inpDate[], struct Date *date){
    int testNum = atoi("1234");
    char yearStr[5];
    char monthStr[3];
    char dayStr[3];
    yearStr[4] = '\0', monthStr[2] = '\0', dayStr[2] = '\0';
    int year;
    int month;
    int day;

    for(int i=0;i<2;i++){
        dayStr[i] = inpDate[i];
        monthStr[i] = inpDate[i+3];
        yearStr[i] = inpDate[i+6];
    }
    yearStr[2] = inpDate[8];yearStr[3] = inpDate[9];

    date->year = atoi(yearStr);
    date->month = atoi(monthStr);
    date->day = atoi(dayStr);

}

struct Date *allocateDays(struct flight *pF, struct accommodation *pA, int numFlights, int numAccommodation, struct Date *dates){
    //Assign each event to a particular day of the trip
    int numEvents = numFlights + numAccommodation;
    if(dates != NULL && numEvents>0){
        printf("Reallocate dates\n");
        dates = (struct Date*)realloc(dates,numEvents*sizeof(struct Date));
    } else if(dates == NULL){
        printf("Allocate dates\n");
        dates = (struct Date*)malloc(numEvents*sizeof(struct Date));
    }

    if(numEvents > 0){

    }


    return dates;
}

int length(char *arr){
    //Calculate length of array before \n character
    int len = 0;
    while(arr[len] != '\n') {
        len++;
    }
    return len;
}

void printPreview(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance, struct Date *dates){
    char airportNames[93];
    //Travellers
    printf("Travellers\n");
    printf("-------------------\n");
    printf("%-30s%-6s%-12s\n\n", "Name", "Age", "Phone Number");
    for(int i=0;i<numTravellers;i++){
        printf("%-30s%-6d%-18s\n", pT[i].name, pT[i].age,pT[i].phoneNumber); // write the string to the screen

    }
    printf("\n");

    //Flights
    printf("Flights\n");
    printf("-------------------\n");
    printf("%-14s%-93s%-13s%-13s%-30s%-20s\n\n","Type", "Airport", "Time", "Date", "Airline", "Flight Number");
    for(int i=0;i<numFlights;i++){
        sprintf(airportNames,"%s -> %s",pF[i].depApt,pF[i].arrApt);
        printf("%-14s%-93s%s->%-7s%-13s%-30s%-20s\n", pF[i].type, airportNames, pF[i].depTime,pF[i].arrTime, pF[i].date, pF[i].airline, pF[i].flightNumber);
    }
    printf("\n");

    //Accommodation
    printf("Accommodation\n");
    printf("-------------------\n");
    for(int i=0;i<numAccommodation;i++){
        printf("%s\n", pA[i].name); // write the string to the file
        printf("%s\n", pA[i].address);
        printf("%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }

    //Travel Insurance
    printf("Travel Insurance\n");
    printf("-------------------\n");
    printf("%-30s%-30s%-25s\n\n","Name", "Policy Number", "Emergency Contact Number");
    for(int i=0;i<numInsurance;i++){
        printf("%-30s%-30s%-25s\n",pI[i].name,pI[i].reference,pI[i].number);
    }

    //Itinerary
    printf("Itinerary\n");
    printf("-------------------\n");

}

void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance){
    FILE *fp;
    char airportNames[93];
    fp = fopen("output.txt", "w"); // open the file in write mode

    if (fp == NULL) { // error checking
        printf("Error opening file\n");
        exit(1);
    }
    //Travellers
    fprintf(fp, "Travellers\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp, "%-30s%-6s%-12s\n\n", "Name", "Age", "Phone Number");
    for(int i=0;i<numTravellers;i++){
        fprintf(fp, "%-30s%-6d%-18s\n", pT[i].name, pT[i].age,pT[i].phoneNumber); // write the string to the file

    }
    fprintf(fp, "\n");

    //Flights
    fprintf(fp, "Flights\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp,"%-14s%-93s%-13s%-13s%-30s%-20s\n\n","Type", "Airport", "Time", "Date", "Airline", "Flight Number");
    for(int i=0;i<numFlights;i++){
        sprintf(airportNames,"%s -> %s",pF[i].depApt,pF[i].arrApt);
        fprintf(fp, "%-14s%-93s%s->%-7s%-13s%-30s%-20s\n", pF[i].type, airportNames, pF[i].depTime,pF[i].arrTime, pF[i].date, pF[i].airline, pF[i].flightNumber);
    }
    fprintf(fp, "\n");

    //Accommodation
    fprintf(fp, "Accommodation\n");
    fprintf(fp, "-------------------\n");
    for(int i=0;i<numAccommodation;i++){
        fprintf(fp, "%s\n", pA[i].name); // write the string to the file
        fprintf(fp, "%s\n", pA[i].address);
        fprintf(fp,"%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }

    //Travel Insurance
    fprintf(fp, "Travel Insurance\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp,"%-30s%-30s%-25s\n\n","Name", "Policy Number", "Emergency Contact Number");
    for(int i=0;i<numInsurance;i++){
        fprintf(fp,"%-30s%-30s%-25s\n",pI[i].name,pI[i].reference,pI[i].number);
    }

    fclose(fp);

}

struct insurance *addInsurance(struct insurance *pI, int *numInsurance){
    (*numInsurance)++;
    pI = realloc(pI,*numInsurance*sizeof(struct insurance));

    printf("Enter Insurance Company Name:\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    // Read the name string
    fgets(pI[*numInsurance-1].name, 30, stdin);
    pI[*numInsurance-1].name[length(pI[*numInsurance-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Policy Number:\n");
    scanf(" %s", pI[*numInsurance-1].reference);
    printf("Enter an Emergency Contact Number for the Insurance Company:\n");
    scanf(" %s", pI[*numInsurance-1].number);

    return pI;
}

struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation, int *eventID){

    (*numAccommodation)++;
    pA = realloc(pA,*numAccommodation*sizeof(struct accommodation));

    printf("Enter Accommodation Name:\n");

    int c;

    while ((c = getchar()) != '\n' && c != EOF){ }

    // Read the name string
    fgets(pA[*numAccommodation-1].name, 30, stdin);
    pA[*numAccommodation-1].name[length(pA[*numAccommodation-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Address, with each line separated by a comma:\n");
    // Read the name string
    fgets(pA[*numAccommodation-1].address, 100, stdin);
    pA[*numAccommodation-1].address[length(pA[*numAccommodation-1].address)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Check In Date:\n");
    scanf(" %s",pA[*numAccommodation-1].dateCI);
    printf("Enter Check Out Date:\n");
    scanf(" %s",pA[*numAccommodation-1].dateCO);

    (*eventID)++;
    pA[*numAccommodation-1].tag = eventID;

    return pA;
}
struct flight *addFlight(struct flight *pF, int *numFlights, struct Airport *airports, int numAirports, int *eventID){
    struct Airport *selectedAirport = (struct Airport*)malloc(sizeof(struct Airport));

    (*numFlights)++;
    pF = realloc(pF,*numFlights*sizeof(struct flight));
    printf("Enter Flight Type (Outbound, Inbound, or Intermediate):\n");
    scanf(" %s",pF[*numFlights-1].type);
    printf("Departing Airport\n");
    searchAirport(airports, selectedAirport, numAirports);
    if(strcmp(selectedAirport->code,"\\N")==0){
        sprintf(pF[*numFlights-1].depApt,"%s (%s)",selectedAirport->name,selectedAirport->code2);
    }else{
        sprintf(pF[*numFlights-1].depApt,"%s (%s)",selectedAirport->name,selectedAirport->code);
    }
    printf("Destination Airport\n");
    searchAirport(airports, selectedAirport, numAirports);

    if(strcmp(selectedAirport->code,"\\N")==0){
        sprintf(pF[*numFlights-1].arrApt,"%s (%s)",selectedAirport->name,selectedAirport->code2);
    }else{
        sprintf(pF[*numFlights-1].arrApt,"%s (%s)",selectedAirport->name,selectedAirport->code);
    }

    printf("Enter Takeoff Time:\n");
    scanf(" %s",pF[*numFlights-1].depTime);
    printf("Enter Landing Time:\n");
    scanf(" %s",pF[*numFlights-1].arrTime);
    printf("Enter Date of Flight:\n");
    scanf(" %s",pF[*numFlights-1].date);
    printf("Enter Airline: \n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    //Read the name string
    fgets(pF[*numFlights-1].airline, 30, stdin);
    pF[*numFlights-1].airline[length(pF[*numFlights-1].airline)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Flight Number:\n");
    scanf(" %s",pF[*numFlights-1].flightNumber);

    free(selectedAirport);
    (*eventID)++;
    pF[*numFlights-1].tag = eventID;

    return pF;
}

struct traveller *addTraveller(struct traveller *pT, int *numTravellers){

    (*numTravellers)++;
    pT = realloc(pT,*numTravellers*sizeof(struct traveller));
    printf("Enter traveller name:\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    // Read the name string
    fgets(pT[*numTravellers-1].name, 30, stdin);
    pT[*numTravellers-1].name[length(pT[*numTravellers-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Traveller Age: \n");
    scanf(" %d", &pT[*numTravellers-1].age);
    printf("Enter traveller phone number: \n");
    scanf("%s", pT[*numTravellers-1].phoneNumber);


    return pT;
}

void loadData(struct Airport *airports, int numAirports){
    FILE *fp;
    char filename[] = "airports.txt";
    char line[500];


    //Read data file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for(int i=0;i<numAirports;i++){
        fgets(line, 500, fp);
        airports = linePrint(line, fp, airports, i);
    }
    //Close the file when done
    fclose(fp);

}

struct Airport *linePrint(char line[],FILE *fp, struct Airport *airports, int i){
    //Takes in a line, separates into tokens, prints only the chosen tokens onto line in a new file
    char *token;
    char name[60], city[40], country[200], code[10], code2[10];
    int tokenIndex = 0;

    token = strtok(line, "\t\"");   //Split string into tokens separated by ','
        while (token != NULL) {


            switch(tokenIndex){
                case 0:
                    strcpy(airports[i].name,token);
                    break;
                case 1:
                    strcpy(airports[i].city,token);
                    break;
                case 2:
                    strcpy(airports[i].country,token);
                    break;
                case 3:
                    strcpy(airports[i].code,token);
                    break;
                case 4:
                    strcpy(airports[i].code2,token);
                    break;
            }
            //printf("%s\n",token);
            token = strtok(NULL, "\t\"");  //Store each token into respective variables
            tokenIndex++;
        }

        tokenIndex = 0;
        return airports;
}

void searchAirport(struct Airport *airports, struct Airport *selectedAirport, int numAirports){

    char inpCity[40], input[10], menuDisplayLine[64];
    int airportCount = 0, satisfied = 0, airportSelection, inpCityLength;
    int *airportIndexArray = (int*)malloc((airportCount)*sizeof(int));
    while (getchar() != '\n') {}
    while(satisfied != 1){

        printf("Enter some letters of City/Region\n");

        fgets(inpCity,40,stdin);
        inpCity[length(inpCity)] = '\0';
        inpCityLength = strlen(inpCity);
        for(int i=0;i<numAirports;i++){

            if(strncmp(inpCity,airports[i].city,inpCityLength)==0){
                airportCount++;
                airportIndexArray = realloc(airportIndexArray,airportCount*sizeof(int));
                airportIndexArray[airportCount-1] = i;
                sprintf(menuDisplayLine,"%d) %s",airportCount,airports[i].name);
                printf("%-64s-\t%s, %s\n",menuDisplayLine, airports[i].city, airports[i].country);

            }
        }
        if(airportCount==0){
            printf("Sorry, no airports were found associated with that place.\n");
        }
        while(airportCount>0){

            printf("Enter the number corresponding to your chosen airport, or 0 to search a different region:\n");
            scanf(" %d", &airportSelection);
            while (getchar() != '\n') {}
            if(airportSelection <= airportCount && airportSelection > 0){
                memcpy(selectedAirport, &airports[airportIndexArray[airportSelection-1]], sizeof(struct Airport));
                printf("You chose: %s\n",selectedAirport->name);
                satisfied = 1;
                break;
            }else if(airportSelection == 0){
                break;
            }
            else{
                printf("Please enter a valid number.\n");
                while (getchar() != '\n') {}
            }
        }
        airportCount = 0;
    }

    free(airportIndexArray);

}

void dispCurrentMenu(int currentMenu){
    switch(currentMenu){
        case 0:
            printf("Travellers\n");
            printf("-------------------\n\n");
            break;
        case 1:
            printf("Flights\n");
            printf("-------------------\n\n");
            break;
        case 2:
            printf("Accommodation\n");
            printf("-------------------\n\n");
            break;
        case 3:
            printf("Travel Insurance\n");
            printf("-------------------\n\n");
            break;
    }

}
