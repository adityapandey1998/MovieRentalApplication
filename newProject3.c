//Movie Rental System by Aditya, Abhishek and Akash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct user
{
  char name[20];
  int no_of_items;
  float total_price; 
}user;

typedef struct movie{
  int id;
  char name[50];
  char genre[20];
  int year;
  float rating;
  float price;
  struct movie *next;
}movie;


user billing_menu(user curr);
user load_user(char name[20],user curr);
user write_new_user(user curr);
float printList(movie *head);
void sortedInsert(movie** head_ref, movie** new_node);
void sortedYearInsert(movie** head_ref, movie** new_node);
void traverse_file(movie** head_ref);
void traverse_random(movie** head_ref);
void traverse_year(movie** head_ref);
void traverse_genre(movie** head_ref, char g[20]);
float printList(movie *head);

char movies[10][50]={0};
float price_of_movies[10]={0};
int selmovcount=0;

int main()
{
  srand((unsigned int)time(NULL));
	int selection;
  system("clear");
  printf("============================================================\n");
  printf("\n------------------------------------------------------------");
	printf("\n-------------------------- Hello ---------------------------\n---------- Welcome to The Movie Rental Application ---------\n");
  printf("------------- Made By: Aditya, Abhishek & Akash ------------");
  printf("\n------------------------------------------------------------");
  printf("\n\n--------------- Press Enter to Continue.... ----------------\n");
  printf("\n============================================================\n");
  getchar();

  do{
    system("clear");
    printf("=================== Movie Rental System ====================\n");
    printf("Choose Option: \n1. Old User\n2. New User\n3. Exit\n");
    char ch;
    ch=getchar();
    fpurge(stdin);
    while(ch!='1' && ch!='2' && ch!='3')
    {
      printf("Enter Valid Choice: \n");
      ch=getchar();
    }

    fpurge(stdin);
    fflush(stdout);


    switch(ch)
    {
      user current_user={0};
      current_user.no_of_items=0;
      case '1':
        {
          system("clear");
          printf("=================== Movie Rental System ====================\n");
          printf("Enter Name: ");
          char name[20];
          fgets(name,20,stdin);
          current_user=load_user(name,current_user);
          int check=current_user.no_of_items;
          if(check==-1)
          {
            printf("User Doesn't exist...\n");
            getchar();
            break;
          }
          current_user=billing_menu(current_user);
          break;
        }

      case '2':
        {
          system("clear");
          printf("=================== Movie Rental System ====================\n");
          printf("1. Continue as Guest\n2. Add User\n");
          char ch2;
          ch2=getchar();
          fpurge(stdin);
          while(ch2!='1' && ch2!='2')
          {
            printf("Enter Valid Choice: \n");
            ch2=getchar();
          }
          fpurge(stdin);
          if(ch2=='1')
          {
            strcpy(current_user.name,"Guest\n");
            current_user=billing_menu(current_user);
          }
          else if(ch2=='2')
          {
            system("clear");
            printf("=================== Movie Rental System ====================\n");
            printf("Enter Name: ");
            char uname[20];
            fgets(uname,20,stdin);
            fpurge(stdin);
            strcpy(current_user.name,uname);
            current_user=billing_menu(current_user);
            current_user=write_new_user(current_user);
          }
          break;
        }

        case '3':
        {
          system("clear");
          printf("=================== Movie Rental System ====================\n");
          printf("Are you sure you want to exit?\n1. Yes\n2. No\n");
          fpurge(stdin);
          char ch3=getchar();
          fpurge(stdin);
          while(ch3!='1' && ch3!='2')
          {
            printf("Enter Valid Choice: \n");
            ch3=getchar();
          }
          if(ch3=='1')
            return 0;
          else;
          break;
        }
    }
    system("clear");
    printf("=================== Movie Rental System ====================\n");
    printf("Press Enter to continue...\n");
    printf("============================================================\n");
    getchar();
	}
  while(1);
  return 0;
}


user load_user(char name[20],user curr)
{

  FILE *fp;
  fp=fopen("user_data.txt","r");
  while(!feof(fp))
  {
    fread(&curr, sizeof(struct user), 1, fp);
    if(strcmp(name,curr.name)==0)
    {
      return curr;
    }
  }
  curr.no_of_items=-1;
  fclose(fp);
  return curr;
}

user write_new_user(user curr)
{
  FILE *fp;
  fp=fopen("user_data.txt","a");
  fwrite(&curr, sizeof(struct user), 1, fp);
  fclose(fp);
  return curr;
}

void sortedInsert(movie** head_ref, movie** new_node)
{
  movie* current;
  if (*head_ref == NULL || (*head_ref)->rating <= (*new_node)->rating)
  {
    (*new_node)->next = *head_ref;
    *head_ref = *new_node;
  }
  else
  {
    current = *head_ref;
    while (current->next!=NULL && current->next->rating > (*new_node)->rating)
      current = current->next;

    (*new_node)->next = current->next;
    current->next = *new_node;
  }
}

