#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

void printdir(char *dir, int depth) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory : %s\n", dir);
		return;
	}

	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
			continue;
		}
		printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-r");
		printf((statbuf.st_mode & S_IRUSR) ? "r": "-");
		printf((statbuf.st_mode & S_IWUSR) ? "w": "-");
		printf((statbuf.st_mode & S_IXUSR) ? "x": "-");
		printf((statbuf.st_mode & S_IRGRP) ? "r": "-");
		printf((statbuf.st_mode & S_IWGRP) ? "w": "-");
		printf((statbuf.st_mode & S_IXGRP) ? "x": "-");
		printf((statbuf.st_mode & S_IROTH) ? "r": "-");
		printf((statbuf.st_mode & S_IWOTH) ? "w": "-");
		printf((statbuf.st_mode & S_IWOTH) ? "x": "-");
		printf(" %d", statbuf.st_uid);
		printf(" %d", statbuf.st_gid);
		printf(" %ld", statbuf.st_size);
		printf(" %s", ctime(&statbuf.st_mtime));

		printf(" %s\n",entry->d_name);

		


	}


	closedir(dp);
}

int main()
{

	printdir("/home/student/siddharth_200905344/week2_os",0);
	printf("done.\n");
	return 0;
}