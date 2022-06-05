#include "Biblio.h"

int main(){
	// initializing variable
	int a, r, b, c, i, g, d, temp, ind, v, h, min;
	int* pind = &ind;
	User u;
	User* arrayUser = &u;
	User* Puser = NULL;
	int numUser; // number of users
	numUser=listUser(&arrayUser);
	Book bo;
	Book* arrayBook = &bo;
	Book** parrayBook = &arrayBook;
	int numBooks = listBook(parrayBook);
	time_t s;
	v = 1;
	do{
		do{		
			printf("\n\n\n       Welcome into the Cy Tech library\n"); // Display of the library interface
			printf("----------------------------------------------\n");
			do {
			    printf("Do you want to:\n1.Connect\n2.Create a new account\n3.Quit the awesome library\n");
			    g=scanf("%d", &r);
			}while (g==0|| r!=1 && r!=2 && r!=3);
			if (r==1) {
				c=connect(arrayUser, pind);
				}
			else if(r==2) {
				   createUser(&numUser, &arrayUser);
		  	   	   do{
					printf("Do you want to connect\n1.Yes\n2.No\n");
					g=scanf("%d",&b);
		 	    }while(g==0 ||b!=1 && b!=2);
		 	    if (b==1) {
				c=connect(arrayUser, pind);
		   	  }
			}
		} while(b==2);

		if(r==1 || r==2){
			printf("\nBienvenue %s !\n", arrayUser[ind].login);
			printf("You've borrowed this books :\n");
			for(i = 0; i < arrayUser[ind].numBook; i++)
			{
				printf("\n %s", arrayUser[ind].bookowner[i].name);
			}
		}
		if(r==3)
		{
			printf("\nBye\n");
			exit(1);
		}
		do {
			do {
			    printf("\nWhat do you want to do?:\n1.Borrow a book\n2.Return a book\n");
				if(c == 2)
					printf("3.Add a book\n");
				printf("4.Sign out\n");
			    d=scanf("%d", &a);
			}while (g==0|| a!=1 && a!=2 && a!=3 && a!= 4);
			if (a==1) {
				v = 1;
				for(i = 0; i < arrayUser[ind].numBook; i++)
				{
					s = time(NULL);
					min = (s/60)%60;
					h = (s/60/60)%24;
					if(arrayUser[ind].bookowner[i].hours < h)
					{
						v=0;
						printf("Unborrow %s first\n", arrayUser[ind].bookowner[i].name);				
					}
					else if(arrayUser[ind].bookowner[i].minutes < min && arrayUser[ind].bookowner[i].hours == h)
					{
						v=0;
						printf("First, you need to unborrow %s", arrayUser[ind].bookowner[i].name);				
					}
				}
				if(v == 1)
				{
					Puser = arrayUser+ind;
					if(c == 1 && arrayUser[ind].numBook < 3){
						borrow(Puser, numUser, arrayUser, numBooks, arrayBook);
					}
					else if(c == 2 && arrayUser[ind].numBook < 5){
						borrow(Puser, numUser, arrayUser, numBooks, arrayBook);
					}
					else{
						printf("You need to unborrow a book first\n\n");
					}
				}				
			}
			else if (a==2) {
				unborrow(arrayUser+ind, numBooks, arrayBook);
			}
			else if (a==3 && c == 2) {
				createBook(&numBooks, &arrayBook);
			}
			
			
		} while(a != 4);
	} while(r != 3);

	for(i = 0; i < numUser; i++){
	}
}
	

		







