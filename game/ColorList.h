#pragma once

//http://www.colordic.org/

//デバッグしてないので値が間違っているものがあるかも。

namespace Color {
	constexpr int GetColor(int R, int G, int B) {
		return 0x000000 | (static_cast<unsigned int>(R) << 16) | (static_cast<unsigned int>(G) << 8) | static_cast<unsigned int>(B);
	}

	//---------------------
	//ブラウザで名前が定義されている140色
	//---------------------
	//MONOTONE
	constexpr int BLACK = GetColor(0, 0, 0);
	constexpr int DIMGRAY = GetColor(0x69, 0x69, 0x69);
	constexpr int GRAY = GetColor(0x80, 0x80, 0x80);
	constexpr int DARKGRAY = GetColor(0xa9, 0xa9, 0xa9);
	constexpr int SILVER = GetColor(0xc0, 0xc0, 0xc0);
	constexpr int LIGHTGRAY = GetColor(0xd3, 0xd3, 0xd3);
	constexpr int GAINSBORO = GetColor(0xdc, 0xdc, 0xdc);
	constexpr int WHITESMOKE = GetColor(0xf5, 0xf5, 0xf5);
	constexpr int WHITE = GetColor(0xff, 0xff, 0xff);
	constexpr int SNOW = GetColor(0xff, 0xfa, 0xfa);
	constexpr int GHOSTWHITE = GetColor(0xf8, 0xf8, 0xff);
	constexpr int FLORALWHITE = GetColor(0xff, 0xfa, 0xf0);
	constexpr int LINEN = GetColor(0xfa, 0xf0, 0xe6);
	constexpr int ANTIQUEWHITE = GetColor(0xfa, 0xeb, 0xd7);
	constexpr int PAPAYAWHIP = GetColor(0xff, 0xef, 0xd5);
	constexpr int BLANCHEDALMOND = GetColor(0xff, 0xeb, 0xcd);
	constexpr int BISQUE = GetColor(0xff, 0xe4, 0xc4);
	constexpr int MOCCASIN = GetColor(0xff, 0xe4, 0xb5);
	constexpr int NAVAJOWHITE = GetColor(0xff, 0xde, 0xad);
	constexpr int PEACHPUFF = GetColor(0xff, 0xda, 0xb9);
	constexpr int MISTYROSE = GetColor(0xff, 0xe4, 0xe1);
	constexpr int LAVENDERBLUSH = GetColor(0xff, 0xf0, 0xf5);
	constexpr int SEASHELL = GetColor(0xff, 0xf5, 0xee);
	constexpr int OLDLACE = GetColor(0xfd, 0xf5, 0xe6);
	constexpr int IVORY = GetColor(0xff, 0xff, 0xf0);
	constexpr int HONEYDEW = GetColor(0xf0, 0xff, 0xf0);
	constexpr int MINTCREAM = GetColor(0xf5, 0xff, 0xfa);
	constexpr int AZURE = GetColor(0xf0, 0xff, 0xff);

