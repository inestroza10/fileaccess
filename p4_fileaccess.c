/*    Project 4: fileaccess */

#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>

static short octarray[9] = {0400, 0200, 0100, 0040, 0020, 0010, 0004, 0002, 0001};
// 0400 = read, 0200 = write, 0010 = execute
// contains the values for the basic permissions

static char perms[10] = "rwxrwxrwx";
// compare permission to file
// holds the character equivalent

int filedata(const char *pathname)
{
  struct stat statbuf;
  struct passwd *pw;
  char descrip[10];
  int j;
  int i = 0, x = 0;

  pw = getpwuid(getuid());
  char *dir = pw -> pw_dir;
  //prints directory from password structure
  
  char fp[sizeof(dir) + sizeof(pathname)];
  //initializing char string to allocate space

  if(pathname[0] == '/')
    {
      while(pathname[i]) // while this isn't null
	{
	  fp[i] = pathname[i]; //getting letter from pathname and setting it to fp[i]
	  ++i;
	}
      //do this while loop if you found a file
      if(stat(fp, &statbuf) == -1)
	{
	  fprintf(stderr, "Couldn't stat %s\n", pathname);
	  return (-1);
	}
    }
  else
    {
      while(dir[i]
	{
	  fp[i] = dir[i];
	  ++i;
	}
	fp[i] = '/';
	++i;

	while(pathname[x]) 
	// goes through directory and once the file is in that direcrtory it goes through the while loop
	  {
	    fp[i] = pathname[x];
	    ++i;
	    ++x;
	  }
	fp[i] = '\0';

	if(stat(fp, &statbuf) == -1)
	  {
	    fprintf(stderr, "Couldn't stat %s\n", fp);
	    return(-1);
	  }
    }
      //if you havent found a file and going through directory, do the else statement
      for(j = 0; j < 9; j++)
	{
	  if(statbuf.st_mode & octarray[j]) // compares
	    descrip[j] = perms[j]; // gets perms and put its in descrip
	  else
	    descrip[j] = '-';
	}
      descrip[9] = '\0';

      printf("\nFile: %s\n", pathname);

      if(getuid() == statbuf.st_uid)
	{
	  int z;
	  printf("User: Owner \n Permissions: ");
	  for(z = 0; z <= 2; ++z)
	    printf("%c", descrip[z]);
	  printf("\n");
	}
      else if(getgid() == statbuf.st_guid)
	{
	  int z;
	  printf("User: Group \n Permissions: ");
	  for(z = 3; z <= 5; ++z)
	    printf("%c", descrip[z]);
	  printf("\n");
	}
      else
	{
	  int z;
	  printf("User: Others \n Permissions: ");
	  for(z = 6; z <= 8; ++z)
	    printf("\n");
	}
      return(0);
    }

  int main(int argc, char *argv[])
  {
    int i;
    for(i = 1; i < argc; i++)
      filedata(argv[i]);
    return 0;
  }
}


