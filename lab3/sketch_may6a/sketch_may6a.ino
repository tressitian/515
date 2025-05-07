#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sorting_hat_model.h"  // ML Model

// OLED 设置
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 按钮引脚定义
#define BUTTON_A 32
#define BUTTON_B 33
#define BUTTON_C 25
#define BUTTON_D 26

// 题目与选项
const char* questions[] = {
  "1. What do you value?",
  "2. What to do if someone cheats?",
  "3. Favorite subject?",
  "4. How do you face challenges?",
  "5. How do friends describe you?",
  "6. What to do with a mystery book?",
  "7. Preferred pet?",
  "8. How do you solve problems?",
  "9. What kind of friends do you like?",
  "10. Dream career?"
};

const char* options[][4] = {
  {"A) Bravery", "B) Loyalty", "C) Intelligence", "D) Ambition"},
  {"A) Call them out", "B) Let them be", "C) Inform teacher", "D) Gain from it"},
  {"A) Defense Arts", "B) Herbology", "C) Charms", "D) Potions"},
  {"A) Face head-on", "B) Team up", "C) Plan first", "D) Outsmart it"},
  {"A) Bold", "B) Kind", "C) Smart", "D) Resourceful"},
  {"A) Read it now", "B) Check safety", "C) Study it", "D) Use for gain"},
  {"A) Owl", "B) Toad", "C) Cat", "D) Phoenix"},
  {"A) Act fast", "B) Compromise", "C) Analyze first", "D) Outsmart"},
  {"A) Adventurous", "B) Loyal", "C) Thoughtful", "D) Powerful"},
  {"A) Auror", "B) Healer", "C) Scholar", "D) Minister"}
};

int responses[10] = {0};
int questionIndex = 0;

// ML 模型
Eloquent::ML::Port::DecisionTree clf;

void setup() {
  Serial.begin(115200);

  // OLED 初始化
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Sorting Hat Ready!");
  display.display();
  delay(2000);

  // 初始化按钮
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  // 显示第一题
  showQuestion();
}

void loop() {
  checkButtons();
}

void showQuestion() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(questions[questionIndex]);

  for (int i = 0; i < 4; i++) {
    display.setCursor(10, 18 + (i * 10));
    display.println(options[questionIndex][i]);
  }

  display.display();
}

void checkButtons() {
  if (digitalRead(BUTTON_A) == LOW) {
    responses[questionIndex] = 1;
    Serial.println("A pressed");
    delay(200);
    nextQuestion();
  }
  else if (digitalRead(BUTTON_B) == LOW) {
    responses[questionIndex] = 2;
    Serial.println("B pressed");
    delay(200);
    nextQuestion();
  }
  else if (digitalRead(BUTTON_C) == LOW) {
    responses[questionIndex] = 3;
    Serial.println("C pressed");
    delay(200);
    nextQuestion();
  }
  else if (digitalRead(BUTTON_D) == LOW) {
    responses[questionIndex] = 4;
    Serial.println("D pressed");
    delay(200);
    nextQuestion();
  }
}

void nextQuestion() {
  questionIndex++;
  if (questionIndex < 10) {
    showQuestion();
  } else {
    classifyHouse();
  }
}

void classifyHouse() {
  display.clearDisplay();
  display.setCursor(10, 10);
  display.setTextSize(1);
  display.println("Sorting...");
  display.display();
  delay(1000);

  float features[10];
  for (int i = 0; i < 10; i++) {
    features[i] = (float)responses[i];
  }

  int house = clf.predict(features);

  display.clearDisplay();
  display.setCursor(10, 10);
  display.setTextSize(2);
  display.print("House: ");
  switch (house) {
    case 0: display.println("Gryffindor"); break;
    case 1: display.println("Hufflepuff"); break;
    case 2: display.println("Ravenclaw"); break;
    case 3: display.println("Slytherin"); break;
  }
  display.display();

  Serial.print("Predicted House: ");
  switch (house) {
    case 0: Serial.println("Gryffindor"); break;
    case 1: Serial.println("Hufflepuff"); break;
    case 2: Serial.println("Ravenclaw"); break;
    case 3: Serial.println("Slytherin"); break;
  }
}