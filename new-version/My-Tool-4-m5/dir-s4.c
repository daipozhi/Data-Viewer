// arg1 input directory
// arg2 output file name


// daipozhi modified
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


static 	char   deb_currentpath[3000];
static int deb_filename_dir(char *path,char *name);
static int deb_str_has_null(char *s1,int s1_len);


//---------------binary tree-------------------------------

//#define  _CRT_SECURE_NO_WARNINGS

//#define   STRICT
//#include <windows.h>
//#include <commdlg.h>

//#include <string.h>
//#include <stdio.h>

//#include <direct.h>
//#include <ctype.h>
//#include <io.h>
//#include <dos.h>
//#include <errno.h>


#define TREE2_SIZE 100000
#define LIST_SIZE  3000

//class tree2
//{
//  private:

static     char  node_mark[TREE2_SIZE];
static     char  node_val[TREE2_SIZE][500];
static     char  node_val2[TREE2_SIZE];

//  private:

static     int   node_pp[TREE2_SIZE][3];
static     int   root_pp;
static     int   buff_pp;
    
static     int   list_stack[LIST_SIZE];
static     char  list_stack_type[LIST_SIZE];
static     int   list_pp;

static     char  out_buff[TREE2_SIZE][500];
static     char  out_buff2[TREE2_SIZE];
static     int   out_pp;
static     int   out_pp2;
 
static     char  out_mixed_buff[TREE2_SIZE][500];
static     char  out_mixed_buff2[TREE2_SIZE];
static     int   out_mixed_pp;
static     int   out_mixed_pp2;
 
//  public:

static     int   find_pp;
static     int   find_pp2;
static     int   find_side;

static     char  find_filename[500];
//static     char  find_filetype[10];
    
static     int   over_flow;

static     char  entry_d_name[500];
static     int   entry_d_type;

//  public:

static     int   init_tree2(void);
static     int   new_node(void);
static     int   clear_node(int pp);
static     int   search_node(char *pstr);
static     int   insert_node(char *pstr);
static     int   dsp_tree2(void);
static     int   after_list(int pf);
static     int   out_list(char *pstr,char ptype);
static     int   dsp_list(void);
static     int   save_list(char *fn);


static     int   save_node_info(int pp,int l,int c);
static     int   clear_node_info(int pp);
static     int   out_list2(int pp);
static     int   out_list3(int pp);
static     int   search_2seper(int p1,int p2,int l,int c);
static     int   search_2seper_cmp(int pp,int pl,int pc);
static     int   test2(void);

static     int   bt_opendir(void);
static     int   bt_readdir(void);
static     int   bt_findclose(void);

static     char  str_lower(char);
static     int   str_lower_string(char *,char *);

/*
  public:

    int   node_info[TREE2_SIZE][3];
    int   node_info_pp;

    int   node_info2[TREE2_SIZE][2];
    int   node_info2_pp;
*/
//};


//class tree2 tree2a;

// end of binary tree --------------------------------



static char          m202_buffer2[3000];


