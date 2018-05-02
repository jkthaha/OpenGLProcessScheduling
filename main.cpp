#include<iostream>
#include<GL/glut.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

using namespace std;

struct process
{
    int bt,at,st,ct,no;
    char name;
};

struct p{
    int no,bt,at,rbt,st,ct;
};

void disp();
void displayOptions();

//Global decalarations
int front=-1,rear=-1,n,pt=0,total=0,wid,q[30],wt=0,tt=0,tb,one=1,np=1,att,index1,btt,btotal=0,keypa=0,same[50],tq=99,co=0;
struct p process[25];
struct process p[15];
float basic=36.0,col[5][3]={{.94,.90,.55},{.48,.0,.93},{.5,1.0,0.0},{1,.84,.0},{1,.6,.2}};
bool doneInput=false;
char line1[] = {"HKBK College Of Engineering"};
char line2[] = {"Computer Science Department"};
char line3[] = {"   Computer Graphics project"};
char line4[] = {"Topic: Process Scheduling Algorithm"};
char line5[] = {"Mohammed Thaha JK	 : 1HK15CS060"};
char line6[] = {"Rahil Ahmed : 1HK15CS075"};
char line7[] = {"(Press 1 to enter the main page)"};
char op[] = {"Options:"};
char op1[] = {"1. First Come First Serve (FCFS)"};
char op2[] = {"2. Round Robin (RR)"};
char op3[] = {"3. Shortest Job First (SJF)"};
char op4[] = {"4. Re-enter the data"};
char op5[] = {"5. Exit :("};
//End of global declarations

void displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen (string);
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    glFlush();
}

void displayName(char *lines)
{
  displayText(500, 450, 1, 1, 1,lines);
}

void displayfirst(void){
    displayText(470, 450, 0, 0, 1,line1);
    displayText(470, 400, 0, 0, 0,line2);
    displayText(470, 350, 0, 0, 0,line3);
    displayText(80, 150, 1, 0, 0,line4);
    displayText(80, 100,0, 0, 0,line5);
    displayText(80, 50, 0, 0, 0,line6);
    displayText(850,20,0,1,0,line7);
}

void restart()
{
    front=-1,rear=-1,pt=0,total=0;
    co=0;tb=0;
    one=1,np=1;btotal=0;keypa=1;
}

void add(int c) //Insert element c into the queue
{
    if(front==-1)
        front=0;
    q[++rear]=c;
}

int rem() //Remove element and return it from the queue
{
    if(rear<front)
    {
        front=rear=-1;
        return -1;
    }
    else
        return q[front++];
}

void insert(int pos,int c) //Insert element c into the queue at a given position
{
    int dr;
    dr=rear;
    int i;
    for(i=dr;i>=pos;i--)
    {
        q[i+1]=q[i];
    }
    q[pos]=c;
    rear++;
}

void printq() //Print the queue
{
    int i;
    if(front!=-1 && front<=rear)
        for(i=front;i<=rear;i++)
        {
            printf("%d \t",q[i] );
        }
    else printf("Queue empty\n");
    printf("\n" );
}

void sort1() //Sort the queue according to their arrival time
{
    int i,j,temp;
    for(i=0;i<n;i++)
        add(i);
    printf("before sorting\n");
    printq();
    printf("after sorting\n");
    for(i=0;i<n;i++)
        for(j=0;j<n-1;j++)
        {
            if(process[q[j]].at>process[q[j+1]].at)
            {
                temp=q[j];
                q[j]=q[j+1];
                q[j+1]=temp;
            }
        }
    printq();
    pt = total = process[q[front]].at;
}

void display(int pno1) //Display Gantt chart on terminal
{
    wt=wt+total;
    printf("-%d |%d| %d- \n",pt,pno1,total);
    p[co].ct=pt;
    p[co].st=total;
    co++;
}


void checkForArrivals(int cp) //Check if new processes have arrived up until the current total
{
    int ofront=front,orear=rear;
    while(ofront<=orear)
    {
        if(process[q[ofront]].at<=total)
        {
            ofront++;
        }
        else{
            insert(ofront, cp);
            return;
        }
    }
    add(cp);
}
//Round robin ends
/*
break
*/

void delay()
{
    for(int i=0;i<35000;i++)
        for(int j=0;j<5000;j++);
}

