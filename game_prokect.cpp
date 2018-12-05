#include <fstream.h>
#include <iomanip.h>
#include <conio.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

const char b=(char)254;
const int width = 78;
const int height = 23;
int y=2;
int x=1;

class player
{
public:
	char name[100];
	int score;

	player()
	{
		score=0;
	}

	void get_name()
	{
		cout<<"Enter your name"<<endl;
		gets(name);
	}

	void plusscore()
	{
		score++;
	}

	void print_score()
	{
		cout<<x++<<") ";
		cout<<setiosflags(ios::left)<<setw(10)<<name<<setw(10)<<score<<endl;
	}
};

player one;

int map()
{
	int i, j;

	cout << "#";
	for (i = 1; i < width; i++)
		cout << "#";
	cout << "#" << endl;
	for (i = 1; i < height; i++)
	{
		cout << "#";
		for (j = 1; j < width; j++)
				cout << " ";
		cout << "#" << endl;
	}
	cout << "#";
	for (i = 1; i < width; i++)
		cout << "#";
	cout << "#" << endl;
	return 0;
}

void wait(long double d)
{
	clock_t start = clock();
	while(clock()-start<d);
}

int plane(int y)
{
	gotoxy(1, y);
	cout << "#" << b << endl;
	cout << "# "<< b << endl <<"#"<< b << b << b
		  << endl <<"# " << b << endl <<"#"<< b << endl;
	return 0;
}


void writescore()
{
	player two;
	ifstream fin("HIGH SCORE.DAT",ios::in|ios::binary);
	ofstream fout("HIGH SCORES.DAT",ios::out|ios::binary|ios::ate);
	while(1)
	{
		fin.read((char*)&two,sizeof(two));
		if(fin.eof())
			break;
		if(strcmp(two.name,one.name)==0)
		fout.seekp(fin.tellg()-sizeof(one),ios::beg);
	}
	fout.write((char*)&one,sizeof(one));
	fout.close();
	fin.close();
}

void game()
{
	one.get_name();
	randomize();
	char ch;
	int i=width-2,k=i,l=k,j=5,n=::y,random1=random(18)+4,random2=random(18)+4;
	int random3=random(18)+4,r=i*10,t=r,s=t,secondcall=0,thirdcall=0,points=0;
	cout<<"PRESS W TO MOVE UP AND S TO MOVE DOWN. PRESS X TO EXIT TO MAIN";
	getch();
	clrscr();
	map();
	plane(y);

	while(1)
	{
		if(kbhit())
		{
			ch=getch();
			switch(ch)
			{
			case 'w':
				if(::y==2)
					break;
				else
				{
					::y--;
					gotoxy(2,::y+1);
					cout<<"   \n#   \n#   \n#   \n#    \n";
					plane(::y);
					break;
				}
			case 's':
			if(::y==height-4)
				break;
			else
			{
				::y++;
				gotoxy(2,::y-1);
				cout<<"   \n#   \n#   \n#   \n#    \n";
				plane(::y);
				break;
			}

			case 'x':
				writescore();
				clrscr();
				return;
				break;
			}
		}
		gotoxy(width-1,height+1);
		cout<<points;
		gotoxy(j,n+2);    //bLASTER
		if(j==width-1)
		cout<<"  ";
		else
		cout<< " -";
		j++;
		wait(1);


		if(r%10==0)                 //ASTEROID   1
		{
			gotoxy(i,random1);
			cout<<(char)254<<"  ";
			i--;
			if(i<width*11/12)
			secondcall=1;
		}
		r--;

		if(t%10==0 && secondcall)                 //ASTEROID  2
		{
			gotoxy(k,random2);
			cout<<(char)254<<"  ";
			k--;
			if(k<width*11/12)
			thirdcall=1;
		}
		t--;

		if(s%10==0 && thirdcall)                 //ASTEROID  3
		{
			gotoxy(l,random3);
			cout<<(char)254<<"  ";
			l--;
		}
			s--;
		gotoxy(width,2);
		cout<<one.score;

		if(j==i&&n+2==random1)
		{
			one.plusscore();
			cout<<" ";
			random1=random(height-5)+4;
			i=width-2;
			r=i*8;
		}

		if(j==k&&n+2==random2)
		{
			one.plusscore();
			cout<<" ";
			random2=random(height-5)+4;
			k=width-2;
			t=k*8;
		}

		if(j==l&&n+2==random3)
		{
			one.plusscore();
			cout<<" ";
			random3=random(height-5)+4;
			l=width-2;
			s=k*8;
		}

		if(j==width)                //balst_terminate
		{
			cout<<"#";
			j=5;
			n=::y;
		}

		if(i==4||k==4||l==4)                    // ATEROID _ TREMINATE
		{
			clrscr();
			cout<<"GAME OVER"<<endl;
			writescore();
			break;
		}
	}
}

void main()
{
	char ch;
	player two;
	x=1;
	while(1)
	{
		ifstream fin("HIGH SCORES.DAT",ios::in|ios::binary);
		if(fin)
		{
			cout<<"High Scores are:"<<endl;
			cout << setiosflags(ios::left) << setw(10) << "   NAME"
			     << setw(10) << "score" << endl;
			while(1)
			{
				fin.read((char*)&two,sizeof(two));
				if(fin.eof())
					break;
				two.print_score();
			}
		}
	fin.close();
	cout<<endl<<"Press w to play and s to exit:"<<endl;
	ch=getch();
	if(ch=='w'||ch=='W')
		game();
	else
		if(ch=='s'||ch=='S')
			exit(1);
		else
			cout<<"wrong output"<<endl;
		x=1;
	}
}



