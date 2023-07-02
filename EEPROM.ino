#include <EEPROM.h>

void Read_EEPROM();
void Write_EEPROM();
void Clear_EEPROM();

const int MAX_TEXT_LENGTH = 100;  // Maximum length of the text to be written
const int EEPROM_SIZE = EEPROM.length();  // Total size of the EEPROM

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("[R] Read EEPROM");
  Serial.println("[W] Write EEPROM");
  Serial.println("[C] Clear EEPROM");
  Serial.print("\nSelect: ");

  while (!Serial.available()) {
    // Wait for user input
  }

  String input = Serial.readStringUntil('\n');
  input.trim(); // Remove leading and trailing whitespace

  if (input.length() == 1) {
    char choice = input.charAt(0);
    Serial.println(choice);

    switch (choice) {
      case 'r':
      case 'R':
        Read_EEPROM();
        break;

      case 'w':
      case 'W':
        Write_EEPROM();
        break;

      case 'c':
      case 'C':
        Clear_EEPROM();
        break;

      default:
        Serial.println("Invalid input!");
        break;
    }
  } else if (input.length() > 1) {
    Serial.println("Invalid input!");
  }
}

void Read_EEPROM() {
  // Code for reading from EEPROM
  int address = 0;
  String dataRead;
  int i = 0;
  
  while (true) {
    char character = EEPROM.read(address + i);
    if (character == '\0') {
      break;
    }
    dataRead += character;
    i++;
  }
  int Data_in_eeprom = dataRead.length();
  int eeprom_size = EEPROM.length();
  int x = 0;
  x = eeprom_size - Data_in_eeprom;
  Serial.print("Used space: ");
  Serial.print(eeprom_size);
  Serial.print("/");
  Serial.println(Data_in_eeprom);
  Serial.println("Data in EEPROM: ");
  Serial.println(dataRead);
}

void Write_EEPROM() {
  Serial.print("Enter some text: ");
  while (!Serial.available()) {
    // Wait for user input
  }

  String input = Serial.readStringUntil('\n');
  input.trim(); // Remove leading and trailing whitespace

  if (input.length() > 0) {
    int textLength = input.length();
    if (textLength > MAX_TEXT_LENGTH) {
      Serial.print("Text too long! Maximum length: ");
      Serial.println(MAX_TEXT_LENGTH);
      return;
    }

    int address = 0;
    bool foundEmptySpace = false;

    // Find the first empty space in EEPROM
    while (address < EEPROM_SIZE) {
      char character = EEPROM.read(address);

      if (character == '\0') {
        foundEmptySpace = true;
        break;
      }

      address++;
    }

    // Write the new text to EEPROM starting from the first empty space
    for (int i = 0; i < textLength; i++) {
      if (foundEmptySpace) {
        char character = input.charAt(i);
        EEPROM.write(address + i, character);
      } else {
        Serial.println("No empty space available in EEPROM!");
        return;
      }
    }

    EEPROM.write(address + textLength, '\0');  // Null-terminate the string in EEPROM

    Serial.println("Text saved in EEPROM.");
  } else {
    Serial.println("No text entered!");
  }
}

void Clear_EEPROM() {
  // Code for clearing EEPROM
//  int eeprom_size = EEPROM.length();
  int z = 1;
  for (int i = 0 ; i < EEPROM_SIZE ; i++) {
      EEPROM.write(i, 0);
      z = 1 + i;
      Serial.print(EEPROM_SIZE);
      Serial.print("/");
      Serial.println(z);
   }
   Serial.println("EEPROM Cleared");
}