static int  bt_opendir(void)
{
  DIR           *dirp;
  struct dirent *entry;

    int           i;
    //char          buffer2[3000];

	out_mixed_pp=0;
	out_mixed_pp2=(-1);

	init_tree2();

	if (dirp = opendir(deb_currentpath))
        {
		while (1)
		{
			if (entry = readdir(dirp))
			{
				if (strcmp(entry->d_name,".") ==0) continue;
				if (strcmp(entry->d_name,"..")==0) continue;

				i=deb_filename_dir(deb_currentpath,entry->d_name);

				if (i==1)
				{
					//if (deb_str_has_null(entry->d_name,500)!=1) continue;

					if (strlen(entry->d_name)>=500) continue;

					strcpy(m202_buffer2,entry->d_name);


				        insert_node(m202_buffer2);
					node_val2[find_pp2]=1;

				}
			}
			else break;
		}

		after_list(1);

		for (i=0;i<out_pp;i++)
		{
			if (i<0) continue;
			if (i>=100000) continue;

			if (out_mixed_pp<0) continue;
			if (out_mixed_pp>=100000) continue;

			if (deb_str_has_null(out_buff[i],500)!=1) continue;

			if (strlen(out_buff[i])>=500) continue;

			strcpy(out_mixed_buff[out_mixed_pp],out_buff[i]);

			out_mixed_buff2[out_mixed_pp]=out_buff2[i];

			out_mixed_pp++;

			if (out_mixed_pp>=TREE2_SIZE) return(-1);
		}

	}
	else return(-1);

	closedir(dirp);

	init_tree2();


	if (dirp = opendir(deb_currentpath))
        {
		while (1)
		{
			if (entry = readdir(dirp))
			{
				if (strcmp(entry->d_name,".") ==0) continue;
				if (strcmp(entry->d_name,"..")==0) continue;

				i=deb_filename_dir(deb_currentpath,entry->d_name);

				if (i==1) continue;

				//if (deb_str_has_null(entry->d_name,500)!=1) continue;

				if (strlen(entry->d_name)>=500) continue;

			        insert_node(entry->d_name);
				node_val2[find_pp2]=0;

			}
			else break;
		}

		after_list(1);

		for (i=0;i<out_pp;i++)
		{
			if (i<0) continue;
			if (i>=100000) continue;

			if (out_mixed_pp<0) continue;
			if (out_mixed_pp>=100000) continue;

			if (deb_str_has_null(out_buff[i],500)!=1) continue;

			if (strlen(out_buff[i])>=500) continue;

			strcpy(out_mixed_buff[out_mixed_pp],out_buff[i]);

			out_mixed_buff2[out_mixed_pp]=out_buff2[i];

			out_mixed_pp++;

			if (out_mixed_pp>=TREE2_SIZE) return(-1);
		}

	}
	else return(-1);

	closedir(dirp);
	
	return(0);
}


static char m105_str1[3000];

static int deb_filename_dir(char *path,char *name)
{
	//char str1[3000];
	struct stat info;

	strcpy(m105_str1,path);
	strcat(m105_str1,"/" );
	strcat(m105_str1,name);

	stat(m105_str1,&info);

	if (S_ISDIR(info.st_mode)) return(1);
	else return(0);
}

static int  bt_findclose( void)
{
	return(0);
}


static char  str_lower(char c1)
{
  if ((c1>='A')&&(c1<='Z')) return(c1-'A'+'a');
  else return(c1);
}

static int  str_lower_string(char *p_instr,char *p_outstr)
{
	int len;
	int i;

	len=(int)strlen(p_instr);

	p_outstr[0]=0;

	for (i=0;i<len;i++)
	{
		p_outstr[i+0]=str_lower(p_instr[i]);
		p_outstr[i+1]=0;
	}

	return(0);
}

static int deb_str_has_null(char *s1,int s1_len)
{
	int i;

	for (i=0;i<s1_len;i++)
		if (s1[i]==0) return(1);

	return(0);
}














//---------------binary tree-------------------------------

static int  init_tree2(void)
{
//  int i,j;
//  for (i=0;i<TREE2_SIZE;i++)
//  {
//    node_mark[i]=(-1);
//  }
  root_pp=(-1);
  buff_pp=0;
//  node_info_pp=0;
//  node_info2_pp=0;

  over_flow=0;

  //out_mixed_pp=0;

  return(0);
}

static int  new_node(void)
{
  int i,j;
/*
  i=(-1);
  j=buff_pp;
  
  while (1)
  {
    if (node_mark[buff_pp]<0)
    {
      node_mark[buff_pp]=0;
      i=buff_pp;
      buff_pp++;
      if (buff_pp>=TREE2_SIZE) buff_pp=0;
      break;
    }
    else
    {
      buff_pp++;
      if (buff_pp>=TREE2_SIZE) buff_pp=0;
      if (buff_pp==j) break;
    }
  }

  return(i);
*/

  i=buff_pp;

  buff_pp++;

  if (buff_pp>=TREE2_SIZE)
  {
	  buff_pp=TREE2_SIZE-1;

	  over_flow=1;

	  printf("Param TREE2_SIZE too small\n");
	
	  exit(1);
  }
  
  return(i);
}