void delay2()
{
    for(int i=0;i<35000;i++)
        for(int j=0;j<10000;j++);
}

void init()
{
    glClearColor(1,1,1,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0,1200,0,500);
    for(int i=0;i<=7;i++)
        same[i]=1;
}//Initialiasation

//Prints the characters on screen at x,y
void strin(char *p,int n,GLint x,GLint y)
{
    glRasterPos2f(x,y);
    for(int i=0;i<n;i++)
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15 , p[i] );
}
//same as above with different font
void stri(char *p,int n,GLint x,GLint y)
{
    glColor3f(1,0.9,0);
    glRasterPos2f(x,y);
    for(int i=0;i<n;i++)
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , p[i] );
}

void constr() // To show the constraints
{
    int p=15,q=200;
    glColor3f(1,.0,.0);
    strin("Please note:",12,p,q);
    strin("___________",12,p,q-4);
    strin("-> The number of processes is limited to 5.",43,p,q-(30*1));
    strin("-> All processes must arrive before 7sec.",41,p,q-(30*2));
    strin("-> Total burst time of all the processes must not exceed 30.",60,p,q-(30*3));
    glColor3f(.0,1.0,0.0);
    strin("PRESS E or e TO RUN PROGRAM FOR STATIC INPUT",44,15,320);
//  strin("PRESS R or r TO RESET THE PROGRAM",33,15,300);
    glColor3f(0.5,0.87,.803);
    strin("Made by Thaha & Rahil",21,5,20);
    glColor3f(0,0,0);
}

//to ask for number of process
void backgrnp()
{
    stri("Enter the number of processes:",30,15,375);
    constr();
    glFlush();
}

//similar as above
void backgrat()
{
    stri("Enter the arrival time of processes: ",37,15,375);
    constr();
    glFlush();
}//background for getting arrival time

//to get the burst time
void backgrbt()
{
    stri("Enter the burst time of processes: ",35,15,375);
    constr();
    glFlush();
}//background for getting brust time


//Request the time quantumg
void backgrtq()
{
    glColor3f(0,0,0);
    stri("Enter the time quantum: ",24,15,375);
    constr();
    glFlush();
}


//Prints arrival time and burst time in the table
void pro()
{
    int j;
    char a;
    for( j=0;j<n;j++)
    {
        a='0'+p[j].at;
        strin(&a,1,183,378-(25*(j+2)));
        a='0'+p[j].bt;
        strin(&a,1,295,378-(25*(j+2)));
    }
}

//draws rectangle for gantt chart
void drawrec(int pa,int qa,int ra, int sa)
{
    int ya=qa,width=pa-ra,height= sa-qa;
    int count,delay=300;
    for(count=ra;count<=ra+width;count++)
    {
        glBegin(GL_LINES);
        glVertex2i(count,ya);
        glVertex2i(count, ya+height);
        glEnd();
        glFlush();
        usleep(delay);
        delay=delay+50;
    }
}

//draws a black rectangle exterior to the above rectangle
void drawloop(int p,int q,int r, int s)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(p,q);
    glVertex2f(p,s);
    glVertex2f(r,s);
    glVertex2f(r,q);
    glEnd();
}

//
void setValuesRR()
{
    int cp;
    sort1(); //Sort the processes according to their arrival time in increasing order
    while(front<=rear)
    {
        cp=rem();
        if(cp!=-1)
        {
            if(process[cp].rbt<=tq && process[cp].rbt>0)
            {
                pt=total;
                total = total + process[cp].rbt;
                process[cp].rbt=0;
                process[cp].ct=pt;
                process[cp].st=total;
                display(cp);
            }
            else if(process[cp].rbt>tq)
            {
                pt=total;
                total=total + tq;
                process[cp].rbt = process[cp].rbt - tq;
                display(cp);
                checkForArrivals(cp);
            }
        }
    }
}

