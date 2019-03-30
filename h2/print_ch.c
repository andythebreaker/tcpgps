
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10//make string
#define CHART_X_HOWMANY 7
#define CHART_Y_HOWMANY 7
#define boat4 "戰艦"
#define boat3 "巡洋艦"
#define boat2 "驅逐艦"
#define kind_of_boat 3

int WWWchart=0;

void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
	strncpy(dest, src + start, cnt);
	dest[cnt] = 0;
}
int op(int sha,int shb,char *ship){
	char *qip=malloc(LEN+1);
	strcpy(qip,ship);
	printf("%s\n",qip);
}

void eNter(){printf("\n");}
void dash(){printf("-");}
void plus(){printf("+");}
void stra(){printf("|");}

void chartUD(){
	for(int i = 0 ; i<(CHART_X_HOWMANY*2-1);i++){
		dash();
	}
}

void chart_row(char *TARGETstring_row,int index_chart_row){
	for(int i = 0 ; i < CHART_Y_HOWMANY*2+1;i++ ){
		if(i%2==0){
			stra();
		}else{
			printf("%c",TARGETstring_row[index_chart_row]);
			index_chart_row++;
		}
	}
	WWWchart=index_chart_row;
}

void plot_map(char *plot_str){
	eNter();
	plus();
	chartUD();
	plus();
	eNter();
	for(int i = 1 ; i<(CHART_Y_HOWMANY*2);i++){
		if(i%2==0){
			stra();	
			chartUD();
			stra();
			eNter();
		}else{
			chart_row(plot_str,WWWchart);
			eNter();
		}
	}
	plus();
	chartUD();
	plus();
	eNter();
	WWWchart=0;
}

int connection(int *connection_input,int Tsize){
//看是否在一直線上
	int sz =Tsize/(int)sizeof(int);
	if(sz%2!=0){
		return -1;
	}
	int chace = -1;
	int chaceX=connection_input[0];
	int chaceY=connection_input[1];

	for(int i =0;i<sz;i+=2){
		chaceX=connection_input[i];
		chaceY=connection_input[i+1];
		for(int k =0;k<sz;k+=2){
			if(k!=i){
				if(chaceX==connection_input[k]&&chaceY==connection_input[k+1]){
					return -1;
				}
			}
		}
	}
	int x_in_same_pos = 1;
	int y_in_same_pos = 1;//if ==1 RPS true;else==0 RPS falst
	chace=connection_input[0];
	for (int i = 0 ;i<sz;i++){
		if(i%2==0){
			if(connection_input[i]==chace){
				x_in_same_pos*=1;
			}else{
				x_in_same_pos*=0;
			}
		}
	}

	chace = connection_input[1];
	for (int i = 0 ;i<sz;i++){
		if(i%2!=0){
			if(connection_input[i]==chace){
				y_in_same_pos*=1;
			}else{
				y_in_same_pos*=0;
			}
		}
	}

	if(x_in_same_pos==0&&y_in_same_pos==0){
		return 0;//no things in same pos
	}
	if(x_in_same_pos==1||y_in_same_pos==1){
		//have thing in same pos
		if(x_in_same_pos==1){
			return 1;//x_coODnate
		}else{
			return 2;//Y...~
		}
	}


	return -1;
}

void sort_CON_bubble(int *INarray,int sz){
	for(int i=0;i<sz-1;i++){
		for(int j = 0 ; j<sz-i-1;j++){
			if(INarray[j]>INarray[j+1]){
				int buf=INarray[j+1];
				INarray[j+1]=INarray[j];
				INarray[j]=buf;
			}
		}
	}
}

int sortED_together(int *INarray,int sz){
	sort_CON_bubble(INarray,sz);
	for(int i = 0 ; i < sz-1 ;i++){
		if(INarray[i+1]!=INarray[i]+1){
			return 0;
		}
	}
	return 1;
}


