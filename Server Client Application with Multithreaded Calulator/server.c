
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>	
#include <pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<ctype.h>
int Result;
int result = 0;
int count = 1;
float resultf;

void* sum1(void* parameter)
{
	pthread_self();

	int* arr = (int*)parameter;
	if (result == 0)
	{
		result = result + arr[0];
	}
	else
	{

		result = result + arr[count];
		count++;



	}
	//printf("Result on %d\n", result);

	pthread_exit(NULL);
}
void* substract1(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;


	result = result - arr[count];
	count++;


	pthread_exit(NULL);
}





void* Multiple1(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;




	result = result * arr[count];
	count++;






	pthread_exit(NULL);
}



void* division1(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;
	float r = 0.0;
	r = result;



	r = (float)r / arr[count];
	count++;


	resultf = r;
	result = (int)resultf;



	pthread_exit(NULL);
}



void* square(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;




	result = result * result;
	count++;


	pthread_exit(NULL);
}




void* cube(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;




	result = result * result * result;
	count++;


	pthread_exit(NULL);
}


void* squareroot(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;




	float z;
	for (z = 0.00; z * z < result; z = z + 0.01);


	resultf = z;
	count++;



	pthread_exit(NULL);
}

void* Power(void* parameter)
{
	pthread_self();
	int* arr = (int*)parameter;
	int number = arr[1];        
	int orginalnumber = result; 



	do {
		result = result * orginalnumber;
		count++;
	} while (count < number);



	pthread_exit(NULL);
}


void* sum(void* parameter)
{

	pthread_self();

	int* arr = (int*)parameter;



	if (result == 0)
	{
		result = result + arr[0];
	}
	else
	{



		result = result + arr[1];
		count++;




	}



	pthread_exit(NULL);
}
void* substract(void* parameter)
{

	pthread_self();
	int* arr = (int*)parameter;




	result = result - arr[1];
	count++;







	pthread_exit(NULL);
}

void* Multiple(void* parameter)
{

	pthread_self();
	int* arr = (int*)parameter;




	result = result * arr[1];
	count++;

	pthread_exit(NULL);
}

void* division(void* parameter)
{

	pthread_self();
	int* arr = (int*)parameter;
	float r = 0.0;
	r = result;



	r = (float)r / arr[1];



	resultf = r;
	result = (int)resultf;







	pthread_exit(NULL);
}

