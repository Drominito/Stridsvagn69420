#include <Arduino.h>
#include <Keypad.h>
#include <HardwareSerial.h>
extern HardwareSerial Serial;

/*Config for Pin and Delay*/
//TUNE THESE SETTINGS
int pin = 13;
int dot = 250;
int dash = dot * 3;
int charMS = dash * 2;
int wordMS = charMS * 1.5;
/*Dot, Dash and Translator for Morse code*/
void Dot() {
    digitalWrite(pin, HIGH);
    delay(dot);
    digitalWrite(pin, LOW);
    delay(dot);
}
void Dash() {
    digitalWrite(pin, HIGH);
    delay(dash);
    digitalWrite(pin, LOW);
    delay(dot);
}
/*Collection for Morse Code Letters*/
class LED {
    public:
        static void Translate(String word) {
            word.toUpperCase();
            for (int i = 0; i < word.length(); i++) {
                char letter = word[i];
                switch (letter) {
                    case 'A':
                        mA();
                        break;
                    case 'B':
                        mB();
                        break;
                    case 'C':
                        mC();
                        break;
                    case 'D':
                        mD();
                        break;
                    case 'E':
                        mE();
                        break;
                    case 'F':
                        mF();
                        break;
                    case 'G':
                        mG();
                        break;
                    case 'H':
                        mH();
                        break;
                    case 'I':
                        mI();
                        break;
                    case 'J':
                        mJ();
                        break;
                    case 'K':
                        mK();
                        break;
                    case 'L':
                        mL();
                        break;
                    case 'M':
                        mM();
                        break;
                    case 'N':
                        mN();
                        break;
                    case 'O':
                        mO();
                        break;
                    case 'P':
                        mP();
                        break;
                    case 'Q':
                        mQ();
                        break;
                    case 'R':
                        mR();
                        break;
                    case 'S':
                        mS();
                        break;
                    case 'T':
                        mT();
                        break;
                    case 'U':
                        mU();
                        break;
                    case 'V':
                        mV();
                        break;
                    case 'W':
                        mW();
                        break;
                    case 'X':
                        mX();
                        break;
                    case 'Y':
                        mY();
                        break;
                    case 'Z':
                        mZ();
                        break;
                    case ' ':
                        delay(wordMS);
                        break;
                }
                delay(charMS);
            }
        }
        static String SMS(String sms) {
            sms.toUpperCase();
            String output = "";
            for (int i = 0; i < sms.length(); i++) {
                char letter = sms[i];
                switch (letter) {
                    case 'A':
                        output += "2";
                        break;
                    case 'B':
                        output += "22";
                        break;
                    case 'C':
                        output += "222";
                        break;
                    case 'D':
                        output += "3";
                        break;
                    case 'E':
                        output += "33";
                        break;
                    case 'F':
                        output += "333";
                        break;
                    case 'G':
                        output += "4";
                        break;
                    case 'H':
                        output += "44";
                        break;
                    case 'I':
                        output += "444";
                        break;
                    case 'J':
                        output += "5";
                        break;
                    case 'K':
                        output += "55";
                        break;
                    case 'L':
                        output += "555";
                        break;
                    case 'M':
                        output += "6";
                        break;
                    case 'N':
                        output += "66";
                        break;
                    case 'O':
                        output += "666";
                        break;
                    case 'P':
                        output += "7";
                        break;
                    case 'Q':
                        output += "77";
                        break;
                    case 'R':
                        output += "777";
                        break;
                    case 'S':
                        output += "7777";
                        break;
                    case 'T':
                        output += "8";
                        break;
                    case 'U':
                        output += "88";
                        break;
                    case 'V':
                        output += "888";
                        break;
                    case 'W':
                        output += "9";
                        break;
                    case 'X':
                        output += "99";
                        break;
                    case 'Y':
                        output += "999";
                        break;
                    case 'Z':
                        output += "9999";
                        break;
                    case ' ':
                        output += "0";
                        break;
                }
            }
        }
    private:
        static void mA() {
            Dot();
            Dash();
        };
        static void mB() {
            Dash();
            Dot();
            Dot();
            Dot();
        };
        static void mC() {
            Dash();
            Dot();
            Dash();
            Dot();
        };
        static void mD() {
            Dash();
            Dot();
            Dot();
        };
        static void mE() {
            Dot();
        };
        static void mF() {
            Dot();
            Dot();
            Dash();
            Dot();
        };
        static void mG() {
            Dash();
            Dash();
            Dot();
        };
        static void mH() {
            Dot();
            Dot();
            Dot();
            Dot();
        };
        static void mI() {
            Dot();
            Dot();
        };
        static void mJ() {
            Dot();
            Dash();
            Dash();
            Dash();
        };
        static void mK() {
            Dash();
            Dot();
            Dash();
        };
        static void mL() {
            Dot();
            Dash();
            Dot();
            Dot();
        };
        static void mM() {
            Dash();
            Dash();
        };
        static void mN() {
            Dash();
            Dot();
        };
        static void mO() {
            Dash();
            Dash();
            Dash();
        };
        static void mP() {
            Dot();
            Dash();
            Dash();
            Dot();
        };
        static void mQ() {
            Dash();
            Dash();
            Dot();
            Dash();
        };
        static void mR() {
            Dot();
            Dash();
            Dot();
        };
        static void mS() {
            Dot();
            Dot();
            Dot();
        };
        static void mT() {
            Dash();
        };
        static void mU() {
            Dot();
            Dot();
            Dash();
        };
        static void mV() {
            Dot();
            Dot();
            Dot();
            Dash();
        };
        static void mW() {
            Dot();
            Dash();
            Dash();
        };
        static void mX() {
            Dash();
            Dot();
            Dot();
            Dash();
        };
        static void mY() {
            Dash();
            Dot();
            Dash();
            Dash();
        };
        static void mZ() {
            Dash();
            Dash();
            Dot();
            Dot();
        };
};

/*Keypad config*/
const int ROW_NUM = 4;
const int COLUMN_NUM = 4;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //Row pins
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //Column pins
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
//Keyword config n' stuff
String keyword = "THIS IS PEQUOD"; //Actual keyword you have to get
String solution = "";
String input = "";
bool solved = false;
//Unity Main()
void setup() {
    pinMode(pin, OUTPUT);
    Serial.begin(9600); //only for debug!!!
    solution = LED::SMS(keyword);
}
//Unity Update()
void loop() {
    char key = keypad.getKey();
    if (key) {
        Serial.println(key); //only for debug!!!
    }
    if (key && key != '*' && key != '#' && !solved) {
        input += key;
        if (input == solution) {
            solved = true;
        }
    }
    if (solved) {
        Dot();
    } else {
        if (key == '#') {
            LED::Translate(keyword); //echoes encrypted keyword
        }
        if (key == '*'){
            input = ""; //resets input
        }
    }
}