	//RED
	constexpr int CORAL = GetColor(0xff, 0x7f, 0x50);
	constexpr int TOMATO = GetColor(0xff, 0x63, 0x47);
	constexpr int ORANGERED = GetColor(0xff, 0x45, 0);
	constexpr int RED = GetColor(0xff, 0, 0);
	constexpr int CRIMSON = GetColor(0xdc, 0x14, 0x3c);
	constexpr int MEDIUMVIOLETRED = GetColor(0xc7, 0x15, 0x85);
	constexpr int DEEPPINK = GetColor(0xff, 0x14, 0x93);
	constexpr int HOTPINK = GetColor(0xff, 0x69, 0xb4);
	constexpr int PALEVIOLETRED = GetColor(0xdb, 0x70, 0x93);
	constexpr int PINK = GetColor(0xff, 0xc0, 0xcb);
	constexpr int LIGHTPINK = GetColor(0xff, 0xb6, 0xc1);
	constexpr int THISTLE = GetColor(0xd8, 0xbf, 0xd8);
	constexpr int MAGENTA = GetColor(0xff, 0, 0xff);
	constexpr int FUCHSIA = GetColor(0xff, 0, 0xff);
	constexpr int VIOLET = GetColor(0xee, 0x82, 0xee);
	constexpr int PLUM = GetColor(0xdd, 0xa0, 0xdd);
	constexpr int ORCHID = GetColor(0xda, 0x70, 0xd6);
	constexpr int MEDIUMORCHID = GetColor(0xba, 0x55, 0xd3);
	constexpr int DARKORCHID = GetColor(0x99, 0x32, 0xcc);
	constexpr int DARKVIOLET = GetColor(0x94, 0, 0xd3);
	constexpr int DARKMAGENTA = GetColor(0x8b, 0, 0x8b);
	constexpr int PURPLE = GetColor(0x80, 0, 0x80);
	constexpr int INDIGO = GetColor(0x4b, 0, 0x82);
	constexpr int DARKSLATEBLUE = GetColor(0x48, 0x3d, 0x8b);
	constexpr int BLUEVIOLET = GetColor(0x8a, 0x2b, 0xe2);
	constexpr int MEDIUMPURPLE = GetColor(0x93, 0x70, 0xdb);
	constexpr int SLATEBLUE = GetColor(0x6a, 0x5a, 0xcd);
	constexpr int MEDIUMSLATEBLUE = GetColor(0x7b, 0x68, 0xee);

	//YELLOW
	constexpr int LIGHTYELLOW = GetColor(0xff, 0xff, 0xe0);
	constexpr int LIGHTGOLDENRODYELLOW = GetColor(0xfa, 0xfa, 0xd2);
	constexpr int LEMONCHIFFON = GetColor(0xff, 0xfa, 0xcd);
	constexpr int WHEAT = GetColor(0xf5, 0xde, 0xb3);
	constexpr int BURLYWOOD = GetColor(0xde, 0xb8, 0x87);
	constexpr int TAN = GetColor(0xd2, 0xb4, 0x8c);
	constexpr int KHAKI = GetColor(0xf0, 0xe6, 0x8c);
	constexpr int YELLOW = GetColor(0xff, 0xff, 0);
	constexpr int GOLD = GetColor(0xff, 0xd7, 0);
	constexpr int ORANGE = GetColor(0xff, 0xa5, 0);
	constexpr int SANDYBROWN = GetColor(0xf4, 0xa4, 0x60);
	constexpr int DARKORANGE = GetColor(0xff, 0x8c, 0);
	constexpr int GOLDENROD = GetColor(0xda, 0xa5, 0x20);
	constexpr int PERU = GetColor(0xcd, 0x85, 0x3f);
	constexpr int DARKGOLDENROD = GetColor(0xb8, 0x86, 0x0b);
	constexpr int CHOCOLATE = GetColor(0xd2, 0x69, 0x1e);
	constexpr int SIENNA = GetColor(0xa0, 0x52, 0x2d);
	constexpr int SADDLEBROWN = GetColor(0x8b, 0x45, 0x13);
	constexpr int MAROON = GetColor(0x80, 0, 0);
	constexpr int DARKRED = GetColor(0x8b, 0, 0);
	constexpr int BROWN = GetColor(0xa5, 0x2a, 0x2a);
	constexpr int FIREBRICK = GetColor(0xb2, 0x22, 0x22);
	constexpr int INDIANRED = GetColor(0xcd, 0x5c, 0x5c);
	constexpr int ROSYBROWN = GetColor(0xbc, 0x8f, 0x8f);
	constexpr int DARKSALMON = GetColor(0xe9, 0x96, 0x7a);
	constexpr int LIGHTCORAL = GetColor(0xf0, 0x80, 0x80);
	constexpr int SALMON = GetColor(0xfa, 0x80, 0x72);
	constexpr int LIGHTSALMON = GetColor(0xff, 0xa0, 0x7a);

