#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<mysql.h>



	int insert_sym(char nam[10],int addr)
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


                                 sprintf(stmt,"insert into symbol values('%s','%d')",nam,addr);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }


   mysql_free_result(result);
   mysql_close(conn);
}




void delete_sym()
                {
                         MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
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

                  if(mysql_query(conn,"use assembler"))
                        {
                                      errormsg(conn);
                        }

                               if(mysql_query(conn,"delete from symbol"))
                                {
                                        errormsg(conn);
                                 }
/*
   mysql_free_result(result);*/
   mysql_close(conn);

}




	int search_sym(char nam[10])
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
                          printf("Gone");
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

                                 sprintf(stmt,"select name from symbol where name='%s'",nam);

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

                                if(!row)
                                        {

                                                return 0;
                                        }
                                else
                                                return 1;

  
   mysql_free_result(result);
   mysql_close(conn);
}



	void error(char error1[30],int line_no)
			{
				 printf("line=%d error: %s\n",line_no,error1);
				 return;
			}

	int check(char *,int line_no);// return 1 will say end reched
	
			

			
			int search_opcode0(char *s) 
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


				 sprintf(stmt,"select mn from optab0 where mn='%s'",s);
                                 
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
			
				if(!row)
					{
				
						return 0;
					}
				else
						return 1;
			
  
   mysql_free_result(result);
   mysql_close(conn);
}



			int insert_inter(int line_no,int addr,char *operator,char *operand1,char *operand2,int format,char *op_code,int op_no)
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
					char op_cod[100]; 

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

			sprintf(op_cod,"select op from table3 where mn='%s'",operator);

			 if(mysql_query(conn,op_cod))
                                {
                                        errormsg(conn);
                                 }
			result=mysql_store_result(conn);
			row=mysql_fetch_row(result);
char *val=row[0];

	sprintf(stmt,"insert into intermediate values('%d','%d','%s','%s','%s','%d','%s','%d')",line_no,addr,operator,operand1,operand2,format,val,op_no);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }


   mysql_free_result(result);
   mysql_close(conn);
}


			
			int search_opcode1(char *s) 
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


                                 sprintf(stmt,"select mn from optab where mn='%s'",s);

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

                                if(!row)
                                        {

                                                return 0;
                                        }
                                else
                                                return 1;

  
   mysql_free_result(result);
   mysql_close(conn);
}



			int search_opcode2(char *s) 
                                {

                                        MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
                                        char stmt[50]; 
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


                             sprintf(stmt,"select mn from optab2 where mn='%s'",s);

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

                                if(!row)
				 {

                                                return 0;
                                        }
                                else
                                                return 1;

  
   mysql_free_result(result);
   mysql_close(conn);
}

/*int fetch(int line_no,char *op_code,char *operand1,char *operand2,int format,int pc)
{
 MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
                                        char stmt[50]; 
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

 		sprintf(stmt,"select pc,op_code,operand1,operand2,format from intermediate where mn='%s'",line_no);

                if(mysql_query(conn,stmt))
                                {
                         errormsg(conn);
                                 }


                        result = mysql_store_result(conn);

                if(result == NULL) 
                        {
                             errormsg(conn);
                         }


int totalrows=mysql_num_rows(result);
int numfields=mysql_num_fields(result);


                row=mysql_fetch_row(result);
                while((row=mysql_fetch_row(result)))
                {
 for(i=0;i<numfields;i++)
                        {
                                char *val=row[i];
                                printf("%s\t",val);
                                printf("\n");
                        }
                }


  
   mysql_free_result(result);
   mysql_close(conn);


}
*/
void delete_inter()
                {
                         MYSQL *conn;
                                        MYSQL_RES *result;
                                        MYSQL_ROW row;
                                        int i;
                                        char *server = "localhost";
                                        char *user = "root";
                                        char *password = "root";
                                        char *database = "mysql";
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

                  if(mysql_query(conn,"use assembler"))
 {
                                      errormsg(conn);
                        }

                               if(mysql_query(conn,"delete from intermediate"))
                                {
                                        errormsg(conn);
                                 }
/*
   mysql_free_result(result);*/
   mysql_close(conn);

}


		
int insert_inter1(int line_no,int addr,char *operator,char *operand1,char *operand2,int format,char *op_code,int op_no)
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
					char op_cod[100]; 

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



	sprintf(stmt,"insert into intermediate values('%d','%d','%s','%s','%s','%d','%s','%d')",line_no,addr,operator,operand1,operand2,format,op_code,op_no);

                                if(mysql_query(conn,stmt))
                                {
                                        errormsg(conn);
                                 }


   mysql_free_result(result);
   mysql_close(conn);
}