void sortedYearInsert(movie** head_ref, movie** new_node)
{
  movie* current;
  if (*head_ref == NULL || (*head_ref)->year <= (*new_node)->year)
  {
    (*new_node)->next = *head_ref;
    *head_ref = *new_node;
  }
  else
  {
    current = *head_ref;
    while (current->next!=NULL && current->next->year > (*new_node)->year)
      current = current->next;

    (*new_node)->next = current->next;
    current->next = *new_node;
  }
}

void traverse_file(movie** head_ref)
{
  FILE *mfp=fopen("new_movie_data2.txt","r");
  char line[100];
  int count=0;
  while(!feof(mfp))
  {
    movie *new_node=(movie*)malloc(sizeof(movie));
    fscanf(mfp, "%d,%[^,],%[^,],%d,%f,%f\n", &(new_node->id),&(new_node->name),&(new_node->genre),&(new_node->year),&(new_node->rating),&(new_node->price));
    new_node->next=NULL;
    sortedInsert(head_ref,&new_node);
  }
  fclose(mfp);
}

void traverse_year(movie** head_ref)
{
  FILE *mfp=fopen("new_movie_data2.txt","r");
  char line[100];
  int count=0;
  while(!feof(mfp))
  {
    movie *new_node=(movie*)malloc(sizeof(movie));
    fscanf(mfp, "%d,%[^,],%[^,],%d,%f,%f\n", &(new_node->id),&(new_node->name),&(new_node->genre),&(new_node->year),&(new_node->rating),&(new_node->price));
    new_node->next=NULL;
    sortedYearInsert(head_ref,&new_node);
  }
  fclose(mfp);
}

void traverse_random(movie** head_ref)
{
  FILE *mfp=fopen("new_movie_data2.txt","r");
  char line[100];
  int count=0;
  int r = rand()%3+1;
  while(!feof(mfp))
  {
    count++;
    movie *new_node=(movie*)malloc(sizeof(movie));
    fscanf(mfp, "%d,%[^,],%[^,],%d,%f,%f\n", &(new_node->id),&(new_node->name),&(new_node->genre),&(new_node->year),&(new_node->rating),&(new_node->price));
    new_node->next=NULL;
    if(count%r==0)
      sortedInsert(head_ref,&new_node);
  }
  fclose(mfp);
}

void traverse_genre(movie** head_ref, char *g)
{
  FILE *mfp=fopen("new_movie_data2.txt","r");
  char line[100];
  int count=0;
  while(!feof(mfp))
  {
    movie *new_node=(movie*)malloc(sizeof(movie));
    fscanf(mfp, "%d,%[^,],%[^,],%d,%f,%f\n", &(new_node->id),&(new_node->name),&(new_node->genre),&(new_node->year),&(new_node->rating),&(new_node->price));
    new_node->next=NULL;
    if(strcmp(g,new_node->genre)==0)
      sortedInsert(head_ref,&new_node);
    else
      free(new_node);
  }
  fclose(mfp);
}


float printList(movie *head)
{
  
  float arr[5]={0};
  char name_movie[5][50]={0};
  float id[5]={0};
  int noofmovies=0;
  float price=0;
  movie *temp = head;
  if(temp==NULL)
  {
    system("clear");
    printf("=================== Movie Rental System ====================\n\n");
    printf("\nYou have reached the end of the list!\n\n");
    // int end=getchar()-'0';
    // while(end!=1 && end!=2)
    //   end=getchar()-'0';
    // fpurge(stdin);
    // if(end==1)
    //   printList(head);
    // else
    //   return price;
  }
  else
  {
    int i=0;
    system("clear");
    printf("=================== Movie Rental System ====================\n\n");
    while(temp != NULL)
    {
      printf("%d.%s - Cost:%.2f - Year:%d\n", i+1, temp->name, temp->price, temp->year);
      arr[i]=temp->price;
      strcpy(name_movie[i],temp->name);
      temp = temp->next;
      i++;
      if(i%5==0)break;
    }
    printf("\n===========================================================\n");
    printf("Choices: \n1. Select Movie No. 1 to 5\n6. View More Movies\n7. Done with this List\n(PLEASE NOTE DUPLICATE ITEMS WILL NOT BE ADDED AGAIN)\n\nEnter Choice: ");
    int selch=getchar()-'0';
    fpurge(stdin);
    while(selch>7 || selch<1)
    {
      printf("Enter Valid Choice: \n");
      selch=getchar()-'0';
    }
    fpurge(stdin);

    switch(selch)
    {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      {
        int flag =0;
        for(int z=0;z<selmovcount;z++)
        {
          if(strcmp(movies[z],name_movie[selch-1])==0)
            flag=1;
        }
        if(!flag)  
        {
          price+=arr[selch-1];
          price_of_movies[selmovcount]=arr[selch-1];
          strcpy(movies[selmovcount++],name_movie[selch-1]);
        }
        break;
      }
      case 6:
      {
        return printList(temp);
        break;
      }
      case 7:
      {
        //return price;
      }
    }
  }
  return price;
}

