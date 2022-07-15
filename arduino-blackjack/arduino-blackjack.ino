#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

//카드 틀
byte frame1[8] = {
  B11111, B10000, B10000, B10000, B10000, B10000, B10000, B10000
};
byte frame2[8] = {
  B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000
};
byte frame3[8] = {
  B11111, B00001, B00001, B00001, B00001, B00001, B00001, B00001
};
byte frame4[8] = {
  B10000, B10000, B10000, B10000, B10000, B10000, B10000, B11111
};
byte frame5[8] = {
  B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111
};
byte frame6[8] = {
  B00000, B00001, B00001, B00001, B00001, B00001, B00001, B11111
};

//카드 숫자. numA, num2, ... , numK까지 구현
byte numA[2][8] = {{ // 2번
  B00000, B00011, B01101, B10001, B10001, B01101, B00011, B00000
}, {
  B00000, B11110, B00000, B00000, B00000, B00000, B11110, B00000
}};
byte num2[2][8] = {{
  B00000, B00110, B01001, B01000, B01000, B00100, B00000, B00000
}, {
  B00000, B00100, B00100, B10100, B01100, B00100, B00000, B00000
}};
byte num3[2][8] = {{
  B00000, B00110, B01001, B01001, B01000, B00100, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B01000, B00000, B00000
}};
byte num4[2][8] = {{
  B00000, B00000, B01111, B00100, B00010, B00001, B00000, B00000
}, {
  B00000, B10000, B11100, B10000, B10000, B10000, B00000, B00000
}};
byte num5[2][8] = {{
  B00000, B01000, B01001, B01001, B01001, B01111, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B00100, B00000, B00000
}};
byte num6_1[2][8] = {{ // 1번
  B00000, B00100, B01001, B01001, B01001, B00111, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B11000, B00000, B00000
}};
byte num6_2[2][8] = {{ // 2번
  B00000, B00000, B01001, B01001, B01001, B00111, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B11000, B00000, B00000
}};
byte num7[2][8] = {{
  B00000, B01100, B01010, B01001, B01000, B01000, B00000, B00000
}, {
  B00000, B00000, B00000, B11100, B00000, B00000, B00000, B00000
}};
byte num8[2][8] = {{
  B00000, B00110, B01001, B01001, B01001, B00110, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B11000, B00000, B00000
}};
byte num9[2][8] = {{
  B00000, B00111, B01001, B01001, B01001, B00110, B00000, B00000
}, {
  B00000, B11000, B00100, B00100, B00100, B01000, B00000, B00000
}};
byte num10_1[2][8] = {{ // 숫자 0 대각선 없음
  B00111, B01000, B01000, B01000, B00111, B00000, B01111, B00100
}, {
  B11000, B00100, B00100, B00100, B11000, B00100, B11100, B00100
}};
byte num10_2[2][8] = {{ // 숫자 0 대각선 있음
  B00111, B01000, B01001, B01010, B00111, B00000, B01111, B00100
}, {
  B11000, B10100, B00100, B00100, B11000, B00100, B11100, B00100
}};
byte numJ_1[2][8] = {{ // 1번
  B00000, B00000, B01111, B01000, B01000, B01000, B00000, B00000
}, {
  B00000, B00000, B11100, B00010, B00010, B00010, B00100, B00000
}};
byte numJ_2[2][8] = {{ // 2번
  B00000, B01000, B01000, B01111, B01000, B01000, B00000, B00000
}, {
  B00000, B00000, B00000, B11100, B00010, B00010, B00100, B00000
}};
byte numJ_3[2][8] = {{ // 3번
  B00000, B00000, B01111, B00000, B00000, B00000, B00000, B00000
}, {
  B00000, B00000, B11100, B00010, B00010, B00010, B00100, B00000
}};
byte numQ_1[2][8] = {{ // 1번
  B00000, B00111, B01000, B01000, B01000, B00111, B00000, B00000
}, {
  B00000, B11100, B01100, B10100, B00100, B11000, B00000, B00000
}};
byte numQ_2[2][8] = {{ // 2번
  B00000, B00111, B01000, B01000, B01000, B00111, B00000, B00000
}, {
  B00010, B11100, B01100, B10100, B00100, B11000, B00000, B00000
}};
byte numK[2][8] = {{
  B00000, B01100, B00010, B00001, B00001, B01111, B00000, B00000
}, {
  B00000, B01100, B10000, B00000, B00000, B11100, B00000, B00000
}};