static int  clear_node(int pp)
{
  int i;

  if (pp<0) return(0);
  if (pp>=TREE2_SIZE) return(0);
  
  node_pp[pp][0]=(-1);
  node_pp[pp][1]=(-1);
  node_pp[pp][2]=(-1);

  for (i=0;i<500;i++)
  {
    node_val[pp][i]=0;
	//node_val2[pp]=0;
  }

  node_val2[pp]=0;

  return(0);
}

static char m201_str1[3000];
static char m201_str2[3000];

static int  search_node(char *pstr)
{
  int i,j;
  //char str1[3000];
  //char str2[3000];

  //if (deb_str_has_null(pstr,500)!=1) return(1);

  if (strlen(pstr)>=500) return(1);
  
  if (root_pp<0)
  {
     find_pp=(-1);
     return(1);
  }

  i=root_pp;

  while (1)
  {
  
    str_lower_string(node_val[i],m201_str1);
    str_lower_string(pstr,m201_str2);

    if (strcmp(m201_str1,m201_str2)==0)
    {
      find_pp=i;
      return(0);
    }

    if (strcmp(m201_str1,m201_str2)>0)
    {
      if (node_pp[i][2]<0)
      {
        find_pp=i;
        find_side=2;
        return(1);
      }
      else
      {
        i=node_pp[i][2];
        continue;
      }
    }
    
    if (strcmp(m201_str1,m201_str2)<0)
    {
      if (node_pp[i][1]<0)
      {
        find_pp=i;
        find_side=1;
        return(1);
      }
      else
      {
        i=node_pp[i][1];
        continue;
      }
    }
    
  }

}

