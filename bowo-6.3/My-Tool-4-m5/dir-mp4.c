// arg1 input file
// arg2 output file
// arg3 file name ext


// daipozhi modified
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>







static int deb_filename_is_dir(char *path);
static int deb_filenameext(char *name,char *fext);
static char  str_lower(char c1);
static int  str_lower_string(char *p_instr);



FILE *m_fp1;
FILE *m_fp2;


char m01_str1[500];
char m01_str2[500];

char m01_str3[3000];
char m01_str4[3000];

char m01_str5[500];

int main(int argc, char **argv)
{
    int i,j,k;

    if (argc!=4)
    {
	printf("\n usage: ./a2.out input.txt output.txt ext-name \n");
        return(1);
    }

    strcpy(m01_str1,argv[1]);
    strcpy(m01_str2,argv[2]);
    strcpy(m01_str5,argv[3]);

    m_fp1=fopen(m01_str1,"r");
    if (m_fp1==NULL)
    {
	printf("\n open input file error\n");
	return(1);
    }


    m_fp2=fopen(m01_str2,"w");
    if (m_fp2==NULL)
    {
	printf("\n open output file error\n");
	return(1);
    }


    while(!feof(m_fp1))
    {
	fgets(m01_str3,3000,m_fp1);

	for (i=strlen(m01_str3)-1;i>=0;i--)
	{
		if ((m01_str3[i]>=0)&&(m01_str3[i]<=' ')) m01_str3[i]=0;
		else break;
	}

        i=deb_filename_is_dir(m01_str3);
	if (i==1) continue;

	deb_filenameext(m01_str3,m01_str4);

	str_lower_string(m01_str4);
	str_lower_string(m01_str5);

	if (strcmp(m01_str4,m01_str5)!=0) continue;

	fputs(m01_str3,m_fp2);
	fputs("\n"    ,m_fp2);
    }

    fclose(m_fp1);
    fclose(m_fp2);

    return(0);
}



static int deb_filename_is_dir(char *path)
{
	struct stat info;

	stat(path,&info);

	if (S_ISDIR(info.st_mode)) return(1);
	else return(0);
}


static int deb_filenameext(char *name,char *fext)
{
	int  i,j,k,l;

	i=(int)strlen(name);
	k=(-1);

	for (j=i-1;j>=0;j--)
	{
		if (name[j]=='.')
		{
			k=j;
			break;
		}
	}

	if (k<0)
	{
		fext[0]=0;
	}
	else
	{
		fext[0]=0;

		for (l=k+1;l<i;l++)
		{
			fext[l-k-1]=name[l];
			fext[l-k-0]=0;
		}
	}

	return(0);
}

static char  str_lower(char c1)
{
  if ((c1>='A')&&(c1<='Z')) return(c1-'A'+'a');
  else return(c1);
}

static int  str_lower_string(char *p_instr)
{
	int len;
	int i;

	len=(int)strlen(p_instr);

	for (i=0;i<len;i++)
	{
		p_instr[i]=str_lower(p_instr[i]);
	}

	return(0);
}