LiquidCrystal_I2C lcd(0x3F, 16, 2);
LiquidCrystal lcd1(12,11,7,6,5,4);
LiquidCrystal lcd2(52,8,53,2,10,51);
int shuffle(int deck[], int card[]) {
  for (int i = 0; i<52;i++) {
        deck[i] = (i / 13 + 3) * 100 + i % 13 + 1;
  }
  int t;
  randomSeed(analogRead(0));
  for(int i = 0; i<52;i++){
      do {
          t =random()%52;
      } while(deck[t] == 0);
      card[i] = deck[t];
      deck[t] = 0;
  }
}
int printFrame(LiquidCrystal_I2C lcd) {
  lcd.createChar(0, frame1);
  lcd.createChar(1, frame2);
  lcd.createChar(2, frame3);
  lcd.createChar(3, frame4);
  lcd.createChar(4, frame5);
  lcd.createChar(5, frame6);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.setCursor(2, 0);
  lcd.write(byte(1));
  lcd.setCursor(3, 0);
  lcd.write(byte(1));
  lcd.setCursor(4, 0);
  lcd.write(byte(1));
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(0, 1);
  lcd.write(byte(3));
  lcd.setCursor(3, 1);
  lcd.write(byte(4));
  lcd.setCursor(4, 1);
  lcd.write(byte(4));
  lcd.setCursor(5, 1);
  lcd.write(byte(4));
  lcd.setCursor(6, 1);
  lcd.write(byte(5));
  lcd.setCursor(9, 0);
  lcd.write(byte(0));
  lcd.setCursor(10, 0);
  lcd.write(byte(1));
  lcd.setCursor(11, 0);
  lcd.write(byte(1));
  lcd.setCursor(12, 0);
  lcd.write(byte(1));
  lcd.setCursor(13, 0);
  lcd.write(byte(1));
  lcd.setCursor(14, 0);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(2));
  lcd.setCursor(9, 1);
  lcd.write(byte(3));
  lcd.setCursor(12, 1);
  lcd.write(byte(4));
  lcd.setCursor(13, 1);
  lcd.write(byte(4));
  lcd.setCursor(14, 1);
  lcd.write(byte(4));
  lcd.setCursor(15, 1);
  lcd.write(byte(5));
  return 1;
}

int bitOr(byte ret[][8], byte tmp[][8], byte frame[8]) {
  for(int i = 0; i<8 ; i++) {
    ret[0][i] = tmp[0][i] | frame[i];
    ret[1][i] = tmp[1][i] | frame[i];
  }
  return 1;
}

int prch(LiquidCrystal_I2C lcd, bool t, int fontNum, byte c[][8]) {
  lcd.createChar(fontNum, c[0]);
  if(t == true) {
    lcd.setCursor(1, 1);  
  } else if(t == false) {
    lcd.setCursor(10, 1);
  } else {
    Serial.println("error");
  }
  lcd.write(byte(fontNum));
  fontNum = fontNum + 1;
  lcd.createChar(fontNum, c[1]);
  if(t == true) {
    lcd.setCursor(2, 1);
  } else if(t==false) {
    lcd.setCursor(11, 1);
  }
  lcd.write(byte(fontNum));
  fontNum = fontNum + 1;
  return fontNum;
}

