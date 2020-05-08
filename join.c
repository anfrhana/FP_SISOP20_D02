#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int length(char *input){
    int length = 0;
    while(input[length]!='\0')
    {
        length++;                               
    }
    return length;
}

int main(int argc, char *argv[]){
	int file1, file2;

	char buf1[256], buf2[256];
	

	if((file1 = open(argv[1], O_RDONLY)) < 0){                     
		printf(1, "Failed to read files %s\n", argv[1]);
		exit();
	}
	if((file2 = open(argv[2], O_RDONLY)) < 0){                     
		printf(1, "failed to read %s\n", argv[2]);
		exit();
	}

	read(file1, buf1, sizeof(buf1)); 
	read(file2, buf2, sizeof(buf2)); 

	int p1;
	int p2;
	p1 = length(buf1);                                       
	p2 = length(buf2);
	
	int cnt1=0,cnt2=0;
	while((cnt1 != p1) || (cnt2 != p2)){

		while(buf1[cnt1] != '\n'){               
			printf(2,"%c",buf1[cnt1]);
			cnt1++;
		}

		while(buf1[cnt1] == '\0'){              
			cnt1++;
		}
		cnt1++;

		printf(2," ");

		while(buf2[cnt2] != '\n'){               	
			printf(2,"%c",buf2[cnt2]);
			cnt2++;
		}

		while(buf2[cnt2] == '\0'){               	
			cnt2++;
		}
		cnt2++;
		
		printf(2,"\n"); 
		if ((cnt1 == p1) || (cnt2 == p2)) break;

	}
	
	close(file1);
	close(file2);
	exit();
}