//To draw the scale
void drawscale()
{
    int i,j;
    char a;
    glLineWidth(2.0);
    glColor3f(1,1,1.0);
    glBegin(GL_LINES);
    glVertex2i(30,145);
    glVertex2i(1111,145);
    for(i=1;i<=30;i++)
    {
        glVertex2f(30+basic*i,145);
        glVertex2f(30+basic*i,141);
    }
    glEnd();
    for(i=0;i<=30;i++)
    {
        if(i<10)
        {
            a='0'+i;
            strin(&a,1,27+basic*i,147);
        }
        else if(i>9 && i<20)
        {
            j=1;
            a='0'+j;
            strin(&a,1,24+basic*i,147);
            a='0'+(i%10);
            strin(&a,1,32+basic*i,147);
        }
        else if(i==30)
        {
            j=3;
            a='0'+j;
            strin(&a,1,27+basic*i,147);
            a='0'+(i%10);
            strin(&a,1,32+basic*i,147);
        }
        else
        {
            j=2;
            a='0'+j;
            strin(&a,1,27+basic*i,147);
            a='0'+(i%10);
            strin(&a,1,32+basic*i,147);
        }
    }
    glFlush();
}

//print arrival time on top
void arri(int po)
{
    for(int i=0;i<n;i++)
    {
        if(p[i].at<=p[po].ct)
        {
            glColor3fv(col[i]);
            strin("P",1,30+36*p[i].at-8,173);
            strin(&p[i].name,1,30+36*p[i].at,173);
            glBegin(GL_LINES);
            glVertex2i(30+36*p[i].at,170);
            glVertex2i(30+36*p[i].at,160);
            glVertex2i(30+36*p[i].at+2,163);
            glVertex2i(30+36*p[i].at,160);
            glVertex2i(30+36*p[i].at-2,163);
            glVertex2i(30+36*p[i].at,160);
            glEnd();
        }
    }
    glFlush();
    glColor3f(0.0,0.87,.803);
}

//Print the number with decimals
void prinum(int x,int y,float num)
{
    int r=(int)num,q=(((int)(num*10))%10),p=(((int)(num*100))%10);
    char a;
    if(r>9)
    {
        a='0'+(r/10);
        strin(&a,1,x,y);
        a='0'+(r%10);
        strin(&a,1,x+8,y);
        strin(".",1,x+16,y);
        a='0'+q;
        strin(&a,1,x+24,y);
        a='0'+p;
        strin(&a,1,x+32,y);
        strin(" ms",3,x+40,y);
        glFlush();
        return;
    }
    a='0'+r;
    strin(&a,1,x,y);
    strin(".",1,x+8,y);
    a='0'+q;
    strin(&a,1,x+16,y);
    a='0'+p;
    strin(&a,1,x+24,y);
    glFlush();
}

//Print average wait time and turn around time
void avg()
{
   int turnAroundTime[20],WaitingTime[20],tTurnAroundTime=0,tWaitingTime=0;

   for(int i=0;i<n;i++)
   {
       turnAroundTime[i] = p[i].st-p[i].at;
       WaitingTime[i] = turnAroundTime[i] - p[i].bt;
       tTurnAroundTime = tTurnAroundTime + turnAroundTime[i];
       tWaitingTime = tWaitingTime + WaitingTime[i];
   }
   float tWait = tWaitingTime/(float)n;
   float tTurn = tTurnAroundTime/(float)n;
   printf("awt = %f att = %f\n",tWait,tTurn);

   strin("Average Waiting Time = ",23,30,70);
   strin("Total Turn around Time = ",25,30,45);
   prinum(250,70,tWait);
   prinum(255,45,tTurn);
}

//calculate average turn around and waiting time for round robin
void avgRR()
{
    int turnAroundTime[20],WaitingTime[20],tTurnAroundTime=0,tWaitingTime=0;

    for(int i=0;i<n;i++)
    {
        turnAroundTime[i] = process[i].st-process[i].at;
        WaitingTime[i] = turnAroundTime[i] - process[i].bt;
        tTurnAroundTime = tTurnAroundTime + turnAroundTime[i];
        tWaitingTime = tWaitingTime + WaitingTime[i];
    }
    float tWait = tWaitingTime/(float)n;
    float tTurn = tTurnAroundTime/(float)n;
    printf("awt = %f att = %f\n",tWait,tTurn);

    strin("Average Waiting Time = ",23,30,70);
    strin("Total Turn around Time = ",25,30,45);
    prinum(250,70,tWait);
    prinum(255,45,tTurn);
}