int prChI2C(LiquidCrystal_I2C lcd, bool t, int ch) {
  if(t==true){
    lcd.setCursor(0, 0);
  } else lcd.setCursor(8, 0);
  if (ch == 1) {
    lcd.print("A");
  } else if(ch == 11) {
    lcd.print("J");
  } else if(ch==12) {
    lcd.print("Q");
  } else if (ch==13) {
    lcd.print("K");
  } else if (ch > 1 && ch < 11) {
    lcd.print(ch);
  } else return 1;
  return 0;
}
int prShI2C(LiquidCrystal_I2C lcd, bool t, int sh) {
  if(t==true){
    lcd.setCursor(0, 1);
  } else lcd.setCursor(8, 1);
  if (sh == 1) {
    lcd.print("Spade");
  } else if(sh == 2) {
    lcd.print("Clover");
  } else if (sh==3) {
    lcd.print("Diamond");
  } else if (sh==4){
    lcd.print("Heart");
  } else return 1;
  return 0;
}
int prCardI2C(LiquidCrystal_I2C lcd, bool t, int card) {
  int sh = card / 100 - 2;
  int ch = card % 100;
  if(prChI2C(lcd, t, ch) == 1){
    lcd.print("cherror");
  }
  if(prShI2C(lcd, t, sh) == 1){
    lcd.print("sherror");
  }
  return 0;
}
int prChNoI2C(LiquidCrystal lcd, bool t, int ch) {
  if(t==true){
    lcd.setCursor(0, 0);
  } else lcd.setCursor(8, 0);
  if (ch == 1) {
    lcd.print("A");
  } else if(ch == 11) {
    lcd.print("J");
  } else if(ch==12) {
    lcd.print("Q");
  } else if (ch==13) {
    lcd.print("K");
  } else if (ch > 1 && ch < 11) {
    lcd.print(ch);
  } else return 1;
  return 0;
}
int prShNoI2C(LiquidCrystal lcd, bool t, int sh) {
  if(t==true){
    lcd.setCursor(0, 1);
  } else lcd.setCursor(8, 1);
  if (sh == 1) {
    lcd.print("Spade");
  } else if(sh == 2) {
    lcd.print("Clover");
  } else if (sh==3) {
    lcd.print("Diamond");
  } else if (sh==4){
    lcd.print("Heart");
  } else return 1;
  return 0;
}
int prCardNoI2C(LiquidCrystal lcd, bool t, int card) {
  int sh = card / 100 - 2;
  int ch = card % 100;
  if(prChNoI2C(lcd, t, ch) == 1){
    lcd.print("cherror");
  }
  if(prShNoI2C(lcd, t, sh) == 1){
    lcd.print("sherror");
  }
  return 0;
}
int check_JQK(int val) {
  if( val % 100 < 11 && val % 100 > 0) {
    return val%100;
  } else if(val%100 == 1) {
    return 1;
  } else if(val%100 > 10 && val%100 < 14) {
    return 10;
  } else return -1;
}
int compare(LiquidCrystal_I2C lcd, int psum, int dsum) {
  Serial.println(dsum);
  if(psum > 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
//    lcd.print("an error occured");
    lcd.print("you lose because");
    lcd.setCursor(0, 1);
    lcd.print("UR sum overed 21");
    return 0;
  } else if (dsum > 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you win         ");
    lcd.setCursor(0, 1);
    lcd.print("dealer overed 21");
    return 0;
  } else if (psum == 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you win         ");
    lcd.setCursor(0, 1);
    lcd.print("sum equals 21");
    return 0;
  } else if (dsum == 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("dealer win");
    lcd.setCursor(0, 1);
    lcd.print("He got 21");
    return 0;
  } 
  return 1;
}
int finish(LiquidCrystal_I2C lcd, int psum, int dsum) {
  if(compare(lcd, psum, dsum)==0) {
    Serial.println("already finished");
  }
  if(psum > dsum) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you win");
    lcd.setCursor(2, 1);
    lcd.print(psum);
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(8, 1);
    lcd.print(dsum);
  } else if(psum == dsum) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("draw");
    lcd.setCursor(0, 1);
    lcd.print(psum);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you lose");
    lcd.setCursor(2, 1);
    lcd.print(psum);
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(8, 1);
    lcd.print(dsum);
  }
}
int position_pin[] = {31,32,33,34};               //4자리 결정 핀
int segment_pin[] = {35,36,37,38,39,40,41,42};     //세그먼트 제어 핀
byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
byte seven_seg_digits[10][8] = 
{
  { 1,1,1,1,1,0,1,1 },  // = 0
  { 1,1,1,0,0,0,0,0 },  // = 1
  { 1,0,1,1,0,1,1,1 },  // = 2
  { 1,1,1,1,0,1,0,1 },  // = 3
  { 1,1,1,0,1,1,0,0 },  // = 4
  { 1,1,0,1,1,1,0,1 },  // = 5
  { 1,1,0,1,1,1,1,1 },  // = 6
  { 1,1,1,1,0,0,0,0 },  // = 7
  { 1,1,1,1,1,1,1,1 },  // = 8
  { 1,1,1,1,1,1,0,1 }   // = 9
  };/*
void sevenSegWrite1(byte digit) //디지털IO 4~11번을 순서대로 어레이의 값으로 출력
{
  byte pin = 30;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}*/
