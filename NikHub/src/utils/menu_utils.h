#pragma once

#include <TFT_eSPI.h>
#include "images/greenWallpaper.h"

inline bool isPointInRect(int px, int py, int rx, int ry, int rw, int rh) {
    return (px >= rx) && (px <= rx + rw) && (py >= ry) && (py <= ry + rh);
}

inline bool isPointInCircle(int px, int py, int cx, int cy, int radius) {
    int dx = px - cx;
    int dy = py - cy;
    return (dx * dx + dy * dy) <= (radius * radius);
}

inline bool isPointInRoundedRect(int px, int py, int rx, int ry, int rw, int rh, int radius) {
    if (isPointInRect(px, py, rx + radius, ry, rw - 2 * radius, rh)) return true;
    if (isPointInRect(px, py, rx, ry + radius, rw, rh - 2 * radius)) return true;

    if (isPointInCircle(px, py, rx + radius, ry + radius, radius)) return true; // Top-left
    if (isPointInCircle(px, py, rx + rw - radius, ry + radius, radius)) return true; // Top-right
    if (isPointInCircle(px, py, rx + radius, ry + rh - radius, radius)) return true; // Bottom-left
    if (isPointInCircle(px, py, rx + rw - radius, ry + rh - radius, radius)) return true; // Bottom-right

    return false;
}

inline void fillSpriteWithWallpaper(TFT_eSprite &sprite, int x, int y) {
    for (int j = 0; j < sprite.height(); j++) {
        for (int i = 0; i < sprite.width(); i++) {
            int srcX = x + i;
            int srcY = y + j;
            if (srcX >= 0 && srcX < GREENWALLPAPER_WIDTH &&
                srcY >= 0 && srcY < GREENWALLPAPER_HEIGHT) {
                uint16_t color = greenWallpaperBitmap[srcY * GREENWALLPAPER_WIDTH + srcX];
                sprite.drawPixel(i, j, color);
            } else {
                sprite.drawPixel(i, j, TFT_BLACK);
            }
        }
    }
}