int check_if_connect(int *input_array,int sz){
	int CN=connection(input_array,sz);
	sz =sz/(int)sizeof(int);

	if(CN==0||CN==-1){return(CN);}
	if(CN==1){
		int *check_is_togetherX = malloc(sz/2);
		for (int i = 0 ; i < sz ; i+=2){
			check_is_togetherX[i/2]=input_array[i+1];
		}
		return (sortED_together(check_is_togetherX,sz/2));
	}else{
		int *check_is_togetherY = malloc(sz/2);
		for (int i = 0 ; i < sz ; i+=2){
			check_is_togetherY[i/2]=input_array[i];
		}
		return (sortED_together(check_is_togetherY,sz/2));
	}
}

void cls(char *targ_string , int sz){

	for (int i = 0 ; i < sz ; i++){
		targ_string[i]=' ';
	}
}

void initallize(int num,int *INarray,int sz){
	sz/=(int)sizeof(int);
	for (int i = 0 ; i < sz ; i++){
		INarray[i]=num;

	}
}

void print_raw_data (int *INarray,int sz){
	sz/=(int)sizeof(int);
	for (int i = 0 ; i < sz ; i++){

		printf("%d",INarray[i]);
	}
	eNter();
}

void data_in(int x,int y ,int sat,int *targ){
	targ[(x-1)*7+y-1]=sat;//x=|;y=-
}

void int2plot(int *int_tar,int sz_i,char *str_tar , int sz_s){
	int sz;
	if(sz_s!=sz_i){
		printf("\nCODE ERROR!\n@fn:int2plot\nproblem:target int & string size not same");

	}else
	{
		sz=sz_i;
	}
	for (int i = 0 ; i <sz ;i++){
		switch(int_tar[i]){
			case 0:
				str_tar[i]=' ';
				break;
			case 1:
				str_tar[i]='A';
				break;
			case 2:
				str_tar[i]='a';
				break;
			case 3:
				str_tar[i]='B';
				break;
			case 6:
				str_tar[i]='b';
				break;
			case 4:
				str_tar[i]='C';
				break;
			case 8:
				str_tar[i]='c';
				break;

			case 5:
				str_tar[i]='X';
				break;
		}
	}
}

void boat(int *int_tar,int sz_i,char *str_tar , int sz_s){
	int sz;
	if(sz_s!=sz_i){
		printf("\nCODE ERROR!\n@fn:int2plot\nproblem:target int & string size not same");

	}else
	{
		sz=sz_i;
	}
	for (int i = 0 ; i <sz ;i++){
		switch(int_tar[i]){
			case 0:
				str_tar[i]=' ';
				break;
			case 1:
				str_tar[i]='A';
				break;
			case 2:
				str_tar[i]=' ';
				break;
			case 3:
				str_tar[i]='B';
				break;
			case 6:
				str_tar[i]=' ';
				break;
			case 4:
				str_tar[i]='C';
				break;
			case 8:
				str_tar[i]=' ';
				break;

			case 5:
				str_tar[i]=' ';
				break;
		}
	}
}

void bord(int *int_tar,int sz_i,char *str_tar , int sz_s){
	int sz;
	if(sz_s!=sz_i){
		printf("\nCODE ERROR!\n@fn:int2plot\nproblem:target int & string size not same");

	}else
	{
		sz=sz_i;
	}
	for (int i = 0 ; i <sz ;i++){
		switch(int_tar[i]){
			case 0:
				str_tar[i]=' ';
				break;
			case 1:
				str_tar[i]=' ';
				break;
			case 2:
				str_tar[i]='O';
				break;
			case 3:
				str_tar[i]=' ';
				break;
			case 6:
				str_tar[i]='O';
				break;
			case 4:
				str_tar[i]=' ';
				break;
			case 8:
				str_tar[i]='O';
				break;

			case 5:
				str_tar[i]='X';
				break;
		}
	}
}

void plot_bord(int *intarray,int sz1,char *instring,int sz2){
	bord(intarray,sz1,instring,sz2);
	plot_map(instring);
}

