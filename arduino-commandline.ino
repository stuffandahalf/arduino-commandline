#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char commandBuffer[50];
int commandBufferSize = 0;
boolean prompt = false;

char argList[15][15];

char *parseCommand(char (*commandBufferAddress)[50], char (*argListAddress)[15][15]);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  /*lcd.print("Choose mode from");
  lcd.setCursor(0, 1);
  lcd.print("1-6: ");*/
  Serial.print("> ");
}

void loop()
{
  if(prompt)
  {
    Serial.print("> ");
    prompt = false;
  }
  
  while(Serial.available() && commandBufferSize < 49)
  {
    //lcd.print((char) Serial.read());
    //Serial.print((char) Serial.read());
    char next = (char) Serial.peek();
    if(next == '~')
    {
      //Serial.println(commandBuffer);
      parseCommand(&commandBuffer, &argList);
      commandBufferSize = 0;
      Serial.read();
      prompt = true;
    }
    else
    {
      commandBuffer[commandBufferSize] = (char) Serial.read();
      commandBuffer[commandBufferSize + 1] = '\0';
      commandBufferSize++;
      prompt = false;
    }
  }
}

char *parseCommand(char (*commandBufferAddress)[50], char (*argListAddress)[15][15])
{
  int i = 0;
  char command[50];
  char arguments[15][15];
  while((*commandBufferAddress)[i] != ' ' && i < 49)
  {
    command[i] = (*commandBufferAddress)[i];
    command[i + 1] = '\0';
    i++;
  }
  
  int argSize = 0;
  int k = 0;
  while((*commandBufferAddress)[i] != '\0')
  {
    if((*commandBufferAddress)[i] != ' ')
    {
      arguments[argSize][k] = (*commandBufferAddress)[i];
      arguments[argSize][k + 1] = '\0';
      k++;
    }
    else
    {
      argSize++;
    }
    i++;
  }
  
  Serial.println(command);
  Serial.println("Arguments:");
  for(int j = 0; j < argSize; j++)
  {
    Serial.print(arguments[j] + '\t');
  }
  return command;
}
