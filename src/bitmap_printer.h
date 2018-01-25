// === bitmap_printer.h ===
#ifndef _BITMAP_PRINTER_H_
#define _BITMAP_PRINTER_H_
    uint16_t read16(File f);
    uint32_t read32(File f);
    void bmpDraw(char *filename, uint8_t x, uint8_t y);
    void print_bitmap(int map_choice);
#endif
