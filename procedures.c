#include"Biblio.h"

void createUser(int* pnumUser, User** parrayUser) { // it ask the role, id and password of the new user and writ it into the file: User.txt
	User user;
	int a, i, g, tmp;
	User* ptmp = NULL;
	char login[50];
	char password[50];
	do {
		printf("\nAre you:\n1.Student\n2.Teacher\n"); // choose the role of the user
		g=scanf("%d",&a);
	}while (g==0 || (a!=1 && a!=2));
	user.role=a;
	printf("\nChoose your login\n"); // choose the login of the user
	scanf("%s",login);
	for (i=0; i<50; i++) {
	   user.login[i] = login[i];
	}
	printf("\nChoose your password\n"); // choose the password of the user
	scanf("%s",password);
	for (i=0; i<50; i++) {
	   user.password[i] = password[i];
	}
	FILE* file=NULL;
	file=fopen("User.txt", "a+");
	if (file == NULL){
	   printf("Cannot open the file\n");
	   exit(1);
	}
	fprintf(file, "#\n%s\n%s\n%d", user.login, user.password, user.role); // write the login, password and role of the user in the file
	fclose(file);
	
	tmp = *pnumUser;
	ptmp = *parrayUser;
	*pnumUser = listUser(parrayUser);
	for(i = 0; i < tmp; i++)
	{
		(*parrayUser)[i].bookowner = ptmp[i].bookowner;
	}
}


void createBook(int* pnumBook, Book** parrayBook)//it write the title, author, genre and id number of the new book that will be added in the file: Book.txt
{
	Book book;
	int a, i, g, tmp;
	Book* ptmp = NULL;
	char name[50];
	char author[50];
	char genre[50];

	printf("Choose the title of the book\n"); // choose the title of the book
	scanf("%s", name);
	for (i=0; i<50; i++) {
	   book.name[i] = name[i];
	}
	printf("Choose the author of the book\n"); // choose the author of the book
	scanf("%s",author);
	for (i=0; i<50; i++) {
	   book.author[i] = author[i];
	}
	printf("Choose the genre of the book\n"); // choose the genre of the book
	scanf("%s", genre);
	for (i=0; i<50; i++) {
	   book.genre[i] = genre[i];
	}
	
	do{
		printf("Choose the id of the book\n"); // choose the id of the book
		g = scanf("%d", &a);
		book.idnum = a;
		if(g!=0)
		{
			for(i = 0; i < *pnumBook; i++)
			{ 
				if(a == (*parrayBook)[i].idnum){
					g = 0;
					printf("Enter another ID");//Two books cannot have the same id number				
				}
			}
		}	
	}while(g ==0);
	

	FILE* file=NULL;
	file=fopen("Book.txt", "a+");
	if (file == NULL){
	   printf("Can not open the file\n");
	   exit(1);
	}
	fprintf(file, "#\n%s\n%s\n%d\n%s\n", book.name, book.author, book.idnum, book.genre); // write the login, password and role of the user in the file
	fclose(file);
	
	tmp = *pnumBook;
	ptmp = *parrayBook;
	*pnumBook = listBook(parrayBook);
	for(i = 0; i < tmp; i++)
	{
		(*parrayBook)[i].borrowed = ptmp[i].borrowed;
	}


}


void borrow(User* user, int numUser, User* array, int numBooks, Book* arrayBook) {//function used to borrow a book by modifying the value of "borrowed"
	int a, i, j, g, v, t, k;
	t=0;
	int h, min;
	time_t s;
  
	a = search(numBooks, arrayBook);
	for (j=0; j<numBooks; j++) {
   	 if (a == arrayBook[j].idnum) {
		if (arrayBook[j].borrowed==0){
			arrayBook[j].borrowed = 1;	
 
			printf("Book name : %s  	",arrayBook[j].name);
			if(user->bookowner == NULL)	 		
			user->bookowner[user->numBook] = arrayBook[j];
			s = time(NULL);
			min = (s/60)%60;
			h = (s/60/60)%24;
			if(user->role == 1)//allows you to know the time at which the student must return his book
			{
				user->bookowner[user->numBook].hours = h + (min + 2 >= 60);
				user->bookowner[user->numBook].minutes = (min + 2) % 60;
			}
			else if(user->role == 2)//allows you to know the time at which the teacher must return his book
			{
				user->bookowner[user->numBook].hours = h + (min + 3 >= 60);
				user->bookowner[user->numBook].minutes = (min + 3) % 60;
			}
			printf("You need to unborrow this book before %02d:%02d\n", user->bookowner[user->numBook].hours, user->bookowner[user->numBook].minutes);	
			user->numBook++;
			printf("You borrowed %d books\n",user->numBook); 
			
		}
		else
			printf("This book is already borrowed by someone\n");//A book cannot be borrowed by two people
	  	 }
	}
}
	

void unborrow (User* user, int numBooks, Book* arrayBook)//function used to unborrow a book
{
	int i, a, g, c;
	c = 0;
	Book* newArray;

	printf("you want to unborrow:\n");
	for(i = 0; i < user->numBook; i++)//the user select the book to unborrow
	{
		printf("%d: %s", i+1, user->bookowner[i].name);
	}
	
	do{
		g = scanf("%d",&a);
	} while(g == 0 && (a >= user->numBook && a <= 0));

	newArray = malloc((user->numBook - 1) * sizeof(Book));//allocate memory for a new array

	for(i = 0; i < user->numBook; i++)//fill the new array without the unborrowed book
	{
		if(user->bookowner[i].idnum != user->bookowner[a-1].idnum)
		{
			newArray[c] = user->bookowner[i];
		}
	}

	for(i = 0; i < numBooks; i++)//assign the new array books to array
	{
		if(arrayBook[i].idnum == user->bookowner[a-1].idnum)
		{
			arrayBook[i].borrowed = 0;
		}
	}

	free(user->bookowner);
	user->bookowner = newArray;
	printf("You have successfully unborrowed this book\n");
	user->numBook--;

	


}
