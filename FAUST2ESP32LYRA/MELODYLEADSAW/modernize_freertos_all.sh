#!/bin/bash

ADF_ROOT="/Users/anantrohmetra/esp/esp-adf"

# Backup function
backup_file() {
    local file="$1"
    if [ ! -f "${file}.bak" ]; then
        cp "$file" "${file}.bak"
    fi
}

# Add FreeRTOS includes if needed (only for headers)
add_freertos_includes() {
    local file="$1"
    if grep -q "xTaskHandle\|xSemaphoreHandle\|xQueueHandle\|xTimerHandle\|portTICK_RATE_MS" "$file"; then
        if ! grep -q "freertos/FreeRTOS.h" "$file"; then
            sed -i '' '1i\
#include "freertos/FreeRTOS.h"\
#include "freertos/task.h"\
#include "freertos/semphr.h"\
#include "freertos/queue.h"\
#include "freertos/timers.h"
' "$file"
        fi
    fi
}

# Modernize a file
modernize_file() {
    local file="$1"
    backup_file "$file"

    # Replace deprecated types
    sed -i '' \
        -e 's/\bxSemaphoreHandle\b/SemaphoreHandle_t/g' \
        -e 's/\bxTaskHandle\b/TaskHandle_t/g' \
        -e 's/\bxQueueHandle\b/QueueHandle_t/g' \
        -e 's/\bxTimerHandle\b/TimerHandle_t/g' \
        "$file"

    # Replace portTICK_RATE_MS with pdMS_TO_TICKS() - BSD sed compatible
    sed -i '' \
        -e 's/\([A-Za-z0-9_]\+\)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(\1)/g' \
        -e 's/\([0-9]\+\)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(\1)/g' \
        "$file"

    # Specific macro fixes
    sed -i '' \
        -e 's/#define DEFAULT_ESP_PERIPH_WAIT_TICK[[:space:]]*([[:space:]]*10\/portTICK_RATE_MS[[:space:]]*)/#define DEFAULT_ESP_PERIPH_WAIT_TICK pdMS_TO_TICKS(10)/g' \
        "$file"
}

# Modernize a header file
modernize_header() {
    local file="$1"
    backup_file "$file"
    add_freertos_includes "$file"

    # Replace type definitions and declarations
    sed -i '' \
        -e 's/typedef.*xSemaphoreHandle.*;/typedef SemaphoreHandle_t esp_periph_mutex_t;/g' \
        -e 's/typedef void (\*timer_callback)(xTimerHandle tmr);/typedef void (*timer_callback)(TimerHandle_t tmr);/g' \
        "$file"

    # Macro fixes
    sed -i '' \
        -e 's/#define DEFAULT_ESP_PERIPH_WAIT_TICK[[:space:]]*([[:space:]]*10\/portTICK_RATE_MS[[:space:]]*)/#define DEFAULT_ESP_PERIPH_WAIT_TICK pdMS_TO_TICKS(10)/g' \
        "$file"
}

# Process all source files
find "$ADF_ROOT" -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d '' file; do
    if [[ "$file" == *.h ]]; then
        modernize_header "$file"
    else
        modernize_file "$file"
    fi
done

echo "Modernization complete. Original files backed up with .bak extension"

# Print summary of remaining deprecated tokens
echo "Remaining deprecated FreeRTOS tokens (if any):"
grep -RIn --include=\*.{c,h,cpp,hpp} -e 'xSemaphoreHandle' -e 'xTaskHandle' -e 'xQueueHandle' -e 'xTimerHandle' -e 'portTICK_RATE_MS' "$ADF_ROOT" | head -n 50 || echo "None found."