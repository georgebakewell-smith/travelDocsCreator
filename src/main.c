#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Airport *linePrint(char line[],FILE *fp, struct Airport *airports, int i);
void loadData(struct Airport *airports, int numAirports);
void searchAirport(struct Airport *airports, struct Airport *selectedAirport, int numAirports);
void dispCurrentMenu(int currentMenu);
struct traveller *addTraveller(struct traveller *pT, int *numTravellers);
struct flight *addFlight(struct flight *pF, int *numFlights, struct Airport *airports, int numAirports, int *eventID);
struct train *addTrain(struct train *pS,int *numTrains, int *eventID);
struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation, int *eventID);
struct insurance *addInsurance(struct insurance *pI, int *numInsurance);
struct Date{
    int year;
    int month;
    int day;
    int time;
    int dateConcat;
    int eventID;
    int dayOfTrip;
    char description[200];
};

void printPreview(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, struct train *pS, int numTravellers, int numFlights, int numAccommodation, int numInsurance, int numTrains, struct Date *dates);
void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, struct train *pS, int numTravellers, int numFlights, int numAccommodation, int numInsurance, int numTrains, struct Date *dates);
int length(char *arr);

struct Date *allocateDays(struct flight*pF, struct accommodation *pA, struct train *pS, int numFlights, int numAccommodation, int numTrains, struct Date *dates);

void day2Date(char inpDate[], char inpTime[], struct Date *date);
void freeTrain(struct train *pS, int numTrains);

struct Airport{
    char name[60];
    char city[40];
    char country[200];
    char code[10];
    char code2[10];
};

struct train{
    int numStops;
    char date[11];
    char *station[5];
    char *arrTime[5];
    char *depTime[5];
    char description[200];
    int tag;
};

struct traveller{
    char name[30];
    int age;
    char phoneNumber[18];
    char passportNumber[30];
};

struct flight{
    char type[13];
    char depApt[60];
    char arrApt[60];
    char depTime[5];
    char arrTime[5];
    char date[11];
    char airline[30];
    char flightNumber[20];
    char description[200];
    int tag;
};

struct accommodation{
    char address[100];
    char name [60];
    char dateCI[11];
    char dateCO[11];
    char descriptionCI[200];
    char descriptionCO[200];
    int tag;

};

struct insurance{
    char name[30];
    char reference[30];
    char number[18];
};

const int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{
    int numTravellers = 0;
    int numFlights = 0;
    int numAccommodation = 0;
    int numInsurance = 0;
    int numTrains = 0;
    int numAirports = 7698; //Numbers in data file are not complete, skips many numbers
    int eventID = 0;
    int transportChoice;


    //Allocate memory to structures
    struct traveller *pT = (struct traveller*)malloc(numTravellers*sizeof(struct traveller));
    struct flight *pF = (struct flight*)malloc(numFlights*sizeof(struct flight));
    struct accommodation *pA = (struct accommodation*)malloc(numAccommodation*sizeof(struct accommodation));
    struct insurance *pI = (struct insurance*)malloc(numInsurance*sizeof(struct insurance));
    struct Airport *airports = (struct Airport*)malloc(numAirports*sizeof(struct Airport));
    struct train *pS = (struct train*)malloc(numTrains*sizeof(struct train));
    struct Date *dates = NULL;

    char option, dum;
    int currentMenu = 0, finish = 0;

    loadData(airports,numAirports);


    while(finish==0){

        dispCurrentMenu(currentMenu);
        printf("Press a to add item, w or s to navigate menu, p to print preview, q to print. Please Enter an Option:\n");
        scanf(" %c", &option);
        switch(option){
            case 'a':
                switch(currentMenu){
                case 0:
                    pT = addTraveller(pT,&numTravellers);
                    break;
                case 1:
                    printf("Press 1 to add flights, 2 to add train.\n");
                    scanf(" %d",&transportChoice);
                    if(transportChoice==1){
                        pF = addFlight(pF, &numFlights, airports, numAirports, &eventID);
                    } else{
                        pS = addTrain(pS,&numTrains, &eventID);
                    }
                    break;
                case 2:
                    pA = addAccommodation(pA, &numAccommodation, &eventID);
                    break;
                case 3:
                    pI = addInsurance(pI, &numInsurance);
                    break;
                }
                system("clear");
                break;
            case 'w':
                currentMenu -= 1;
                if(currentMenu==-1){
                    currentMenu = 3;
                }
                system("clear");
                break;
            case 's':
                currentMenu += 1;
                if(currentMenu==4){
                    currentMenu = 0;
                }
                system("clear");
                break;
            case 'p':
                system("clear");
                dates = allocateDays(pF,pA,pS,numFlights,numAccommodation, numTrains,dates);
                printPreview(pT, pF, pA, pI, pS, numTravellers, numFlights, numAccommodation, numInsurance, numTrains, dates);
                printf("\n\nEnter any character to continue:\n");
                scanf(" %c",&dum);
                break;

            case 'q':
                finish = 1;
                dates = allocateDays(pF,pA,pS,numFlights,numAccommodation, numTrains,dates);
                createDoc(pT, pF, pA, pI, pS, numTravellers, numFlights, numAccommodation, numInsurance, numTrains, dates);
                break;

            default:
                printf("Type one of the above options.\n");

        }
    }

    free(pT);
    free(pF);
    free(pA);
    free(pI);
    freeTrain(pS,numTrains);
    free(airports);
    free(dates);


    return 0;
}

