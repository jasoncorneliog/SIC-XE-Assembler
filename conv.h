#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
int conv(char a)
{if(a=='0') return 0;
else if(a=='1')	return 1;
else if(a=='2')	return 2;
else if(a=='3')	return 3;
else if(a=='4')	return 4;
else if(a=='5')	return 5;
else if(a=='6')	return 6;
else if(a=='7')	return 7;
else if(a=='8')	return 8;
else if(a=='9')	return 9;
else if(a=='a'|| a=='A') return 10;
else if(a=='b'|| a=='B') return 11;
else if(a=='c'|| a=='C') return 12;
else if(a=='d'|| a=='D') return 13;
else if(a=='e'|| a=='E') return 14;
else if(a=='f'|| a=='F') return 15;
else return -1;
}
int hexa_decimal(char p[])
{
  int i=0,rem,n,a;
  a=1;
  rem=conv(p[i]);
  n=strlen(p)-1;
  while(i<n)
        {
                rem=conv(p[i++]);
                a=a*rem*16;
        }
  rem=conv(p[i]);
  if(a==1)
        return rem;
  else
        a=a+rem;
 return a;
}

int get_hexa(char *ch)
{	
	int i,x=0,sum=0,temp;
	for(i=strlen(ch)-1;i>=0;i--)
	{
		temp=conv(ch[i]);
		if(temp==-1)
		return -1;
		sum=sum+(temp*pow(16,x));
		x++;
	}
	return sum;
}
int get_deci(char *ch)
{
        int i,x=0,sum=0,temp;
        for(i=strlen(ch)-1;i>=0;i--)
        {
 		temp=conv(ch[i]);
                if(temp<0||temp>9)
                return -1;
                sum=sum+(temp*pow(10,x));
                x++;
        }
        return sum;	
}
void strrev(char* str)
{
    int length = strlen(str),i,j;
    char temp;
	j=length-1;

    for( i = 0;i < length/2; i++,j--){
        temp=str[i];
	str[i]=str[j];
	str[j] = temp;
    }
	    return;
}




void decimal_hexa(int a,char p[])
{
  int i=0,rem;
  if(a==0)
	p[i++]='0';

 else  while(a!=0)
	{
		rem=a%16;	
		switch(rem)
		{
		 case 10: p[i++]='A';break;
		 case 11: p[i++]='B';break;
		 case 12: p[i++]='C';break;
		 case 13: p[i++]='D';break;
		 case 14: p[i++]='E';break;
		 case 15: p[i++]='F';break;
		 default: p[i++]=rem+'0';
		}
		a=a/16;
	}
  p[i]='\0';
  strrev(p);
}
int is_alpha(char *p)
{
  int i,l;
  l=strlen(p);
  for(i=0;i<l;i++)
    if(!isalpha(p[i])) return 0;
  return 1;
}
void to_upper(char *p)
{
 int i,l;
  l=strlen(p);
  for(i=0;i<l;i++)
    p[i]=toupper(p[i]);
	
  return; 
}
void check_nix(char *a,int *n,int *i,char *op_code,int *x,int *xbpe){
        int q,m;
        q=hexa_decimal(op_code);
        m=strlen(a);
        if(a[0]=='#'){
                q=q+1;
                *i=1;
        }
        else if(a[0]=='@'){ 
                q=q+2;
                *n=1;
        }
        else{   
                *n=*i=1;
                q=q+3;
      
        }
        decimal_hexa(q,op_code);
	puts(op_code);
        if('X'==toupper(a[m-1])&&a[m-2]==','){
                *xbpe+=8;
                *x=1;
                a[m-2]='\0';
        }

}
/*
int main()
{
 char p[10]="hiu1ieAL",*a;
 a=p;
 to_upper(a);
 puts(a);
 return 1;
}
*/
