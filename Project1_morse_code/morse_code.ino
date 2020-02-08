
//------------------------------------------------------------------------
//              Audrey Long - Project 1 - 02-08-2020
// This program converts a string into the morse code equivalent on an LED
//------------------------------------------------------------------------

//----------------------------------------------------------------
// Varibles to be user throughout the Project
//----------------------------------------------------------------
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

//----------------------------------------------------------------
// Function to setup the serial connection and pin establishment
//----------------------------------------------------------------
void setup() {

  pinMode (inputPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Please enter a string to be translated to morse code:");

}

//----------------------------------------------------------------
// Main loop
//----------------------------------------------------------------

void loop() {
  getInput();

}

//-------------------------------------------------------------------
// Function to get the correct user input and convert into Morse code
//-------------------------------------------------------------------

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

//----------------------------------------------------------------
// Function to display the character to corresponsing LED behavior
//----------------------------------------------------------------

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

//--------------------------------------------------------------
// Function to convert Morse code string with lenth of LED blink
//--------------------------------------------------------------
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
