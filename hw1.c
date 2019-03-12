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

int comp(char* targ,char* moth){


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


printf("\n請輸入待測發票:\n");
	char *input_num=malloc(LEN+1);
	strcpy(input_num," "); 
scanf("%s",input_num);


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

	return 0;

}

