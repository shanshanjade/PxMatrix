# PxMatrix 使用文档

## 准备材料

### 参考文献资料

[instructable PxMatrix项目](https://www.instructables.com/RGB-LED-Matrix-With-an-ESP8266/)

### Arduino库

- arduino库中下载PxMatrix.h库 
- arduino库中下载GifDecoder库
- arduino库中下载Ticker库

### 硬件

- ESP8266板子一块
- 64*32 P3室内板一块
  - 16扫模式
  - 

### 接线图

<img src="https://content.instructables.com/ORIG/F13/DT7V/JH0TS7PZ/F13DT7VJH0TS7PZ.png?auto=webp&frame=1&width=1024&fit=bounds&md=357df19af4fdc44c6a3cd6957bd8fc2d"  />

## 库的使用方法

### PxMatrix库的使用

1. 包含库

```c++
#include <PxMatrix.h>
```

2. 定义引脚

```c++
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2
```

3. 定义宽高

```c++
#define matrix_width 32
#define matrix_height 16
```

4. 包含ticker库并创建 display_ticker 对象

```c++
#include <Ticker.h>
Ticker display_ticker;
```

6. 定义显示更新时间

```c++
uint8_t display_draw_time=60; //30-70 is usually fine 其实这个值越小越好,但esp8266处理能力有限,可以大概定在15-30ms左右
```

7. 创建display对象

```c++
//PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
//PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);
```

8.  自动更新显示画面函数 & 是否开启自动更新函数

```c++
void display_updater()
{
  display.display(display_draw_time);
}
void display_update_enable(bool is_enable)
{
  if (is_enable)
    display_ticker.attach(0.004, display_updater);
  else
    display_ticker.detach();
}
```

9. setup函数中

```
display.begin(8);
display.begin(16);
display.begin(32);
```

10. display对象继承自Adafruit_GFX, 只要会使用Adafruit_GFX就可以正常使用display对象

```c++
display.clearDisplay(); //清屏方法和Adafruit_GF稍有不同
yield(); //在长时间的非loop循环中喂狗


```











### GifDecoder库的使用






