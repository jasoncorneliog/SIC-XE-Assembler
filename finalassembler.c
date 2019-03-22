#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<mysql.h>
#include "myhex.h"
#include "get_obj.h"
//#include "conv.h"


		FILE *fp;
		int locctr=0,starting_add,op_no=1,qq=1;
		char *program_name,*first,*p_name,pt[10];
		char filename[10];
		void pass1();
		void pass2();
		int check(char *,int line_no);// return 1 will say end reched
		void get_token();
		char *label,*operator,*operand1,*operand2,*extra;
		char line[100];
		int file_length;
//MAIN

void header_record(char *length)
{
    char te[10];
    FILE *fp;
    char *header=(char*)malloc(25*sizeof(char));
    int i=0,temp=0;
	decimal_hexa(starting_add,te);
    header[0]='H';
    header[1]='^';
    header[2]='\0';
//	printf("hi");
	program_name=pt;
    strcat(header,program_name);
    if(strlen(header)<8)
    for(i=strlen(header);i<8;i++)
    {
        strcat(header," ");
    }
    strcat(header,"^");
    strcat(header,te);
    temp=strlen(header)+6-strlen(te);
    for(i=strlen(header);i<temp;i++)
    {
        strcat(header," ");
    }
    strcat(header,"^");
    strcat(header,length);
     temp=strlen(header)+6-strlen(te);
    for(i=strlen(header);i<temp;i++)
    {
        strcat(header," ");
    }
    //printf("%d",strlen(header));char *starting_add,char *next_objcode)
   // printf("%s",header);
    //fprintf(fp,"%s\n",header);
    fp=fopen("records_outut.c","w");
    fprintf(fp,"%s\n",header);
    fclose(fp);
}





void free_arr(char *a)
{
    int i;
    for(i=0;i<strlen(a);i++)
    a[i]='\0';
}




int text_record(int end_file)
{
    FILE *f;
    int i=0,temp,dl,flag=1,length;//dl is to count no.of delimiters
    int address1,address2;//address1 is for initial address while add2 is for other addresses
    char starting_add[10];//stores hexadecimal address
        char ob_code[65];//=(char*)malloc(65*sizeof(char));
    char leng_of_record[2];//=(char*)malloc(2*sizeof(char));
char text[100];//=(char*)malloc(1000*sizeof(char));
    char objcode[8];//(char*)malloc(8*sizeof(char));//temporary objcode holder
text[0]='T';
    text[1]='^';
    text[2]='\0';
puts(text);
{
    temp=0;
    dl=0;
    length=0;
puts(text);
    get_objcode(&address1,ob_code,qq);
	qq++;
    strcat(ob_code,"^");dl++;
//	printf("asdlkj%d\n",end_file);
   end_file--;
   // ob_code[strlen(ob_code)]='\0';
   //printf("hiii%d\n",end_file);
    starting_add[0]='\0';
    strcat(starting_add,"aaaa00");
    strcat(text,starting_add);
    temp=strlen(text)+6-strlen(starting_add);
    for(i=strlen(text);i<temp;i++)
    {
        strcat(text," ");
    }
    strcat(text,"^");
        while(flag==1)
    {
	if(end_file>0)
        get_objcode(&address2,objcode,qq);
        temp=(strlen(objcode)+strlen(ob_code)-dl);
        if(temp<=60&&end_file>0)
        {
		qq++;
		printf("asdlkj%d\n",end_file);
            strcat(ob_code,objcode);
            end_file--;
            free_arr(objcode);
 	   strcat(ob_code,"^");
           dl++;
        }
    else
    {
    flag=0;
    }
    }
   strcat(text,"0a");
    strcat(text,"^");dl++;
    strcat(text,ob_code);
f=fopen("records_outut.c","a+");
fprintf(f,"\n%s\n",text);
fclose(f);

   return end_file;
}
}


