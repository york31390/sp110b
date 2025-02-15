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


int main() {
  info_argc_t info = {
    "test.csv",
    "test.dat",
    DATABASE,
  };
  unsigned int choice = 119;
  while (choice != 5) {
    switch (choice) {
      case 1: {
        puts("database");
        database(info.target_data);
        break;
      }

      case 2: {
        puts("management");
        management(&info);
        break;
      }

      case 3: {
        puts("merge");
        merge(&info);
        break;
      }

      case 4: {
        puts("example");
        example(info.target_data);
        break;
      }

      case 5: {
        puts("Bye Bye~");
        break;
      }

      case 119: {
        printf("%s",
          "\nEnter request\n"
          " 1    database\n"
          " 2    management\n"
          " 3    merge data\n"
          " 4    example data\n"
          " 5    end program\n"
          " 119  help\n"
        );
        break;
      }

      default: {
        puts("Incorrect choice, Please enter function number.(1~5, help is 119)");
        break;
      }
    }
  choice = init_menu();
  }
}

unsigned int init_menu() {
  // 初始化功能選擇輸入
  printf("%s", "\n > ");
  unsigned int init_menu_choice;
  scanf("%u", &init_menu_choice);
  return init_menu_choice;
}

unsigned int database_menu() {
  // 資料庫功能選擇輸入
  printf("%s", "\n (database) > ");
  unsigned int database_menu_choice;
  scanf("%u", &database_menu_choice);
  return database_menu_choice;
}

void database(vehicle_management_t *data_p) {
  // 資料庫主程式
  unsigned int choice = 119;

  while (choice != 4) {
    switch (choice) {
      case 1:
        creat_database();
        break;

      case 2: {
        use_database(data_p);
        break;
      }

      case 3: {
        close_database(data_p);
        break;
      }

      case 4: {
        puts("Bye Bye~");
        break;
      }

      case 119: {
        printf("%s",
          "\nEnter request\n"
          " 1    create database, please keyin name\n"
          " 2    selete use database\n"
          " 3    close database\n"
          " 4    exit\n"
          " 119  help\n"
        );
        break;
      }

      default: {
        puts("Incorrect choice, Please enter function number.(1~3, help is 119)");
        break;
      }
    }
    choice = database_menu();
  }
}

void creat_database() {
  // 建立資料庫
  FILE *file_p;
  char database_name[50];
  vehicle_management_t database = {0, "null", 0, "null", "null", "null", "null", "null", 0};

  printf("%s", "Please keyin database name: ");
  scanf("%s", database_name);

  if ((file_p = fopen(database_name, "wb")) == NULL) {
    puts("File could not be opened.");

  } else {

    for (size_t i = 0; i < DATABASE; i++) {
      fwrite(&database, sizeof(vehicle_management_t), 1, file_p);
    }
    printf("%s%s%s", "database ", database_name, " is success.\n");
  }
  fclose(file_p);
}

void use_database(vehicle_management_t *data_p) {
  // 選擇使用的資料庫
  FILE *file_p;
  unsigned int count = 0;
  char database_name[50];
  printf("%s", "Please keyin database name: ");
  scanf("%s", database_name);

  if ((file_p = fopen(database_name, "rb")) == NULL) {
    puts("File could not be opened.");

  } else {
    printf("%s\n", "compute file size...");

    while (!feof(file_p)) {
      fread(&data_p[count], sizeof(vehicle_management_t), 1, file_p);
      if (count < DATABASE) {
        count++;
      }
    }
    printf("%u\n", count);
  }
  fclose(file_p);
  printf("%s%s%s\n", "use ", database_name, " database");
}

