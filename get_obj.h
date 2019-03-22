#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"conv.h"
#include<mysql.h>
#include<string.h>
int get_line_no(){
 return 1;
}


char get_reg(char *name)
		{
			  MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
                                        char stmt[150]; 
                         conn = mysql_init(NULL);
          void errormsg(MYSQL *conn)
                {
                          fprintf(stderr, "%s\n", mysql_error(conn));
                          mysql_close(conn);
                }
  
           if(!mysql_real_connect(conn,server,user, password,database,0,NULL,0))
                        {
                                      errormsg(conn);
                        }
  if(mysql_query(conn, "use assembler"))
                        {
                                      errormsg(conn);
                        }

                                 sprintf(stmt,"select value from register where name='%s'",name);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }



                 result = mysql_store_result(conn);
 if(result == NULL) 
                        {
                             errormsg(conn);
                         }

                row=mysql_fetch_row(result);

		char t='c';
		//strcpy(t,row[0]);
		return t;
   mysql_free_result(result);
   mysql_close(conn);
}

void get_line(int op_no,char *op_code,char *operand1,char *operand2,char *format,char *pc,int *line_no)
				{
					  MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
                                        char stmt[150]; 
                         conn = mysql_init(NULL);
          void errormsg(MYSQL *conn)
                {
                          fprintf(stderr, "%s\n", mysql_error(conn));
                          mysql_close(conn);
                }
  
           if(!mysql_real_connect(conn,server,user, password,database,0,NULL,0))
                        {
                                      errormsg(conn);
                        }


	 if(mysql_query(conn, "use assembler"))
                        {
                                      errormsg(conn);
                        }

                                 sprintf(stmt,"select op_code,operand1,operand2,format,addr,line_no from intermediate where op_no='%d'",op_no);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }


                 result = mysql_store_result(conn);


                if(result == NULL) 
                        {
                             errormsg(conn);
                         }

                row=mysql_fetch_row(result);
		char t[10];
		strcpy(op_code,row[0]);
		//puts(op_code);
		strcpy(operand1,row[1]);
		strcpy(operand2,row[2]);
		strcpy(format,row[3]);
		strcpy(pc,row[4]);
		strcpy(t,row[5]);
                *line_no=get_deci(t);


   mysql_free_result(result);
   mysql_close(conn);
}


		int get_addr(char *name)
		{


 					 MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
                                        char stmt[150]; 
                         conn = mysql_init(NULL);
          void errormsg(MYSQL *conn)
                {
                          fprintf(stderr, "%s\n", mysql_error(conn));
                          mysql_close(conn);
                }
  
           if(!mysql_real_connect(conn,server,user, password,database,0,NULL,0))
                        {
                                      errormsg(conn);
                        }
	  if(mysql_query(conn, "use assembler"))
                        {
                                      errormsg(conn);
                        }

                                 sprintf(stmt,"select address from symbol where name='%s'",name);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }



                 result = mysql_store_result(conn);
 if(result == NULL) 
                        {
                             errormsg(conn);
                         }

                row=mysql_fetch_row(result);
		char t[10];
		int a;
	if(!row)
{
			return -1;}
else
		strcpy(t,row[0]);
		a=get_deci(t);
                return a;

   mysql_free_result(result);
   mysql_close(conn);
}







