#include"Biblio.h"



int counter(FILE* file, char c) {
//it count the number of users registered in the program and return this number
	rewind(file);
	int nmb=0;
	int l;
	while(l!=EOF)
		{
		l = fgetc(file);
			if(l == c){
		nmb++;
			}
		}
	return(nmb);
}
//make the list of user and return the length of the list
int listUser(User** listUser) {
	int nUsers;
	FILE* file = NULL;
	file = fopen("User.txt", "r"); // open the file with every user
	if (file == NULL){
	   printf("Cannot open the file\n");
	   exit(1);
	}
	nUsers = counter(file, '#')+1;
	*listUser = malloc((nUsers)*sizeof(User)); // list of user
	int c = 'a';
	int g,i;
	char frr[50];
	rewind(file);
	while (c!=EOF) { //loop to get the user 
		for(i=0; i<nUsers; i++) {
			
		    g=fscanf(file, "%s", ((*listUser)[i].login)); 
		    if (g==0) {
			printf("\nerror, fscanf(file, s, ((*listUser)[i].login));"); //it checks if there is no error with the login
			exit(1);
		    }
		    g=fscanf(file, "%s", ((*listUser)[i].password));
		    if (g==0) {
			printf("\nerror, fscanf(file, s, ((*listUser)[i].password)); ");//it checks if there is no error with the password
			exit(1);
		    }
		    g=fscanf(file, "%d", &((*listUser)[i].role));
		    if (g==0) {
			printf("\nerror, fscanf(file, d, &((*listUser)[i].role)); ");//it checks if there is no error with the role
			exit(1);
		    }
		    (*listUser)[i].numBook=0;
		    if ((*listUser)[i].role == 1) {
			(*listUser)[i].bookowner=malloc(3*sizeof(Book));
			}
		    else if ((*listUser)[i].role == 2) {
			(*listUser)[i].bookowner=malloc(5*sizeof(Book));
			}
	        c=fgetc(file);
		c=fgetc(file);
		c=fgetc(file);
		}
	}
	fclose(file);
	return (nUsers);
}



int connect(User* listUser, int* idx) {//it check the user's id and password and return the user's rule 
	char a[50]; 
	char b[50];
	int c, g, i, j, nUsers, v;
	FILE* file=NULL;
	file = fopen("User.txt","r");
	if(file == NULL)
	{
		printf("Cannot open the file");
		exit(1); 
	} 
	v=0;
	do {
	    do {
	       printf("\nEnter your login\n");
	       g=scanf("%s", a);
	       }while (g==0);
	    nUsers = counter(file, '#')+1;

	    for (i=0; i<nUsers; i++) {

		    if ( strcmp(a,listUser[i].login) == 0) {//it checks if the login corresponds to the login of an existing account
		        do {
			    printf("\nEnter your password\n");
			    g=scanf("%s", b);
			} while (g==0);
			if (strcmp(b, listUser[i].password) == 0) {//it checks if the login corresponds to the login of an existing account
				c=(*(listUser+i)).role;
				*idx=i;
				v=1;
			}
			    
		    }

	    }

	   if (v==0) {
	      printf("\nYour login or your password is wrong\n");
	      }
	}while (v == 0);
	return c;
}




int listBook(Book** listBook) {//make the list of books and return the length of the list
	int nBooks;
	Book book;
	FILE* file = NULL;
	file = fopen("Book.txt", "r"); // open the file with every book
	if (file == NULL){
	   printf("Cannot open the file\n");
	   exit(1);
	}
	nBooks = counter(file, '#')+1;
	*listBook = malloc((nBooks)*sizeof(Book)); // list of book
	char* c = malloc(3 * sizeof(char));
	int g,i;
	char f;
	char* s = NULL;
	char* si = &f;
	rewind(file);
	i=0;
	while(i<nBooks){
	    s = fgets(((*(*listBook + i)).name), 100, file);
		
	    if (s==NULL) {
		printf("\nerror, fgets(((*(*listBook + i)).name), 100, file)");
		exit(1);
	    }
	    s = fgets(((*(*listBook + i)).author), 100, file);
	    if (s==NULL) {
		printf("\nerror, fgets(((*(*listBook + i)).author), 100, file)");
		exit(1);
	    }
	   
		c=fgets(c, 10,file);
		c[strlen(c)] = '\0';
	  	((*(*listBook + i)).idnum) = (int) strtol(c, NULL, 10); // atoi doesn't work for some reason (that's the only way we found)
	   
	    s = fgets(((*(*listBook + i)).genre), 100, file);
	    if (s==NULL) {
		printf("\nerror, fgets(((*(*listBook + i)).genre), 100, file)");
		exit(1);
	    }

	    (*(*listBook + i)).borrowed=0;
	    (*(*listBook + i)).hours = 0;
	    (*(*listBook + i)).minutes = 0;
	    *c=fgetc(file);
	    *c=fgetc(file);
	     i++;
	}
	fclose(file);
	free(c);
	return (nBooks);
}

//this function allows you to sort the books in alphabetical order according to their title but also according to their genre, it allows to display them and read the user's reponse
int search(int numBooks, Book* arrayBook)
{
	int g, a, i, j, k, alph, v;
	int count = 0;
	Book tmp;
	printf("\nSearch for a book by 1.author 2.title 3.genre\n");
	
	do{
		g=scanf("%d", &a);
	} while(g == 0 || (a == 1 && a == 2 && a == 3));

	if(a==1)//it sorts the books by author in alphabetical order
	{
		for(i = 0; i < numBooks; i++){
			alph = i;
			for(j = i; j < numBooks; j++){
				if( strcmp(arrayBook[alph].author, arrayBook[j].author) > 0 )	{
					alph = j;
				}
			}
			tmp = arrayBook[i];
			arrayBook[i] = arrayBook[alph];
			arrayBook[alph] = tmp;
		}
	}else if(a==2)//it sorts the books by title in alphabetical order
	{
		for(i = 0; i < numBooks; i++){
			alph = i;
			for(j = i; j < numBooks; j++){
				if( strcmp(arrayBook[alph].name, arrayBook[j].name) > 0 )	{
					alph = j;
				}
			}
			tmp = arrayBook[i];
			arrayBook[i] = arrayBook[alph];
			arrayBook[alph] = tmp;
		}
	}

	else if(a==3)//it sorts the books by genre
	{
		printf("\nWrite the id number to borrow a book\n----------------------------------\n");
		for(i = 0; i < numBooks; i++){

			alph = i;
			for(j = i; j < numBooks; j++){
				if( strcmp(arrayBook[alph].genre, arrayBook[j].genre) > 0 )	{
					alph = j;
				}
			}
			tmp = arrayBook[i];
			arrayBook[i] = arrayBook[alph];
			arrayBook[alph] = tmp;
		}
		

		for(i = 0; i < numBooks; i++){
			if(arrayBook[i].borrowed == 0)
				printf("Genre : %s	%d :%s       %s\n", arrayBook[i].genre, arrayBook[i].idnum, arrayBook[i].name, arrayBook[i].author);
		}
	}
	if(a == 1 || a == 2){
		printf("\nWrite the id number to borrow a book\n----------------------------------\n");
		for(i = 0; i < numBooks; i++){
			if(arrayBook[i].borrowed == 0)
				printf("\n\n%d :%s       %s\n", arrayBook[i].idnum, arrayBook[i].name, arrayBook[i].author);
		}
	}
	

	scanf("%d", &a);
	return a;
}