//display gantt chart
void gchart()
{
    int i;
    char a;
    float me;
    // setcst();
    drawscale();
   // basic=34;
    strin("Gantt Chart",11,30,158+40);
    strin("___________",11,30,156+40);
    for(i=0;i<=rear;i++)
    {
        glColor3fv(col[q[i]]);
        drawrec(30+p[i].st*36,100,30+p[i].ct*36,130);
        glLineWidth(2.0);
        glColor3f(0.0,0,0);
        drawloop(30+p[i].st*36,100,30+p[i].ct*36,130);
        glColor3fv(col[q[i]]);
        me=(30+p[i].st*36+30+p[i].ct*36)/2;
        strin("P",1,me-8,88);
        a='0'+q[i];
        strin(&a,1,me,88);
        arri(i);
        glFlush();
        delay2();
    }
    glLineWidth(1.0);
    glColor3f(1,.84,.0);
}

//To make the table
void table()
{
    int p,q,r,s,i;
    char a;
    keypa=0;
    glColor3f(1,1,1);
    p=30;
    q=375-(25*(1+n));
    s=375;
    r=330;
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(p,q);
    glVertex2i(p,s);
    glVertex2i(r+30,s);
    glVertex2i(r+30,q);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(130,s);
    glVertex2i(130,q);
    glVertex2i(233+13,s);
    glVertex2i(233+13,q);
    glVertex2i(p,350);
    glVertex2i(r+30,350);
    glEnd();
    strin("Process",7,55,355);
    strin("Arrival time",12,135,355);
    strin("Burst time",10,253,355);
    for( i=1;i<=n;i++)
    {
        strin("P",1,75,378-(25*(i+1)));
        a='0'+i-1;
        strin(&a,1,83,378-(25*(i+1)));
    }
    pro();
    glFlush();
    glLineWidth(1.0);
    glColor3f(0.0,0.87,.803);
}

//static example
void example()
{
    p[0].at=process[0].at=4;
    p[1].at=process[1].at=2;
    p[2].at=process[2].at=0;
    p[3].at=process[3].at=1;
    p[4].at=process[4].at=3;
    p[0].bt=process[0].rbt=process[0].bt=3;
    p[1].bt=process[1].rbt=process[1].bt=5;
    p[2].bt=process[2].rbt=process[2].bt=4;
    p[3].bt=process[3].rbt=process[3].bt=1;
    p[4].bt=process[4].rbt=process[4].bt=5;
    n=5;
    int i;
    for(i=0;i<n;i++)
    {
        p[i].name='0'+char(i);
    }
    tq=2;
    glClear(GL_COLOR_BUFFER_BIT);
    displayOptions();
}

//reshape func
void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    glClear (GL_COLOR_BUFFER_BIT);
    restart();
    keypa=0;
}

//displays options
void displayOptions()
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayText(600, 200, 1, 1, 1,op5);
    displayText(600, 230, 1, 1, 1,op4);
    displayText(600, 260, 1, 1, 1,op3);
    displayText(600, 290, 1, 1, 1,op2);
    displayText(600, 320, 1, 1, 1,op1);
    displayText(600, 350, 1, 0, 0,op);
    table();
    char s=tq+'0';
    displayText(110,200,1,1,1,"set of processes");
    displayText(110,201,1,1,1,"____________");
    displayText(310+60,290,1,1,0,"Time Quantum = ");
    displayText(490+60,290,1,1,0,&s);
}

void setValues()
{
    int i;
    char a;
    float me;
    int cp;
    sort1();
    int iof=0;
    while(front<=rear)
    {

        cp=rem();
        if(cp!=-1)
        {
            if(process[cp].rbt>0)
            {
                pt=total;
                total = total + process[cp].rbt;
                process[cp].rbt=0;
                printf("-%d |%d| %d- \n",pt,cp,total);
                p[iof].ct=pt;
                p[iof].st=total;
                p[iof].no=cp;
                iof++;
            }
        }
    }
    // setcst();
    drawscale();
    //basic=34;
    strin("Gantt Chart",11,30,158+40);
    strin("___________",11,30,156+40);
    for(i=0;i<n;i++)
    {
        glColor3fv(col[q[i]]);
        drawrec(30+p[i].st*36,100,30+p[i].ct*36,130);
        glLineWidth(2.0);
        glColor3f(0.0,0,0);
        drawloop(30+p[i].st*36,100,30+p[i].ct*36,130);
        glColor3fv(col[q[i]]);
        me=(30+p[i].st*36+30+p[i].ct*36)/2;
        strin("P",1,me-8,88);
        a='0'+p[i].no;
        strin(&a,1,me,88);
        arri(i);
        glFlush();
        delay2();
    }
    glLineWidth(1.0);
    glColor3f(1,.84,.0);
}

