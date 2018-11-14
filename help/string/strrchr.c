


#include <stdlib.h>

char * my_strrchr(const char * str,int ch)

{

   char *p = (char *)str;

   while (*str) str++;

   while (str-- != p && *str != (char)ch);

   if (*str == (char)ch)

        return( (char *)str );

   return(NULL);

}

int main()

{

   char *str = "e:\\muisc\ok\\3.pm3";

   char * p;

   char ch;

  

   ch = '\\';

   p = (char *)my_strrchr(str,ch);

   if(p == NULL)

      printf("Can't find the character %c !\n",ch);

   else

      printf("Find the character %s !\n",p+1);

  

   ch = 'b';

   p = (char *)my_strrchr(str,ch);

   if(p == NULL)

      printf("Can't find the character %c !\n",ch);

   else

      printf("Find the character %c !\n",*p);

   system("pause");

   return 0;

}