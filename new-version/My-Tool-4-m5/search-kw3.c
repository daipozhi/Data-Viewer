// arg1 input file
// arg2 output file
// arg3,4,5,6  search key words


// daipozhi modified
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



static int deb_filename_is_dir(char *path);
static char str_lower(char c1);
static int  str_lower_string(char *p_instr);
static int  str_find(char *ps1,char *ps2);

static int ext_init(void);
static int ext_in(char *ext);
static int deb_filenameext(char *name,char *fext);




FILE *m_fp1;
FILE *m_fp2;
FILE *m_fp3;

char m01_str1[500];
char m01_str2[500];

char m01_str3[3000];
char m01_str4[3000000];
char m01_str6[3000000];

char m01_str5[4][500];
int  m01_val5[4];

int  m01_val7;

char m01_ext8[10][10];
int  m01_pp8;

char m01_ext9[300];

int main(int argc, char **argv)
{
    int i,j,k,l;
    int n1,n2,n3,n4;

    if (argc<4)
    {
	printf("\n usage: ./a3.out input.txt output.txt keyword1 (keyword2) (keyword3) \n");
        return(1);
    }

    ext_init();

    strcpy(m01_str1,argv[1]);
    strcpy(m01_str2,argv[2]);

    m01_str5[0][0]=0;
    m01_str5[1][0]=0;
    m01_str5[2][0]=0;
    m01_str5[3][0]=0;

    if (argc>=4)
    {
	strcpy(m01_str5[0],argv[3]);
	str_lower_string(m01_str5[0]);
               m01_val5[0]=1;
    }
    else m01_val5[0]=0;
    
    if (argc>=5)
    {
	strcpy(m01_str5[1],argv[4]);
	str_lower_string(m01_str5[1]);
               m01_val5[1]=1;
    }
    else m01_val5[1]=0;
    
    if (argc>=6)
    {
	strcpy(m01_str5[2],argv[5]);
	str_lower_string(m01_str5[2]);
               m01_val5[2]=1;
    }
    else m01_val5[2]=0;
    
    if (argc>=7)
    {
	strcpy(m01_str5[3],argv[6]);
	str_lower_string(m01_str5[3]);
               m01_val5[3]=1;
    }
    else m01_val5[3]=0;
    
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
	m01_str3[0]=0;

	fgets(m01_str3,3000,m_fp1);

        m01_val7=1;

	for (i=strlen(m01_str3)-1;i>=0;i--)
	{
		if ((m01_str3[i]>=0)&&(m01_str3[i]<=' ')) m01_str3[i]=0;
		else break;
	}

	//printf("open file:%s,\n",m01_str3);

	if (strlen(m01_str3)<1) break;

        i=deb_filename_is_dir(m01_str3);
	if (i==1) continue;

	deb_filenameext(m01_str3,m01_ext9);

	str_lower_string(m01_ext9);

	l=ext_in(m01_ext9);
	if (l!=1) continue;

	m_fp3=fopen(m01_str3,"r");
	if (m_fp3==NULL)
	{
	    continue;
	}


	while(!feof(m_fp3))
	{
	    m01_str4[0]=0;
	    m01_str6[0]=0;

	    fgets(m01_str4,3000000,m_fp3);

	    for (i=strlen(m01_str4)-1;i>=0;i--)
	    {
		if ((m01_str4[i]>=0)&&(m01_str4[i]<=' ')) m01_str4[i]=0;
		else break;
	    }

	    strcpy(m01_str6,m01_str4);
	    str_lower_string(m01_str6);

            if (m01_val5[0]==0) n1=1;
	    else n1=str_find(m01_str6,m01_str5[0]);

            if (m01_val5[1]==0) n2=1;
	    else n2=str_find(m01_str6,m01_str5[1]);

            if (m01_val5[2]==0) n3=1;
	    else n3=str_find(m01_str6,m01_str5[2]);

            if (m01_val5[3]==0) n4=1;
	    else n4=str_find(m01_str6,m01_str5[3]);

	    if ((n1==1)&&(n2==1)&&(n3==1)&&(n4==1))
	    {
		if (m01_val7==1)
		{
			fputs("***in file***"   ,m_fp2);
			fputs(m01_str3,m_fp2);
			fputs("\n"    ,m_fp2);

			m01_val7=0;

			//printf("%s","***in file***");
			//printf("%s",m01_str3);
			//printf("\n");
		}

		fputs(m01_str4,m_fp2);
		fputs("\n"    ,m_fp2);

		//printf("%s",m01_str4);
		//printf("\n");
	    }
	}

	fclose(m_fp3);
    }

    fclose(m_fp2);
    fclose(m_fp1);

    return(0);
}

static int deb_filename_is_dir(char *path)
{
	struct stat info;

	stat(path,&info);

	if (S_ISDIR(info.st_mode)) return(1);
	else return(0);
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

static int str_find(char *ps1,char *ps2)
{
    int n1,n2;
    int i,j,k;

    n1=strlen(ps1);
    n2=strlen(ps2);

    if (n1<n2) return(0);

    for (i=0;i<=n1-n2;i++)
    {
        k=0;
	for (j=0;j<n2;j++)
	{
		if (ps2[j]!=ps1[i+j])
		{
			k=1;
			break;
		}
	}
	if (k==0) return(1);
    }

    return(0);
}

static int ext_init(void)
{
//char m01_ext8[10][10];
//int  m01_pp8;

  m01_pp8=0;

  strcpy(m01_ext8[m01_pp8],"txt");   m01_pp8++;
  strcpy(m01_ext8[m01_pp8],"h");     m01_pp8++;
  strcpy(m01_ext8[m01_pp8],"c");     m01_pp8++;
  strcpy(m01_ext8[m01_pp8],"cpp");   m01_pp8++;

  return(0);
}

static int ext_in(char *ext)
{
  int i;

  for (i=0;i<m01_pp8;i++)
  {
    if (strcmp(ext,m01_ext8[i])==0) return(1);
  }

  return(0);
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










