#include "Expander.h"

Adafruit_MCP23017 *mcp[MCP23017_MAX_I2C_ADDR - MCP23017_MIN_I2C_ADDR + 1];

void i2c_scan() {
    for(uint8_t i = 0; i <= (MCP23017_MAX_I2C_ADDR - MCP23017_MIN_I2C_ADDR); i++)
        mcp[i] = NULL;
    uint8_t arr_idx = 0;
    for (uint8_t i = MCP23017_MIN_I2C_ADDR; i <= MCP23017_MAX_I2C_ADDR; i++) {
        Wire.beginTransmission (i);
        if (Wire.endTransmission () == 0) {
            mcp[arr_idx] = new Adafruit_MCP23017();
            mcp[arr_idx]->begin(i - MCP23017_MIN_I2C_ADDR);
            arr_idx++;
        }
    }
    return;
}

uint8_t get_mcp_idx(int pin) {
    if(pin < MAX_BOARD_PORTS) {
        return(255);
    }
    pin -= MAX_BOARD_PORTS;
    uint8_t idx = (uint8_t) (pin / MAX_MCP23017_PORTS);
    return(idx);
}

uint8_t get_mcp_pin(int pin, uint8_t mcp_idx) {
    return(pin - MAX_BOARD_PORTS - mcp_idx * MAX_MCP23017_PORTS);
}

void show_expanders() {
    Serial.print("<PORT EXPANDERS:");
    boolean filled = 0;
    for(uint8_t i = 0; i <= (MCP23017_MAX_I2C_ADDR - MCP23017_MIN_I2C_ADDR); i++) {
        if(mcp[i]) {
            filled++;
            Serial.print(" MCP23017 #");
            Serial.print(i);
        }
    }
    if (! filled)
        Serial.print(" NONE");
    Serial.print(">");
    return;
}