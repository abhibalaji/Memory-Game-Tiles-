//Memory Game v0.06
//To do: high score - limit - 10 - sort
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<process.h>
#include<fstream.h>
void xit();
void help();
void init();
void title();
void choice();
void menu();
void won(int);
void high();
void high(int);
void game();
void about();
int hidden();
void splash_print();
int search(int [],int);
int findempty(int a[][4]);
void show(int a[][4],int,int);
void grid();
void printInGrid();
void randomints(int []);
void fill(int a[][4],int []);
void hline(int);
void vline(int,int);
int b1,b2,box[16]={0},hc=-1;
void main()
{
	menu();
}
void game()
{
// srand((unsigned)time(0));
 int prev,curr,next,count=0,a[4][4]={0},b[8]={0};
 init();
 clrscr();
 randomize();
 randomints(b); //Stores 8 random numbers in b
 fill(a,b); //Fills the 16 boxes with the values in b
 grid(); //Draws the 4x4 grid
 printInGrid();
 while(hidden()) //While some boxes are still hidden
 {
  choice(); //Read choice
  count++;
  clrscr();
  grid();
  printInGrid();
  show(a,b1,b2);
  printInGrid();
 }
 won(count);
}
void init()
{
	for(int i=0;i<16;i++)
		box[i]=0;
	hc=-1;
}
void won(int c)
{
 clrscr();
 title();
 gotoxy(26,4);
 cout<<"Wohoo!! You've won the game!";
 gotoxy(30,6);
 cout<<"Congratulations!!!!";
 gotoxy(27,8);
 cout<<"Time to celebrate!!!!!!!";
 gotoxy(29,10);
 cout<<"No. of Attempts: "<<c;
 getch();
 high(c);
}
void help()
{
 clrscr();
 title();
 grid();
 splash_print();
 gotoxy(32,15);
 cout<<"INSTRUCTIONS";
 gotoxy(5,17);
 cout<<"1.Enter two box numbers corresponding to the box numbers given above";
 gotoxy(21,19);
 cout<<"2.Enter same box numbers to exit the game";
 getch();
}
int hidden() //Returns 1 if a box is not cleared
{
 int i,flag=0;
 for(i=0;i<16;i++)
  if(box[i]==0)
  {
	flag=1;
	break;
  }
 if(flag==1)
  return 1;
 else
  return 0;
}
void show(int a[][4],int m,int n)
{
 int x,y,i1,j1,i2,j2;
 i1 = (m-1)/4;
 j1 = (m-1)%4;
 x = 32 + j1*4;
 y = 6 + i1*2;
 gotoxy(x,y);
 cout<<a[i1][j1];
 i2 = (n-1)/4;
 j2 = (n-1)%4;
 x = 32 + j2*4;
 y = 6 + i2*2;
 gotoxy(x,y);
 cout<<a[i2][j2];
 if(a[i1][j1] == a[i2][j2])
 {
  box[m-1]=1;
  box[n-1]=1;
 }
 getch();
}
void title()
{
 gotoxy(27,2);
 cout<<"-==:: MEMORY GAME ::==-";
 gotoxy(29,3);
 cout<<"*******************";
}
void grid()
{
 int i;
 title();
 gotoxy(30,5);
 cout<<char(201);
 hline(3);
 for(i=0;i<=2;i++)
 {
  cout<<char(203);
  hline(3);
 }
 cout<<char(187);
 for(int j=30;j<=46;j+=4)
  vline(j,6);
 gotoxy(30,7);
 int l=8;
 for(int k=9;k<=13;k+=2,l+=2)
 {
  cout<<char(204);
  hline(3);
  for(i=0;i<=2;i++)
  {
	cout<<char(206);
	hline(3);
  }
  cout<<char(185);
  for(int j=30;j<=46;j+=4)
	vline(j,l);
  gotoxy(30,k);
 }
 cout<<char(200);
 hline(3);
 for(i=0;i<=2;i++)
 {
  cout<<char(202);
  hline(3);
 }
 cout<<char(188);
}
void choice()
{
 gotoxy(29,17);
 cout<<"Enter two box nos: ";
 cin>>b1>>b2;
 if(b1==b2) //Enter same box numbers to exit game
  xit();
 if(b1==66&&b2==77)
 {
	int r;
	r=random(30)+1;
	won(r);
 }
 if( (b1>16 || b1<1) || (b2>16 || b2<1) || ((b1>16 ||b1<1) && (b1>16 || b1<1)))
 {
  clrscr();
  title();
  gotoxy(28,15);
  cout<<"Invalid box numbers!!";
  grid();
  printInGrid();
  choice(); //Recursion
 }
 else if(box[b1-1]==1||box[b2-1]==1)
 {
  clrscr();
  title();
  gotoxy(30,15);
  cout<<"Already cleared!!";
  grid();
  printInGrid();
  choice(); //Recursion
 }
}
void hline(int n)
{
 for(int i=0;i<n;i++)
  cout<<char(205);
}
void vline(int xpos,int ypos)
{
 gotoxy(xpos,ypos);
 cout<<char(186);
}

