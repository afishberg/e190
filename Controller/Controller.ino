
// pins
// buttons (8)
const int pin_lstick_b = 2;
const int pin_rstick_b = 3;
const int pin_lup = 4;
const int pin_ldown = 5;
const int pin_rup = 6;
const int pin_rdown = 7;
const int pin_lbump = 8;
const int pin_rbump = 9;

// switch (1)
const int pin_swtch = 10;

// analog (6)
const int pin_lstick_x = A0;
const int pin_lstick_y = A1;
const int pin_rstick_x = A2;
const int pin_rstick_y = A3;
const int pin_lpotent = A4;
const int pin_rpotent = A5;

// states
const int state_analog_length = 6;
const int state_digital_length = 9;
const int state_length = state_analog_length + state_digital_length;

int state[state_length]; // current state
int pstate[state_length]; // previous state

// state locs
const int lstick_x = 0;
const int lstick_y = 1;
const int rstick_x = 2;
const int rstick_y = 3;
const int lpotent = 4;
const int rpotent = 5;
const int lstick_b = 6;
const int rstick_b = 7;
const int lup = 8;
const int ldown = 9;
const int rup = 10;
const int rdown = 11;
const int lbump = 12;
const int rbump = 13;
const int swtch = 14;

// keybindings
char analog_bindings[][4] = {
{'w', 's', 'd', 'a'},
{'w', 's', 'd', 'a'}
};

char bindings[][15] = {
{
  ' ', ' ', ' ' , ' ' , ' ', ' ',
  0x81, '-', // stick
  '-', '-', // left
  'q', 'e', // right
  ' ', '[', // bump
  'I' // switch
},
{
  ' ', ' ', ' ' , ' ' , ' ', ' ',
  '-', '-', // stick
  'q', '3', // left
  '[', 'e', // right
  0x81, ' ', // bump
  'I' // switch
}
};

int kb = 0;



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pin_lstick_b, INPUT_PULLUP);
  pinMode(pin_rstick_b, INPUT_PULLUP);
  pinMode(pin_lup, INPUT_PULLUP);
  pinMode(pin_ldown, INPUT_PULLUP);
  pinMode(pin_rup, INPUT_PULLUP);
  pinMode(pin_rdown, INPUT_PULLUP);
  pinMode(pin_lbump, INPUT_PULLUP);
  pinMode(pin_rbump, INPUT_PULLUP);

  pinMode(pin_swtch, INPUT_PULLUP);

  pinMode(pin_lstick_x, INPUT);
  pinMode(pin_lstick_y, INPUT);
  pinMode(pin_rstick_x, INPUT);
  pinMode(pin_rstick_y, INPUT);
  pinMode(pin_lpotent, INPUT);
  pinMode(pin_rpotent, INPUT);

  init_state();
  Keyboard.begin();
  Mouse.begin();
}

void init_state() {
  for (int i = 0; i < state_analog_length; i++) {
    state[i] = 512;
  }
  for (int i = state_analog_length; i < state_length; i++) {
    state[i] = HIGH;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  //  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  readState();
  printState();
  analogControl();
  buttonControl();
  delay(10);        // delay in between reads for stability
}

void setPState() {
  for (int i = 0; i < state_length; i++) {
    pstate[i] = state[i];
  }
}

void readState() {
  setPState();

  state[lstick_x] = analogRead(pin_lstick_x);
  state[lstick_y] = analogRead(pin_lstick_y);
  state[rstick_x] = analogRead(pin_rstick_x);
  state[rstick_y] = analogRead(pin_rstick_y);
  state[lpotent] = analogRead(pin_lpotent);
  state[rpotent] = analogRead(pin_rpotent);

  state[lstick_b] = digitalRead(pin_lstick_b);
  state[rstick_b] = digitalRead(pin_rstick_b);
  state[lup] = digitalRead(pin_lup);
  state[ldown] = digitalRead(pin_ldown);
  state[rup] = digitalRead(pin_rup);
  state[rdown] = digitalRead(pin_rdown);
  state[lbump] = digitalRead(pin_lbump);
  state[rbump] = digitalRead(pin_rbump);
  state[swtch] = digitalRead(pin_swtch);
}

void printState() {
  Serial.print("[.");
  for (int i = 0; i < 15; i++) {
    Serial.print(state[i]);
    Serial.print(".");
  }
  Serial.println("]");
}

void analogControl() {
  // left stick
  int dir, pdir;
  dir = getDir(lstick_x);
  pdir = getPDir(lstick_x);
  
  if (hasMoved(lstick_x)) {
    if (pdir > 0) {
      Keyboard.release(analog_bindings[kb][2]);
    } else if (pdir < 0) {
      Keyboard.release(analog_bindings[kb][3]);      
    }
    
    if (dir > 0) {
      Keyboard.press(analog_bindings[kb][2]);
    } else if (dir < 0) {
      Keyboard.press(analog_bindings[kb][3]);      
    }
  }
  
  dir = getDir(lstick_y);
  pdir = getPDir(lstick_y);
  
  if (hasMoved(lstick_y)) {
    if (pdir > 0) {
      Keyboard.release(analog_bindings[kb][0]);
    } else if (pdir < 0) {
      Keyboard.release(analog_bindings[kb][1]);      
    }
    
    if (dir > 0) {
      Keyboard.press(analog_bindings[kb][0]);
    } else if (dir < 0) {
      Keyboard.press(analog_bindings[kb][1]);      
    }
  }
  
  // right stick
  double scaler = pow(2, scale(state[lpotent]) / 2.);
  Mouse.move(
  scale(state[rstick_x]) * scaler, // 3
  -scale(state[rstick_y]) * scaler // 1.5
  );
}

void buttonControl() {
  kb = (state[swtch] ? 1 : 0);
  for (int i = lstick_b; i <= rbump; i++) {
//    if (state[swtch]) {
      if(wasPressed(i)) {
        if (bindings[kb][i] == '[') {
          Mouse.press();
        } else {
          Keyboard.press(bindings[kb][i]);
        }
      } else if (wasReleased(i)) {
         if (bindings[kb][i] == '[') {
          Mouse.release();
        } else {
          Keyboard.release(bindings[kb][i]);
        }
      }
}

boolean wasPressed(int i) {
  return state[i] == LOW && pstate[i] == HIGH;
}


boolean wasReleased(int i) {
  return state[i] == HIGH && pstate[i] == LOW;
}


boolean isHeld(int i) {
  return state[i] == LOW;
}

int getDir(int i) {
  return calcDir(state[i]);
}

int getPDir(int i) {
  return calcDir(pstate[i]);
}

int calcDir(int analog) {
  int scaled = scale(analog);
  if (scaled > 0) {
    return 1;
  } else if (scaled < 0) {
    return -1;
  } else {
    return 0;
  }
}

boolean hasMoved(int i) {
  return getDir(i) != getPDir(i);
}


int scale(int i) {
  if (i > 950) {
    return 5; // 950 - 1023
  } else if (i > 877) {
    return 4; // 877 - 950
  } else if (i > 804) {
    return 3; // 804 - 877
  } else if (i > 731) {
    return 2; // 731 - 804
  } else if (i > 658) {
    return 1; // 658 - 731
  } else if (i > 365) {
    return 0; // 365 - 658
  } else if (i > 292) {
    return -1; // 292 - 365
  } else if (i > 219) {
    return -2; // 219 - 292
  } else if (i > 146) {
    return -3; // 146 - 219
  } else if (i > 73) {
    return -4; // 73 - 146
  } else {
    return -5; // 0 - 73
  }
}

