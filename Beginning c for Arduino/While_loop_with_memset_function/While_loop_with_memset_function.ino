int searchList[200];

void setup() {
  int index=0;
  int target = 5343;
  Serial.begin(115200);
  memset(searchList, 0, sizeof(searchList));   // clear the array

  searchList[160] = target;

  while(true)
  {
    if(searchList[index]== target)
    {
      break;
    }
    index++;
  }
  Serial.print("Found target at index = ");
  Serial.println(index);

}

void loop() {
  // put your main code here, to run repeatedly:

}