void end_record(char *exe_address)
{
    FILE *fp;
    char *end=(char*)malloc(10*sizeof(char));
    end[0]='E';
    end[1]='^';
    end[2]='\0';
    strcat(end,exe_address);
    fp=fopen("records_outut.c","a+");
    fprintf(fp,"%s\n",end);
    fclose(fp);
}

		int main(int a,char *arg[])
	{
		char c; 
		strcpy(filename,arg[1]);
		FILE *fp;
		fp=fopen(arg[1],"r");
		while((c=getc(fp))!=EOF)
		printf("%c",c); 
                delete_inter();
		delete_sym();
		pass1();
//		fetch();
		printf("\nStarting address=%d\n",starting_add);
		printf("\nlength=%d\n",(locctr-starting_add)); 
		printf("\nLocation counter= %d\n",locctr);
		return 1; 
	}
//Pass-1
		void pass1()
		{
			  int line_ptr=0,buff_ptr=0,line_no=1;
				  fp=fopen(filename,"r");
  		        		  fseek(fp,0,SEEK_END);
				  file_length=ftell(fp);
					  fseek(fp,0,SEEK_SET);
			  char c,buffer[file_length];
					  fread(buffer,1,file_length,fp);
		 while(buff_ptr<file_length)
			 {
				line_ptr=0;
					  while(buff_ptr<file_length)
        					{
                					c=buffer[buff_ptr++];
               						int i=(int)c;
                					if(i==10) {break;}
                					line[line_ptr++]=c;

					        }
	  line[line_ptr]='\0';

			  if(line_ptr==0)
				{line_no++;continue;}
  			char *start,*addr,*extr;
  				p_name=strtok(line," ");
  				start=strtok(NULL," ");
  				addr=strtok(NULL," ");
  				extr=strtok(NULL," ");
  				program_name=p_name;
				 printf("\nProgram name= %s\n",p_name);
				strcpy(pt,p_name);
  			if(p_name[0]==';')
				{line_no++;continue;}
			  if(strcmp(p_name,"START")==0)
					{error("program name missing",line_no);break;}
  		          if(!is_alpha(p_name))
					error("program name must be in alphabet",line_no);
			  if(start==NULL||start[0]==';') 
					{error("START must follow after program name",line_no);break;} 
			 to_upper(start);

			 if(strcmp(start,"START")!=0)
				 	{error("START MISSING",line_no);break;}

			  if(addr==NULL||addr[0]==';') 
					 break;
 		else 
  				if((locctr=get_hexa(addr))==-1)
  				{ 
 				locctr=0;
				error("address should be in hexadecimal",line_no);
  			 	break;
				}

		  if(extr==NULL) 
    			break;
 		 if(extr[0]==';')
 		        break;

		else
				  {error("too many argument",line_no);break;}
 				 break;
	 }
//start ends


		line_no++;
		starting_add=locctr;
 int end=0,f_line=0;
 			while(buff_ptr<file_length)
 				 {
 				   line_ptr=0;
 				       while(buff_ptr<file_length)
 					       {
        				        c=buffer[buff_ptr++];
        				        int i=(int)c;
        				        if(i==10) {break;}
        				        line[line_ptr++]=c;

       						 }
      		  line[line_ptr]='\0';
		if(line_ptr==0)
			 {line_ptr++;continue;}
 		if(end==1)
			{error("after end no code should exist",++line_no);return;}
		if(check(line,line_no)==0)
			line_no++;
		else
			end=1;

		  }

		if(end==0)
			 {error("no end",line_no);}

 fclose(fp);
int length_=locctr-starting_add;
char length_char[5];
decimal_hexa(length_,length_char);
	header_record(length_char);
    //text_record("0000");
int y;
y=op_no-1;
printf("goood   %d\n",y);
    while(y>0)
    {
        y=text_record(y);

    }
   end_record("1000");

	 return;
}
//int insert_inter(int op_no,int addr,char *operator,char *operand1,char *operand2);

