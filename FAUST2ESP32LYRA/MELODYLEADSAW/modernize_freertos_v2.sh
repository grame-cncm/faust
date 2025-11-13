#!/bin/bash

# Directory containing the ESP-ADF source code
ADF_ROOT="/Users/anantrohmetra/esp/esp-adf"

# Backup function
backup_file() {
    local file="$1"
    if [ ! -f "${file}.bak" ]; then
        cp "$file" "${file}.bak"
    fi
}

# Function to update FreeRTOS types and macros in a file
modernize_file() {
    local file="$1"
    echo "Modernizing $file..."
    backup_file "$file"
    
    # Replace deprecated types
    sed -i '' \
        -e 's/xSemaphoreHandle/SemaphoreHandle_t/g' \
        -e 's/xTaskHandle/TaskHandle_t/g' \
        -e 's/xQueueHandle/QueueHandle_t/g' \
        -e 's/xTimerHandle/TimerHandle_t/g' \
        "$file"

    # Replace deprecated macros - improved patterns
    sed -i '' \
        -e 's/#define[[:space:]]*[A-Z_]*[[:space:]]*([[:space:]]*[0-9]\+[[:space:]]*\/[[:space:]]*portTICK_RATE_MS)/#define \1 pdMS_TO_TICKS(\2)/g' \
        -e 's/([[:space:]]*[0-9]\+[[:space:]]*\/[[:space:]]*portTICK_RATE_MS)/pdMS_TO_TICKS(\1)/g' \
        -e 's/time_ms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(time_ms)/g' \
        -e 's/ms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(ms)/g' \
        "$file"

    # Specific fixes for known macro definitions
    sed -i '' \
        -e 's/#define DEFAULT_ESP_PERIPH_WAIT_TICK[[:space:]]*([[:space:]]*10\/portTICK_RATE_MS[[:space:]]*)/#define DEFAULT_ESP_PERIPH_WAIT_TICK pdMS_TO_TICKS(10)/g' \
        "$file"
}

# Function to update header files
modernize_header() {
    local file="$1"
    echo "Modernizing header $file..."
    backup_file "$file"
    
    # Add modern FreeRTOS includes if needed
    if grep -q "xTaskHandle\|xSemaphoreHandle\|xQueueHandle\|xTimerHandle\|portTICK_RATE_MS" "$file"; then
        sed -i '' '1i\
#include "freertos/FreeRTOS.h"\
#include "freertos/task.h"\
#include "freertos/semphr.h"\
#include "freertos/queue.h"\
#include "freertos/timers.h"' "$file"
    fi
    
    # Replace type definitions and declarations
    sed -i '' \
        -e 's/typedef.*xSemaphoreHandle.*;/typedef SemaphoreHandle_t esp_periph_mutex_t;/g' \
        -e 's/typedef void (\*timer_callback)(xTimerHandle tmr);/typedef void (*timer_callback)(TimerHandle_t tmr);/g' \
        "$file"

    # Replace macro definitions in headers too
    sed -i '' \
        -e 's/#define DEFAULT_ESP_PERIPH_WAIT_TICK[[:space:]]*([[:space:]]*10\/portTICK_RATE_MS[[:space:]]*)/#define DEFAULT_ESP_PERIPH_WAIT_TICK pdMS_TO_TICKS(10)/g' \
        "$file"
}

# Process all source files
find "$ADF_ROOT" -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d '' file; do
    if [[ "$file" == *".h" ]]; then
        modernize_header "$file"
    else
        modernize_file "$file"
    fi
done

echo "Modernization complete. Original files backed up with .bak extension"
