#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


void funk(){
	// usiamo lseek()
	//off_t lseek(int fd, off_t offset, int whence);
	// usiamo lseek per spostarci alla posizione 100 dall'inizio del file
	char * filename = "Text01.txt";
	int fd;
	off_t current_file_offset;

	fd = open(filename, O_RDWR);
	if(fd==-1){
		perror("Error in Open");
		exit(EXIT_FAILURE);
	}
	current_file_offset = lseek(fd, 0, SEEK_CUR);
	printf("Offset attuale: %d\n", current_file_offset);

	// mi sposto alla fine del file

	current_file_offset = lseek(fd, -1, SEEK_END);
	printf("Offset attuale: %d\n", current_file_offset);

	// leggiamo 100 byte dalla posizione 100
	current_file_offset = lseek(fd, 100, SEEK_SET);
	printf("Offset attuale: %d\n", current_file_offset);

	char buff[100 + 1] = {0};
	int res = read(fd, buff, 100);
	printf("Read ha letto %d bytes\n"
			"il cui contenuto e` \n%s\n", res, buff);


	// mi posiziono 100 byte dopo la fine del file
	current_file_offset = lseek(fd, 100, SEEK_END);
	printf("Offset attuale: %d\n", current_file_offset);

	memset(buff, '!', 100);
	res = write(fd, buff, 10);
	printf("Write ha scritto %d bytes\n", res);


}

int main(){
	funk();
	return 0;
}