	//GREEN
	constexpr int DARKCYAN = GetColor(0, 0x8b, 0x8b);
	constexpr int TEAL = GetColor(0, 0x80, 0x80);
	constexpr int DARKSLATEGRAY = GetColor(0x2f, 0x4f, 0x4f);
	constexpr int DARKGREEN = GetColor(0, 0x64, 0);
	constexpr int GREEN = GetColor(0, 0x80, 0);
	constexpr int FORESTGREEN = GetColor(0x22, 0x8b, 0x22);
	constexpr int SEAGREEN = GetColor(0x2e, 0x8b, 0x57);
	constexpr int MEDIUMSEAGREEN = GetColor(0x3c, 0xb3, 0x71);
	constexpr int MEDIUMAQUAMARINE = GetColor(0x66, 0xcd, 0xaa);
	constexpr int DARKSEAGREEN = GetColor(0x8f, 0xbc, 0x8f);
	constexpr int AQUAMARINE = GetColor(0x7f, 0xff, 0xd4);
	constexpr int PALEGREEN = GetColor(0x98, 0xfb, 0x98);
	constexpr int LIGHTGREEN = GetColor(0x90, 0xee, 0x90);
	constexpr int SPRINGGREEN = GetColor(0, 0xff, 0x7f);
	constexpr int MEDIUMSPRINGGREEN = GetColor(0, 0xfa, 0x9a);
	constexpr int LAWNGREEN = GetColor(0x7c, 0xfc, 0);
	constexpr int CHARTREUSE = GetColor(0x7f, 0xff, 0);
	constexpr int GREENYELLOW = GetColor(0xad, 0xff, 0x2f);
	constexpr int LIME = GetColor(0, 0xff, 0);
	constexpr int LIMEGREEN = GetColor(0x32, 0xcd, 0x32);
	constexpr int YELLOWGREEN = GetColor(0x9a, 0xcd, 0x32);
	constexpr int DARKOLIVEGREEN = GetColor(0x55, 0x6b, 0x2f);
	constexpr int OLIVEDRAB = GetColor(0x6b, 0x8e, 0x23);
	constexpr int OLIVE = GetColor(0x80, 0x80, 0);
	constexpr int DARKKHAKI = GetColor(0xbd, 0xb7, 0x6b);
	constexpr int PALEGOLDENROD = GetColor(0xee, 0xe8, 0xaa);
	constexpr int CORNSILK = GetColor(0xff, 0xf8, 0xdc);
	constexpr int BEIGE = GetColor(0xf5, 0xf5, 0xdc);

	//BLUE
	constexpr int ALICEBLUE = GetColor(0xf0, 0xf8, 0xff);
	constexpr int LAVENDER = GetColor(0xe6, 0xe6, 0xfa);
	constexpr int LIGHTSTEELBLUE = GetColor(0xb0, 0xc4, 0xde);
	constexpr int LIGHTSLATEGRAY = GetColor(0x77, 0x88, 0x99);
	constexpr int SLATEGRAY = GetColor(0x70, 0x80, 0x90);
	constexpr int STEELBLUE = GetColor(0x46, 0x82, 0xb4);
	constexpr int ROYALBLUE = GetColor(0x41, 0x69, 0xe1);
	constexpr int MIDNIGHTBLUE = GetColor(0x19, 0x19, 0x70);
	constexpr int NAVY = GetColor(0, 0, 0x80);
	constexpr int DARKBLUE = GetColor(0, 0, 0x8b);
	constexpr int MEDIUMBLUE = GetColor(0, 0, 0xcd);
	constexpr int BLUE = GetColor(0, 0, 0xff);
	constexpr int DODGERBLUE = GetColor(0x1e, 0x90, 0xff);
	constexpr int CORNFLOWERBLUE = GetColor(0x64, 0x95, 0xed);
	constexpr int DEEPSKYBLUE = GetColor(0, 0xbf, 0xff);
	constexpr int LIGHTSKYBLUE = GetColor(0x87, 0xce, 0xfa);
	constexpr int SKYBLUE = GetColor(0x87, 0xce, 0xeb);
	constexpr int LIGHTBLUE = GetColor(0xad, 0xd8, 0xe6);
	constexpr int POWDERBLUR = GetColor(0xb0, 0xe0, 0xe6);
	constexpr int PALETURQUOISE = GetColor(0xaf, 0xee, 0xee);
	constexpr int LIGHTCYAN = GetColor(0xe0, 0xff, 0xff);
	constexpr int CYAN = GetColor(0, 0xff, 0xff);
	constexpr int AQUA = GetColor(0, 0xff, 0xff);
	constexpr int TURQUIOSE = GetColor(0x40, 0xe0, 0xd0);
	constexpr int MEDIUMTURQUOISE = GetColor(0x48, 0xd1, 0xcc);
	constexpr int DARKTURQUOISE = GetColor(0, 0xce, 0xd1);
	constexpr int LIGHTSEAGREEN = GetColor(0x20, 0xb2, 0xaa);
	constexpr int CADETBLUE = GetColor(0x5f, 0x9e, 0xa0);