//set start time and completion time accordingly for sjf
void setValuesForSJF()
{
    int i,j,qb[10],temp,index=0,cp;
    bool flag=true,visited[6];
    float me;
    char a;
    int iof=0;

    for(i=0;i<10;i++)
    {
        visited[i]=false;
    }

    for(i=0;i<n;i++)
    {
        qb[i]=i;
    }

    total=pt=process[0].at;

    for(i=0;i<n-1;i++)
        if(process[i].at>process[i+1].at)
            total=pt=process[i+1].at;


    for(i=0;i<n;i++)
        for(j=0;j<n-1;j++)
        {
            if(process[qb[j]].rbt>process[qb[j+1]].rbt)
            {
                temp=qb[j];
                qb[j]=qb[j+1];
                qb[j+1]=temp;
            }
        }

    while(flag)
    {
        for(j=0;j<n;j++)
            for(i=0;i<n;i++)
            {
                cp = qb[i];
                if(process[cp].at<=total && !visited[cp])
                {
                    pt = total;
                    total = total + process[cp].rbt;
                    p[iof].ct=pt;
                    p[iof].st=total;
                    p[iof].no=cp; iof++;
                    printf("-%d |%d| %d- \n",pt,cp,total);
                    visited[cp]=true;
                    process[cp].rbt=0;
                    break;
                }
            }
        for(i=0;i<n;i++)
        {
            flag=false;
            if(!visited[i])
            {
                flag=true;
                break;
            }
        }
    }
    drawscale();
    //basic=34;
    strin("Gantt Chart",11,30,158+40);
    strin("___________",11,30,156+40);
    for(i=0;i<n;i++)
    {
        glColor3fv(col[qb[i]]);
        drawrec(30+p[i].st*36,100,30+p[i].ct*36,130);
        glLineWidth(2.0);
        glColor3f(0.0,0,0);
        drawloop(30+p[i].st*36,100,30+p[i].ct*36,130);
        glColor3fv(col[q[i]]);
        me=(30+p[i].st*36+30+p[i].ct*36)/2;
        strin("P",1,me-8,88);
        a='0'+p[i].no;
        strin(&a,1,me,88);
        arri(i);
        glFlush();
        delay2();
    }
    glLineWidth(1.0);
    glColor3f(1,.84,.0);
}