static int  insert_node(char *pstr)
{
  int i,j;

  //if (deb_str_has_null(pstr,500)!=1) return(1);

  if (strlen(pstr)>=500) return(1);

  i=search_node(pstr);

  if (i==0)
  {
	  find_pp2=find_pp;
	  return(0);
  }
  else
  {
    if (find_pp<0)
    {
      j=new_node();
      if (j<0)
      {
        //MessageBox(0,"error at insert_node() when call new_node()","message",MB_OK);
	over_flow=1;
        return(1);
		// not more than 10000
      }
      else
      {
        root_pp=j;
        clear_node(j);
        strcpy(node_val[j],pstr);
	find_pp2=j;
        return(0);
      }
    }
    else
    {
      j=new_node();
      if (j<0)
      {
        //MessageBox(0,"error at insert_node() when call new_node()","message",MB_OK);
	over_flow=1;
        return(1);
		// not more than 10000
      }
      else
      {
        clear_node(j);
        strcpy(node_val[j],pstr);

        node_pp[j][0]=find_pp;

        if (find_side==2) node_pp[find_pp][2]=j;
        else node_pp[find_pp][1]=j;

	find_pp2=j;

        return(0);
      }
    }
  }
}
/*
int  dsp_tree2(void)
{
  int  i,j,k,l,m,n,o;
  int  p1,p2,p3,p4,p5,p6,p7,p8;
  
  char str1[500];
  char str2[500];
  char str3[500];
  char str4[500];
  char str5[500];
  char str6[500];
  char str7[500];
  char str8[500];
  char str9[500];
  char str10[500];
  char str11[500];
  char str12[500];
  char str13[500];
  char str14[500];
  char str15[500];
  char str16[500];

  i=root_pp;
  j=node_pp[i][1];
  k=node_pp[i][2];

  sprintf(str1,"level1,val=%s,pp=%d,%d,",node_val[i],node_pp[i][1],node_pp[i][2]);
  
  if (j>=0)
  {
    sprintf(str2,"level2-1,val=%s,pp=%d,%d,",node_val[j],node_pp[j][1],node_pp[j][2]);
    l=node_pp[j][1];
    m=node_pp[j][2];
  }
  else
  {
     strcpy(str2,"");
     l=(-1);
     m=(-1);
  }

  if (k>=0)
  {
    sprintf(str3,"level2-2,val=%s,pp=%d,%d,",node_val[k],node_pp[k][1],node_pp[k][2]);
    n=node_pp[k][1];
    o=node_pp[k][2];
  }
  else
  {
    strcpy(str3,"");
    n=(-1);
    o=(-1);
  }

  if (l>=0)
  {
    sprintf(str4,"level3-1,val=%s,pp=%d,%d,",node_val[l],node_pp[l][1],node_pp[l][2]);
    p1=node_pp[l][1];
    p2=node_pp[l][2];
  }
  else
  {
    strcpy(str4,"");
    p1=(-1);
    p2=(-1);
  }

  if (m>=0)
  {
    sprintf(str5,"level3-2,val=%s,pp=%d,%d,",node_val[m],node_pp[m][1],node_pp[m][2]);
    p3=node_pp[m][1];
    p4=node_pp[m][2];
  }
  else
  {
    strcpy(str5,"");
    p3=(-1);
    p4=(-1);
  }

  if (n>=0)
  {
    sprintf(str6,"level3-3,val=%s,pp=%d,%d,",node_val[n],node_pp[n][1],node_pp[n][2]);
    p5=node_pp[n][1];
    p6=node_pp[n][2];
  }
  else
  {
    strcpy(str6,"");
    p5=(-1);
    p6=(-1);
  }

  if (o>=0)
  {
    sprintf(str7,"level3-4,val=%s,pp=%d,%d,",node_val[o],node_pp[o][1],node_pp[o][2]);
    p7=node_pp[o][1];
    p8=node_pp[o][2];
  }
  else
  {
    strcpy(str7,"");
    p7=(-1);
    p8=(-1);
  }

  if (p1>=0)
  {
    sprintf(str9,"level4-1,val=%s,pp=%d,%d,",node_val[p1],node_pp[p1][1],node_pp[p1][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str9,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p2>=0)
  {
    sprintf(str10,"level4-2,val=%s,pp=%d,%d,",node_val[p2],node_pp[p2][1],node_pp[p2][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str10,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p3>=0)
  {
    sprintf(str11,"level4-3,val=%s,pp=%d,%d,",node_val[p3],node_pp[p3][1],node_pp[p3][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str11,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p4>=0)
  {
    sprintf(str12,"level4-4,val=%s,pp=%d,%d,",node_val[p4],node_pp[p4][1],node_pp[p4][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str12,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p5>=0)
  {
    sprintf(str13,"level4-5,val=%s,pp=%d,%d,",node_val[p5],node_pp[p5][1],node_pp[p5][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str13,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p6>=0)
  {
    sprintf(str14,"level4-6,val=%s,pp=%d,%d,",node_val[p6],node_pp[p6][1],node_pp[p6][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str14,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p7>=0)
  {
    sprintf(str15,"level4-7,val=%s,pp=%d,%d,",node_val[p7],node_pp[p7][1],node_pp[p7][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str15,"");
    //p7=(-1);
    //p8=(-1);
  }

  if (p8>=0)
  {
    sprintf(str16,"level4-8,val=%s,pp=%d,%d,",node_val[p8],node_pp[p8][1],node_pp[p8][2]);
    //p7=node_pp[p1][1];
    //p8=node_pp[p1][2];
  }
  else
  {
    strcpy(str16,"");
    //p7=(-1);
    //p8=(-1);
  }

  sprintf(str8,"%s , \n %s,%s, \n %s,%s,%s,%s, \n %s,%s,%s,%s,%s,%s,%s,%s, \n",str1,str2,str3,str4,str5,str6,str7,str9,str10,str11,str12,str13,str14,str15,str16);

  //MessageBox(0,str8,"message dsp tree2",MB_OK);

  return(0);
}
*/

static   char m401_str1[300];

