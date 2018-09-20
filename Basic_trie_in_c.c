
// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>


// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')





struct file_strc
{
    char Alphabet;
    char fname[20];
    int flag;
};

void read_file()
{
    FILE *fp;
    fp=fopen("root.txt","r");
    int i=1;
    struct file_strc fc;
    printf("ready to print\n");
    for(i=0;i<26;i++)
    {
        fread(&fc, sizeof(fc), 1, fp);
        //fscanf(fp,"%c %s %d\n",&fc.Alphabet,&fc.fname,&fc.flag);
        printf("%c %s %d\n",fc.Alphabet,fc.fname,fc.flag);
    }
    fclose(fp);

}
char* get_filename(char letter1,char letter,int level)
{
    char number[100];
    char filename[20];
    filename[0]=letter1;
    filename[1]=letter;
    sprintf(filename+2, "%d",level);
    strcpy(filename,strcat(filename,".txt"));
    printf("%s",filename);
    return filename;
}


int create_file(char file[20])
{
    FILE *fp;
    struct file_strc fs;
    fp=fopen(file,"w");
    printf("in create file");
    if(fp==NULL)
    {
        printf("file not created");
        return 0;
    }

    int i=1;
    fs.flag=0;
    strcpy(fs.fname,"null");
    printf("ready to write");
    for(i=0;i<26;i++)
    {
        fs.Alphabet='a'+i;
        fwrite(&fs, sizeof(fs), 1, fp);
    }
    printf("finished");
    fclose(fp);
    return 1;
}










struct file_strc read_file_direct(int num,FILE *fp)
{

    int i=1;
    struct file_strc c;
    printf("ready to print %d\n",num);
    fseek(fp,(sizeof(c))*num,SEEK_SET);
    fread(&c, sizeof(c), 1, fp);
    printf("====%c %s %d====\n",c.Alphabet,c.fname,c.flag);
    return c;

}


void write_file_direct(int num,FILE *fp,struct file_strc c)
{

    int i=1;
    struct file_strc x;
    printf("ready to print %d\n",num);
    fseek(fp,(sizeof(c))*num,SEEK_SET);
    int pos=ftell(fp);
    fread(&x, sizeof(x), 1, fp);




    strcpy(x.fname,c.fname);
    x.flag=c.flag;


    fseek(fp,pos,SEEK_SET);
    fwrite(&x,sizeof(x),1,fp);
    //printf("%c %s %d\n",c.Alphabet,c.fname,c.flag);


}



// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node

void insert(const char *key)
{
    int level=0;
    int length = strlen(key);
    int index;
printf("1)%s\n",key);
 char filename[20];

        FILE *fp;
        index = CHAR_TO_INDEX(key[level]);
        fp=fopen("root.txt","r+");
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        struct file_strc fs;
        fs=read_file_direct(index,fp);

        printf("======%s=========\n",fs.fname);
        printf("\n index %d length =%d\n",level,length);
        if(level==length-1)
        {

           struct file_strc c;
                c.Alphabet=key[level];
           c.flag=1;
           strcpy(c.fname,"null");
             write_file_direct(index,fp,c);





        }





        else if (strcmp(fs.fname,"null")==0)
            {
                char filee[20];
                strcpy(filee,get_filename(key[level],key[level+1],level+2));
                printf("\n 3) %s\n",filee);

                struct file_strc c;
                c.Alphabet=key[level+1];

                    c.flag=0;

                strcpy(c.fname,filee);


                write_file_direct(index,fp,c);

                index = CHAR_TO_INDEX(key[level+1]);

                create_file(filee);

                freopen(filee,"r+",fp);
                if(fp==0)
                {
                    printf("file not found \n");
                    break;
                }
                printf("\ncalling freopen\n");
            }

        freopen(fs.fname,"r+",fp);
         if(fp==0)
                {
                    printf("file not found \n");
                    break;
                }
    }
fclose(fp);
    // mark last node as leaf

}



// Returns true if key presents in trie, else false
bool search(const char *key)
{
    int level;
    int length = strlen(key);
    int index;
 FILE *fp;
 struct file_strc f;
 fp=fopen("root.txt","r");
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

       f= read_file_direct(index,fp);

       if(level==length-1){printf("substring is present");
         return f.flag;}
       else if (strcmp(f.fname,"null")==0)
            return false;

       freopen(f.fname,"r",fp);
    }

    return (f.flag);
}

// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][32] = {"god","go","g","godbc","godbcam"};
    char output[][32] = {"Not present in trie", "Present in trie"};


    // Construct trie
    int i;
   // for (i = 0; i < ARRAY_SIZE(keys); i++)
   printf("calling insert\n");
    insert( keys[0]);
      //create_file("root.txt");

      //read_file();
printf("finished insert\n");
//create_file("fgdg.txt");
//printf("%s",get_filename('a','b',2));
//printf("%s --- %s\n",keys[4] , output[search(root, "go")] );


getch();
}




