#include "types.h"
#include "user.h" 
#include "date.h" 

int check_leap(int);
void month_name(int);
void month_number(int x);
void day_name(int,int,int);
void time(void);
void today(void);
void command_s(void);
void command_plus1(void);
void command_r(void);
void day(char *);
void day2(char *x);

int main(int argc, char *argv[])
{
	if(argc==1)
	today();

	else if((argc==2)&&(strcmp("-r",*(argv+1))==0))
	command_r();

	else if((argc==2))
	day(*(argv+1)); 
	//command_plus1();
	
	else if((argc==3))
	day2(*(argv+1)); 	
	//command_s();

	else printf(1,"Invalid command. Please try again.\n");
	
exit();
}


int check_leap(int x)
{
	int flag = 0;
	if(x%400==0)
		flag = 1;
	else if(x%100==0)
		flag = 0;
	else if(x%4==0)
		flag = 1;
	else 
		flag = 0;
	return(flag);
}

void month_name(int x)
{
	switch(x)
	{
		case 1:printf(1,"Jan");
		       break;
		case 2:printf(1,"Feb");
		       break;
		case 3:printf(1,"Mar");
		       break;
		case 4:printf(1,"Apr");
		       break;
		case 5:printf(1,"May");
		       break;
		case 6:printf(1,"Jun");
		       break;
		case 7:printf(1,"Jul");
		       break;
		case 8:printf(1,"Aug");
		       break;
		case 9:printf(1,"Sep");
		       break;
		case 10:printf(1,"Oct");
		       break;
		case 11:printf(1,"Nov");
		       break;
		case 12:printf(1,"Dec");
		       break;
	}
}

void month_number(int x)
{
	switch(x)
	{
		case 1:printf(1,"01");
		       break;
		case 2:printf(1,"02");
		       break;
		case 3:printf(1,"03");
		       break;
		case 4:printf(1,"04");
		       break;
		case 5:printf(1,"05");
		       break;
		case 6:printf(1,"06");
		       break;
		case 7:printf(1,"07");
		       break;
		case 8:printf(1,"08");
		       break;
		case 9:printf(1,"09");
		       break;
		case 10:printf(1,"10");
		       break;
		case 11:printf(1,"11");
		       break;
		case 12:printf(1,"12");
		       break;
	}
}

void day_name(int x,int y,int z)
{
	int initial_day = 4;
	int count = 0;	
	if(x>1970)
	{
		for(int i=1970;i<x;i++)
		{
			if(check_leap(i))
				count += 366;
			else
				count += 365;
		}
	}
	for(int i=1;i<y;i++)
	{
		if(i==2)
		{
			if(check_leap(x))
				count += 29;
			else
				count += 28;
		}
		else if((i<8)&&(i%2==1))
			count += 31;
		else if((i<8)&&(i%2==0))
			count += 30;
		else if((i>=8)&&(i%2==0))
			count += 31;
		else
			count += 30;
	}

	int final_day = (initial_day+count+z-1)%7;
	switch(final_day)
	{
		case 0:printf(1,"Sun");
		       break;
		case 1:printf(1,"Mon");
		       break;
		case 2:printf(1,"Tue");
		       break;
		case 3:printf(1,"Wed");
		       break;
		case 4:printf(1,"Thu");
		       break;
		case 5:printf(1,"Fri");
		       break;
		case 6:printf(1,"Sat");
		       break;
	 }
}

void time()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	if(r.minute>59)
	{
		r.hour += 8;
		r.minute = r.minute-59;
	}
	else
	{
		r.hour += 7;
	}
	if(r.hour>=24)
		r.hour -= 24;
	printf(1," %d:%d:%d",r.hour,r.minute,r.second);
}

void today()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);
	printf(1," ");
	month_name(r.month);
	printf(1," %d",r.day);
	time();
	printf(1," WIB");
	printf(1," %d\n",r.year); 
}

void command_s()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	month_name(r.month); 
	printf(1,"/%d/%d",r.day,r.year);
	time();
	printf(1,"\n");
}

void command_plus1()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}	
	printf(1,"%d-",r.day);
	month_number(r.month); 
	printf(1,"-%d\n",r.year);
}

void command_r()
{
	printf(2,"blm bs");
}
void day(char *x)
{
	command_plus1();
}
void day2(char *x)
{
	command_s();
}