static int  after_list(int pf)
{
  int  i,j,k;
  //char str1[300];

  list_pp=0;
  out_pp=0;
  out_pp2=(-1);
  
  i=root_pp;
  if (i<0) return(0);

  if (node_pp[i][1]>=0)
  {
    list_stack[list_pp]=node_pp[i][1];
    list_stack_type[list_pp]=1;
    list_pp++;
  }

  list_stack[list_pp]=i;
  list_stack_type[list_pp]=2;
  list_pp++;
  
  if (node_pp[i][2]>=0)
  {
    list_stack[list_pp]=node_pp[i][2];
    list_stack_type[list_pp]=1;
    list_pp++;
  }

  while (list_pp>0)
  {
    list_pp--;
    j=list_pp;

    if (list_stack_type[j]==1)
    {
      k=list_stack[j];
      
      if (node_pp[k][1]>=0)
      {
        list_stack[list_pp]=node_pp[k][1];
        list_stack_type[list_pp]=1;
        list_pp++;

        //sprintf(str1,"add left tree %s,list_pp=%d,",node_val[node_pp[k][1]],list_pp);
        //MessageBox(0,str1,"message",MB_OK);
      }

      list_stack[list_pp]=k;
      list_stack_type[list_pp]=2;
      list_pp++;

      //sprintf(str1,"add mid tree %s,list_pp=%d,",node_val[k],list_pp);
      //MessageBox(0,str1,"message",MB_OK);

      if (node_pp[k][2]>=0)
      {
        list_stack[list_pp]=node_pp[k][2];
        list_stack_type[list_pp]=1;
        list_pp++;

        //sprintf(str1,"add right tree %s,list_pp=%d,",node_val[node_pp[k][2]],list_pp);
        //MessageBox(0,str1,"message",MB_OK);
      }
    }
    else
    {
      k=list_stack[j];

      if (pf==1) out_list(node_val[k],node_val2[k]);
/*
      if (pf==2) out_list2(k);

      if (pf==3) out_list3(k);
*/
      //sprintf(str1,"out val %s,",node_val[k]);
      //MessageBox(0,str1,"message",MB_OK);
    }
  }

  return(0);
}

static int  out_list(char *pstr,char ptype)
{
  if (out_pp<0) return(0);
  if (out_pp>=100000) return(0);

  if (deb_str_has_null(pstr,500)!=1) return(0);

  if (strlen(pstr)>=500) return(0);
  
  strcpy(out_buff[out_pp],pstr);
  out_buff2[out_pp]=ptype;

  out_pp++;

  if (out_pp>=100000) out_pp=100000-1;

  return(0);
}
/*
int  out_list2(int pp)
{
  int i,j,k;
  int p1,p2;

  i=node_val2[pp][0];

  p1=node_info2_pp;
  p2=node_info2_pp;

  while (i>=0)
  {
	  j=node_info[i][0];
	  k=node_info[i][1];

	  node_info2[node_info2_pp][0]=j;
	  node_info2[node_info2_pp][1]=k;

	  node_info2_pp++;

	  i=node_info[i][2];
  }

  p2=node_info2_pp;

  node_val2[pp][2]=p1;
  node_val2[pp][3]=p2;

  return(0);
}

static char m402_str1[300];

static int  out_list3(int pp)
{
  int  i,j,k;
  //char str1[300];
  FILE *fp;

  fp=fopen("test1.txt","a");
  if (fp==NULL) return(1);

  sprintf(m402_str1,"val=%s,val2=%d,%d,%d,%d,",node_val[pp],node_val2[pp][0],node_val2[pp][1],node_val2[pp][2],node_val2[pp][3]);
  fputs(m402_str1,fp);
  fputs("\n",fp);

  fclose(fp);

  return(0);
}
*/
static int  dsp_list(void)
{
  //char str1[300];
  /*
  sprintf(str1,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",
               out_buff[0],
               out_buff[1],
               out_buff[2],
               out_buff[3],
               out_buff[4],
               out_buff[5],
               out_buff[6],
               out_buff[7],
               out_buff[8],
               out_buff[9]
               );
  */             
  //MessageBox(0,str1,"message dsp list",MB_OK);

  return(0);
}

