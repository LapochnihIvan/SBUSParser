# SBUSParser description:
This is library for parsing SBUS packages

# sbus_defs.h:
## Public structures:
### sbus_decode:
#### Description:
This is parsed channels storage structure.
If trust_flag equals true channels value are valid
#### Declaration:
```c
typedef struct sbus_decode
{
    uint16_t channels_val[SBUS_CHANNELS_COUNT];
    bool trust_flag; //true if channels_val are completed
} sbus_decode_t;
```

## Public defines: 
### SBUS_HEADER:
#### Description:
This is a byte that must be at beginnig of SBUS package
#### Declaration:
```c
#define SBUS_HEADER ((uint8_t)0x0FU)
```

### SBUS_FOOTER:
#### Description:
This is a byte that must be at ending of SBUS package
#### Declaration:
```c
#define SBUS_FOOTER ((uint8_t)0x00U)
```

### SBUS_INPUT_SIZE:
#### Description:
This is size of SBUS package in bytes
#### Declaration:
```c
#define SBUS_INPUT_SIZE ((uint8_t)25U)
```

### SBUS_CHANNELS_BYTES:
#### Description:
This is size of part of SBUS package wich contains channels values
#### Declaration:
```c
#define SBUS_CHANNELS_BYTES ((uint8_t)(SBUS_INPUT_SIZE - 2U))
```

### SBUS_CHANNEL_BIT_SIZE:
#### Description:
This is size of one channels in bits in SBUS package
#### Declaration:
```c
#define SBUS_CHANNEL_BIT_SIZE ((uint8_t)11U)
```

### SBUS_DIGITAL_CHANNELS_BYTE_NUM:
#### Description:
This is size of part of SBUS package wich contains digital channels values
#### Declaration:
```c
#define SBUS_DIGITAL_CHANNELS_BYTE_NUM (SBUS_INPUT_SIZE - 2)
```

### SBUS_17_CHANNEL_MASK
#### Description:
This is bit mask to get SBUS 17th channel value
#### Declaration:
```c
#define SBUS_17_CHANNEL_MASK ((uint8_t)0x01U)
```

### SBUS_18_CHANNEL_MASK
#### Description:
This is bit mask to get SBUS 18th channel value
#### Declaration:
```c
#define SBUS_18_CHANNEL_MASK ((uint8_t)0x01U)
```

# parse_sbus.h:
## Public functions:
### parse_sbus:
#### Description:
This function take SBUS raw data buffers with different sizes and
write result to destination when SBUS footer was detected.
Argument src is SBUS raw data buffer.
Argument length is SBUS raw data buffer lenght.
Function hasn't return value
#### Signature:
```c
void parse_sbus(sbus_decode_t* dest, const uint8_t* src, uint8_t length);
```

# print_abus_decode:
## Public enums:
### sbus_dbg_port:
#### Description:
This is enum of print destinations variants
#### Declaration:
```c
typedef enum sbus_dbg_port
{
    uart,
    xbee,
    usb,
    terminal
} sbus_dbg_port_t;
```

## Public functions:
### print_sbus_decode:
#### Description:
This function print SBUS parsing result to one of debug ports.
Argument decode is SBUS parsing result.
Argument port is debug port to printing.
Function hasn't return value
#### Signature:
```c
void print_sbus_decode(const sbus_decode_t* decode, sbus_dbg_port_t port);
```
