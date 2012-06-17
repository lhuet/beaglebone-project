/* gpio3.c
*
*  Author: A.Gibson
*
*  Date: 4th May 2011
*
*  Purpose: Example code to pulse the motor on and off
*
* gpio 146 is the dc motor (via level converter and mosfet board)
* gpio 170 is the motor enable relay
*
*  Last modified 05/05/2011 to clean up the output
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>

FILE *fp;

int main(void)
{

    system("devmem2 0x480021E0 h 0x10c");
    system("devmem2 0x480021C4 h 0x10c");
    system("devmem2 0x48002174 h 0x10c");
    system("devmem2 0x48002178 h 0x10c");
    char set_value[4];

    int toggle = 0;

    if (( fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
        printf("Can not open export file \n");
        exit(1);
    }

    rewind(fp);

    //strcpy(set_value, "10");
    strcpy(set_value, "146");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    printf("146 now exported \n");

    if (( fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
        printf("Can not open export file \n");
        exit(1);
    }

    rewind(fp);

    strcpy(set_value, "170");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);


   printf("170 now exported\n");
    if  (( fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
        printf("Can not open export file \n");
        exit(1);
    }

    rewind(fp);

    strcpy(set_value, "186");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    printf("186 now exported\n");

    if((fp = fopen("/sys/class/gpio/gpio170/direction", "rb+")) == NULL)
    {
        printf("Can not open direction file\n");
        exit(1);
    }

    rewind(fp);
    strcpy(set_value, "out");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    printf("170 direction set to output\n");


    if((fp = fopen("/sys/class/gpio/gpio186/direction", "rb+")) == NULL)
    {
        printf("Can not open direction file\n");
        exit(1);
    }

    rewind(fp);
    strcpy(set_value, "out");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    printf("186 direction set to output\n");

    if((fp = fopen("/sys/class/gpio/gpio146/value", "rb+")) == NULL)
    {
        printf("Can't open value file");
        exit(1);
    }

    rewind(fp);
    strcpy(set_value, "1");
    fwrite(&set_value, sizeof(char), 1, fp);
    fclose(fp);

    printf("146 set to 1\n");

    if((fp = fopen("/sys/class/gpio/gpio186/value", "rb+")) == NULL)
    {
        printf("Can't open value file");
        exit(1);
    }

    rewind(fp);
    strcpy(set_value, "1");


    fwrite(&set_value, sizeof(char), 1, fp);
    fclose(fp);

    printf("186 set to 1\n");

    if((fp = fopen("/sys/class/gpio/gpio170/value", "rb+")) == NULL)
    {
        printf("Can't open value file");
        exit(1);
    }

    rewind(fp);
    strcpy(set_value, "0");
    fwrite(&set_value, sizeof(char), 1, fp);
    fclose(fp);

    printf("170 set to 0\n");



    while(1)
    {


        if((fp = fopen("/sys/class/gpio/gpio186/value", "rb+")) == NULL)
        {
            printf("Can not open value file\n");
            exit(1);
        }
        toggle =  !toggle;

        if(toggle)
        {
            rewind(fp);
            strcpy(set_value, "1");
            fwrite(&set_value, sizeof(char), 1 ,fp);
            fclose(fp);
            printf("...value set to 1\n");
        }
        else
        {
            rewind(fp);
            strcpy(set_value, "0");
            fwrite(&set_value, sizeof(char), 1 ,fp);
            fclose(fp);
            printf("...value set to 0\n");
        }
        sleep(5);
   }
   return 0;
}


