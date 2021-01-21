#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>


const char* path; //Ten FILE

typedef struct{
	int number; //So luong thu tu ghi trong FILE
	char date[50]; //Thoi gian ghi nhan DD/MM/YYYY
	char rent_Motel[2]; // Yes-No su dung thue nha
	int electricity; //So dien
	int water; //So nuoc
	int internet[2]; //Yes-No su dung Internet
	int sum_Money; //Tong tien
}Motel;

//Dem so luong hang trong FILE
int getLine(){
	int test=0;
	int line=1;
	FILE *file=fopen(path,"r");
	while(!feof(file)){ //end-of-file
		test=fgetc(file); //Lay ky tu tiep theo
		if(test=='\n')
			line++;
	}
	return line;
}

//Doc FILE
void readFile(Motel data[], int number){
	int i;
	FILE *file=fopen(path,"r");
	for(i=1;i<=number;i++){
		fscanf(file,"%d%s%s%d%d%s%d",
			&data[i].number,&data[i].date,&data[i].rent_Motel,&data[i].electricity,&data[i].water,&data[i].internet,&data[i].sum_Money);
	}
}

//In FILE ra man hinh
void output(Motel data[], int number, char* fileName_numberRoom){
	int i;
	printf("============================= PHONG TRO SO %s ===============================\n", fileName_numberRoom);
	printf("\n|------|------------|----------|-------------|----------|----------|---------------|");
	printf("\n|  NO  |    TIME    |   RENT   | ELECTRICITY |   WATER  | INTERNET |       SUM     |");
	printf("\n|------|------------|----------|-------------|----------|----------|---------------|");
	
	for(i=1;i<=number;i++){
		printf("\n|%6d|%12s|%10s|%13d|%10d|%10s|%15d|",
			data[i].number,data[i].date,data[i].rent_Motel,data[i].electricity,data[i].water,data[i].internet,data[i].sum_Money);
	}
	printf("\n|------|------------|----------|-------------|----------|----------|---------------|");
	printf("\n\n");
}

//void local_time(Motel data[]){
//	int index = 0;
//  int i;
//  char *token;
//  char *a = (char *)malloc(100*sizeof(char));
//  char **b = (char **)malloc(100*sizeof(char));
//  fflush(stdin);
//  
//  //Get local time
//  time_t curtime;
//  time(&curtime); 
////  printf("%s", ctime(&curtime));
//  a=ctime(&curtime);
//  //end 
//
//  token = strtok(a, " "); //cat chuoi bang cac ky tu ,. va space
//  while(token != NULL){
//  	b[index] = token;
//		index++;
//		token = strtok(NULL, " "); //cat chuoi tu vi tri dung lai truoc do
//  }
//  
//  for (i =0; i<index; i++) //in ra cac tu theo thu tu 
//    printf ("%s ", b[i]);
//	
////	strcpy(data->date,b[0]); //Thu
////	strcat(data->date," ");
////	strcat(data->date,b[1]); //Thang
////	strcat(data->date," ");
////	strcat(data->date,b[2]); //Ngay
////	strcat(data->date," ");
////	strcat(data->date,b[3]); //Gio
////	strcat(data->date," ");
////	strcat(data->date,b[4]); //Nam
//
//}

void local_time(Motel data[]){
  char *a = (char *)malloc(100*sizeof(char));
  
	//Get local time
  time_t curtime;
  time(&curtime);
  a=ctime(&curtime);
  //end
  
  strcpy(data->date,a);
}

void input(Motel data[], int number){
	data->number=number; //sao chep STT vao struct
	
	printf("\n=====XIN MOI NHAP CAC THONG TIN=====\n");
	data->number++; //Cong don STT
	local_time(data); //Thoi gian hien tai tren he thong
	printf("Current-local-time: %s", data->date);
	
	//Xac nhan phong co duoc thue hay khong
	printf("Phong nay co dang duoc cho thue khong? Y/N "); scanf("%s",&data->rent_Motel);
	if(stricmp("Y",data->rent_Motel)==0){
		printf("Nhap so dien: "); scanf("%d",&data->electricity);
		printf("Nhap so nuoc: "); scanf("%d",&data->water);
		printf("Co su dung Internet khong? Y/N "); scanf("%s",&data->internet);
		
		//Ghi FILLE
		FILE* file=fopen(path,"a+");
		fprintf(file,"\n%d %s %d %d %s %s", data->number, data->rent_Motel, data->electricity, data->water, data->internet, data->date);
		fclose(file);
	}
	else return;
	
	printf("\nSTT: %d",data->number);
	printf("\nConfirm rent: %s", data->rent_Motel);
	printf("\nSo dien: %d", data->electricity);
	printf("\nSo nuoc: %d", data->water);
	printf("\ninternet: %s", data->internet);
	printf("\nDate: %s", data->date);
}

int main(){
	Motel M;
	

//=============Truy cap vao FILE cua Phong nao================
	char fileName_phong[]="Phong";
	char fileName_numberRoom[2]; //so phong
	char fileName_extensionFile[]=".txt";
	char fileName[15];
	
	printf("Nhap so phong: ");
	gets(fileName_numberRoom);

	//Cong chuoi --> ten root_File
	strcpy(fileName,fileName_phong);
	strcat(fileName,fileName_numberRoom);
	strcat(fileName,fileName_extensionFile);
	printf("\nTen FILE: %s\n", fileName);
	path=fileName;
//=============THE END OF Truy cap vao FILE cua Phong nao================
	

	M.number=getLine(); //Gan gia tri number trong FILE
	printf("%d", M.number);
	Motel data[M.number]; //Khoi tao danh sach cac du lieu ung thang
	readFile(data, M.number);
	output(data, M.number, fileName_numberRoom);
	input(data,M.number);
	return 0;
}