void close_database(vehicle_management_t *data_p) {
  // 關閉資料庫並把資料清空
  FILE *file_p;
  char database_name_p[50];
  printf("%s", "Please keyin svae data the database name: ");
  scanf("%s", database_name_p);

  if ((file_p = fopen(database_name_p, "rb+")) == NULL) {
    puts("File could not be opened.");

  } else {
    printf("%s\n", "svae file...");

    for (size_t i = 0; i < DATABASE; i++) {
      fseek(file_p, i * sizeof(vehicle_management_t), SEEK_SET);
      fwrite(&data_p[i], sizeof(vehicle_management_t), 1, file_p);
      vehicle_management_t null = {0, "null", 0, "null", "null", "null", "null", "null", 0};
      data_p[i] = null;
    }
  }
  fclose(file_p);
  printf("%s%s%s", "database ", database_name_p, " is success.\n");
}

unsigned int management_meun() {
  // 管理功能選擇輸入
  printf("%s", "\n (management) > ");
  unsigned int management_menu_choice;
  scanf("%u", &management_menu_choice);
  return management_menu_choice;
}

void management(info_argc_t *info_p) {
  // 管理主程式
  unsigned int choice = 119;
  while (choice != 7) {
    switch (choice) {
      case 1: {

        export_csv(info_p->target_data);
        break;
      }

      case 2: {
        selete(info_p->target_data);
        break;
      }

      case 3: {
        update(info_p->target_data);
        break;
      }

      case 4: {
        insert(info_p->target_data);
        break;
      }

      case 5: {
        drop(info_p->target_data);
        break;
      }

      case 6: {
        print_part_of_data(info_p);
        break;
      }

      case 7: {
        puts("Bye Bye~");
        break;
      }

      case 119: {
        printf("%s",
          "\nEnter request\n"
          " 1    store a formatted csv file of accounts called\n"
          " 2    selete an data\n"
          " 3    update an data\n"
          " 4    insert a new data\n"
          " 5    delete an data\n"
          " 6    print data\n"
          " 7    end program\n"
          " 119  help\n"
        );
        break;
      }

      default: {
        puts("Incorrect choice, please enter function number.");
        break;
      }
    }
    choice = management_meun();
  }
}

void export_csv(vehicle_management_t *data_p) {
  // 將記憶體的資料輸出csv格式
  unsigned int count = DATABASE;
  char file_name[50];
  printf("%s", "Please keyin file name: ");
  scanf("%s", file_name);
  write_data(file_name, data_p, &count);

}

void insert(vehicle_management_t *data_p) {
  // 插入資料，輸入編號選擇插入位置
  unsigned int account = 0;
  unsigned int count = DATABASE;
  if (sizeof(data_p) == 0) {
    printf("%s\n", "Is not dat.");
  } else {
    printf("%s%u%s\n", "Enter account to update (1 - ", count, "): ");
    printf("%s", "\n (insert) >>> ");
    scanf("%d", &account);

    if (data_p[account - 1].number != 0) {
      printf("Account #%u already contains information.\n", data_p[account - 1].number);
      print_row_data(data_p[account - 1]);

    } else {
      data_p[account - 1].number = account;
      keyin_row(&data_p[account - 1]);
    }
  }
}

void selete(vehicle_management_t *data_p) {
  // 搜尋資料，以姓名篩選指定的資料
  unsigned int count = DATABASE;
  printf("%s%u%s", "Enter name search (1 - ", count, ")\n");

  printf("%s", "\n (selete) >>> ");
  search(data_p);
}

void drop(vehicle_management_t *data_p) {
  // 刪除資料，輸入該數字的編號
  unsigned int account = 0;
  vehicle_management_t temp = {0, "null", 0, "null", "null", "null", "null", "null", 0};

  printf("%s%u%s\n", "Enter account to delete (1 - ", DATABASE, ")");
  printf("%s", "\n (delete) >>> ");
  scanf("%d", &account);

  if (data_p[account - 1].number == 0) {
    printf("Account %d does no exist.\n", account);

  } else {
    data_p[account - 1] = temp;
    puts("Delete success");
  }
}

