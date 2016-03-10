#! /bin/bash

# -y non-interactive mode
# 1 I2C bus
# 0x48 I2C address of ADC
# 0x01 address of configuration register
# 0x83C3 configureation to write
# w 16 bit word
i2cset -y 1 0x48 0x01 0x83C3 w

# - y non-interactive mode
# 1 I2c bus
# I2C 0x48 address of ADC
# 0x00 address of conversion register
# w 16 bit word
# returns LSB then MSB, drop last 4 bits
i2cget -y 1 0x48 0x00 w
