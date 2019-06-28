static int i=0;
static int flag=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //initialize input pin 
  pinMode(9,INPUT);

  //initialize output pin
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);

  //initialize flags control
  i=0;
  flag=0;
  
  digitalWrite(10,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(9)==HIGH)
  {
    digitalWrite(10,LOW);

    //repeate 15 for capture ecg signal
    if(i<15)
    {
          //loop on 6 analog pin in ecg-shiled to get values of each part of heart pulse
          for(int CurrentCh=0;CurrentCh<6;CurrentCh++){

              //stop MCU for listen
              digitalWrite(11,LOW);
              
              //read analog value ecg signal
              int ADC_Value = analogRead(CurrentCh);
              //print on serial monitor
              Serial.println(ADC_Value);
            
              if(ADC_Value >=100 || ADC_Value<500)
              {
                 flag++;
                 if(flag>200)
                 {
                   i=15;
                 }
              }
              else
              {
                 flag=0;
              }
            
              long binary_val=decimalToBinary(ADC_Value);
            
              while(binary_val!=0)
              {
                int digit=binary_val % 10;
                digitalWrite(13,digit);
                delay(1000);
                binary_val=binary_val/10;
              }
              if(binary_val==0)
              {
                digitalWrite(12,HIGH);
                delay(1000);
                digitalWrite(12,LOW);
              }
         }
         i++;
   }
   else
   {
    digitalWrite(11,HIGH);
   }
  }
}

//Function to convert a decinal number to binary number
long decimalToBinary(long n) {
    int remainder; 
 long binary = 0, i = 1;
  
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}
