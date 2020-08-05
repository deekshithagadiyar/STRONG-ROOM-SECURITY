//Library for controlling LCDs
#include<LiquidCrystal.h>

//Allows reading keypad button pushes
#include<Keypad.h>  

//Creating an object for library LiquidCrystal
LiquidCrystal lcd(13, 11, 10, 9, 8, 7);

//declaring number of rows and columns in keypad used
const byte rows=4; 
const byte cols=4;
//const-Variable qualifier which modify the behaviour of a variable
//byte-Stores an 8 bit unsigned number

//Design of used keypad
char mapkeys[rows][cols]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//char-stores alpha numeric constants

//Declaring pin numbers of arduino connected to rows and columns of keypad
byte rowpins[rows]={3,2,1,0};
byte colpins[cols]={A0,A1,A2,A3};

//Assigning all the parameters of keypad with keypad library
Keypad mykeypad=Keypad(makeKeymap(mapkeys),rowpins,colpins,rows,cols);

//no-counts how many time wrong password is entered
//int-stores an integer value
int no=0;


void setup()
{  
 //use begin function to activate LCD
  lcd.begin(16,2);
   
  //declaring mode of a pin connected to LED and BUZZER
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
 
}

void loop()
{
  //if some key is pressed then it will be stored in a variable keypressed
  char keypressed=mykeypad.getKey();
  
  
  if(keypressed!=NO_KEY)
  {
  if(keypressed=='A')
  {
    //if the password entered is 'A' then door will open and green LED will turn ON
    digitalWrite(4,HIGH);
    
   //If the password is correct then LCD will display asteric('*')
   
    lcd.setCursor(5,1);
    lcd.print("****");
  }
  //For three unsuccssesful attempt red LED will blink once
  else if(keypressed!='A' && (no==0))
  {
    digitalWrite(5,HIGH);
    digitalWrite(5,LOW);
    no=1;
    
    lcd.setCursor(0,1);
    lcd.print("WRONG PASSWORD");
    delay(2);
  }
  else if(keypressed!='A' && (no==1))
  {
    digitalWrite(5,HIGH);
    digitalWrite(5,LOW);
    no=2;
   
    lcd.setCursor(0,1);
    lcd.print("WRONG PASSWORD");
    delay(2);
  }
  else if(keypressed!='A'&& (no==2))
  {
    digitalWrite(5,HIGH);
    digitalWrite(5,LOW);
    no=3;

    lcd.setCursor(0,1);
    lcd.print("WRONG PASSWORD");
    delay(2);
  }
 //For the fourth unsuccessesful attempt buzzer will turn ON along with red LED blinking
  else if(keypressed!='A' && (no=3))
  {
   //To stop the BUZZER sound and blinking of red LED enter MASTER password 'D'
    if(keypressed=='D')
    {
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
    }
    else
    {
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      delay(1000);
     
      lcd.setCursor(0,1);
      lcd.print("ENTER MASTER PASSWORD");
      delay(288);
    }
  }
    
  }    
  
}
