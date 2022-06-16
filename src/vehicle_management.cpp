/* vehicle_management.cpp

vehicle management 汽車管理軟體
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
#define DATABASE 500
#define LICENSE_PLATE 22
#define ENGINE 10
#define NAME 22
#define ID 12
#define PHONE_NUMBER 17
#define ADDR 6400
#define DATE 22
#define MONEY 22

typedef struct {
  unsigned int number;
  char license_plate[LICENSE_PLATE];
  unsigned int engine_number;
  char name[NAME];
  char id[ID];
  char phone_number[PHONE_NUMBER];
  char address[ADDR];
  char date[DATE];
  int amount_of_money;
} vehicle_management_t;

typedef struct {
  char file_name[50];
  char database_name[50];
  unsigned int count;
  vehicle_management_t source_data[DATABASE];
  vehicle_management_t target_data[DATABASE];
} info_argc_t;

