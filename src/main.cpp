#include <WiFi.h>

// Wi-Fi 网络名称和密码
const char* ssid = "跞轩之家";
const char* password = "13763333092";

// 定义 LED 引脚
const int ledPin1 = 2; // LED1 引脚
const int ledPin2 = 4; // LED2 引脚

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  delay(100);

  // 初始化 LED 引脚为输出模式
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // 开始连接 Wi-Fi
  Serial.println("正在连接到 Wi-Fi...");
  WiFi.begin(ssid, password);

  // 等待连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // 连接成功
  Serial.println("\nWi-Fi 已连接!");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 轮流点亮 LED1 和 LED2
  digitalWrite(ledPin1, HIGH); // 点亮 LED1
  digitalWrite(ledPin2, LOW);  // 熄灭 LED2
  delay(500);                  // 延迟 500 毫秒

  digitalWrite(ledPin1, LOW);  // 熄灭 LED1
  digitalWrite(ledPin2, HIGH); // 点亮 LED2
  delay(500);                  // 延迟 500 毫秒
}