void freeTrain(struct train *pS, int numTrains){
    for(int i=0;i<numTrains;i++){
        for(int j=0;j<pS[i].numStops;j++){
            free(pS[i].station[j]);
            if(j<pS[i].numStops-1){free(pS[i].depTime[j]);}
            free(pS[i].arrTime[j]);
        }
    }
    free(pS);
}

void day2Date(char inpDate[], char inpTime[], struct Date *date){
    char dateConcat[11];
    char yearStr[5];
    char monthStr[3];
    char dayStr[3];
    yearStr[4] = '\0', monthStr[2] = '\0', dayStr[2] = '\0';
    int year;
    int month;
    int day;
    int time;

    for(int i=0;i<2;i++){
        dayStr[i] = inpDate[i];
        monthStr[i] = inpDate[i+3];
        yearStr[i] = inpDate[i+6];
    }
    yearStr[2] = inpDate[8];yearStr[3] = inpDate[9];

    sprintf(dateConcat,"%s%s%s%c%c",yearStr ,monthStr, dayStr, inpTime[0], inpTime[1]);

    date->year = atoi(yearStr);
    date->month = atoi(monthStr);
    date->day = atoi(dayStr);
    date->time = atoi(inpTime);

    date->dateConcat = atoi(dateConcat);
}

struct Date *allocateDays(struct flight *pF, struct accommodation *pA, struct train *pS, int numFlights, int numAccommodation, int numTrains, struct Date *dates){
    //Assign each event to a particular day of the trip
    int numEvents = numFlights + 2*numAccommodation + numTrains, numSwaps=0, tempID, tempDate, tempDay, tempMonth, tempYear;
    char tempDescription[200];
    if(dates != NULL && numEvents>0){
        dates = (struct Date*)realloc(dates,numEvents*sizeof(struct Date));
    } else if(dates == NULL){
        dates = (struct Date*)malloc(numEvents*sizeof(struct Date));
    }

