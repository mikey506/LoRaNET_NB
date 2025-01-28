#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Tetris game variables
const int gridWidth = 10;
const int gridHeight = 20;
int grid[gridWidth][gridHeight] = {0}; // 0 = empty, 1 = filled

// Tetromino shapes
const int tetrominos[7][4][4] = {
  { {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} }, // I
  { {0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0} }, // O
  { {0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0} }, // T
  { {0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0} }, // S
  { {0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0} }, // Z
  { {0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,1,0} }, // L
  { {0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0} }  // J
};

int currentTetromino[4][4] = {0};
int currentX = gridWidth / 2 - 2;
int currentY = 0;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Initialize the grid
  for (int x = 0; x < gridWidth; x++) {
    for (int y = 0; y < gridHeight; y++) {
      grid[x][y] = 0;
    }
  }

  // Randomly select the first tetromino
  randomSeed(analogRead(0));
  selectNextTetromino();
}

void loop() {
  drawGrid();
  updateGame();
  delay(500); // Game speed
}

void selectNextTetromino() {
  int randomIndex = random(7);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      currentTetromino[i][j] = tetrominos[randomIndex][i][j];
    }
  }
  currentX = gridWidth / 2 - 2;
  currentY = 0;
}

void drawGrid() {
  tft.fillScreen(TFT_BLACK);
  for (int x = 0; x < gridWidth; x++) {
    for (int y = 0; y < gridHeight; y++) {
      if (grid[x][y] == 1) {
        tft.fillRect(x * 12, y * 12, 12, 12, TFT_WHITE);
      }
    }
  }

  // Draw current tetromino
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentTetromino[i][j] == 1) {
        tft.fillRect((currentX + i) * 12, (currentY + j) * 12, 12, 12, TFT_RED);
      }
    }
  }
}

void updateGame() {
  if (canMove(0, 1)) {
    currentY++;
  } else {
    mergeTetromino();
    clearLines();
    selectNextTetromino();
    if (!canMove(0, 0)) {
      // Game over
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString("Game Over", 50, 100, 4);
      while (1);
    }
  }
}

bool canMove(int offsetX, int offsetY) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentTetromino[i][j] == 1) {
        int newX = currentX + i + offsetX;
        int newY = currentY + j + offsetY;
        if (newX < 0 || newX >= gridWidth || newY >= gridHeight || (newY >= 0 && grid[newX][newY] == 1)) {
          return false;
        }
      }
    }
  }
  return true;
}

void mergeTetromino() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentTetromino[i][j] == 1) {
        grid[currentX + i][currentY + j] = 1;
      }
    }
  }
}

void clearLines() {
  for (int y = gridHeight - 1; y >= 0; y--) {
    bool lineFull = true;
    for (int x = 0; x < gridWidth; x++) {
      if (grid[x][y] == 0) {
        lineFull = false;
        break;
      }
    }
    if (lineFull) {
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < gridWidth; x++) {
          grid[x][yy] = grid[x][yy - 1];
        }
      }
      for (int x = 0; x < gridWidth; x++) {
        grid[x][0] = 0;
      }
      y++; // Check the same line again
    }
  }
}
