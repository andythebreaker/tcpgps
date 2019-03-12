#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10
int ex =-1;
/*
 * 
 * sub fuction need put before main
 * 0ggVG=
 * need first initialization or will error
 * printf && scanf
 * need %~~
 * char -> c
 * string -> s
 * int -> d
 * scan need & but print dont need
 * 
 * ...update when i recall
 *
 * 如果輸入錯誤，直接重來，沒有提示訊息!
 */

//C-sub_string

/*
 * how to use:
 * substr(t, s, 6, 5);
 * t = out put
 * s = in put
 */
 void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
	   strncpy(dest, src + start, cnt);
	   dest[cnt] = 0;
	 }

/*
int try_pr(){
	//string abc "abc";
	int II=17;
	printf("OK");
	return (0);
}
*/

int scn_chk (char* tar_string ,int how_meny){
	size_t length_=strlen(tar_string);
	//	printf("%lu",length_);

	if((int)length_==how_meny){
		printf("輸入成功\n");
		return (1);
	}else{
		if(ex!=0){
			printf("輸入錯誤\n");
		}
		ex++;
		return (0);
	}


	return (-1);
}





int main()

{



	char *ssp=malloc(LEN+1);
	char *sp =malloc(LEN+1);
	char *hd1 =malloc(LEN+1);
	char *hd2 =malloc(LEN+1);
	char *hd3 =malloc(LEN+1);
	char *six1 =malloc(LEN+1);
	char *six2 =malloc(LEN+1);
	char *six3=malloc(LEN+1);
	strcpy(ssp," "); 
	strcpy(sp," ");
	strcpy(hd1," ");
	strcpy(hd2," ");
	strcpy(hd3," ");
	strcpy(six1," ");
	strcpy(six2," ");
	strcpy(six3," ");
	/*
	   strcpy(ssp,"12345678"); 
	   strcpy(sp,"87654321");
	   strcpy(hd1,"11111111");
	   strcpy(hd2,"22222222");
	   strcpy(hd3,"33333333");
	   strcpy(six1,"123");
	   strcpy(six2,"456");
	   strcpy(six3,"789");
	   */

	printf("統一發票兌獎系統\n");
	printf("請輸入:\n");
	ex = 0;
	while(scn_chk( ssp,8)==0){
		printf("a. 特別獎\n");
		scanf("%s",ssp); 
	}
	ex = 0;
	while(scn_chk(sp ,8)==0){

		printf("b. 特獎\n");
		scanf("%s",sp);
	}
	ex = 0;
	while(scn_chk(hd1 ,8)==0){
		printf("c. 頭獎的 第一組號碼\n");
		scanf("%s",hd1);
	}
	ex = 0;
	while(scn_chk(hd2 ,8)==0){
		printf("d. 頭獎的 第二組號碼\n");
		scanf("%s",hd2);
	}
	ex = 0;
	while(scn_chk( hd3,8)==0){
		printf("e. 頭獎的 第三組號碼\n");
		scanf("%s",hd3);
	}
	ex = 0;
	while(scn_chk( six1,3)==0){
		printf("f. 增開六獎的 第一組號碼\n");
		scanf("%s",six1);
	}
	ex = 0;
	while(scn_chk( six2,3)==0){
		printf("g. 增開六獎的 第二組號碼\n");
		scanf("%s",six2);
	}
	ex = 0;
	while(scn_chk(six3 ,3)==0){
		printf("h. 增開六獎的 第三組號碼\n");
		scanf("%s",six3);
	}


	printf("\n所有獎項\n");

	printf("\na. 特別獎\n");
	printf("%s",ssp); 
	printf("\nb. 特獎\n");
	printf("%s",sp);
	printf("\nc. 頭獎的 第一組號碼\n");
	printf("%s",hd1);
	printf("\nd. 頭獎的 第二組號碼\n");
	printf("%s",hd2);
	printf("\ne. 頭獎的 第三組號碼\n");
	printf("%s",hd3);
	printf("\nf. 增開六獎的 第一組號碼\n");
	printf("%s",six1);
	printf("\ng. 增開六獎的 第二組號碼\n");
	printf("%s",six2);
	printf("\nh. 增開六獎的 第三組號碼\n");
	printf("%s",six3);

	char *input_num=malloc(LEN+1);
	strcpy(input_num," "); 
	
	ex = 0;
	while(scn_chk(input_num ,8)==0){
		printf("\n請輸入待測發票:\n");
		scanf("%s",input_num);
		
	}
	
	
int rlst =0;

	
	

	
	char *p12=malloc(LEN+1);
	char *p13=malloc(LEN+1);
	char *p14=malloc(LEN+1);
	char *p15=malloc(LEN+1);
	char *p16=malloc(LEN+1);
	
	char *p22=malloc(LEN+1);
	char *p23=malloc(LEN+1);
	char *p24=malloc(LEN+1);
	char *p25=malloc(LEN+1);
	char *p26=malloc(LEN+1);
	
	char *p32=malloc(LEN+1);
	char *p33=malloc(LEN+1);
	char *p34=malloc(LEN+1);
	char *p35=malloc(LEN+1);
	char *p36=malloc(LEN+1);
	
	char *i2=malloc(LEN+1);
	char *i3=malloc(LEN+1);
	char *i4=malloc(LEN+1);
	char *i5=malloc(LEN+1);
	char *i6=malloc(LEN+1);
	
	char *input_3=malloc(LEN+1);
substr(input_3,input_num,5,3);
	substr(p12,hd1,1,7);
	substr(p13,hd1,2,6);
	substr(p14,hd1,3,5);
	substr(p15,hd1,4,4);
	substr(p16,hd1,5,3);
	
	substr(p22,hd2,1,7);
	substr(p23,hd2,2,6);
	substr(p24,hd2,3,5);
	substr(p25,hd2,4,4);
	substr(p26,hd2,5,3);
	
	substr(p32,hd3,1,7);
	substr(p33,hd3,2,6);
	substr(p34,hd3,3,5);
	substr(p35,hd3,4,4);
	substr(p36,hd3,5,3);
	
	substr(i2,input_num,1,7);
	substr(i3,input_num,2,6);
	substr(i4,input_num,3,5);
	substr(i5,input_num,4,4);
	substr(i6,input_num,5,3);
	
	
	if(strcmp(ssp,input_num)==0){rlst =10000000;}else if(
	strcmp(sp,input_num)==0){rlst =2000000;}else if(
	strcmp(hd1,input_num)==0){rlst =200000;}else if(
	strcmp(hd2,input_num)==0){rlst =200000;}else if(
	strcmp(hd3,input_num)==0){rlst =200000;}else if(
		
		strcmp(p12,i2)==0){rlst =40000;}else if(
		strcmp(p22,i2)==0){rlst =40000;}else if(
		strcmp(p32,i2)==0){rlst =40000;}else if(
		
		strcmp(p13,i3)==0){rlst =10000;}else if(
		strcmp(p23,i3)==0){rlst =10000;}else if(
		strcmp(p33,i3)==0){rlst =10000;}else if(
		
		strcmp(p14,i4)==0){rlst =4000;}else if(
		strcmp(p24,i4)==0){rlst =4000;}else if(
		strcmp(p34,i4)==0){rlst =4000;}else if(
		
		strcmp(p15,i5)==0){rlst =1000;}else if(
		strcmp(p25,i5)==0){rlst =1000;}else if(
		strcmp(p35,i5)==0){rlst =1000;}else if(
		
	strcmp(p16,i6)==0){rlst =200;}else if(
	
	strcmp(p26,i6)==0){rlst =200;}else if(
	
	strcmp(p36,i6)==0){rlst =200;}else if(
	strcmp(six1,input_3)==0){rlst =-200;}else if(
	strcmp(six2,input_3)==0){rlst =-200;}else if(
	strcmp(six3,input_3)==0){rlst =-200;}
	
	else {rlst =0;}

	/*
	   scn_chk(ssp,8);

	   printf("%s",sp);
	   int ip=123;

	   scanf("%d",&ip);
	   size_t length=strlen(ssp);
	   printf("字串長度%lu\n",length);
	   printf("%d",ip);
	   try_pr();
	   */
//printf("%d",rlst);
	
	int no_use =0;
	char *op_mon=malloc(LEN+1);
	strcpy(op_mon,"\n中獎!\n中獎結果:");
	
	if (rlst<0){
	strncat(op_mon,"增開",3);
		rlst+=400;
		no_use=1;
	}else if (rlst==0){
	strcpy(op_mon,"\n==未中獎==\n");
	}else{
	no_use=1;
	}
	if(no_use==1){
	switch (rlst){
		case 10000000:
			strncat(op_mon,"特別獎",4);
			break;
			case 2000000:
			strncat(op_mon,"特獎",3);
			break;
			case 200000:
			strncat(op_mon,"頭獎",3);
			break;
			case 40000:
			strncat(op_mon,"二獎",3);
			break;
			
			case 10000:
			strncat(op_mon,"三獎",3);
			break;
			
			case 4000:
			strncat(op_mon,"四獎",3);
			break;
			
			case 1000:
			strncat(op_mon,"五獎",3);
			break;
			
			case 200:
			strncat(op_mon,"六獎",3);
			break;
	}
	}else{
	no_use=0;
	}
	
	printf("%s",op_mon);
	
	
	return 0;

}