void update(vehicle_management_t *data_p) {
  // 更新資料，輸入數字選擇更新位置
  unsigned int count = DATABASE;
  unsigned int account = 0;

  printf("%s%u%s", "Enter number to update (1 - ", count, ")\n");
  printf("%s", "\n (update) >>> ");
  scanf("%d", &account);
  print_row_data(data_p[account - 1]);

  if (data_p[account - 1].number == 0) {
    printf("Account #%d has no information.\n", account);

  } else {
    data_p[account - 1].number = account;
    keyin_row(&data_p[account - 1]);
  }
}

void example(vehicle_management_t *data_p) {
  // 產生示範資料，該資料會自動儲存在記憶體
  vehicle_management_t create[SIZE] = {
    {
      1,
      "5132-8093-6999-5158",
      21086155,
      "Lory L. Hash",
      "J262986562",
      "+1 7022986198",
      "673 Cooks Mine Road Albuquerque NM 87108",
      "January 17 1978",
      73200
    }, {
      2,
      "5255-7185-6812-4208",
      39416756,
      "賀曉彤",
      "Q214131854",
      "+1 2149393884",
      "4713 Deercove Drive Dallas TX 75202",
      "November 1 1938",
      812000
    }, {
      3,
      "4916-1212-9727-7104",
      20138697,
      "Donna J. Johnson",
      "E129441704",
      "+1 6016561902",
      "670 高雄市左營區吉利四街400號",
      "February 2 1999",
      114900
    }
  };
  for (size_t i = 0; i < SIZE; i++) {
    data_p[i] = create[i];
  }
}

unsigned int merge_menu() {
  // 合併功能選擇輸入
  printf("%s", "\n (merge) > ");
  unsigned int merge_menu_choice;
  scanf("%u", &merge_menu_choice);
  return merge_menu_choice;
}

void merge(info_argc_t *info_p) {
  // 合併主程式
  unsigned int choice = 119;

  while (choice != 3) {
    switch (choice) {
      case 1: {

        file_merge_data(info_p);
        break;
      }

      case 2: {

        data_merge_file(info_p);
        break;
      }

      case 3: {
        puts("Bye Bye~");
        break;
      }

      case 119: {
        printf("%s",
          "\nEnter request\n"
          " 1    file merge to data\n"
          " 2    data merge to file\n"
          " 3    exit\n"
          " 119  help\n"
        );
        break;
      }

      default: {
        puts("Incorrect choice, please enter function number.");
        break;
      }
    }
    choice = merge_menu();
  }

}

void file_merge_data(info_argc_t *info_p) {
  // 檔案合併到記憶體
  // 操作時會重新讀取選擇資料庫並覆蓋原先記憶體資料
  use_database(info_p->target_data);

  printf("%s", "Please keyin sources file name: ");
  scanf("%s", info_p->file_name);
  read_data(info_p);

  print_part_of_data(info_p);
  source_merge_to_target(info_p->source_data, info_p->target_data, &info_p->count);
  print_part_of_data(info_p);

}

void data_merge_file(info_argc_t *info_p) {
  // 記憶體合併到檔案
  // 操作時會重新讀取選擇資料庫並覆蓋原先記憶體資料
  printf("%s", "Please keyin target file name: ");
  scanf("%s", info_p->file_name);
  read_data(info_p);

  for (size_t i = 0; i < info_p->count; i++) {
    info_p->target_data[i] = info_p->source_data[i];
  }

  use_database(info_p->source_data);

  print_part_of_data(info_p);
  source_merge_to_target(info_p->source_data, info_p->target_data, &info_p->count);
  print_part_of_data(info_p);

  write_data(info_p->file_name, info_p->target_data, &info_p->count);
}

