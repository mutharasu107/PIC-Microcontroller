#include <stdio.h>
#include <stdlib.h>

struct course 
{
  int marks;
  char sub[30];
};

int main() 
{
  struct course *ptr;				
  int n, count =0, count1=0;					/* n = Number of subject user input */
  printf("Enter the number of records: ");
  scanf("%d", &n);

  // Memory allocation for n structures
  ptr = (struct course *)malloc(n * sizeof(struct course));
  for (int i = 0; i < n; ++i) 
  {
    printf("Enter subject and marks:\n");
    scanf("%s %d", (ptr + i)->sub, &(ptr + i)->marks);
  }

  printf("Displaying Information:\n");
  for (int i = 0; i < n; ++i) 
  {
     if( 35 <= (ptr + i)->marks)
     {
	printf("pass : %s\t%d\n", (ptr + i)->sub, (ptr + i)->marks);
	count ++;
     }
     else 
     {
	printf("fail : %s\t%d\n", (ptr + i)->sub, (ptr + i)->marks);
	count1 ++;
     }
  }
  printf("students pass : %d\n",count);
  printf("students fail : %d\n",count1);

  free(ptr);

  return 0;
}
