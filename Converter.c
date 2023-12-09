#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxLength 10000

// Struct in cs code
struct Column
    {
        char Title[50];
    }Columns[50];

// Main code for .exe
int main(int argc, char *argv[])
{
  // Argc error
  if (argc!=4)
  {
    printf("Yanlis girdiniz\n");
    printf("\nDogru Kullanim sekli : <Uygulama ismi> <CSV dosya adi> <json dosya adi> <header=ON | OFF>\n");
    return 0;
  }

    // Open a csv file
    int ColumnCounter=0;
    FILE* csv;
    csv = fopen(argv[1], "r");
    
    // Checking file for empty or not 
    char metin[MaxLength]="";
    if (csv == NULL) {
      perror("Hata : ");
      return 0;
    }
    char buffer[MaxLength];

    // Get header from csv file
    fgets(buffer, MaxLength, csv);
    char* field = strtok(buffer, ";");
    while(field)
      {
        strcpy(Columns[ColumnCounter].Title, field);
        field = strtok(NULL, ";");
        ColumnCounter++;
      }
    char *header = argv[3];

    // Write json format in vscode
    while (fgets(buffer, MaxLength, csv))
    {
      size_t counter=0;
      
      char* field = strtok(buffer, ";");
      strcat(metin,"\n{\n");
      while(field)
      {
        strcat(metin,"'");

        // Header=ON or OFF mode code
        if (strcmp(argv[3], "header=ON") == 0)
        {
          strcat(metin,Columns[counter].Title);
          strcat(metin,"'");
          strcat(metin,":");
          strcat(metin,"'");
        }
        strcat(metin,field);
        strcat(metin,"'");
        strcat(metin,",");
        strcat(metin,"\n");
        field = strtok(NULL,";");
        counter = counter + 1;
      }
      strcat(metin,"}\n");
    }
    fclose(csv);
 
    // Create a json file
    FILE *json;
    json = fopen(argv[2],"w");
    
    // Write json file
    fputs(metin, json);
    fclose(json);
    return 0;
}