	namespace PaintColorSwatch {
		constexpr int GREENUMBER = GetColor(18, 17, 0);
		constexpr int RAWUMBER = GetColor(23, 17, 1);
		constexpr int GOLDENGREEN = GetColor(28, 45, 1);
		constexpr int GREENGOLD = GetColor(30, 50, 1);
		constexpr int IRGAZINEGREEN = GetColor(45, 48, 1);
		constexpr int YELLOWGREEN = GetColor(193, 231, 50);
		constexpr int SAPGREEN = GetColor(21, 37, 0);
		constexpr int GREENEARTH = GetColor(62, 86, 0);
		constexpr int CHROMEGREEN = GetColor(0, 72, 24);
		constexpr int HOOKERSGREEN = GetColor(42, 60, 0);
		constexpr int PERMANENTGREENLIGHT = GetColor(0, 111, 63);
		constexpr int PHTHALOGREEN = GetColor(0, 66, 39);
		constexpr int EMERALDGREEN = GetColor(3, 131, 46);
		constexpr int PHTHALOCYANINEGREEN = GetColor(0, 117, 88);
		constexpr int AQUAGREEN = GetColor(21, 172, 163);
		constexpr int BLUEGREEN = GetColor(0, 49, 43);
		constexpr int MANGANESEBLUE = GetColor(0, 65, 123);
		constexpr int SALONBLUE = GetColor(1, 59, 122);
		constexpr int SERULEANBLUE = GetColor(0, 223, 255);
		constexpr int KINGSBLUE = GetColor(81, 205, 255);
		constexpr int COBALTBLUE = GetColor(0, 34, 134);
		constexpr int DARKULTRAMARINEBLUE = GetColor(14, 3, 107);
		constexpr int LIGHTULTRAMARINEBLUE = GetColor(33, 11, 138);
		constexpr int FRENCHULTRAMARINE = GetColor(16, 11, 139);
		constexpr int LIGHTBLUEVIOLET = GetColor(97, 115, 241);
		constexpr int ULTRAMARINEVIOLET = GetColor(37, 10, 91);
		constexpr int DIOXAZINEPURPLE = GetColor(52, 0, 98);
		constexpr int MANGANESEVIOLET = GetColor(85, 0, 42);
		constexpr int COBALTVIOLET = GetColor(191, 72, 176);
		constexpr int QUINACRIDONEMAGENTA = GetColor(169, 0, 57);
		constexpr int REMBRANDTROSE = GetColor(196, 14, 54);
	};

	//---------------------
	//和色
	//---------------------
	constexpr int NADESHIKO = GetColor(0xdc, 0x9f, 0xb4);
	constexpr int KOHBAI = GetColor(0xe1, 0x6b, 0xbc);
	constexpr int SUOH = GetColor(0x8e, 0x35, 0x4a);
	constexpr int TAIKOH = GetColor(0xf8, 0xc3, 0xcd);
	constexpr int IKKONZOME = GetColor(0xf4, 0xa7, 0xb9);
	constexpr int KUWAZOME = GetColor(0x64, 0x36, 0x3c);
	constexpr int MOMO = GetColor(0xf5, 0x96, 0xaa);
};