void plot_boat(int *intarray,int sz1,char *instring,int sz2){
	boat(intarray,sz1,instring,sz2);
	plot_map(instring);
}

void plot_all(int *intarray,int sz1,char *instring,int sz2){
	int2plot(intarray,sz1,instring,sz2);
	plot_map(instring);
}

int die_check(int *targ,int sz,int *INwin,int winsz){
	int b4 = 0;
	int b3 =0;
	int b2 = 0;
	for(int i = 0 ; i < sz ; i++){
		switch(targ[i]){
			case 2:
				b2++;
				break;
			case 6:
				b3++;
				break;
			case 8:
				b4++;
				break;

		}
	}
	if(b2==2){b2=1;}else{b2=0;}
	if(b3==3){b3=1;}else{b3=0;}
	if(b4==2){b4=1;}else{b4=0;}
	if(INwin[0]!=b2){printf("該次轟炸有命中一個軍艦，名稱為");
		printf(boat2);
		printf("且被擊沉");
		INwin[0]=b2;
		return 2;
	}
	if(INwin[1]!=b3){printf("該次轟炸有命中一個軍艦，名稱為");
		printf(boat3);
		printf("且被擊沉");
		INwin[1]=b3;
		return 3;
	}
	if(INwin[2]!=b4){printf("該次轟炸有命中一個軍艦，名稱為");
		printf(boat4);
		printf("且被擊沉");
		INwin[2]=b4;
		return 4;
	}




	return 0;

}

int vic(int *WINtarg,int WINsz){
	int win_buf=1;
	for(int i = 0 ; i<WINsz ; i++){
		win_buf*=WINtarg[i];
	}
	return(win_buf);
}

int att_changer(int *dat,int sz,int x,int y,int *winIN,int winINsz){
	int index=(x-1)*7+y-1;
	if(dat[index]==0){
		data_in(x,y,5,dat);
		printf("該次轟炸沒有命中任何軍艦");
		return 0;
	}
	if((dat[index]==2)||(dat[index]==6)||(dat[index]==8)){
		printf("錯誤，已攻擊過");
		return -1;
	}
	if((dat[index]==1)||(dat[index]==3)||(dat[index]==4)){

		data_in(x,y,dat[index]*2,dat);
		int buf=die_check(dat,sz,winIN,winINsz);
		if(buf!=0){return (buf);}else{
			printf("該次轟炸有命中一個軍艦，該軍艦的名稱為");
			switch(dat[index]){
				case 2:
					printf(boat2);
return -2;
					break;
				case 6:
					printf(boat3);
return -3;
					break;
				case 8:
					printf(boat4);
return -4;
					break;
			}
		}
	}


	return -1;
}






int main()

{
	int SZ = (CHART_X_HOWMANY*CHART_Y_HOWMANY*(int)sizeof(char));
	char *str49=malloc(SZ);
	strcpy(str49,"abcdefghijklmnopqrstuvwxyz0123456789@#$9876543210");
	int data[SZ];
	initallize(0,data,sizeof(data));
	int win[kind_of_boat];
	initallize(0,win,sizeof(win));

	/*
	 *data_info
	 *un_def=0
	 *boat_a:1;b:3;c:4
	 *boat_hited::abc=268
	 *empty_hit=5
	 */

	print_raw_data(data,sizeof(data));
	data_in(1,6,1,data);
	data_in(5,7,2,data);
	print_raw_data(data,sizeof(data));
	plot_boat(data,SZ,str49,SZ);
	plot_bord(data,SZ,str49,SZ);
	plot_all(data,SZ,str49,SZ);
	//	int2plot(data,SZ,str49,SZ);
	//	boat(data,SZ,str49,SZ);
	//bord(data,SZ,str49,SZ);

	//	plot_map(str49);


	//	cls(str49,SZ);
	//	plot_map(str49);
	eNter();
	int see[4] = {7,5,7,6};
	printf("\n%d\n",check_if_connect(see,sizeof(see)));
	return 0;

}