//execute Shortest Job First
void execSJF()
{
    int i;
    for(i=0;i<n;i++)
    {
        process[i].at=p[i].at;
        process[i].rbt=process[i].bt=p[i].bt;
    }
    for(i=0;i<n;i++)
    {
        p[i].name='0'+char(i);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    table();
    displayName("Shortest Job First");
    setValuesForSJF();
    displayText(700, 300, 1, 1, 0,"Press 'm' to go back to the main menu");
    avg();
}

//execute FCFS
void execFCFS()
{
    int i;
    for(i=0;i<n;i++)
    {
        process[i].at=p[i].at;
        process[i].rbt=process[i].bt=p[i].bt;
    }
    for(i=0;i<n;i++)
    {
        p[i].name='0'+char(i);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    table();
    displayName("First Come First Serve");
    setValues();
    displayText(700, 300, 1, 1, 0,"Press 'm' to go back to the main menu");
    avg();
}

//Execute round robin
void execRR()
{
    int i;
    for(i=0;i<n;i++)
    {
        process[i].at=p[i].at;
        process[i].rbt=process[i].bt=p[i].bt;
    }

    for(i=0;i<n;i++)
    {
        p[i].name='0'+char(i);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    table();
    displayName("Round Robin");
    setValuesRR();
    gchart();
    displayText(700, 300, 1, 1, 0,"Press 'm' to go back to the main menu");
    avgRR();
}

void key1(unsigned char k,int x,int y)
{
    char a=k;
    int numb;
    if(keypa==0 && !doneInput)
    {
        if(a == '1') {
            keypa=1;
            glClearColor(0.1,0.1,.6,.803);
            glClear (GL_COLOR_BUFFER_BIT);
            backgrnp();
        }
    }
    else if(keypa==1 && !doneInput)
    {
        if(isdigit(a) && one==1)
        {
            one=0;
            numb=a-'0';
            if(np==1)
            {
                if(numb<=5)
                {
                    stri(&a,1,360,375);
                    backgrnp();
                    np=0;
                    att=numb-1;
                    index1=0;
                    n=numb;
                    usleep(300000);
                    glClear(GL_COLOR_BUFFER_BIT);
                    backgrat();
                    one=1;
                }
                else
                {
                    for(int k=0;k<3;k++) {
                        glClear(GL_COLOR_BUFFER_BIT);
                        backgrnp();
                        glFlush();
                        glColor3f(1, 1, 1);
                        strin("ERROR", 5, 15, 95);
                        strin("_____", 5, 15, 93);
                        strin("Number of processes greater than 5 not allowed ", 47, 15, 80);
                        glFlush();
                        delay();
                        glClear(GL_COLOR_BUFFER_BIT);
                        glClearColor(0.1,0.1,.6,.803);
                        backgrnp();
                        delay();
                    }
                    one=1;
                    glClearColor(0.1,0.1,.6,.803);
                }
            }
            else if(att>=0)
            {
                if(numb<=30)
                {
                    same[numb]=0;
                    stri(&a,1,430,375);
                    att--;
                    delay();
                    backgrat();

                    p[index1++].at=numb;
                    one=1;
                    if(att<0)
                    {
                        delay();
                        glClear(GL_COLOR_BUFFER_BIT);
                        btt=n-1;
                        index1=0;
                        backgrbt();
                    }
                    glClear(GL_COLOR_BUFFER_BIT);
                }
            }
            else if(btt>=0)
            {
                if(numb<=30)
                {
                    stri(&a,1,410,375);
                    delay();
                    btt--;
                    backgrbt();
                    tb=tb+numb;
                    p[index1++].bt=numb;
                    btotal+=numb;
                    if(tb>=30) {

                        for (int k = 0; k < 3; k++) {
                            glColor3f(1, 1, 1);
                            strin("ERROR", 5, 15, 95);
                            strin("_____", 5, 15, 93);
                            strin("Total burst time greater than 30 not allowed. Restarting the program!", 69, 15, 80);
                            glColor3f(0.0, 0.87, .803);
                            backgrbt();
                            glFlush();
                            delay();
                            glClear(GL_COLOR_BUFFER_BIT);
                            backgrbt();
                            glFlush();
                            delay();
                        }
                        one=1;
                        restart();
                        disp();
                    }
                    one=1;
                    glClear(GL_COLOR_BUFFER_BIT);
                    if(btt<0)
                    {
                        delay();
                        glClear(GL_COLOR_BUFFER_BIT);
                        glFlush();
                        backgrtq();
                    }
                }
            }
            else if(tq==99){
                tq=numb;
                stri(&a,1,280,375);
                glFlush();
                delay();
                doneInput=true;
                glClear(GL_COLOR_BUFFER_BIT);
                glFlush();
                displayOptions();
                //exec();
            }
        }
        else if(k=='R'||k=='r')
        {
            np=1;
            glClear(GL_COLOR_BUFFER_BIT);
            backgrnp();
        }
        else if(k=='e'||k=='E')
        {
            example();
            doneInput=true;
            np=0;
        }
        else
        {
            glColor3f(1,1,1);
            stri("ERROR",5,15,95);
            stri("_____",5,15,93);
            stri("Number not pressed",18,15,80);
            glClearColor(0.1,0.1,.6,.803);
            if(np==1)
                backgrnp();
            else if(att==1)
                backgrat();
            else
                backgrbt();
            glFlush();
            one=1;
        }
    }
    else if(doneInput)
    {
        switch(a)
        {
            case '1': execFCFS();
                      break;
            case '2': execRR();
                      break;
            case '3': execSJF();
                      break;
            case '4': glClear(GL_COLOR_BUFFER_BIT);
                      tq=99;
                      restart();
                      doneInput=false;
                      backgrnp();
                      break;
            case '5': glutDestroyWindow(wid);
                exit(0);
            case 'm':
            case 'M': restart();
                      doneInput=true;
                      displayOptions();
                      break;
        }
        glFlush();
    }
}

void disp()
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayfirst();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200,500);
    glutInitWindowPosition(100,100);
    wid =  glutCreateWindow("Process Scheduling");
    init();
    glutDisplayFunc(disp);
    glutKeyboardFunc(key1);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
