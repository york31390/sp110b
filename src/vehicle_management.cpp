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

unsigned int init_menu();

// database
unsigned int database_menu();
void database(vehicle_management_t *data_p);
void creat_database();
void use_database(vehicle_management_t *data_p);
void close_database(vehicle_management_t *data_p);

// management
unsigned int management_meun();
void management(info_argc_t *info_p);
void export_csv(vehicle_management_t *data_p);
void insert(vehicle_management_t *data_p);
void selete(vehicle_management_t *data_p);
void drop(vehicle_management_t *data_p);
void update(vehicle_management_t *data_p);

// print example data
void example(vehicle_management_t *data_p);

// file merge to database
unsigned int merge_menu();
void merge(info_argc_t *info_p);
void file_merge_data(info_argc_t *info_p);
void data_merge_file(info_argc_t *info_p);
void source_merge_to_target(vehicle_management_t *source_data_p,
    vehicle_management_t *target_data_p, unsigned int *count_p);

// Share function
void keyin(vehicle_management_t *data_p, unsigned int *count_p);
void keyin_row(vehicle_management_t *data_row_p);
void search(vehicle_management_t *data_p);
void print_data(vehicle_management_t *data_p, unsigned int *count_p);
void print_row_data(vehicle_management_t data);
void write_data(char *file_name_p, vehicle_management_t *data_p, unsigned int *count_p);
void write_row_data(char *file_name_p, vehicle_management_t data);
void read_data(info_argc_t *info_p);
int compare(vehicle_management_t database_data_p, vehicle_management_t file_data_p);
void print_part_of_data(info_argc_t *info_p);


