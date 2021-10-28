#include <Arduino.h>
#include <FS.h>
#include <PxMatrix.h>
#include <GifPlayer.h>
GifPlayer gifPlayer;
#include <Ticker.h>
Ticker display_ticker;


uint8_t display_draw_time = 10; //30-70 is usually fine

String file_name = "/323.gif";

void display_updater()
{
  display.display(display_draw_time);
}

void display_update_enable(bool is_enable)
{
  if (is_enable)
    display_ticker.attach(0.002, display_updater);
  else
    display_ticker.detach();
}

void setup()
{
  Serial.begin(115200);
  display.begin(16);
  display.setBrightness(40);
  display.clearDisplay();
  display.setColorOffset(0,0,60);
  display_update_enable(true);
  if(SPIFFS.begin()){
    Serial.println("");
    Serial.println("SPIFFS文件系统开始");
  } else {
    Serial.println("SPIFFS文件系统开始启动失败");
  }
}


void loop(){
  if(Serial.available()>0){
    file_name = Serial.readString();
  }
  uint32_t result;
  File imageFile = SPIFFS.open(file_name, "r");
  if (!imageFile) {
      Serial.println("Failed to open");
      return;
  }
  
  gifPlayer.setFile(imageFile);
  if (!gifPlayer.parseGifHeader()) {
    imageFile.close();
    Serial.println("No gif header");
    return;
  }
  display.clearDisplay();
  gifPlayer.parseLogicalScreenDescriptor();
  gifPlayer.parseGlobalColorTable();
  do {
    gifPlayer.drawFrame();
    result = gifPlayer.drawFrame();
    display.showBuffer();
  } while (result != ERROR_FINISHED);
  imageFile.seek(0);
  Serial.println("Gif播放完成");
  
}