int check(char line[],int line_no)
{

	  label=strtok(line," ");
	 operator=strtok(NULL," ");
	 operand1=strtok(NULL," ");
 	operand2=strtok(NULL," ");
 	extra=strtok(NULL," ");

		 if(label[0]==';')
			 return 0;
	 to_upper(label);
 int format=3;
 		if(label[0]=='+')
			 {label++;format=4;}


	if(operator==NULL||operator[0]==';')
		 {
			if(search_opcode0(label))
				{
				 insert_inter(line_no,locctr,label,"-","-",1,"-",op_no);op_no++;
				 locctr+=1;return 0;
				}

	if(strcmp(label,"END")==0)
		 {error("end should have starting address",line_no);return 1;}
	if(search_opcode1(label))
		 {error("operand must have argument",line_no);return 0;}
        if(search_opcode2(label))
		 {error("operator must have 2 arguments",line_no);return 0;}
		  error("invalid oparand",line_no);
	return 0;
 }
 to_upper(operator);

	 if(operator[0]=='+')
		{operator++;format=4;}
 if(operand1==NULL||operand1[0]==';')
 {

		if(search_opcode0(label))
			 {error("operator must not contain operator",line_no);return 0;}
	if(search_opcode0(operator))
		{
		 if(!is_alpha(label))
				 {error("label must be alphabet",line_no);return 0;}
		 if(search_sym(label))
				 {error("label duplication",line_no);return 0;}
		 insert_sym(label,locctr);
			insert_inter(line_no,locctr,operator,"-","-",1,"-",op_no);op_no++;
			locctr+=1;return 0;
		}
	if(search_opcode1(label))
		{
		  if(strcmp(label,"CLEAR")==0||strcmp(label,"SVC")==0||strcmp(label,"TIXR")==0)
		  	{locctr+=2;format=2;}
		  else
		  	locctr+=format;
		  insert_inter(line_no,locctr,operator,operand1,"-",format,"-",op_no);op_no++;
		  return 0;
		}
	if(search_opcode2(label))
		{error("operator must have 2 arguments",line_no);return 0;}
	if(search_opcode1(operator))
		 {error("operator must have argument",line_no);return 0;}
	if(search_opcode2(operator))
		 {error("operator must have 2 arguments",line_no);return 0;}
	 if(strcmp(label,"END")==0)
		 { return 1;}
	error("invalid operand",line_no);
	return 0;
 }
int t=-1;
char alpha[5];
   t=get_deci(operand1);
decimal_hexa(t,alpha);
to_upper(operand1);
  if(operand2==NULL||operand2[0]==';')
 {
	 if(search_opcode2(label))
	  {
		insert_inter(line_no,locctr,label,operator,operand1,2,"-",op_no);op_no++;
		locctr+=2;return 0;
	  }

		if(search_opcode1(operator)) 
			{
        			 if(!is_alpha(label))
					{error("label must be alphabet",line_no);return 0;}
                 		if(search_sym(label))
					 {error("label duplication",line_no);return 0;}
                		 insert_sym(label,locctr);

				if(strcmp(operator,"CLEAR")==0||strcmp(operator,"SVC")==0||strcmp(operator,"TIXR")==0)
					{
						insert_inter(line_no,locctr,operator,operand1,"-",2,"-",op_no);op_no++;
                        			locctr+=2;
					}

				else	{
		 		insert_inter(line_no,locctr,operator,operand1,"-",format,"-",op_no);op_no++;
				locctr+=format;
					}
		return 0;
               		 }


		 if(strcmp(operator,"WORD")==0)
			  {  printf("ds");
				if(!is_alpha(label))
					 {error("label must be alphabet",line_no);return 0;}
		            if(search_sym(label))
					 {error("label duplication",line_no);return 0;}
				if(t==-1)
					{error("operand must be integer",line_no);return 0;}
			
				insert_inter1(line_no,locctr,operator,"-","-",5,alpha,op_no);op_no++;
			insert_sym(label,locctr);locctr+=3;return 0;}


		 if(strcmp(operator,"RESW")==0)
			{   if(!is_alpha(label))
					 {error("label must be alphabet",line_no);return 0;}
		            if(search_sym(label))
					 {error("label duplication",line_no);return 0;}
                		 //insert_sym(label,locctr);


				if(t==-1)
						{error("invalid oparand",line_no); return 0;}
                                          insert_sym(label,locctr);locctr+=(t*3);
				
                                              return 0;
                        }

		if(strcmp(operator,"RESB")==0)
                        {
				 if(!is_alpha(label))
					 {error("label must be alphabet",line_no);return 0;}
		                 if(search_sym(label))
					 {error("label duplication",line_no);return 0;}
               			  //insert_sym(label,locctr);
				if(t==-1)
					  error("invalid oparand",line_no);

				else
					   {insert_sym(label,locctr); locctr+=t;}
                          return 0;
                        }



		 if(strcmp(operator,"BYTE")==0)
                {      int i;

				 if(!is_alpha(label))
					 {error("label must be alphabet",line_no);return 0;}

                		 if(search_sym(label))
					 {error("label duplication",line_no);return 0;}

				 insert_sym(label,locctr);
				//insert_inter(line_no,locctr,operator,"-","-",5,
                       i=strlen(operand1);

				if(i>3&&operand1[0]=='X'&&operand1[1]=='\''&&operand1[i-1]=='\'')
			{
					int m;
					m=i;
					i-=3;
					insert_sym(label,locctr);
					locctr+=i;
					char ln[2];
					strcat(ln,operand1[2]);
					strcat(ln,operand1[3]);
					printf("%s",ln);

			}

		/*		if(i>3&&operand1[0]=='C'&&operand1[1]=='\''&&operand1[i-1]=='\'')
                        {
					int f;
					f=i;
					i-=3;
		        		insert_sym(label,locctr);
                       			locctr+=i;
				int q2,k,m,n,c[3],o,p,q1;
				p=0;
				o=1;
				q1=0;
				q2=0;
				for(k=2;k<i-1;k++)
				{
				m=(int)operand1[k];
				decimal_hexa(m,c[o]);
				o++;
				}
				if(f==6)
				{
						for(o=1;o<4;o++)
						{
							p=p+c[o];
							if(q1<2){p=p*100;}
							q1++;
						}
					insert_inter(line_no,locctr,operator,"-","-",5,p,op_no);op_no++;
				}
				else if(f==5)
				{
					for(o=1;o<3;o++)
                                                {
                                                        p=p+c[o];
                                                        if(q2<1){p=p*100;}
                                                        q2++;
                                                }
                                        insert_inter(line_no,locctr,operator,"-","-",5,p,op_no);op_no++;
				}

				else if(f==4)
				{ for(o=1;o<2;o++)
                                                {
                                                        p=p+c[o];
                                                }
                                        insert_inter(line_no,locctr,operator,"-","-",5,p,op_no);op_no++;

				}
			}*/

			else
				 error("operand formate = C'operand' or x'operand' ",line_no);
             return 0 ;
		}


		   if(strcmp(operator,"END")==0) {

						if(!is_alpha(label))
							 {error("label must be alphabet",line_no);return 1;}
		                                 if(search_sym(label))
							 {error("label duplication",line_no);return 1;}
                		                 insert_sym(label,locctr);
						//if(search_sym(operand)) {error("",line_no);return 1;}
							locctr+=3;return 1;}
                			error("undefined operator ",line_no);
               				 return 0;
 						}
  			to_upper(operand2);
  			if(extra==NULL||extra[0]==';')
		{
				if(search_opcode2(operator))
					{
					if(!is_alpha(label))
							 {error("label must be alphabet",line_no);return 0;}
                 			if(search_sym(label))
							 {error("label duplication",line_no);return 0;}
		 			insert_sym(label,locctr);
					insert_inter(line_no,locctr,operator,operand1,operand2,2,"-",op_no);op_no++;
					locctr+=2;
					 return 0;
					}
		 error("undefined operator ",line_no);
                return 0;

		}
	error("too many arguments",line_no);
 	return 0;
}

