int inPin1 = 7;   
int inPin2 = 8;
int val1 = 0;  
int val2 = 0;
int flag = 0 ;

void setup() {
  pinMode(inPin1, INPUT);  // declare LED as output
  pinMode(inPin2, INPUT);    // declare pushbutton as input
  Serial.begin(9600);
}

void loop(){
  
  val1 = digitalRead(inPin1);  // read input value
  val2 = digitalRead(inPin2);
  
  if (val1 == HIGH)
    flag=1;

  if (val2 == HIGH)
    flag=0;

  if(flag==1)
    Serial.println("Hello Computer");
  else
    Serial.println("Bye Computer");
  
  
}
