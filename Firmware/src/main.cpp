#include <EEPROM.h>
#include <Wire.h>
#include <DisplayImages.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SW 7
#define ENC_A 3
#define ENC_B 2

// LED Pins (Order: AUX, USB, BT, OPT, WIFI, HDMI)
const int ledPins[] = {4, 5, 6, 9, 10, 11};

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define FRAME_DELAY (42)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))

const unsigned char *allIcons[6] = {icon_aux, icon_usb, icon_bt, icon_optical, icon_wifi, icon_hdmi};
const char *modeNames[] = {"AUX", "USB AUDIO", "BLUETOOTH", "OPTICAL", "WI-FI", "HDMI ARC"};
const unsigned char *allScreens[6] = {
    epd_bitmap_screen_AUX,
    epd_bitmap_screen_USB,
    epd_bitmap_screen_Bluetooth,
    epd_bitmap_screen_Optical,
    epd_bitmap_screen_Airplay,
    epd_bitmap_screen_HDMI};

// --- VARIABLES ---
int selectedItem = 0;
int activeMode = 0;
int topVisibleItem = 0;
int lastClk;
int menu_mem = 0;
bool isMenuOpen = true;

int frame = 0;
byte delay_boot_menu = 24 * 3; // in 24 is equal to 1 sec

void boot_screen()
{
  display.clearDisplay();
  display.drawBitmap(40, 10, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}

void handleScrolling()
{
  if (selectedItem < topVisibleItem)
  {
    topVisibleItem = selectedItem;
  }
  else if (selectedItem >= topVisibleItem + 3)
  {
    topVisibleItem = selectedItem - 2;
  }
  if (selectedItem == 0)
    topVisibleItem = 0;
  if (selectedItem == 5)
    topVisibleItem = 3;
}

void drawMenu()
{
  display.clearDisplay();
  display.drawBitmap(120, 0, bg_scrollbar, 8, 64, WHITE);
  int scrollY = map(selectedItem, 0, 5, 0, 56);
  display.fillRect(125, scrollY, 3, 8, WHITE);

  for (int i = 0; i < 3; i++)
  {
    int index = topVisibleItem + i;

    if (index <= 5)
    {
      int yPos = i * 21;

      if (index == selectedItem)
      {
        display.drawBitmap(0, yPos, bg_item_sel, 128, 21, WHITE);
        display.drawBitmap(4, yPos + 2, allIcons[index], 18, 16, WHITE);
        display.setTextColor(WHITE);
      }
      else
      {
        display.drawBitmap(4, yPos + 2, allIcons[index], 18, 16, WHITE);
        display.setTextColor(WHITE);
      }

      display.setTextSize(1);
      display.setCursor(28, yPos + 6);
      display.print(modeNames[index]);

      if (index == activeMode)
      {
        display.setCursor(100, yPos + 6);
        display.print("*");
      }
    }
  }
  display.display();
}

void drawScreen()
{
  display.clearDisplay();
  display.drawBitmap(0, 0, allScreens[activeMode], 128, 64, WHITE);
  display.display();
}

void updateLEDs(int active)
{
  for (int i = 0; i < 6; i++)
  {
    if (i == active)
      digitalWrite(ledPins[i], LOW);
    else
      digitalWrite(ledPins[i], HIGH);
  }
}

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(SW, INPUT_PULLUP);
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  for (int i = 0; i < 6; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }

  lastClk = digitalRead(ENC_A);

  activeMode = EEPROM.read(menu_mem);
  if (activeMode < 0 || activeMode > 5)
    activeMode = 0;

  selectedItem = activeMode;

  if (selectedItem > 1)
    topVisibleItem = selectedItem - 1;
  if (selectedItem == 5)
    topVisibleItem = 3;

  // updateLEDs(activeMode);

  isMenuOpen = false;
  // drawScreen();
  for (byte i = 0; i < delay_boot_menu; i++)
    boot_screen();

  display.clearDisplay();
  display.display();
}

void loop()
{
  int currentClk = digitalRead(ENC_A);
  if (currentClk != lastClk && currentClk == LOW)
  {
    if (isMenuOpen)
    {
      if (digitalRead(ENC_B) != currentClk)
      {
        selectedItem++;
        if (selectedItem > 5)
          selectedItem = 0;
      }
      else
      {
        selectedItem--;
        if (selectedItem < 0)
          selectedItem = 5;
      }
      handleScrolling();
      drawMenu();
    }
    else
    {
      isMenuOpen = true;
      selectedItem = activeMode;
      handleScrolling();
      drawMenu();
    }
  }
  lastClk = currentClk;

  if (digitalRead(SW) == LOW)
  {
    delay(50);
    while (digitalRead(SW) == LOW)
      ;

    if (isMenuOpen)
    {
      activeMode = selectedItem;
      EEPROM.write(menu_mem, activeMode);
      updateLEDs(activeMode);

      isMenuOpen = false;
      drawScreen();
    }
    else
    {
      isMenuOpen = true;
      selectedItem = activeMode;
      handleScrolling();
      drawMenu();
    }
  }
}