void sevenSegWrite(byte digit) //디지털IO 4~11번을 순서대로 어레이의 값으로 출력
{
  digitalWrite(22, seven_seg_digits[digit][0]);
  digitalWrite(23, seven_seg_digits[digit][1]);
  digitalWrite(24, seven_seg_digits[digit][2]);
  digitalWrite(25, seven_seg_digits[digit][3]);
  digitalWrite(26, seven_seg_digits[digit][4]);
  digitalWrite(27, seven_seg_digits[digit][5]);
  digitalWrite(28, seven_seg_digits[digit][6]);
  digitalWrite(29, seven_seg_digits[digit][7]);
}
void show(int number) {
  //4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == 4){
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  //8개 세그먼트를 제어해서 원하는 숫자 출력
  for(int i = 0; i < 8; i++){
     byte segment = (data[number] & (0x01 << i)) >> i;
     if(segment == 1){
       digitalWrite(segment_pin[7 - i], HIGH);
     } else {
       digitalWrite(segment_pin[7 - i], LOW);
     }
  }
}
void setup()
{
  for(int i = 0; i < 4; i++) {
     pinMode(position_pin[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
  
  pinMode(22, OUTPUT);   
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  /*
  pinMode(30, OUTPUT);   
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  */
  //push button
  pinMode(46, INPUT);
  pinMode(47, INPUT);
  //card deck init for shuffle
  int deck[52];
  int card[52];
  shuffle(deck, card);
//  byte tmp[2][8];
//  byte ret[2][8];
//  int fontNum=6;
  Serial.begin(9600);
  //3 lcd display
  lcd.init();
  lcd.backlight();  
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
//  printFrame(lcd);
  //set player cards + dealer cards, max: 5
  int pcard[5];
  int dcard[5];
  pcard[0] = card[0];
  dcard[0] = card[1];
  pcard[1] = card[2];
  dcard[1] = card[3];
  pcard[2] = card[4];
  dcard[2] = card[5];
  pcard[3] = card[6];
  dcard[3] = card[7];
  pcard[4] = card[8];
  dcard[4] = card[9];
  //automatically set the value of A cards
  for(int i = 0 ; i<5 ; i++) {
    if(pcard[i]%100==1) {
      int tmp=0;
      for(int j = 0; j<i;j++){
        tmp = tmp + pcard[j];
      }
      if (tmp <= 11) {
        pcard[i] = pcard[i] + 10;
      }
    }
    if(dcard[i]%100==1) {
      int tmp1=0;
      for(int j = 0; j<i;j++){
        tmp1 = tmp1 + dcard[j];
      }
      if (tmp1 <= 11) {
        pcard[i] = pcard[i] + 10;
      }
    }
  }
  
  //print dealer's 1 card, player's 2 card
  prCardI2C(lcd, true, dcard[0]);
  prCardNoI2C(lcd1, true, pcard[0]);
  prCardNoI2C(lcd1, false, pcard[1]);

  //initialize sum of player's card and dealer's
  int psum = 0;
  int dsum = 0;

  //check idx of card num(0보다 작은지, 13보다 큰지, JQK는 10으로)
  for(int i = 0 ; i < 5 ; i++) {
    if(check_JQK(pcard[i]%100) == -1 || check_JQK(dcard[i]%100) == -1) {
      Serial.println("JQKerror");
      return;
    }
  }
  //turn 1
  psum = check_JQK(pcard[0]%100) + check_JQK(pcard[1]%100);
  show(int(psum/10));
  /*
  Serial.println(psum%10);
  sevenSegWrite1(byte(int(psum/10)));*/
  show(int(psum/10));
  sevenSegWrite(byte(psum%10));
  dsum = check_JQK(dcard[0]%100) + check_JQK(dcard[1]%100);
  if(psum > 21) {
    lcd.setCursor(0, 0);
    lcd.print("an error occured");
    return;
  } else if (psum == 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you win");
    lcd.setCursor(0, 1);
    lcd.print("sum equals 21");
    return;
  } else if (dsum == 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("dealer win");
    lcd.setCursor(0, 1);
    lcd.print("He got 21");
    return;
  }
  //if game wasn't finished, print "push for more card"
  lcd.setCursor(7, 0);
  lcd.print("push for");
  lcd.setCursor(7, 1);
  lcd.print("more card");
  //temporary variable for button
  bool but;
  while(1) {
    if(digitalRead(46)==1) {
      but = true;
      break;
    } else if(digitalRead(47)==1) {
      but = false;
      break;
    }
  }
  delay(200);
  compare(lcd, psum, dsum);
  if(but == false) {
    finish(lcd, psum, dsum);
    return;
  }
  prCardNoI2C(lcd2, true, pcard[2]);
  psum = psum + check_JQK(pcard[2]%100);
  //sevenSegWrite1(byte(int(psum/10)));
  sevenSegWrite(byte(psum%10));
  show(int(psum/10));
  if(dsum <= 16) {
    dsum = dsum + check_JQK(dcard[2]%100);    
  }
  if(compare(lcd, psum, dsum) == 0) {
    return;
  }
  //if game wasn't finished, print "push for more card"
  lcd.setCursor(7, 0);
  lcd.print("push for");
  lcd.setCursor(7, 1);
  lcd.print("more card");
  //temporary variable for button
  bool but1;
  while(1) {
    if(digitalRead(46)==1) {
      but1 = true;
      break;
    } else if(digitalRead(47)==1) {
      but1 = false;
      break;
    }
  }
  delay(200);
  compare(lcd, psum, dsum);
  if(but1 == false) {
    finish(lcd, psum, dsum);
    return;
  }
  prCardNoI2C(lcd2, false, pcard[3]);
  psum = psum + check_JQK(pcard[3]%100);
 // sevenSegWrite1(byte(int(psum/10)));
  sevenSegWrite(byte(psum%10));
  show(int(psum/10));
  if(dsum <= 16) {  
    dsum = dsum + check_JQK(dcard[3]%100);
  }
  if(compare(lcd, psum, dsum) == 0) {
    return;
  }
  //if game wasn't finished, print "push for more card"
  lcd.setCursor(7, 0);
  lcd.print("push for");
  lcd.setCursor(7, 1);
  lcd.print("more card");
  bool but2;
  while(1) {
    if(digitalRead(46)==1) {
      but2 = true;
      break;
    } else if(digitalRead(47)==1) {
      but2 = false;
      break;
    }
  }
  delay(200);
  if(but2 == false) {
    finish(lcd, psum, dsum);
    return;
  }
  compare(lcd, psum, dsum);
  prCardI2C(lcd, false, pcard[4]);
  psum = psum + check_JQK(pcard[4]%100);
  //sevenSegWrite1(byte(int(psum/10)));
  sevenSegWrite(byte(psum%10));
  show(int(psum/10));
  if(dsum <= 16) {
    dsum = dsum + check_JQK(dcard[4]%100);    
  }
  if(psum <= 21) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you win! sum of");
    lcd.setCursor(0, 1);
    lcd.print("5 cards < 21");
    return;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("you lose because");
    lcd.setCursor(0, 1);
    lcd.print("UR sum overed 21");
    return;
  }
}

void loop()
{
}
