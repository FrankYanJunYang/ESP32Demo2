#include <TFT_eSPI.h> // 使用 TFT_eSPI 库
#include <SPI.h>

// 定义屏幕宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

// 定义游戏网格大小
#define GRID_SIZE 8
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)

// 初始化 TFT_eSPI 对象
TFT_eSPI tft = TFT_eSPI();

// 贪吃蛇的状态
int snakeX[100], snakeY[100]; // 贪吃蛇的身体坐标
int snakeLength = 3;          // 初始长度
int foodX, foodY;             // 食物坐标
int direction = 0;            // 方向: 0=右, 1=下, 2=左, 3=上

// 定义控制方向的引脚
#define UP_BUTTON 2    // GPIO 2 控制向上
#define DOWN_BUTTON 3  // GPIO 3 控制向下
#define LEFT_BUTTON 4  // GPIO 4 控制向左
#define RIGHT_BUTTON 5 // GPIO 5 控制向右

// 生成食物
void spawnFood() {
  foodX = random(0, GRID_WIDTH);
  foodY = random(0, GRID_HEIGHT);
}

// 初始化游戏
void initGame() {
  snakeLength = 3;
  snakeX[0] = GRID_WIDTH / 2;
  snakeY[0] = GRID_HEIGHT / 2;
  for (int i = 1; i < snakeLength; i++) {
    snakeX[i] = snakeX[0] - i;
    snakeY[i] = snakeY[0];
  }
  spawnFood();
}

// 绘制网格
void drawGrid() {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < snakeLength; i++) {
    tft.fillRect(snakeX[i] * GRID_SIZE, snakeY[i] * GRID_SIZE, GRID_SIZE, GRID_SIZE, TFT_GREEN);
  }
  tft.fillRect(foodX * GRID_SIZE, foodY * GRID_SIZE, GRID_SIZE, GRID_SIZE, TFT_RED);
}

// 更新贪吃蛇状态
void updateSnake() {
  // 移动身体
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // 移动头部
  if (direction == 0) snakeX[0]++;
  if (direction == 1) snakeY[0]++;
  if (direction == 2) snakeX[0]--;
  if (direction == 3) snakeY[0]--;

  // 检查是否吃到食物
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    spawnFood();
  }

  // 检查是否撞墙或撞自己
  if (snakeX[0] < 0 || snakeX[0] >= GRID_WIDTH || snakeY[0] < 0 || snakeY[0] >= GRID_HEIGHT) {
    initGame(); // 游戏结束，重新开始
  }
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      initGame(); // 游戏结束，重新开始
    }
  }
}

// 处理按键输入
void handleInput() {
  if (digitalRead(UP_BUTTON) == LOW && direction != 1) direction = 3;    // 上
  if (digitalRead(DOWN_BUTTON) == LOW && direction != 3) direction = 1;  // 下
  if (digitalRead(LEFT_BUTTON) == LOW && direction != 0) direction = 2;  // 左
  if (digitalRead(RIGHT_BUTTON) == LOW && direction != 2) direction = 0; // 右
}

void setup() {
  // 初始化串口
  Serial.begin(115200);

  // 初始化屏幕
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // 初始化按键引脚
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // 初始化游戏
  initGame();
}

void loop() {
  handleInput();   // 处理输入
  updateSnake();   // 更新贪吃蛇状态
  drawGrid();      // 绘制游戏画面
  delay(200);      // 控制游戏速度
}