void source_merge_to_target(vehicle_management_t *source_data_p,
    vehicle_management_t *target_data_p, unsigned int *count_p) {
  // 將兩種不同陣列合併，分別是來源合併目標，通過將來源合併到目標
  unsigned int _compare;
  for (size_t i = 0; i < *count_p; i++) {
    _compare = 1;
    for (size_t j = 0; j < *count_p; j++) {
      _compare &= compare(target_data_p[j], source_data_p[i]);
    }
    if ((target_data_p[i].number == 0) && _compare) {
      target_data_p[i] = source_data_p[i];

    } else if ((target_data_p[i].number != 0) && _compare) {
      for (size_t k = 1; k < (*count_p - i); k++) {
        if (target_data_p[k + i].number == 0) {
          target_data_p[k + i] = source_data_p[i];
        }
      }
    }
  }
  printf("%s\n", "data merge file is success");

}

void keyin(vehicle_management_t *data_p, unsigned int *count_p) {
  // 連續資料輸入

  for (size_t i = 0; i < *count_p; i++) {
    keyin_row((data_p + i));

  }
}

void keyin_row(vehicle_management_t *data_row_p) {
  // 單筆資料輸入
  printf("%s", "\n輸入車牌：");
  scanf(" %[^\n]", data_row_p->license_plate);

  printf("%s", "輸入引擎編號：");
  scanf(" %u", &data_row_p->engine_number);

  printf("%s", "輸入姓名：");
  scanf(" %[^\n]", data_row_p->name);

  printf("%s", "輸入身份證字號：");
  scanf(" %[^\n]", data_row_p->id);

  printf("%s", "輸入電話：");
  scanf(" %[^\n]", data_row_p->phone_number);

  printf("%s", "輸入地址：");
  scanf(" %[^\n,\"]", data_row_p->address);

  printf("%s", "輸入時間：");
  scanf(" %[^\n,\"]", data_row_p->date);

  printf("%s", "輸入租金：");
  scanf(" %u", &data_row_p->amount_of_money);

}

void search(vehicle_management_t *data_p) {
  // 篩選指定資料，此為使用姓名欄位做篩選
  // 篩選後會清除其他非篩選資料，如果沒有找到記憶體的資料會被空值清空
  vehicle_management_t null = {0, "null", 0, "null", "null", "null", "null", "null", 0};
  char search_name[NAME];
  unsigned int count = 0;
  scanf(" %[^\n]", search_name);

  printf("\n\n%s%s\n\n", "姓名：", search_name);
  for (size_t i = 0; i < DATABASE; i++) {
    if (strcmp((data_p + i)->name, search_name) == 0) {
      if (data_p[count].number == 0) {
        data_p[count] = data_p[i];
        data_p[count].number = count + 1;
        data_p[i] = null;
        count++;
      }
    } else if (i < DATABASE) {
      data_p[i] = null;

    } else if ((i + 1) == DATABASE) {
      printf("%s\n", "Search from database, not in.");
    }
  }
}

void print_data(vehicle_management_t *data_p, unsigned int *count_p) {
  // 顯示記憶體中陣列資料
  for (size_t i = 0; i < *count_p; i++) {
    printf("%p\n", &*(data_p + i));
    print_row_data(*(data_p + i));
  }
}

void print_row_data(vehicle_management_t data) {
  // 顯示單筆資料
  printf("%-10u%-22s%-15u%-20s%-12s%-17s%-64s%-22s%-20u\n",
    data.number,
    data.license_plate,
    data.engine_number,
    data.name,
    data.id,
    data.phone_number,
    data.address,
    data.date,
    data.amount_of_money
  );
}

void write_data(char *file_name_p, vehicle_management_t *data_p, unsigned int *count_p) {
  // 建立資料夾並寫入資料
  FILE *file_p;
  puts("File is write...");
  if ((file_p = fopen(file_name_p, "w")) == NULL) {
    puts("File could not be opened");
  } else {
    fclose(file_p);
    for (size_t i = 0; i < *count_p; i++) {
      if ((data_p + i)->number != 0) {
        write_row_data(file_name_p, *(data_p + i));
      }
    }
    printf("%p row: %u\n", &*(data_p + (*count_p - 1)), *count_p);
  }
}

