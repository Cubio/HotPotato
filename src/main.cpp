#include <M5StickCPlus2.h>
#include <M5GFX.h>
#include <PlayRtttl.hpp>
#include "xbm.h" // Sketch tab header for xbm images

bool endgame = false;

// beeper pin
const int TONE_PIN = 2;

// Calculate arraySize for Songs.
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

// No idea, but this need to do that game works. Just beep sound.
char Start[] = {"Beep:d=16,o=6,b=400:32d"};

// End song, when game end. Times up.
char endSong[] = {"Cat:d=16,o=6,b=95:29d,25d#,26d,27d#,32d,32d#,32d,32d#"};

// Songs
String SONGS[] = {
    "PacMan:d=16,o=6,b=140:b5,b,f#,d#,8b,8d#,c,c7,g,f,8c7,8e,b5,b,f#,d#,8b,8d#,32d#,32e,f,32f,32f#,g,32g,32g#,a,8b'",
    "TheSimpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6",
    "StarWars:d=32,o=5,b=45,l=2,s=N:p,f#,f#,f#,8b.,8f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,e6,8c#6",
    "dkong:d=4,o=5,b=160:2c,8d.,d#.,c.,16b,16c6,16b,16c6,16b,16c6,16b,16c6,16b,16c6,16b,16c6,16b,2c6",
    "Bond:d=4,o=5,b=320:c,8d,8d,d,2d,c,c,c,c,8d#,8d#,2d#,d,d,d,c,8d,8d,d,2d,c,c,c,c,8d#,8d#,d#,2d#,d,c#,c,c6,1b.,g,f,1g.",
    "ImperialMarch:d=4,o=5,b=100:e,e,e,8c,16p,16g,e,8c,16p,16g,e,p,b,b,b,8c6,16p,16g,d#,8c,16p,16g,e,8p",
    "WormsThe:d=4,o=6,b=125:8c5,8d5,e5,g5,g5,8f5,8e5,8d.5,16c5,8d5,8e5,d5,16p,8d5,8d.5,16c5,8d5,8e5,2c5,8d.5,16c5,8d5,8e5,d5,8c5,8d5,e5,g5,g5,8f5,8e5,8d.5,16c5,8d5,8e5,d5,16p,8d5,8d.5,16c5,8d5,8e5,2c5,8d.5,16c5,8d5,8e5,d5",
    "Zelda:d=4,o=6,b=120:8f5,8a5,b5,8f5,8a5,b5,8f5,8a5,8b5,8e,d,8b5,8c,8b5,8g5,2e5,8p,8d5,8e5,8g5,2e5,8p,8d5,8e5,f5,8g5,8a5,b5,8c,8b5,e5,8p,8d5,8c5,8f5,8e5,8g5,8f5,8a5,8g5,16a_5,16a5,16a5,16g5,2a5",
    "Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6",
    "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,2p,e,b,a,b,e6,2b.,2p,g6,f#6,e6,d6,e6,2b.,2p,g6,f#6,e6,d6,f#6,2b.,2p,e,b,a,b,d6,2b.,2p,e,b,a,b,e6,2b.,2p,e6,2b.",
    "KnightRider:d=4,o=5,b=125:16e,16p,16f,16e,16e,16p,16e,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16e,16p,16f,16e,16e,16p,16f,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d"};

// PickUp some song from array.
String randomSong()
{

  if (ARRAY_SIZE(SONGS) != 0)
  {
    int randomSong = random(0, ARRAY_SIZE(SONGS));
    return SONGS[randomSong]; // Return the song
  }
  else
  {
    Serial.print("Array is empty, error");
    return "";
  }
}

// Game
void hotpatatosGame()
{
  endgame = true;

  // Random time for gameing.
  long RandomGameDuration = random(8000, 30000);
  // Present millis, how long board has been running.
  long startTime = millis();
  long endTime = millis() + RandomGameDuration;
  Serial.print("Starting game");
  Serial.print(startTime);
  Serial.print(endTime);
  do
  {

    // Select some song.
    String SongTo = randomSong();
    char *asd = const_cast<char *>(SongTo.c_str());

    // Play song
    startPlayRtttlPGM(TONE_PIN, asd);
    while (updatePlayRtttl())
    {
      // Times UP end the game
      if (endTime < millis())
      {
        // Clear screen.
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        delay(1);

        // End image, just for fun.
        int x = (M5.Lcd.width() - BperunaWidth);
        int y = (M5.Lcd.height() - BperunaHeight);
        M5.Lcd.drawXBitmap(x, y, Bperuna, BperunaWidth, BperunaHeight, TFT_WHITE);

        Serial.print("Times up, game ower.");
        stopPlayRtttl();
        playRtttlBlocking(TONE_PIN, endSong);
        endgame = false;
        return;
      }
      // For changing song.
      delay(1);
    }

  } while (endgame);
  return;
}

void setup()
{

  // For debug
  Serial.begin(115200);
  delay(1000);

  auto cfg = M5.config();
  M5.begin(cfg);

  // Image
  int x = (M5.Lcd.width() - BAperunaWidth);
  int y = (M5.Lcd.height() - BAperunaHeight);
  M5.Lcd.drawXBitmap(x, y, BAperuna, BAperunaWidth, BAperunaHeight, TFT_WHITE);

  // Beep sound, no idea whay but then game work.
  playRtttlBlocking(TONE_PIN, Start);
}

void loop()
{
  M5.update();

  // IF Button has been pressed. Start the game.
  if (M5.BtnA.wasReleased())
  {

    // Just clear the screen.
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    delay(1);

    int x = (M5.Lcd.width() - BAperunaWidth);
    int y = (M5.Lcd.height() - BAperunaHeight);
    M5.Lcd.drawXBitmap(x, y, BAperuna, BAperunaWidth, BAperunaHeight, TFT_WHITE);
    Serial.print("HotHotPotato Game Starting");
    hotpatatosGame();
  }
}
