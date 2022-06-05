#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
typedef struct {
	char name[50]; // name of the book
	char author[50]; // author of the book
	int idnum; // identificaton number of the book
	char genre[50]; // genre of the book
	int borrowed; // whether the book is borrowed or not
	int hours;
	int minutes;
}Book;

typedef struct {
	char login[50]; // login of the user
	char password[50]; // password of the user 
	int role; // role of the user (1 for student and 2 for teacher)
	int numBook; // number of book borrowed
	Book* bookowner; // books the user owns
}User;




void createUser(int* pnumUser, User** parrayUser);
void createBook(int* pnumBook, Book** parrayBook);
int counter(FILE* file, char c);
int listUser(User** listUser);
int connect(User* listUser, int* idx);
void borrow(User* user, int numUser, User* array, int numBooks, Book* arrayBook);
int listBook(Book** listBook);
void unborrow (User* user, int numBooks, Book* arrayBook);
int search(int numBooks, Book* arrayBook);