user billing_menu(user curr)
{
  int cchoice;
  float price = 0, xp=0;

  do
  {
  	system("clear");
    printf("=================== Movie Rental System ====================\n");
    printf("View Movies in order: \n1. Rating\n2. Genre\n3. Year Of Release\n4. I'm Feeling Lucky\n");
    char moviech=getchar();
    fpurge(stdin);
    while(moviech!='1' && moviech!='2' && moviech!='3' && moviech!='4')
    {
      printf("Enter Valid Choice: \n");
      moviech=getchar();
    }
    fpurge(stdin);

    switch(moviech)
    {
      case '1':
      {
        movie *head_ref=NULL;
        traverse_file(&head_ref);
        price+=printList(head_ref);
        break;
      }

      case '2':
      {
      	system("clear");
        printf("=================== Movie Rental System ====================\n");
      	printf("Select Genre: \n1. Comedy\n2. Action\n3. Adventure\n4. Drama\n5. Biographies\n");
      	char gch=getchar();
        fpurge(stdin);
    		while(gch!='1' && gch!='2' && gch!='3' && gch!='4' && gch!='5')
        {
          printf("Enter Valid Choice: \n");
      		gch=getchar();
        }
    		fpurge(stdin);
    		//movie *head_ref=NULL;
  			if(gch=='1')
  			{
  				char g[20]=" Comedy";
          movie *head_ref=NULL;
  				traverse_genre(&head_ref,g);
  				price+=printList(head_ref);
  				break;
  			}
        else if(gch=='2')
  			{
  				char g[20]=" Action";
          movie *head_ref=NULL;
  				traverse_genre(&head_ref,g);
  				price+=printList(head_ref);
  				break;
  			}
        else if(gch=='3')
  			{
  				char g[20]=" Adventure";
          movie *head_ref=NULL;
  				traverse_genre(&head_ref,g);
  				price+=printList(head_ref);
  				break;
  			}
        else if(gch=='4')
  			{
  				char g[20]=" Drama";
          movie *head_ref=NULL;
  				traverse_genre(&head_ref,g);
  				price+=printList(head_ref);
  				break;
  			}
        else if(gch=='5')
  			{
  				char g[20]=" Biography";
          movie *head_ref=NULL;
  				traverse_genre(&head_ref,g);
  				price+=printList(head_ref);
  				break;
  			}
        break;
      }

      case '3':
      {
        movie *head_ref=NULL;
        traverse_year(&head_ref);
        price+=printList(head_ref);
        break;
      }

      case '4':
      {
        movie *head_ref=NULL;
        traverse_random(&head_ref);
        price+=printList(head_ref);
        break;
      }
    }
    printf("\n===========================================================\n");
    printf("\nDo you want to browse for more movies?\n1. Yes\n2. No\n");
    cchoice=getchar()-'0';
    fpurge(stdin);
    while(cchoice!=1 && cchoice!=2)
    {
      printf("Enter Valid Choice: \n");
      cchoice=getchar()-'0';
    }
    fpurge(stdin);
    if(selmovcount==10)
    {
      printf("\nMax Cart Limit (10 items) Reached!!!");
      cchoice=0;
    }
  }
  while(cchoice==1);
  char remch;
  do
  {
    system("clear");
    printf("=================== Movie Rental System ====================\n");
    printf("You have selected: ");
    for(int x=0;x<selmovcount;x++)
    {
      printf("\n%d.%s",x+1,movies[x]);
      xp+=price_of_movies[x];
    }
    if(selmovcount==0)
    {
      printf("No Movies :(\n");
      break;
    }
    printf("\n===========================================================\n");
    printf("\nDo you want to REMOVE any of the movies?\n1. Yes - I want to edit cart\n2. No - I am confirming the choices\n");
    remch=getchar();
    fpurge(stdin);
    while(remch!='1' && remch!='2')
    {
      printf("Enter Valid Choice: \n");
      remch=getchar();
    }
    fpurge(stdin);
    if(selmovcount==0)
      {
        printf("\nCart is Empty\n");
        price=0;
      }

    if(remch=='1')
    {
      if(selmovcount==0)
      {
        //printf("Emptied Cart");
        price=0;
      }
      else
      {
        printf("Enter movie no. to remove: ");
        int mrch=getchar()-'0';
        fpurge(stdin);
        while(mrch>selmovcount || mrch<1)
        {
          printf("Enter Valid Choice: \n");
          mrch=getchar()-'0';
        }
        selmovcount--;
        for(int a=mrch-1; a<selmovcount;a++)
        {
          strcpy(movies[a],movies[a+1]);
        }
        price-=price_of_movies[mrch-1];
      }

    }
  }
  while(remch=='1');
  system("clear");
  printf("=================== Movie Rental System ====================\n\n");
  printf("========================= Your Bill ========================");

  printf("\nHi %s",curr.name);
  printf("\nYour Selected Movies are: ");
  if(selmovcount==0)
  {
    printf(" No Movies Selected :(\n");
    price=0;
  }
  for(int x=0;x<selmovcount;x++)
      printf("\n%d.%s",x+1,movies[x]);
  printf("\n\nYour total billing amount is: %.2f\n",price);
  printf("\n===========================================================\n");

  selmovcount=0;
  for(int k=0;k<10;k++)
  {
    strcpy(movies[k],"");
    price_of_movies[k]=0;
  }
  getchar();
  return curr;
}