void get_objcode(int *addr1,char text[],int line_no){
char operand1[10],operand2[10],op_code[2],op_code1[2],disp[3],addr[5],*op,cxbpe[1];
int k,target;
int n,i,x,b,p,e,text_index=0,xbpe,format,disp1,length=0,pc,er=0,line;
char s[10],w[10];
	get_line(line_no,op_code,operand1,operand2,s,w,&line);
	format=get_deci(s);
	pc=get_deci(w);
	*addr1=pc;
	n=0,i=0;
	if(format==1){
		text[text_index++]=op_code[0];
		text[text_index++]=op_code[1];
		length+=2;
	}
	if(format==2){
	//	printf("hi");
		if(strcmp(op_code,"B4")==0||strcmp(op_code,"B8")==0)	//clear
		{
		text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
		text[text_index++]=get_reg(operand1);
		text[text_index++]='0';
		}
		else if(strcmp(op_code,"B0")==0)	//svc
		{
		text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
		k=get_deci(operand1);
		decimal_hexa(k,op_code);
                text[text_index++]=op_code[0];
		text[text_index++]='0';
		}
		else if(strcmp(op_code,"A4")==0||strcmp(op_code,"A8")==0)
		{
		text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
                text[text_index++]=get_reg(operand1);
		k=get_deci(operand1);
                decimal_hexa(k,op_code);
                text[text_index++]=op_code[0];
		}
		else{
		text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
		text[text_index++]=get_reg(operand1);
		text[text_index++]=get_reg(operand2);
		}
		length+=4;
	}
	if(format==3){
		xbpe=e=0;
		pc+=3;
		strcpy(op_code1,op_code);
		check_nix(operand1,&n,&i,op_code,&x,&xbpe);
		int q1,var=2;
		char q[3];
		strcpy(op_code1,op_code);
		strcpy(op_code,"00");
		q1=strlen(op_code1)-1;
		var=1;
                        while(q1>=0){
                                op_code[var--]=op_code1[q1--];
                        }
		var=2;
		strcpy(disp,"000");
                if((i==0&&n==1)||(i==1&&n==0))
                        op=operand1+1;
		else
			op=operand1;
		if(i==1&&n==0){
			int a;
			char a1;
			a=get_deci(op);
			if(a==-1)
				printf("error\n");
			decimal_hexa(a,q);
                        q1=strlen(q)-1;
                        while(q1>=0){
                                disp[var--]=q[q1--];
                        }
		}
	     else{
		target=get_addr(op);
		if(target==-1)
		er=-1;
		disp1=target-pc;
		xbpe+=2;
		p=1;
		if(disp1>=0&&disp1<=2047){
			strcpy(disp,"000");
			decimal_hexa(disp1,q);
			q1=strlen(q)-1;
			while(q1>=0){
				disp[var--]=q[q1--];
			}
		}
		if(disp1<0&&disp1>=-2048){
			disp1=4096+disp1;
			decimal_hexa(disp1,disp);
		}
	     }	
		puts(op_code);
		puts(disp);
                text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
		decimal_hexa(xbpe,cxbpe);
		text[text_index++]=cxbpe[0];
		text[text_index++]=disp[0];
		text[text_index++]=disp[1];
		text[text_index++]=disp[2];
		if(strcmp(op_code1,"4C")==0){
			
			strcpy(text,"4F0000");
		}
		length+=6;
	}
	if(format==4){
		xbpe=e=1;
                check_nix(operand1,&n,&i,op_code,&x,&xbpe);
                int aq1,avar=4;
                char aq[5];
		strcpy(op_code1,op_code);
                strcpy(op_code,"00");
                aq1=strlen(op_code1)-1;
                avar=1;
                        while(aq1>=0){
                                op_code[avar--]=op_code1[aq1--];
                        }
                avar=4;
                strcpy(addr,"00000");
		if((i==0&&n==1)||(i==1&&n==0))
                        op=operand1+1;
                else
                        op=operand1;
		 if(i==1&&n==0){
                        int aa;
                        char aa1;
                        aa=get_deci(op);
                        if(aa==-1)
                                printf("error\n");
                        decimal_hexa(aa,aq);
                        aq1=strlen(aq)-1;
                        while(aq1>=0){
                                addr[avar--]=aq[aq1--];
                        }
                }
		else {
			target=get_addr(op);
			if(target==-1)
			er=-1;
                        decimal_hexa(target,aq);
                        aq1=strlen(aq)-1;
                        while(aq1>=0){
                                addr[avar--]=aq[aq1--];
                        }
                   
                }
                text[text_index++]=op_code[0];
                text[text_index++]=op_code[1];
                decimal_hexa(xbpe,cxbpe);
                text[text_index++]=cxbpe[0];
                text[text_index++]=addr[0];
                text[text_index++]=addr[1];
                text[text_index++]=addr[2];
		text[text_index++]=addr[3];
                text[text_index++]=addr[4];
	}
	text[text_index]='\0';
	if(er==-1)
		printf("error");
	printf("that is\n");
	puts(text);
	return;
	
}
/*
int main()
{
char temp[10];
int f,loc;
get_objcode(&loc,temp);
printf("%s\t%d\n",temp,loc);
return 1;
}
*/