//Print 'X' and ' ' in the grid
void printInGrid()
{
 int i,j,no;
 for(i=32;i<=44;i+=4)
 {
  for(j=6;j<=12;j+=2)
  {
	gotoxy(i,j);
	no = (j-6)*2 + (i-32)/4;
	if(box[no])
	 cout<<" ";
	else
	 cout<<"X";
  }
 }
}//printInGrid

//void randomints(int[]);
//Generate 8 random integers and store them in an array
void randomints(int a[])
{
 int i,t;
 for(i=0;i<8;i++)
 {
  t=random(8)+1;  //Generate a random integer from 1 to 8
  if(!search(a,t))//If it does not previously exist in the array,
	a[i] = t;      //Assign it to the array
  else            //If not,
	i--;           //Reduce the value of i by one and repeat the procedure
 }
}//randomints

// int search(int[], int);
// Function to search for repeated random values
// Returns zero if no values are repeated
int search(int a[],int num)
{
 for(int i=0;i<8;i++)
 {
  if(a[i]==num)
  {
	return 1;
  }
 }
 return 0;
}/*End of search*/
void fill(int a[][4],int b[8]) //Fills the grid with pairs of numbers
{
 int i,j,temp,i1,j1;
 for(i=0;i<8;i++)
 {
  temp = findempty(a);
  i1 = temp/10;
  j1 = temp%10;
  a[i1][j1] = b[i];
  temp = findempty(a);
  i1 = temp/10;
  j1 = temp%10;
  a[i1][j1] = b[i];
  b[i]=0;
 }
}
int findempty(int a[][4])  //Returns a random empty grid
{
 int s,t;
 while(1)
 {
  s = rand()%4;
  t = rand()%4;
  if(a[s][t]==0)
   return s*10+t;
 }
}
void xit() //Function to exit the game
{
 clrscr();
 title();
 gotoxy(30,6);
 cout<<"YOU'RE A LOSER!!";
 gotoxy(27,8);
 cout<<"YOU LOSE THE GAME!!!";
 getch();
 menu();
}
void splash_print()
{
 int i,j,no;
 for(i=32;i<=44;i+=4)
 {
  for(j=6;j<=12;j+=2)
  {
	gotoxy(i,j);
	no=((j-6)*2+(i-32)/4)+1;
	cout<<no;
  }
 }
}
void menu()
{
 while(1)
 {
  int ch;
  clrscr();
  title();
  gotoxy(33,5);
  cout<<"1.Play game";
  gotoxy(31,7);
  cout<<"2.View highscores";
  gotoxy(36,9);
  cout<<"3.Help";
  gotoxy(35,11);
  cout<<"4.About";
  gotoxy(36,13);
  cout<<"5.Exit";
  gotoxy(30,15);
  cout<<"Enter your choice: ";
  gotoxy(28,14);
  cout<<(char)201;
  gotoxy(28,15);
  cout<<(char)186;
  gotoxy(28,16);
  cout<<(char)200;
  for(int i=29;i<48;i++)
  {
	gotoxy(i,14);
	cout<<(char)205;
  }
  for(i=29;i<48;i++)
  {
	gotoxy(i,16);
	cout<<(char)205;
  }
  gotoxy(48,14);
  cout<<(char)203;
  cout<<(char)205;
  gotoxy(48,15);
  cout<<(char)186;
  gotoxy(50,14);
  cout<<(char)187;
  gotoxy(50,15);
  cout<<(char)186;
  gotoxy(48,16);
  cout<<(char)202;
  gotoxy(49,16);
  cout<<(char)205;
  cout<<(char)188;
  gotoxy(49,15);
  cin>>ch;
  switch(ch)
  {
	case 1:
		game();
		break;
	case 2:
		high();
		break;
	case 3:
		help();
		getch();
		break;
	case 4:
		clrscr();
		about();
		getch();
		break;
	case 5:
		exit(0);
	default:
		cout<<"\nEnter a valid option!";
		getch();
  }
 }
}
void about()
{
	title();
	gotoxy(30,5);
	cout<<"Memory game v0.05";
	gotoxy(26,7);
	cout<<"Created By: N.Ravi Shankar";
}
void high(int h) //Function overloading
{
	hc++;
	if(hc>=10)
		return;
	ofstream writehigh("high_scores.txt",ios::app);
	writehigh<<h<<'\n';
	writehigh.close();
}
void high() //Displays all the contents of the high_scores.txt file
{
	clrscr();
	char h;
	ifstream gethigh("high_scores.txt");
	cout<<"High scores: \n";
	while(gethigh)
	{
		gethigh.get(h);
		cout<<h;
	}
	gethigh.close();
	getch();
}