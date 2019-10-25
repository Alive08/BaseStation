#ifndef Expander_h
#define Expander_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>

#define MAX_BOARD_PORTS 20
#define MAX_MCP23017_PORTS 16
#define MCP23017_MIN_I2C_ADDR 32 // datasheet
#define MCP23017_MAX_I2C_ADDR 39 // datasheet

void i2c_scan();
uint8_t get_mcp_idx(int);
uint8_t get_mcp_pin(int, uint8_t);
void show_expanders();

extern Adafruit_MCP23017 *mcp[MCP23017_MAX_I2C_ADDR - MCP23017_MIN_I2C_ADDR + 1];

#endif