void write_row_data(char *file_name_p, vehicle_management_t data) {
  // 透過追加方式寫入資料

  FILE *file_p;

  if ((file_p = fopen(file_name_p, "a")) == NULL) {
    puts("File could not be opened");
  } else {
    fprintf(file_p, "%u,\"%s\",%u,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%u\n",
      data.number,
      data.license_plate,
      data.engine_number,
      data.name,
      data.id,
      data.phone_number,
      data.address,
      data.date,
      data.amount_of_money
    );
    fclose(file_p);
  }
}

void read_data(info_argc_t *info_p) {
  // 讀取資料
  FILE *file_p;
  unsigned int count = 0;
  char line[7000];
  char *cut;

  if ((file_p = fopen(info_p->file_name, "r")) == NULL) {
    puts("File could not be opened");

  } else {
    printf("%s\n", "compute file size...");

    while (fgets(line, DATABASE, file_p) != NULL) {
      cut = strtok(line, ",");
      info_p->source_data[count].number = atoi(cut);

      cut = strtok(NULL, "\",");
      strcpy(info_p->source_data[count].license_plate, cut);

      cut = strtok(NULL, ",\"");
      info_p->source_data[count].engine_number = atoi(cut);

      cut = strtok(NULL, "\",\"");
      strcpy(info_p->source_data[count].name, cut);

      cut = strtok(NULL, "\",\"");
      strcpy(info_p->source_data[count].id, cut);

      cut = strtok(NULL, "\",\"");
      strcpy(info_p->source_data[count].phone_number, cut);

      cut = strtok(NULL, "\",\"");
      strcpy(info_p->source_data[count].address, cut);

      cut = strtok(NULL, "\",");
      strcpy(info_p->source_data[count].date, cut);

      cut = strtok(NULL, ",\"");
      info_p->source_data[count].amount_of_money = atoi(cut);

      if (info_p->source_data[count].number != 0) {
        print_row_data(info_p->source_data[count]);
      }

      if (count < DATABASE) {
        count++;
      }
    }
    info_p->count = count;
  }
}

int compare(vehicle_management_t source_data_p, vehicle_management_t target_data_p) {
  /*比對數字後回傳數字結果

  一樣 return 0
  不一樣 return 1
  */
  int license_plate = strcmp(
    source_data_p.license_plate,
    target_data_p.license_plate
  );
  int engine_number = source_data_p.engine_number == target_data_p.engine_number;
  int name = strcmp(
    source_data_p.name,
    target_data_p.name
  );
  int id = strcmp(
    source_data_p.id,
    target_data_p.id
  );
  int phone_number = strcmp(
    source_data_p.phone_number,
    target_data_p.phone_number
  );
  int address = strcmp(
    source_data_p.address,
    target_data_p.address
  );
  int date = strcmp(
    source_data_p.date,
    target_data_p.date
  );
  int amount_of_money = source_data_p.amount_of_money == target_data_p.amount_of_money;
  return license_plate || !engine_number || name || id || phone_number || address || date || !amount_of_money;
}

void print_part_of_data(info_argc_t *info_p) {
  // 顯示記憶體有數值的資料，不會將空值也顯示出來
  // 會區分結構中兩個不同的資料，包括來源資料與目標資料
  printf("\n%s\n\n", "顯示來源資料");
  for (size_t i = 0; i < info_p->count; i++) {
    if (info_p->source_data[i].number != 0) {
      print_row_data(info_p->source_data[i]);
    }
  }
  printf("\n%s\n\n", "顯示目標資料");
  for (size_t i = 0; i < info_p->count; i++) {
    if (info_p->target_data[i].number != 0) {
      print_row_data(info_p->target_data[i]);
    }
  }
}
