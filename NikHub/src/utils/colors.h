#pragma once
// grz chatgpt di esistere

#ifndef COLORS_H
#define COLORS_H

// Macro conversione RGB888 -> BGR565
#define RGB565(r,g,b) ( ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3) )

// Toni di grigio
#define TFT_DARKGREY    0x7BEF
#define TFT_LIGHTGREY   0xC618
#define TFT_SILVER      0xC618
#define TFT_DIMGRAY     0x6B4D
#define TFT_GAINSBORO   0xDEFB

// Toni di blu
#define TFT_NAVY        0x000F
#define TFT_DARKBLUE    0x0011
#define TFT_MEDIUMBLUE  0x0019
#define TFT_SKYBLUE     0x867D
#define TFT_LIGHTBLUE   0xAEDC
#define TFT_DEEPSKYBLUE 0x05FF
#define TFT_STEELBLUE   0x4416
#define TFT_DODGERBLUE  0x1C9F
#define TFT_ROYALBLUE   0x435C
#define TFT_CORNFLOWER  0x64BD

// Toni di verde
#define TFT_EXTRADARKGREEN 0x0220
#define TFT_DARKGREEN   0x03E0
#define TFT_FOREST      0x2444
#define TFT_SEAGREEN    0x2C4A
#define TFT_LIME        0x07E0
#define TFT_LIMEGREEN   0x3666
#define TFT_SPRINGGREEN 0x07EF
#define TFT_MEDIUMGREEN 0x03F0
#define TFT_LIGHTGREEN  0x9772
#define TFT_GREENYELLOW 0xAFE5

// Toni di rosso
#define TFT_DARKRED     0x8800
#define TFT_FIREBRICK   0xB104
#define TFT_CRIMSON     0xD8A7
#define TFT_INDIANRED   0xCAEB
#define TFT_SALMON      0xFC0E
#define TFT_LIGHTSALMON 0xFD0F
#define TFT_CORAL       0xFBEA
#define TFT_TOMATO      0xFB08

// Toni di viola
#define TFT_DARKVIOLET  0x901A
#define TFT_MEDIUMVIOLET 0x939B
#define TFT_VIOLET      0xEC1D
#define TFT_ORCHID      0xDB9D
#define TFT_MEDIUMORCHID 0xBABA
#define TFT_PLUM        0xDD1B

// Toni di marrone
#define TFT_SADDLEBROWN 0x8A22
#define TFT_SIENNA      0x9A85
#define TFT_CHOCOLATE   0xD344
#define TFT_PERU        0xCC28
#define TFT_TAN         0xD591
#define TFT_WHEAT       0xF6F6
#define TFT_BURLYWOOD   0xDDD0

// Toni caldi/gialli
#define TFT_KHAKI       0xF731
#define TFT_LIGHTKHAKI  0xEF31
#define TFT_GOLD        0xFEA0
#define TFT_LIGHTYELLOW 0xFFFC
#define TFT_LEMONCHIFFON 0xFFF9

#endif // COLORS_H
