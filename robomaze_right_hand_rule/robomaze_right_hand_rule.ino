char directions[30]; 
#include<LiquidCrystal.h>
LiquidCrystal lcd(11,10,5,4,3,2);

const int r1=24;
const int r2=25;
const int l1=0;
const int l2=1;
int l,c1,c2,c3,r;
int i=0;
int tdelay=450;
int fdelay=5;
void forward()
{
  digitalWrite(l1,1);
  digitalWrite(l2,0);
  digitalWrite(r1,1);
  digitalWrite(r2,0);  
}


void Stop()
{
  digitalWrite(l1,0);
  digitalWrite(l2,0);
  digitalWrite(r1,0);
  digitalWrite(r2,0);  

}

void smallright()
{
  digitalWrite(l1,1);
  digitalWrite(l2,0);
  digitalWrite(r1,0);
  digitalWrite(r2,0);  

}
void smallleft()
{
  digitalWrite(l1,0);
  digitalWrite(l2,0);
  digitalWrite(r1,1);
  digitalWrite(r2,0);  

}


void right()
{
  digitalWrite(l1,1);
  digitalWrite(l2,0);
  digitalWrite(r1,0);
  digitalWrite(r2,1);  
}

void left()
{
  digitalWrite(l1,0);
  digitalWrite(l2,1);
  digitalWrite(r1,1);
  digitalWrite(r2,0);  
}
int eosens()
{
  readsens();
  if(((c1+c2+c3)==1 || (c1+c2+c3)==2))
    return 1;
  else
    return 0;
    
}

void readsens()
{
  l=digitalRead(26);
  c1=digitalRead(27);
  c2=digitalRead(28);
  c3=digitalRead(29);
  r=digitalRead(30);
  lcd.print(l);
  lcd.print("--"); 
  lcd.print(c1);
  lcd.print("--"); 
  lcd.print(c2);
  lcd.print("--"); 
  lcd.print(c3);
  lcd.print("--"); 
  lcd.print(r);
  lcd.print("--");
 }
void inch()
{
  lcd.print("INCH FUNCTION");
  Stop();
  delay(350);
  forward();
  delay(350);
  Stop();
  delay(350);
  readsens();
  lcd.clear();
}

void align()
{
  Stop();
  delay(500);
  forward();
  delay(60);
  Stop();
  delay(100);
  readsens();
  lcd.clear();
}
void printing(char prtdirection[])
{
  lcd.clear();
  for(i=0;prtdirection[i]!='E';i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(2000);
}
void setup() 
{
  lcd.begin(16,2);
  lcd.print("MSR with HR");
  delay(500);
  lcd.clear();
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(26,INPUT);
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);
}
void loop()
{
  lcd.clear();
  readsens();
  lcd.clear();
  if((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))
  {
    lcd.print("FORWARD");
    forward();
  }
  else if(((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1)))
  {
    lcd.print("LEFT");
    smallleft();
  }
   else if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1)))
  {
    lcd.print("RIGHT");
    smallright();
  }
  else if(((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)))
  {
    lcd.print("U TURN");
    right();
    delay(1000);
    Stop();
    delay(1000);
    
    directions[i]='U';
    i++;
  }
  else if(((l==1)&&(c1==1)||(c3==1)&&(r==1)))
  { 
    align();
    if(((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0)))
    {
      lcd.print("Ryt/ St.&Ryt?");
      inch();
      if(((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)))
      {
        lcd.print("right");
        right();
        delay(tdelay);
      }
      else if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("Right");
        directions[i]='R';
        i++;
        right();
        delay(tdelay);
       }
     }
    else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))
    {
      lcd.print("Left/ St.&Left?");
      inch();
      if(((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)))
      {
        lcd.print("Left");
        left();
        delay(tdelay);
      }
      else if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("straight");
        directions[i]='S';
        i++;
        forward();
        delay(fdelay);
      }    
    }
    else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
    {
      lcd.print(" T/END/4");
      inch();
      if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("4 way");
        directions[i]='R';
        i++;
        right();
        delay(tdelay);
      }
      else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r=1))
    {
      lcd.print(" T-int");
      directions[i]='R';
      i++;
      right();
      delay(tdelay);    
     }
     else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
     {
      lcd.print(" end of maze");
      directions[i]='E';
      while(1)
      {
        printing(directions);
        Stop();   
      }
     }
   
   }
}
}
