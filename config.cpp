#include "config.h"

//
//
//                 .--.            .--.
//         _     _ |__|      _.._  |__|
//   /\    \\   // .--.    .' .._| .--.
//   `\\  //\\ //  |  |    | '     |  |
//     \`//  \'/   |  |  __| |__   |  |
//      \|   |/    |  | |__   __|  |  |
//       '         |  |    | |     |  |
//                 |__|    | |     |__|
//                         | |
//                         | |
//                         |_|


char ssid[] = "marcia.net_enlaluna";
char pass[] = "Log_tePiacesse7No.Pasaran";

//  char ssid[] = "HANGAR_convidats";
//  char pass[] = "convidatsHANGAR";

uint8_t ip[4] ={192,168,0,10};

unsigned int outPort = 57120;          // remote port to receive OSC
unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)


//
//  .---.
//  |   | .--.               .
//  |   | |__|   .--./)    .'|
//  |   | .--.  /.''\\    <  |                .|
//  |   | |  | | |  | |    | |              .' |_
//  |   | |  |  \`-' /     | | .'''-.     .'     |        _
//  |   | |  |  /("'`      | |/.'''. \   '--.  .-'      .' |
//  |   | |  |  \ '---.    |  /    | |      |  |       .   | /
//  |   | |__|   /'""'.\   | |     | |      |  |     .'.'| |//
//  '---'       ||     ||  | |     | |      |  '.' .'.'.-'  /
//              \'. __//   | '.    | '.     |   /  .'   \_.'
//               `'---'    '---'   '---'    `'-'


//Pins for (lamps if any)
const bool HASLamps = 1;
bool hasLamps() { return HASLamps;}
uint8_t Lamps[LAMPS] = {13, 33, 32, 18, 16, 5};


//
//                                     _______
//  _________   _...._                 \  ___ `'.
//  \        |.'      '-.               ' |--.\  \
//   \        .'```'.    '.             | |    \  '
//    \      |       \     \    __      | |     |  '
//     |     |        |    | .:--.'.    | |     |  |        _
//     |      \      /    . / |   \ |   | |     ' .'      .' |
//     |     |\`'-.-'   .'  `" __ | |   | |___.' /'      .   | /
//     |     | '-....-'`     .'.''| |  /_______.'/     .'.'| |//
//    .'     '.             / /   | |_ \_______|/    .'.'.-'  /
//  '-----------'           \ \._,\ '/               .'   \_.'
//                           `--'  `"


//Pins used for buttons tied to ground always use number of entries specified in VCS
byte padPins[VCS] = {15, 21, 3, 17, 4, 19};


//
//
//   __  __   ___                                  .--.
//  |  |/  `.'   `.                                |__|
//  |   .-.  .-.   '                 .|   .-,.--.  .--.
//  |  |  |  |  |  |     __        .' |_  |  .-. | |  |    ____     _____
//  |  |  |  |  |  |  .:--.'.    .'     | | |  | | |  |   `.   \  .'    /
//  |  |  |  |  |  | / |   \ |  '--.  .-' | |  | | |  |     `.  `'    .'
//  |  |  |  |  |  | `" __ | |     |  |   | |  '-  |  |       '.    .'
//  |__|  |__|  |__|  .'.''| |     |  |   | |      |__|       .'     `.
//                   / /   | |_    |  '.' | |               .'  .'`.   `.
//                   \ \._,\ '/    |   /  |_|             .'   /    `.   `.
//                    `--'  `"     `'-'                  '----'       '----'


//Matrix setup
extern byte rowPins_m1[ROWS] = {25, 14}; //connect to the row pinouts of the keypad
extern byte colPins_m1[COLS] = {27, 12}; //connect to the column pinouts of the keypad

char matrix1_1 [ROWS][COLS] = { //a = b = b3 c = b2 # = b4
  {'a','#'/*...*/},//add characters in rows and columns as needed
  {'c','b'/*...*/}
};

//Shift layout make sure, bang is always present as it signigies shift when pressed long
char matrix1_2 [ROWS][COLS] = {
  {'A','#'/*...*/},
  {'c','B'/*...*/}//Shift layout make sure, bang is always present as it signigies shift when pressed long
};


//                  .-'''-.
//                 '   _    \
//     _..._     /   /` '.   \                   __.....__
//   .'     '.  .   |     \  '               .-''         '.
//  .   .-.   . |   '      |  '      .|     /     .-''"'-.  `.
//  |  '   '  | \    \     / /     .' |_   /     /________\   \
//  |  |   |  |  `.   ` ..' /    .'     |  |                  |        _
//  |  |   |  |     '-...-'`    '--.  .-'  \    .-------------'      .' |
//  |  |   |  |                    |  |     \    '-.____...---.     .   | /
//  |  |   |  |                    |  |      `.             .'    .'.'| |//
//  |  |   |  |                    |  '.'      `''-...... -'    .'.'.-'  /
//  |  |   |  |                    |   /                        .'   \_.'
//  '--'   '--'                    `'-'


//notes to play, add amount of notes specified in VCS o more no less or it WILL break
uint8_t seqNotes[VCS] = {24,25,26,27,32,35};
uint8_t momNotes[VCS] = {24,25,26,27,32,35};
