#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/inotify.h>
#include<limits.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1 ) )
char buffer[BUF_LEN];


void display_notify_event(struct inotify_event* e){
	printf("inotify event wd = %d\n", e->wd);
			//che tipo di evento e` accaduto?
	if ( e-> mask & IN_ACCESS){  //E` STATO APERTO
		printf("IN ACCES [read()]\n");
	}
	if ( e-> mask & IN_ATTRIB){  // MODIFICATI ATTRIBUTI
			printf("IN ATTRIB [read()]\n");
	}
	if ( e-> mask & IN_CLOSE_NOWRITE){  // E` STATO CHIUSO DOPO SOLA LETTURA
			printf("IN NOWRITE [read()]\n");
	}
	if ( e-> mask & IN_CLOSE_WRITE){ // E` STATO CHIUSO DOPO SCRITTURA
			printf("IN CLOSEWRITE [read()]\n");
	}
	if ( e-> mask & IN_CREATE){  // UN FILE O DIR E`` STATO CREATO
			printf("IN CREATE[read()]\n");
	}
	if ( e-> mask & IN_DELETE){  // E` STATO CANCELLATO UN FILE DALL CARTELLA
			printf("IN DELETE [read()]\n");
	}
	if ( e-> mask & IN_DELETE_SELF){ // E` STATO CANCELLATO IL FILE/CARTELLA CHE STO MONITORANDO
			printf("IN DELSELF [read()]\n");
	}
	if ( e-> mask & IN_MODIFY){  // IL FILE E` STATO MODIFICATO
			printf("IN MODIFY [read()]\n");
	}
	if ( e-> mask & IN_OPEN){ // IL FILE E` STATO APERTO CON UNA SYSCALL OPEN
			printf("IN OPEN[read()]\n");
	}

	//printo il percorso
	// se l'evento e` sul file che sto monitorando, il nome e` sottinteso e non viene messo nella struct
	// altrimenti viene salvato in .name
	if ( e-> len > 0){
		printf("filename = %s\n\n", e->name);
	}else{
		printf("missing filename\n\n");
	}
}

// monitoro un cartella con inotify
int main(void) {
	int inotify_fd;
	char *dir_name = ".";
	int wd;

	inotify_fd = inotify_init();
			if(inotify_fd == -1){
				perror("inotify");
				exit(1);
			}
	 wd = inotify_add_watch(inotify_fd, dir_name, IN_ALL_EVENTS);
	 	 	 if(wd == -1){
	 	 		perror("add watch");
	 	 		exit(1);
	 	 	 }
	int bytes_read;
	char*p;
	while(1){  // legge all'infinito adll'inotify_fd
		bytes_read = read(inotify_fd, buffer, BUF_LEN);
	 	 if(bytes_read == -1){
	 	 		perror("read");
	 	 		exit(1);
	 	 	 }
	 	printf("read returned %d bytes\n", bytes_read);

	 	for(p = buffer; p <buffer + bytes_read; ){
	 		struct inotify_event *event;
	 		event = (struct inotify_event *) p; // punto a p con un cast
	 		display_notify_event(event);
	 		p = p + sizeof(struct inotify_event)  + event->len;
	 	}
	}

	return EXIT_SUCCESS;
}