void DMAS(char* str, int Lenght) {
	//printf("string %s\n", str);
	pthread_t thread[20];
	char Equation[1024];
	bzero(Equation, 1024);
	strcpy(Equation, str);
	//printf("string %s\n", Equation);
	int lenght, i = 0, y = 0, Add = 0, Sub = 0, Mul = 0, Div = 0;
	int arr[2];
	char str1[2];
	int New[lenght];
	int same[lenght], x = 0, same1 = 0;
	lenght = Lenght;
	for (i = 0; i < lenght; i++) {
		//printf("The character is %c\n", Equation[i]);
		if (Equation[i] == '/') {
			same[x] = i;
			Div++;
			x++;
			same1++;
			i++;
		}
	}
	for (i = 0; i < same1; i++) {

	}

	x = 0;
	if (Div > 0) {
		for (i = 0; i < same1; i++) {
			arr[0] = atoi(&Equation[(same[i] - 1)]);
			arr[1] = atoi(&Equation[(same[i] + 1)]);
			pthread_create(&thread[i], NULL, sum, (void*)arr);
			pthread_join(thread[i], NULL);


			pthread_create(&thread[i], NULL, division, (void*)arr);
			pthread_join(thread[i], NULL);
			New[i] = (int)resultf;
			result = 0;
		}
		x = 0;
		for (i = 0; i < lenght; i++) {
			if (i == (same[y] - 1)) {

				sprintf(str1, "%d", New[y]);
				Equation[x] = str1[0];
				x++;
				y++;
				i = i + 2;
			}
			else {
				Equation[x] = Equation[i];
				x++;
			}
		}
		while (x < lenght) {
			Equation[x] = ' ';
			x++;
		}
		lenght -= same1 * 2;
	}
	x = 0, same1 = 0;
	//printf("The Equation after Div is now%s\n\n", Equation);
	for (i = 0; i < lenght; i++) {
		if (Equation[i] == '*') {
			same[x] = i;
			Mul++;
			x++;
			same1++;
			i++;
		}
	}


	if (Mul > 0) {
		for (i = 0; i < same1; i++) {
			arr[0] = atoi(&Equation[(same[i] - 1)]);
			arr[1] = atoi(&Equation[(same[i] + 1)]);

			pthread_create(&thread[i], NULL, sum, (void*)arr);
			pthread_join(thread[i], NULL);

			pthread_create(&thread[i], NULL, Multiple, (void*)arr);
			pthread_join(thread[i], NULL);


			New[i] = result;


			result = 0;


		}

		x = 0;
		y = 0;


		for (i = 0; i < lenght; i++) {

			if (i == (same[y] - 1)) {

				sprintf(str1, "%d", New[y]);

				Equation[x] = str1[0];
				x++;
				y++;
				i = i + 2;
			}
			else {
				Equation[x] = Equation[i];
				x++;
			}
		}
		while (x < lenght) {
			Equation[x] = ' ';
			x++;
		}
		lenght -= same1 * 2;
	}
	x = 0, same1 = 0;


	for (i = 0; i < lenght; i++) {
		if (Equation[i] == '+') {
			Add++;
			same[x] = i;
			x++;
			same1++;
			i++;
		}
	}


	if (Add > 0) {
		for (i = 0; i < same1; i++) {
			arr[0] = atoi(&Equation[(same[i] - 1)]);
			arr[1] = atoi(&Equation[(same[i] + 1)]);

			pthread_create(&thread[i], NULL, sum, (void*)arr);
			pthread_join(thread[i], NULL);
			pthread_create(&thread[i], NULL, sum, (void*)arr);
			pthread_join(thread[i], NULL);
			New[i] = result;





		}result = 0;
		

		x = 0;
		y = 0;


		for (i = 0; i < lenght; i++) {
			if (i == (same[y] - 1)) {

				sprintf(str1, "%d", New[y]);
				Equation[x] = str1[0];
				x++;
				y++;
				i = i + 2;
			}
			else {
				Equation[x] = Equation[i];
				x++;
			}
		}
		while (x < lenght) {
			Equation[x] = ' ';
			x++;
		}
		lenght -= same1 * 2;
	}
	x = 0, same1 = 0;


	for (i = 0; i < lenght; i++) {
		if (Equation[i] == '-') {
			Sub++;
			same[x] = i;
			x++;
			same1++;
			i++;
		}
	}


	if (Sub > 0) {
		for (i = 0; i < same1; i++) {
			arr[0] = atoi(&Equation[(same[i] - 1)]);
			arr[1] = atoi(&Equation[(same[i] + 1)]);

			pthread_create(&thread[i], NULL, sum, (void*)arr);
			pthread_join(thread[i], NULL);
			pthread_create(&thread[i], NULL, substract, (void*)arr);
			pthread_join(thread[i], NULL);
			New[i] = result;





		}result = 0;

		x = 0;
		y = 0;


		for (i = 0; i < lenght; i++) {
			if (i == (same[y] - 1)) {

				sprintf(str1, "%d", New[y]);
				Equation[x] = str1[0];
				x++;
				y++;
				i = i + 2;
			}
			else {
				Equation[x] = Equation[i];
				x++;
			}
		}
		while (x < lenght) {
			Equation[x] = ' ';
			x++;
		}
	}


	x = 0, same1 = 0;
	Add = 0, Sub = 0, Mul = 0, Div = 0;
	Result = atoi(&Equation[0]);
	

}
int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Port No. is Not Provided : Program Terminated\n");
		exit(1);
	}
	int socketfd, newsocket, Portno, option = 0, i, x = 0;
	char Buff[1024];
	struct sockaddr_in ServerAddr, ClientAddr;
	socklen_t clientlen;
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		printf("Error in Creating a Socket\n");
	}
	bzero((char*)&ServerAddr, sizeof(ServerAddr));

	Portno = atoi(argv[1]);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = INADDR_ANY;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(Portno);
	bind(socketfd, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

	listen(socketfd, 5);
A:
	printf("\n\n      ****** Server is Listening ******      \n\n");
	clientlen = sizeof(ClientAddr);
	newsocket = accept(socketfd, (struct sockaddr*)&ClientAddr, &clientlen);
	if (newsocket < 0) {
		printf("The New Socket is Not created\n");
	}
	else {
		printf("      ****** A Client is Arrived ******      \n\n");
	}
	x = 0;
	read(newsocket, &option, sizeof(int));

	if (option == 1) {
		printf(" ______________________________________________________________________ \n");
		printf("|                                                                      |\n");
		printf("|                        Client wants to CHAT                          |\n");
		printf("|______________________________________________________________________|\n\n");
		while (1) {
			bzero(Buff, 1024);
			read(newsocket, Buff, 1023);
			if (x != 0) {
				printf("Client : %s\n", &Buff);
			}
			else {
				x++;
			}

			if (Buff[0] == 'B' || Buff[0] == 'b' && Buff[1] == 'y' && Buff[2] == 'e') {
				printf("Server : Bye, Have a Nice Day\n");
				break;
			}
			else {
				bzero(Buff, 1024);
				printf("Server : ");
				fgets(Buff, 1024, stdin);
				write(newsocket, Buff, strlen(Buff));
			}
		}
	}
	else if (option == 2) {
		printf(" ______________________________________________________________________ \n");
		printf("|                                                                      |\n");
		printf("|               The Client wants to receive a File                     |\n");
		printf("|______________________________________________________________________|\n\n");
		char file1[50];
		FILE* f;
		int words = 0, lenght, type = 0;
		char c;

		read(newsocket, &type, sizeof(int));
		read(newsocket, &lenght, sizeof(int));



		bzero(file1, 50);
		read(newsocket, file1, 50);



		f = fopen(file1, "r");
		if (f == NULL) {
			printf("Sorry I don't have such File\n");
			write(newsocket, &words, sizeof(int));
			goto A;
		}

		while (c = getc(f) != EOF) {
	
			fscanf(f, "%s", Buff);
			if (isspace(c) || c == '\t' || c == ' ') {
				words++;
			}
			words++;
		}
	
		write(newsocket, &words, sizeof(int));
		rewind(f);

		char ch;

		while (ch != EOF) {

			fscanf(f, "%s", Buff);
			write(newsocket, Buff, 1024);
			ch = fgetc(f);
		}
		printf("The File has been Sent\n\n");

	}
	else if (option == 3) {

		printf(" ______________________________________________________________________ \n");
		printf("|                                                                      |\n");
		printf("|           The Client wants to use Multi Threaded Calculator          |\n");
		printf("|______________________________________________________________________|\n\n");

		pthread_t thread;

		read(newsocket, &option, sizeof(int));
		int lenght1 = 0;
		bzero(Buff, 1024);
		if (option == 1) {
			int op;
			int val;
			read(newsocket, &op, sizeof(int));
			//printf("The Read char is %d\n", op);


			read(newsocket, &val, sizeof(int));
			//printf("On values %d\n", val);
			int arr[val];
			bzero(Buff, 1024);
			printf("Client wants to operate on Numbers :");;
			//read(newsocket, &arr, sizeof(arr));
			for (i = 0; i < val; i++) {
				
				read(newsocket, &arr[i], sizeof(int));
				printf(" %d", arr[i]);
				//printf("Read values %d %d\n", i, arr[i]);
			}
			//printf("out\n");
			if (op == 1)
			{
				printf("\nClient wants to Operate: +\n");
				//printf("yes\n");
				for (int i = 0; i < val; i++)
				{
					//printf("Value on arr i %d %d", i, arr[i]);
					pthread_create(&thread, NULL, sum1, (void*)arr);
					pthread_join(thread, NULL);
				}
				printf("Result = %d\n", result);
			}
			else if (op == 2)
			{
				printf("\nClient wants to Operate: -\n");
				//printf("Value on arr i %d %d", i, arr[i]);
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val - 1; i++)
				{
					pthread_create(&thread, NULL, substract1, (void*)arr);
					pthread_join(thread, NULL);
				}
				printf("Result = %d\n", result);
			}
			else if (op == 3)
			{
				printf("\nClient wants to Operate: *\n");
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val - 1; i++)
				{
					pthread_create(&thread, NULL, Multiple1, (void*)arr);
					pthread_join(thread, NULL);
				}
				printf("Result = %d\n", result);
			}
			else if (op == 4)
			{
				printf("\nClient wants to Operate: /\n");
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val - 1; i++)
				{
					pthread_create(&thread, NULL, division1, (void*)arr);
					pthread_join(thread, NULL);

				}
				printf("Result = %.2f\n", resultf);
			}
			else if (op == 5)
			{
				printf("\nClient wants to Operate: Square\n");
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val; i++)
				{
					pthread_create(&thread, NULL, square, (void*)&arr);
					pthread_join(thread, NULL);

				}
				printf("Result = %d\n", result);
			}
			else if (op == 6)
			{
				printf("\nClient wants to Operate: cube\n");
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val; i++)
				{
					pthread_create(&thread, NULL, cube, (void*)&arr);
					pthread_join(thread, NULL);
				}
				printf("Result = %d\n", result);
			}
			else if (op == 7)
			{
				printf("\nClient wants to Operate: square root\n");
				pthread_create(&thread, NULL, sum1, (void*)arr);
				pthread_join(thread, NULL);
				for (int i = 0; i < val; i++)
				{
					pthread_create(&thread, NULL, squareroot, (void*)&arr);
					pthread_join(thread, NULL);
				}
				printf("\nResult = %.2f\n", resultf);
				result = resultf;
			}
			write(newsocket, &result, sizeof(int));
			result = 0;
			resultf = 0;
			count = 1;
		}
		else if (option == 2) {
			read(newsocket, Buff, 1024);
			printf("The Recived Buff is %s", Buff);
			i = 0;
			while (Buff[i] != NULL) {
				lenght1++;
				i++;
			}
			DMAS(Buff, lenght1);
			printf("The Result is %d\n\n", Result);
			write(newsocket, &Result, sizeof(int));
		}
		goto A;
	}
	goto A;
	close(newsocket);
	close(socketfd);
	return 0;

}

