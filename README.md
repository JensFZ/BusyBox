# BusyBox

In diesen Projekt geht es darum, dass man einen Status einer Website abfragt und, je nach rückgabe, eine grüne oder rote LED Schaltet.

der Web API Code wird demnächst auch hier noch hochgeladen

<img src="https://github.com/JensFZ/BusyBox/raw/master/KiCad/BusyBox.png" width="400">

## Einrichtung Arduino IDE

- zusützliche Boardverwalter URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- über den Boardverwalter nun das Board "esp8266" suchen und installieren
- Als Board nun über "Werkzeuge" -> "Board" -> "ESP8266 Boards" -> "NodeMCU 1.0 (ESP-12E Module)" auswählen
- Uploadspeed auf 115200 stellen
- Port auf den entsprechenden COM Port stellen

## Verwendete Hardware
- 1x NodeMCU Lua Amica Modul V2 ESP8266 ESP-12F
- 1x LED Green
- 1x LED Red
- 1x DIP-Switch 2 Slide
- 5x 1k Wiederstand
- optional LCD 16x2 i2c


## Contributing
Pull requests sind wilkommen. Bei größeren Änderungen eröffnen Sie bitte zunächst ein Issue, um zu besprechen, was Sie ändern möchten.

## License
[MIT](https://choosealicense.com/licenses/mit/)
