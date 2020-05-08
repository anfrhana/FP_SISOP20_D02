#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void rm_one(char *s) {
	if (unlink(s) < 0) {
		printf(2, "rm: %s failed to delete\n", s);
		return;
	}
}

void rm_recurse(char *dir) {
	int fd;
	char buf[512], *p;
	struct dirent de;
	struct stat st;

	fd = open(dir, O_RDONLY);

	fstat(fd, &st);

	switch (st.type) {
		case T_FILE:
			rm_one(dir);
			break;
		case T_DIR:
			strcpy(buf, dir);
			p = buf+strlen(buf);
			*p = '/';
			p++;

			while(read(fd, &de, sizeof(de)) == sizeof(de)) {
				if(de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
					continue;

				memmove(p, de.name, strlen(de.name));
				p[strlen(de.name)] = 0;

				fstat(open(buf, O_RDONLY), &st);
				if (st.type == T_FILE) 
					rm_one(buf);
				else if (st.type == T_DIR)
					rm_recurse(buf);
			}

			break;
	}

	unlink(dir);

	close(fd);
}

void rm_all(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
	printf(2, "ERROR\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ERROR\n", path);
    close(fd);
    return;
  }

	if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ERROR\n");
    }

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      	if(de.inum == 0) continue;
      	memmove(p, de.name, DIRSIZ);
      	p[DIRSIZ] = 0;
      	if(stat(buf, &st) < 0){
        	printf(1, "ERROR\n", buf);
        	continue;
      	}
		if (st.type == T_FILE)rm_one(&buf[2]);
    }
  close(fd);
}

int main(int argc, char *argv[])
{
	
	if(argc < 2){
		printf(2, "Usage: rm [OPTIONS] files...\n");
		exit();
	}
	if((argc==2)&&(strcmp("*",*(argv+1))==0)){
		rm_all(".");
	}

	else if(argc==2){
		char *nfile = argv[1];
		int cnt = 0;

		for (int i = strlen(nfile); i >= 0; i--) 
 		{
    		   if(nfile[i] != '.'){
      		     cnt++;
   		   }
  		}
		if ((cnt-1) == strlen(nfile)){
		printf (1,"%s: Is a directory\n", nfile);
		}
		else rm_one(argv[1]);
		  
	}		
	else if((argc==3)&&(strcmp("-r",*(argv+1))==0))
	{
		char *nfile = argv[2];
		int cnt = 0;
		for (int i = strlen(nfile); i >= 0; i--) 
 		{
    		   if(nfile[i] == '.'){
      		     cnt++; break;
   		  }

  		}
		if (cnt == 1){
		printf (1,"%s: Not a directory\n", nfile);
		}
		else rm_recurse(argv[2]);
	}
	

	exit();
}

