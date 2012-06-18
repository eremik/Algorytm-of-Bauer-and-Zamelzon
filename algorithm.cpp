#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
 
char stack_z[10];
double stack_c[10];
int tos_z=0;
int tos_c=0;
char   number[11];  
 
void push_z (char a)
{
    stack_z[tos_z]=a;
    tos_z++;
}
 
void push_c (double a)
{
    stack_c[tos_c]=a;
    tos_c++;
}
 
char pop_z ()
{
    tos_z--; 
    return stack_z[tos_z];
}
 
double pop_c ()
{
    tos_c--; 
    return stack_c[tos_c];
}
 
void do_op ()
{
    double op1=pop_c();
    double op2=pop_c();
    char znak=pop_z();
    double res;
    switch (znak)
    {
    case '+': res=op1+op2; break;
    case '-': res=op2-op1; break;
    case '*': res=op1*op2; break;
    case '/': res=op2/op1; 
    }
    push_c(res);
}
 
int main()      
{
    FILE *in; 
    in=fopen("expr_valin.txt", "r");
    char ch;
    int t=0, i=0; 
    double count;
i=0;
while((ch=getc(in))!='\n')
{
top_of_switch: 
 
 switch(ch) 
 {
      case '=': 
        { 
            switch(stack_z[tos_z-1]) 
            {
            case '*': case '/': case '+'   : case '-':
                {
                    do_op(); goto top_of_switch;
                }
            case '(': 
                {
                    cout<<"Error"<<endl; continue;
                }
            case '\0': 
                {
                    break;
                }
            }
        }
 
    case '(': 
        {push_z(ch); continue;}
   
    case ')': 
        { 
            switch(stack_z[tos_z-1]) 
            {
                case '*': case '/': case '+'   : case '-':
                {
                    do_op(); goto top_of_switch;
                }
                case '(': 
                {
                    pop_z(); continue;
                }
            }
        }
 
    case '+': case '-':
        {
            switch(stack_z[tos_z-1]) 
            {
            case '\0': case '(': push_z(ch); continue;
            case '+'   : case '-': do_op(); push_z(ch); continue;
            default    :  do_op(); goto top_of_switch;
            }
        }
 
    case '/':
        {
            switch(stack_z[tos_z-1]) 
            {
            case '*': case '/':  {do_op(); push_z(ch); continue;}
            default : {push_z(ch); continue;}
            }
        }
    
    case '*':
        {
            switch(stack_z[tos_z-1]) 
            {
            case '*': case '/':  {do_op(); push_z(ch); continue;}
            default : {push_z(ch); continue;}
            }
        }
 
    default :
        {
            i = 0;
            do number[i++] = ch; while(isdigit(ch=getc(in)) || (ch=='.'));
            number[i] = '\0';  ungetc(ch,in);
            push_c(atof(number));
        }
      
    }
    }
    fclose(in);
    cout<<"Calculation is completed\n";
    count=stack_c[0];
    cout<<count<<" ";
    cout<<endl;
    system("PAUSE");
    return 0;
}
