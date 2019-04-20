// Pin numbers for the switches. They are pulled up, therefore you should connect the other lead of the switch to ground.
int left = 12;
int right = 11;
int up =  10;
int down = 9;

// Variables storing the players coordinates
short player_x;
short player_y;
short coin_x;
short coin_y;

const short board_size = 8; // Size of the board, can be customizable
int score = 0; // Variable holding the current score
char board[board_size][board_size]; // Game board

// Functions declarations
void clearBoard();
void printBoard();
int getKeyPress();
void handleMove();
bool checkIfScored();
void placeNewCoin();

void setup() {
  // Declaring the pins as inputs and pulling them up
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  Serial.begin(9600); // Starting the serial monitor
  // Placing the player in the middle of the map
  player_x = board_size / 2;
  player_y = board_size / 2;
  placeNewCoin();  // Placing the coin on the map randomly
  clearBoard(); // Initializing the board
}

void loop() {
  printBoard();
  int keyPress = getKeyPress();
  handleMove(keyPress);
  bool hasScored = checkIfScored();
  if(hasScored){ // If the player has scored, grants a point and places a new coin
    score++;
    placeNewCoin();
  }
  delay(200); // Dunno why it needs that much as the debounce is normally around 50ms, but less than that and it goes two cells in one press
}

// Loop which waits until the player presses a button and then returns the key code
int getKeyPress(){
  while(true){
    if(digitalRead(up) == LOW){
      return up;
    }
    else if(digitalRead(down) == LOW){
      return down;
    }
    else if(digitalRead(left) == LOW){
      return left;
    }
    else if(digitalRead(right) == LOW){
      return right;
    }
  }
}

// Checks if the player moved to the same coordinates as the coins
bool checkIfScored(){
  if(player_x == coin_x && player_y == coin_y){
    return true;
  }
  return false;
}

// Places a coin randomly other than on the player (shouldn't get stuck, but if this ever loops infinitely I'm gonna become a priest)
void placeNewCoin(){
  while(true){
    int new_x = random(0, board_size - 1);
    int new_y = random(0, board_size - 1);
    if(!(player_x == new_x && player_y == new_y)){ // If the coordinates are not the same as the players location
      coin_x = new_x;
      coin_y = new_y;
      return;
    }
  }
}

// Handles the movement of the player
void handleMove(int moveDirection){
  if(moveDirection == up){
    if(player_y > 0){ // Check so the player can't go further than to the bounds of the board, in other directions respectively
      player_y -= 1;
    }
  }
  else if(moveDirection == down){
    if(player_y < board_size - 1){
      player_y += 1;
    }
  }
  else if(moveDirection == left){
    if(player_x > 0){
      player_x -= 1;
    }
  }
  else if(moveDirection == right){
    if(player_x < board_size - 1){
      player_x += 1;
    }
  }
}

// Prints the board on the serial monitor
void printBoard(){
  Serial.print("\n\nScore: ");
  Serial.print(score);
  Serial.print("\n");
  clearBoard();
  board[player_x][player_y] = '#';
  board[coin_x][coin_y] = '$';
  for(int i = 0; i < board_size; i++){
    for(int j = 0; j < board_size; j++){
      Serial.print(board[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
}

// Fills the board with asterisks
void clearBoard(){
  for(int i = 0; i < board_size; i++){
    for(int j = 0; j < board_size; j++){
      board[i][j] = '*';
    }
  }
}


