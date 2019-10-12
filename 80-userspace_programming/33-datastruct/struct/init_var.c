#include <stdio.h>


struct Books
{
	char  title[50];
	char  author[50];
	char  subject[100];
	int   book_id;
} book = {"Language C", "RUNOOB", "Programming", 123456};


//#if DL_NOTE_STRUCT_PART_BUILD == 1
int main(void)
//#else
//int main_init_var(void)
//#endif
{
	printf("title : %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book.title, book.author, book.subject, book.book_id);
	return 0;
}