static int  save_list(char *fn)
{
  FILE *fp;
  int   i,j;
  /*
  fp=fopen(fn,"w");
  if (fp==NULL)
  {
    //MessageBox(0,fn,"Error at open file",MB_OK);
    return(1);
  }

  for (i=0;i<out_pp;i++)
  {
//    fputs(out_buff[i],fp);
    fputs("\n",fp);
  }

  fclose(fp);
  */
  return(0);
}
/*
int  search_2seper(int n1,int n2,int pl,int pc)
{
	int p1,p2;
	int i,j;
	int find;

	find=0;
	p1=n1;
	p2=n2;

	if (p2<=p1) return(0);

	while(1)
	{
		i=(p1+p2)/2;
		if (i<=p1)
		{
			j=search_2seper_cmp(i,pl,pc);
			if (j==0)
			{
				find=1;
				break;
			}
			else
			{
				find=0;
				break;
			}
		}
		else
		{
			if (i>=p2)
			{
				find=0;
				break;
			}
			else
			{
				j=search_2seper_cmp(i,pl,pc);
				if (j==0)
				{
					find=1;
					break;
				}
				else
				{
					if (j>0)
					{
						p1=i;
						continue;
					}
					else
					{
						p2=i;
						continue;
					}
				}
			}
		}
	}

	return(find);
}

int  search_2seper_cmp(int pp,int pl,int pc)
{
	int i,j;

	i=node_info2[pp][0];
	j=node_info2[pp][1];

	if (i>pl) return(-1);
	else
	{
		if (i<pl) return(1);
		else
		{
			if (j>pc) return(-1);
			else
			{
				if (j<pc) return(1);
				else return(0);
			}
		}
	}
}

int  test2(void)
{
	int  i,j;
	char str1[300];
	FILE *fp;

	fp=fopen("test2.txt","a");
	if (fp==NULL) return(1);

	for (i=0;i<200;i++)
	{
		sprintf(str1,"info=%d,%d,%d,info2=%d,%d,",
			node_info[i][0],
			node_info[i][1],
			node_info[i][2],
			node_info2[i][0],
			node_info2[i][1]);
		fputs(str1,fp);
		fputs("\n",fp);
	}

	fclose(fp);

	return(0);
}
*/
/*
int main(void)
{

	tree2a.init_tree2();
  

	MessageBox(0,"start...","box",MB_OK);


	MessageBox(0,"add 53","box",MB_OK);
	tree2a.insert_node("053");
	tree2a.dsp_tree2();

	MessageBox(0,"add 75","box",MB_OK);
	tree2a.insert_node("075");
	tree2a.dsp_tree2();

	MessageBox(0,"add 139","box",MB_OK);
	tree2a.insert_node("139");
	tree2a.dsp_tree2();

	MessageBox(0,"add 49","box",MB_OK);
	tree2a.insert_node("049");
	tree2a.dsp_tree2();

	MessageBox(0,"add 145","box",MB_OK);
	tree2a.insert_node("145");
	tree2a.dsp_tree2();

	MessageBox(0,"add 36","box",MB_OK);
	tree2a.insert_node("036");
	tree2a.dsp_tree2();

	MessageBox(0,"add 101","box",MB_OK);
	tree2a.insert_node("101");
	tree2a.dsp_tree2();

	MessageBox(0,"add 050","box",MB_OK);
	tree2a.insert_node("050");
	tree2a.dsp_tree2();

	MessageBox(0,"add 070","box",MB_OK);
	tree2a.insert_node("070");
	tree2a.dsp_tree2();

  tree2a.after_list();
  tree2a.dsp_list();
*/
/*
	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	MessageBox(NULL,"add 50","box",MB_OK);
	tree2a.insert(50);
	tree2a.dsp();

	MessageBox(NULL,"add 30","box",MB_OK);
	tree2a.insert(30);
	tree2a.dsp();

	MessageBox(NULL,"add 60","box",MB_OK);
	tree2a.insert(60);
	tree2a.dsp();

	MessageBox(NULL,"add 70","box",MB_OK);
	tree2a.insert(70);
	tree2a.dsp();

	MessageBox(NULL,"add 10","box",MB_OK);
	tree2a.insert(10);
	tree2a.dsp();

	MessageBox(NULL,"add 40","box",MB_OK);
	tree2a.insert(40);
	tree2a.dsp();

	MessageBox(NULL,"add 55","box",MB_OK);
	tree2a.insert(55);
	tree2a.dsp();

	MessageBox(NULL,"add 58","box",MB_OK);
	tree2a.insert(58);
	tree2a.dsp();

	MessageBox(NULL,"add 65","box",MB_OK);
	tree2a.insert(65);
	tree2a.dsp();

	MessageBox(NULL,"add 75","box",MB_OK);
	tree2a.insert(75);
	tree2a.dsp();

	MessageBox(NULL,"add 80","box",MB_OK);
	tree2a.insert(80);
	tree2a.dsp();


	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	tree2a.insert(50);
	tree2a.insert(30);
	tree2a.insert(60);
	tree2a.insert(70);
	tree2a.insert(10);
	tree2a.insert(40);
	tree2a.insert(55);
	tree2a.insert(58);
	tree2a.insert(65);
	tree2a.insert(75);
	tree2a.insert(80);


	tree2a.dsp();

	MessageBox(NULL,"del 55","box",MB_OK);
	tree2a.delt(55);
	tree2a.dsp();

	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	tree2a.insert(50);
	tree2a.insert(30);
	tree2a.insert(60);
	tree2a.insert(70);
	tree2a.insert(10);
	tree2a.insert(40);
	tree2a.insert(55);
	tree2a.insert(58);
	tree2a.insert(75);
	tree2a.insert(80);

	tree2a.dsp();

	MessageBox(NULL,"del 70","box",MB_OK);
	tree2a.delt(70);
	tree2a.dsp();

	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	tree2a.insert(50);
	tree2a.insert(30);
	tree2a.insert(60);
	tree2a.insert(10);
	tree2a.insert(40);
	tree2a.insert(55);
	tree2a.insert(58);
	tree2a.insert(75);
	tree2a.insert(80);
	tree2a.dsp();

	MessageBox(NULL,"del 55","box",MB_OK);
	tree2a.delt(55);
	tree2a.dsp();

	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	tree2a.insert(50);
	tree2a.insert(30);
	tree2a.insert(58);
	tree2a.insert(75);
	tree2a.insert(10);
	tree2a.insert(40);
	tree2a.insert(55);
	tree2a.insert(60);
	tree2a.insert(80);
	tree2a.dsp();

	MessageBox(NULL,"del 80","box",MB_OK);
	tree2a.delt(80);
	tree2a.dsp();

	root=new mnode;
	tree2a.clr(root);
	MessageBox(NULL,"start...","box",MB_OK);

	tree2a.insert(50);
	tree2a.insert(30);
	tree2a.insert(60);
	tree2a.insert(70);
	tree2a.insert(10);
	tree2a.insert(40);

	tree2a.insert(55);
	tree2a.insert(58);
	tree2a.insert(65);
	tree2a.insert(75);
	tree2a.insert(80);

	tree2a.dsp();
*/
/*
	MessageBox(NULL,"del 50","box",MB_OK);
	tree2a.delt(50);
	tree2a.dsp();

	MessageBox(NULL,"del 55","box",MB_OK);
	tree2a.delt(55);
	tree2a.dsp();

	MessageBox(NULL,"del 70","box",MB_OK);
	tree2a.delt(70);
	tree2a.dsp();

	MessageBox(NULL,"del 75","box",MB_OK);
	tree2a.delt(75);
	tree2a.dsp();
*/
/*
	return(0);
}
*/

