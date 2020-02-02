//This program converts a string into the morse code
//equivalent on an LED

int dotLength = 100;
int spaceLength = 250;
int gapLength = 50;
const byte maxChars = 32;
char inputArray[maxChars]; // an array to store the received data
boolean finished = false;
int inputPin = 13;

char *morseLetters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", " "
};


void setup() {

  pinMode (inputPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Please enter a string to be translated to morse code:");

}

void loop() {
  getInput();

}

void getInput() {
  static byte index = 0;
  char endMarker = '\n';
  char readChar;



  while (Serial.available() > 0 && !finished ) {
    readChar = tolower(Serial.read());

    if (readChar != endMarker && readChar != '!') {
      if (isalpha(readChar) || isspace(readChar) )
      {
        displayMorse(readChar - 'a');
        inputArray[index] = readChar;
        index ++;

        if (index >= maxChars) {
          index = maxChars - 1;
        }

      }
      else
      {
        Serial.print(readChar);
        Serial.println(" is not a valid input.");
        break;
      }
    }
    else if (readChar == '!') {
      inputArray[index] = '!';
      inputArray[index+1] = '\0';
      Serial.println(inputArray);
      Serial.println("It's finished!");
      finished = true;
    }
    else {
      inputArray[index] = '\0';
      Serial.println(inputArray);
      index = 0;

    }
  }
}

void displayMorse(int letter) {

  char* morseLetter = morseLetters[letter];
  int i = 0;
  if (letter == -65) {
    delay(spaceLength);
  } else {
    while (morseLetter[i] != NULL) {
      flashLED(morseLetter[i]);
      i++;
    };
  };
}

void flashLED(char symbol) {

  if (symbol == '.')
  {
    digitalWrite(13, HIGH);
    delay(dotLength);
    digitalWrite(13, LOW);
    delay(gapLength);
  } else { // This is implicitly known to be a -
    digitalWrite(13, HIGH);
    delay(dotLength * 3);
    digitalWrite(13, LOW);
    delay(gapLength);
  };

}
