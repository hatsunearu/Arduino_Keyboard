// Arduino Keyboard, diode
// hatsunearu
// http://www.github.com/hatsunearu/Arduino_Keyboard

//Start user definables

//number of rows and columns
const int ROWS = 3;
const int COLS = 3;

//first pin number of rows -- ROW_STARTPIN + ROWS - 1 will be the last pin consumed
const int ROW_STARTPIN = 3;
const int COL_STARTPIN = 6; 

//debounce timer, pushes within this ms will be ignored
const int DEBOUNCE_DELAY = 15;

int debounce_row = -1;
int debounce_col = -1;
long debounce_lasttime = 0;

void setup() {	

  //init everything to low
  for (int i=COL_STARTPIN; i < COL_STARTPIN + COLS; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for (int j=ROW_STARTPIN; j < ROW_STARTPIN + ROWS; j++) {
    pinMode(j, OUTPUT);
    digitalWrite(j, LOW);
  }

}

void loop() {

  sweepMatrix();

}

void sweepMatrix() {

  //set columns as input with pullup
  for(int i=COL_STARTPIN; i < COL_STARTPIN + COLS; i++) {

    pinMode(i, INPUT_PULLUP);

    //sweep row to check if switch has pulled the excitation pin low
    for (int j=ROW_STARTPIN; j < ROW_STARTPIN + ROWS; j++) {

      pinMode(j, OUTPUT);
      digitalWrite(j, LOW);

      if (digitalRead(i) == LOW && (j != debounce_row || i != debounce_col || mills() - debounce_lasttime > DEBOUNCE_DELAY)) {

        debounce_row = j;
        debounce_col = i;
        debounce_lasttime = millis();

        //check if inverse makes the pin pull low
        pinMode(j, INPUT_PULLUP); 
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);

        //reverse is true, non-dioded switch
        if (digitalRead(j) == LOW) {
          buttonAction(2 * (COLS * (j - ROW_STARTPIN) + (i - COL_STARTPIN)) + 1);
          return;
        }
        //reverse is false, dioded switch
        buttonAction(2 * (COLS * (j - ROW_STARTPIN) + (i - COL_STARTPIN)));
        return;

      }

    }
    
  }

}

void buttonAction(int buttonid) {

  //do cool stuff
  Serial.print("Button: ");
  Serial.println(buttonid);

}