// end binary tree ------------------------------------------






int init_read(void);
int init_read2(void);

char m01_str1[500];
char m01_str2[500];
char m01_str3[500];
char m01_str4[500];

char m01_dir_v1[100000][500];
int  m01_dir_v2[100000];
int  m01_dir_p1[30][2];
int  m01_dir_p2;
int  m01_dir_p3[30][2];

FILE *m_fp1;

int main(int argc, char **argv)
{
    int i,j,k;

    if (argc!=3)
    {
	printf("\n usage: ./a.out my-dir output.txt \n");
        return(1);
    }

    strcpy(m01_str1,argv[1]);
    strcpy(m01_str2,argv[2]);

    m01_dir_p2=0;

    for (i=0;i<30;i++)
    {
      m01_dir_p1[i][0]=0;
      m01_dir_p1[i][1]=0;
    }

    for (i=0;i<30;i++)
    {
      m01_dir_p3[i][0]=0;
      m01_dir_p3[i][1]=0;
    }

    for (j=0;j<100000;j++)
	    for (k=0;k<500;k++)
		m01_dir_v1[j][k]=0;

    for (j=0;j<100000;j++)
	    m01_dir_v2[j]=0;

    m_fp1=fopen(m01_str2,"w");
    if (m_fp1==NULL)
    {
	printf("\n open output file error\n");
	return(1);
    }


    init_read();

    for (i=m01_dir_p1[0][0];i<m01_dir_p1[0][1];i++)
    {
	fputs(m01_str1,m_fp1);
	fputs("/"     ,m_fp1);
	fputs(m01_dir_v1[i],m_fp1);
        fputs("\n"    ,m_fp1);
    }

    while (1)
    {
	if (m01_dir_p3[m01_dir_p2][1]>=m01_dir_p1[m01_dir_p2][1])
	{
	    if (m01_dir_p2>0)
	    {
		m01_dir_p2--;
		continue;
	    }
	    else break;
	}

	if (m01_dir_v2[m01_dir_p3[m01_dir_p2][1]]==0)
	{
	    if (m01_dir_p2>0)
	    {
		m01_dir_p2--;
		continue;
	    }
	    else break;
	}

	m01_dir_p3[m01_dir_p2][1]++;

	strcpy(m01_str4,m01_str1);

	for (i=0;i<=m01_dir_p2;i++)
	{
		strcat(m01_str4,"/");
		strcat(m01_str4,m01_dir_v1[ m01_dir_p3[i][1] -1  ] );
	}


	init_read2();

	for (i=m01_dir_p1[m01_dir_p2][0];i<m01_dir_p1[m01_dir_p2][1];i++)
	{
		fputs(m01_str4,m_fp1);
		fputs("/"     ,m_fp1);
		fputs(m01_dir_v1[i],m_fp1);
	        fputs("\n"    ,m_fp1);
	}

    }

    fclose(m_fp1);

    return(0);
}

int init_read(void)
{
    int i;

    strcpy(deb_currentpath,m01_str1);
    bt_opendir();

    for (i=0;i<out_mixed_pp;i++)
    {
	strcpy(m01_dir_v1[i],out_mixed_buff[i]);
               m01_dir_v2[i]=out_mixed_buff2[i];
    }

    m01_dir_p1[0][0]=0;
    m01_dir_p1[0][1]=0+out_mixed_pp;
    m01_dir_p2=0;
    m01_dir_p3[0][0]=0;
    m01_dir_p3[0][1]=0;
}


int init_read2(void)
{
    int i,j,k;

    strcpy(deb_currentpath,m01_str4);

    j=m01_dir_p1[m01_dir_p2][1];

    bt_opendir();

    m01_dir_p2++;

    for (i=0;i<out_mixed_pp;i++)
    {
	strcpy(m01_dir_v1[j+i],out_mixed_buff[i]);
               m01_dir_v2[j+i]=out_mixed_buff2[i];
    }

    m01_dir_p1[m01_dir_p2][0]=j;
    m01_dir_p1[m01_dir_p2][1]=j+out_mixed_pp;
    m01_dir_p3[m01_dir_p2][0]=j;
    m01_dir_p3[m01_dir_p2][1]=j;
}

