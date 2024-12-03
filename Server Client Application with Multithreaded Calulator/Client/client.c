
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<ctype.h>
int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Port No. is Not Provided : Program Terminated\n");
		exit(1);
	}
	int socketfd, Portno, option, x = 0, new;
	char Buff[1024];
	struct sockaddr_in ServerAddr;
	socklen_t clientlen;
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		printf("Error in Creating Socket\n");
	}
	bzero((char*)&ServerAddr, sizeof(ServerAddr));

	Portno = atoi(argv[1]);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = INADDR_ANY;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(Portno);
	new = connect(socketfd, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if (new < 0) {
		printf(" Server with Port No %d is not available \n ", Portno);
		exit(1);
	}
	printf("    \n *********Connected to a Server Successfully Port No is : %d *********   \n\n", Portno);
	printf(" _________________________________________________________________________________ \n");
	printf("|                                                                                |\n");
	printf("|      1) Press 1 to Chat with the Server                                        |\n");                
	printf("|      2) Press 2 to Recive a File from the Server                               |\n");
	printf("|      3) Press 3 for Multi Threaded Calculator                                  |\n");
	printf("|________________________________________________________________________________|\n\n");


	printf("Please , Enter your choice :");
	scanf("%d", &option);
	write(socketfd, &option, sizeof(int));
	if (option == 1) {
		goto x;
	}
	else if (option == 2) {
		goto y;
	}
	else if (option == 3) {
		goto A;
	}
x:
	while (1) {
		bzero(Buff, 1024);
		if (x != 0) {
			printf("Client : ");
		}
		else {
			x++;
		}
		fgets(Buff, 1024, stdin);
		write(socketfd, Buff, strlen(Buff));
		if (Buff[0] == 'B' || Buff[0] == 'b' && Buff[1] == 'y' && Buff[2] == 'e') {
			printf("\nServer : Bye, Have a Nice Day\n");
			break;
		}
		bzero(Buff, 1024);
		read(socketfd, Buff, 1024);
		printf("\nServer: %s", &Buff);

	}
	goto z;

y:
	char file[30];
	int i, lenght = 0, type;
	printf("Enter the File name : ");
	scanf("%s", &file);
	//printf("The name of File is : %s\n", file);
	for (i = 0; i < 30; i++) {
		if (file[i] != '.') {
			lenght++;
		}
		else {
			break;
		}
	}
	write(socketfd, &type, sizeof(int));
	write(socketfd, &lenght, sizeof(int));
	write(socketfd, file, strlen(file));
	FILE* f;
	
	int words = 0;
	int ch = 0;
	read(socketfd, &words, sizeof(int));
	char space = ' ';
	if (words == 0) {
		printf("Server don't have any such %s File\n ", file);
		exit(1);
	}
	f = fopen(file, "a");
	while (ch != (words + 1)) {
		read(socketfd, Buff, 1024);
		fprintf(f, "%s", Buff);
		fprintf(f, "%c", space);
		ch++;
	}

	printf("The File has been Received Successfully\n");

	goto z;
A:
	printf(" ______________________________________________________________________ \n");
	printf("|                                                                      |\n");
	printf("|    1) Press 1 to Use Multi Threaded Calculator                       |\n");
	printf("|    2) Press 2 to Solve Equation by DMAS rule                         |\n");
	printf("|______________________________________________________________________|\n");
	printf("Please , Enter your choice :");
	scanf("%d", &option);
	write(socketfd, &option, sizeof(int));
	int Result;
	bzero(Buff, 1024);
	if (option == 1) {
		int Num, op, value;

		printf("Which Operation do you want to operate :\n");
		printf("*For Sum Enter 1 \n*For Sub Enter 2 \n*For Mul Enter 3 \n*For Div Enter 4 \n*For Sqare Enter 5 \n*For Cube Enter 6 \n");
		printf("For SqareRoot Enter 7 \n");
		printf("Enter your choice :");
		scanf("%d", &op);
		write(socketfd, &op, sizeof(int));
		printf("On how many numbers : ");
		scanf("%d", &Num);
		write(socketfd, &Num, sizeof(int));

		//write(socketfd, &value, sizeof(int));
		
		for (i = 0; i < Num; i++) {
			printf("Enter Numbers %d :", (i+1));
			scanf("%d", &value);
			write(socketfd, &value, sizeof(int));

		}

		read(socketfd, &Result, sizeof(int));
		printf("The Result receive from Server is  : %d\n\n", Result);

	}
	else if (option == 2) {
		printf("Enter the Equation to Evaluate :");
		scanf("%s", &Buff);
		write(socketfd, Buff, strlen(Buff));

		read(socketfd, &Result, sizeof(int));
		printf("The Result of Equation is : %d", Result);
	}
z:
	close(socketfd);
	return 0;

}