    if(numEvents > 0){
        for(int i=0;i<numFlights;i++){
            day2Date(pF[i].date, pF[i].depTime,&dates[i]);
            dates[i].eventID = pF[i].tag;
            sprintf(dates[i].description,"%s",pF[i].description);
        }


        for(int i=0;i<numAccommodation;i++){
            day2Date(pA[i].dateCI, "9999",&dates[i+numFlights]);
            dates[i+numFlights].eventID = pA[i].tag;
            sprintf(dates[i+numFlights].description,"%s",pA[i].descriptionCI);
            day2Date(pA[i].dateCO,"0000" ,&dates[i+numFlights+numAccommodation]);
            dates[i+numFlights+numAccommodation].eventID = pA[i].tag;
            sprintf(dates[i+numFlights+numAccommodation].description,"%s",pA[i].descriptionCO);
        }

        for(int i=0;i<numTrains;i++){
            day2Date(pS[i].date,pS[i].depTime[0] ,&dates[i+numFlights+2*numAccommodation]);
            dates[i+numFlights+2*numAccommodation].eventID = pS[i].tag;
            sprintf(dates[i+numFlights+2*numAccommodation].description,"%s",pS[i].description);
        }

        int i=0;
        do{

            if(i==numEvents-1){
                i = 0;
                if(numSwaps==0){
                    break;
                }
                numSwaps = 0;
            }
            if(dates[i].dateConcat>dates[i+1].dateConcat){
                numSwaps++;
                tempDate = dates[i].dateConcat;
                tempID = dates[i].eventID;
                sprintf(tempDescription,"%s\0",dates[i].description);
                tempYear = dates[i].year;
                tempMonth = dates[i].month;
                tempDay = dates[i].day;
                dates[i].dateConcat = dates[i+1].dateConcat;
                dates[i].eventID = dates[i+1].eventID;
                sprintf(dates[i].description,"%s\0",dates[i+1].description);
                dates[i].year = dates[i+1].year;
                dates[i].month = dates[i+1].month;
                dates[i].day = dates[i+1].day;
                dates[i+1].dateConcat = tempDate;
                dates[i+1].eventID = tempID;
                sprintf(dates[i+1].description,"%s\0",tempDescription);
                dates[i+1].year = tempYear;
                dates[i+1].month = tempMonth;
                dates[i+1].day = tempDay;

            }

            i++;
        }while(1);

        for(int i=0;i<numEvents;i++){
            if(i==0){
                dates[i].dayOfTrip = 1;
            } else if(dates[i].dateConcat/100==dates[i-1].dateConcat/100){
                dates[i].dayOfTrip = dates[i-1].dayOfTrip;
            } else{
                dates[i].dayOfTrip = (dates[i].dateConcat/100-dates[i-1].dateConcat/100)%(100-daysInMonths[dates[i-1].month-1]) + dates[i-1].dayOfTrip;
            }
        }
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

void printPreview(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, struct train *pS, int numTravellers, int numFlights, int numAccommodation, int numInsurance, int numTrains, struct Date *dates){
    char airportNames[93];
    //Travellers
    printf("Travellers\n");
    printf("-------------------\n");
    printf("%-30s%-6s%-18s%-30s\n\n", "Name", "Age", "Phone Number","Passport Number");
    for(int i=0;i<numTravellers;i++){
        printf("%-30s%-6d%-18s%-30s\n", pT[i].name, pT[i].age,pT[i].phoneNumber, pT[i].passportNumber); // write the string to the screen

    }
    printf("\n\n");

    //Flights
    printf("Flights\n");
    printf("-------------------\n");
    printf("%-14s%-93s%-13s%-13s%-30s%-20s\n\n","Type", "Airport", "Time", "Date", "Airline", "Flight Number");
    for(int i=0;i<numFlights;i++){
        sprintf(airportNames,"%s -> %s",pF[i].depApt,pF[i].arrApt);
        printf("%-14s%-93s%s->%-7s%-13s%-30s%-20s\n", pF[i].type, airportNames, pF[i].depTime,pF[i].arrTime, pF[i].date, pF[i].airline, pF[i].flightNumber);
    }
    printf("\n\n");

    //Trains
    if(numTrains != 0){
        printf("Trains\n");
        printf("-------------------\n");
        printf("%-14s%-30s%-17s%-30s%-8s\n\n","Date","Departing Station","Departing Time","Arrival Station","Arrival Time");
        for(int i=0;i<numTrains;i++){
            printf("%-14s%-30s%-17s%-30s%-8s\n",pS[i].date,pS[i].station[0],pS[i].depTime[0],pS[i].station[pS[i].numStops-1],pS[i].arrTime[pS[i].numStops-1]);
            if(pS[i].numStops>2){
                printf("\tConnecting at:");
                for(int j=0;j<pS[i].numStops-2;j++){
                    if(j!=0){printf(",");}
                    printf("\t%s",pS[i].station[j+1]);
                }
                printf("\n");
            }
        }
        printf("\n\n");
    }

    //Accommodation
    printf("Accommodation\n");
    printf("-------------------\n");
    for(int i=0;i<numAccommodation;i++){
        printf("%s\n", pA[i].name); // write the string to the file
        printf("%s\n", pA[i].address);
        printf("%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }
    printf("\n");

    //Travel Insurance
    printf("Travel Insurance\n");
    printf("-------------------\n");
    printf("%-30s%-30s%-25s\n\n","Name", "Policy Number", "Emergency Contact Number");
    for(int i=0;i<numInsurance;i++){
        printf("%-30s%-30s%-25s\n",pI[i].name,pI[i].reference,pI[i].number);
    }
    printf("\n\n");

    //Itinerary
    printf("Itinerary\n");
    printf("-------------------\n\n");
    for(int i=0;i<numFlights+2*numAccommodation+numTrains;i++){
        if(i==0||dates[i].dayOfTrip>dates[i-1].dayOfTrip){
            if(i>0){
                printf("\n");
            }
            printf("Day %d - %d/%d\n",dates[i].dayOfTrip,dates[i].day,dates[i].month);
            printf("----------\n");
            printf("%s\n",dates[i].description);
        } else{
            printf("%s\n",dates[i].description);
        }
    }

}

void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, struct train *pS, int numTravellers, int numFlights, int numAccommodation, int numInsurance, int numTrains, struct Date *dates){
    FILE *fp;
    char airportNames[93];
    fp = fopen("output.md", "w"); // open the file in write mode

    if (fp == NULL) { // error checking
        printf("Error opening file\n");
        exit(1);
    }
    //Travellers
    fprintf(fp, "#Travellers\n");
    
    fprintf(fp, "%-30s%-6s%-18s%-30s\n\n", "##Name", "Age", "Phone Number", "Passport Number");
    for(int i=0;i<numTravellers;i++){
        fprintf(fp, "%-30s%-6d%-18s%-30s\n", pT[i].name, pT[i].age,pT[i].phoneNumber, pT[i].passportNumber); // write the string to the file

    }
    fprintf(fp, "\n\n");
    fprintf(fp, "---\n");

    //Flights
    fprintf(fp, "#Flights\n");
    fprintf(fp,"%-14s%-93s%-13s%-13s%-30s%-20s\n\n","##Type", "Airport", "Time", "Date", "Airline", "Flight Number");
    for(int i=0;i<numFlights;i++){
        sprintf(airportNames,"%s -> %s",pF[i].depApt,pF[i].arrApt);
        fprintf(fp, "%-14s%-93s%s->%-7s%-13s%-30s%-20s\n", pF[i].type, airportNames, pF[i].depTime,pF[i].arrTime, pF[i].date, pF[i].airline, pF[i].flightNumber);
    }
    fprintf(fp, "\n\n");
    fprintf(fp, "---\n");

    //Trains
    if(numTrains != 0){
        fprintf(fp,"#Trains\n");
        
        fprintf(fp,"%-14s%-30s%-17s%-30s%-8s\n\n","##Date","Departing Station","Departing Time","Arrival Station","Arrival Time");
        for(int i=0;i<numTrains;i++){
            fprintf(fp,"%-14s%-30s%-17s%-30s%-8s\n",pS[i].date,pS[i].station[0],pS[i].depTime[0],pS[i].station[pS[i].numStops-1],pS[i].arrTime[pS[i].numStops-1]);
            if(pS[i].numStops>2){
                fprintf(fp,"\tConnecting at:");
                for(int j=0;j<pS[i].numStops-2;j++){
                    if(j!=0){fprintf(fp,",");}
                    fprintf(fp,"\t%s",pS[i].station[j+1]);
                }
                fprintf(fp, "\n");
            }
        }
        fprintf(fp,"\n\n");
        fprintf(fp, "---\n");
    }
    

    //Accommodation
    fprintf(fp, "#Accommodation\n");
    for(int i=0;i<numAccommodation;i++){
        fprintf(fp, "%s\n", pA[i].name); // write the string to the file
        fprintf(fp, "%s\n", pA[i].address);
        fprintf(fp,"%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }
    fprintf(fp,"\n");
    fprintf(fp, "---\n");

    //Travel Insurance
    fprintf(fp, "#Travel Insurance\n");
    fprintf(fp,"%-30s%-30s%-25s\n\n","##Name", "Policy Number", "Emergency Contact Number");
    for(int i=0;i<numInsurance;i++){
        fprintf(fp,"%-30s%-30s%-25s\n",pI[i].name,pI[i].reference,pI[i].number);
    }
    fprintf(fp,"\n\n");
    fprintf(fp, "---\n");

    //Itinerary
    fprintf(fp,"#Itinerary\n");
    for(int i=0;i<numFlights+2*numAccommodation+numTrains;i++){
        if(i==0||dates[i].dayOfTrip>dates[i-1].dayOfTrip){
            if(i>0){
                fprintf(fp,"\n");
                fprintf(fp,"---\n");
            }
            fprintf(fp,"##Day %d - %d/%d\n",dates[i].dayOfTrip,dates[i].day,dates[i].month);
            
            fprintf(fp,"* %s\n",dates[i].description);
        } else{
            fprintf(fp,"* %s\n",dates[i].description);
        }
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
    fgets(pA[*numAccommodation-1].name, 60, stdin);
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
    pA[*numAccommodation-1].tag = *eventID;
    sprintf(pA[*numAccommodation-1].descriptionCI,"Check in to %s",pA[*numAccommodation-1].name);
    sprintf(pA[*numAccommodation-1].descriptionCO,"Check out of %s",pA[*numAccommodation-1].name);

    return pA;
}
struct flight *addFlight(struct flight *pF, int *numFlights, struct Airport *airports, int numAirports, int *eventID){
    struct Airport *selectedAirport = (struct Airport*)malloc(sizeof(struct Airport));

    (*numFlights)++;
    pF = realloc(pF,*numFlights*sizeof(struct flight));
    printf("Enter Flight Type (Outbound, Inbound, or Intermediate):\n");
    scanf(" %s",pF[*numFlights-1].type);
    printf("Departing Airport\n");
    while (getchar() != '\n') {}
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
    pF[*numFlights-1].tag = *eventID;
    sprintf(pF[*numFlights-1].description,"%s flight from %s to %s",pF[*numFlights-1].depTime,pF[*numFlights-1].depApt,pF[*numFlights-1].arrApt);
    return pF;
}

struct train *addTrain(struct train *pS,int *numTrains, int *eventID){
    int numStops = 0, finished = 0;
    char option;
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    (*numTrains)++;
    pS = realloc(pS,*numTrains*sizeof(struct train));
    pS[*numTrains-1].station[0] = (char*)malloc(30*sizeof(char));
    pS[*numTrains-1].depTime[0] = (char*)malloc(5*sizeof(char));
    pS[*numTrains-1].arrTime[0] = (char*)malloc(5*sizeof(char));
    printf("Enter date:\n");
    fgets(pS[*numTrains-1].date,11,stdin);
    while (getchar() != '\n') {}
    printf("Enter departure station:\n");
    fgets(pS[*numTrains-1].station[0],30,stdin);
    pS[*numTrains-1].station[0][length(pS[*numTrains-1].station[0])] = '\0';
    printf("Enter Departing Time:\n");
    scanf(" %s",pS[*numTrains-1].depTime[0]);

    while(finished!=1){
        printf("Would you like to add a connecting station? Press y or n\n");
        scanf(" %s",&option);
        while (getchar() != '\n') {}
        if(option=='n'){
            break;
        }
        numStops++;
        pS[*numTrains-1].station[numStops] = (char*)malloc(30*sizeof(char));
        pS[*numTrains-1].arrTime[numStops] = (char*)malloc(5*sizeof(char));
        pS[*numTrains-1].depTime[numStops] = (char*)malloc(5*sizeof(char));
        printf("Enter connecting station:\n");
        fgets(pS[*numTrains-1].station[numStops],30,stdin);
        pS[*numTrains-1].station[numStops][length(pS[*numTrains-1].station[numStops])] = '\0';
        printf("Enter arrival time at this station:\n");
        scanf(" %s",pS[*numTrains-1].arrTime[numStops]);
        printf("Enter departure time at this station:\n");
        scanf(" %s",pS[*numTrains-1].depTime[numStops]);

    }

    pS[*numTrains-1].station[numStops+1] = (char*)malloc(30*sizeof(char));
    pS[*numTrains-1].arrTime[numStops+1] = (char*)malloc(5*sizeof(char));
    printf("Enter final station:\n");
    fgets(pS[*numTrains-1].station[numStops+1],30,stdin);
    pS[*numTrains-1].station[numStops+1][length(pS[*numTrains-1].station[numStops+1])] = '\0';
    printf("Enter arrival time at this station:\n");
    scanf(" %s",pS[*numTrains-1].arrTime[numStops+1]);
    pS[*numTrains-1].numStops = numStops + 2;

    (*eventID)++;
    pS[*numTrains-1].tag = *eventID;
    sprintf(pS[*numTrains-1].description,"%s Train from %s to %s",pS[*numTrains-1].depTime[0],pS[*numTrains-1].station[0],pS[*numTrains-1].station[numStops+1]);

    return pS;
}

struct traveller *addTraveller(struct traveller *pT, int *numTravellers){

    (*numTravellers)++;
    pT = realloc(pT,*numTravellers*sizeof(struct traveller));
    while (getchar() != '\n') {}
    printf("Enter traveller Name:\n");

    // Read the name string
    fgets(pT[*numTravellers-1].name, 30, stdin);
    pT[*numTravellers-1].name[length(pT[*numTravellers-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Traveller Age: \n");
    scanf(" %d", &pT[*numTravellers-1].age);
    printf("Enter Traveller Phone Number: \n");
    scanf(" %s", pT[*numTravellers-1].phoneNumber);
    printf("Enter Passport Number\n");
    scanf(" %s", pT[*numTravellers-1].passportNumber);


    return pT;
}

void loadData(struct Airport *airports, int numAirports){
    FILE *fp;
    char filename[] = "./assets/airports.txt";
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
            printf("Transport\n");
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
