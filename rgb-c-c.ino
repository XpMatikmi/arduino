int r=11;
int g=10;
int b=9;
int button1=13;
int button2=8;
int b1state = 0;
int b2state = 0;
int prog=0;
int frq = 0;
int invrtfrq = 0;
int c;
void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  b1state = digitalRead(button1);
  b2state = digitalRead(button2);
  analogWrite(r,255);
  analogWrite(g,255);
  analogWrite(b,255);
  while(b1state== 1){
    delay(200);
    while(b1state == 1){
      
      if(prog==0){
        c = r;
      }
      if(prog==1){
        c = g;
      }
      if(prog==2){
        c = b;
      }
      frq = analogRead(A0);
      analogWrite(c,0);
      for (int i=0; i <= frq; i++){
        frq = analogRead(A0);
        if(digitalRead(button1)==HIGH){
          frq = 0;
          b1state = 0;
        }
        if(digitalRead(button2) == 1){
          prog = 1 + prog;
          if(prog > 3){
            prog = 0;
          }
        }
        delay(1);
      }
      analogWrite(c,255);
      for (int i=0; i <= frq; i++){
        frq = analogRead(A0);
        if(digitalRead(button1)==HIGH){
          frq = 0;
          b1state = 0;
        }
        if(digitalRead(button2) == 1){
          prog = 1 + prog;
          if(prog > 3){
            prog = 0;
          }
        }
        delay(1);
      }
      Serial.println(b1state);
    }
    delay(200);
  }
  while(b2state == 1){
    delay(200);
    while(b2state == 1){
      Serial.println(b2state);
      Serial.println(frq);
      delay(1);
      frq = abs(analogRead(A0) - 1024);
      if(frq >= 0 && frq < 256){
        analogWrite(r,frq);
        analogWrite(g,255);
        analogWrite(b,255);
      }
      if(frq >= 256 && frq < 512){
        analogWrite(g,frq - 256);
        analogWrite(r,abs(frq - 512));
        analogWrite(b,255);
      }
      if(frq >= 512 && frq < 768){
        analogWrite(b,frq - 512);
        analogWrite(g,abs(frq - 768));
        analogWrite(r,255);
      }
      if(frq >= 768 && frq < 1024){
        invrtfrq = abs(frq - 1024);
        analogWrite(r,invrtfrq);
        analogWrite(g,invrtfrq);
        analogWrite(b,invrtfrq);
      }
      if(digitalRead(button2) == 1){
        b2state = 0;
        analogWrite(r,255);
        analogWrite(g,255);
        analogWrite(b,255);
        delay(200);
      }
    }
    delay(200);
  }
}
