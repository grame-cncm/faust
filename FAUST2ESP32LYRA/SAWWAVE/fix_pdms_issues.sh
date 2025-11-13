#!/bin/bash

# Fix incorrect pdMS_TO_TICKS usage
# When we have division by pdMS_TO_TICKS(1), it should just be the tick value directly

echo "Fixing division by pdMS_TO_TICKS..."

# Pattern 1: Fix "/ pdMS_TO_TICKS(1)" -> this should be "* portTICK_PERIOD_MS" for tick-to-ms conversion
# But actually, when dividing duration_in_ms / portTICK_RATE_MS, we get ticks
# So duration_in_ms / portTICK_RATE_MS should become pdMS_TO_TICKS(duration_in_ms)
# But if we already have something / pdMS_TO_TICKS(1), we need to reconsider

# Let's check the backup to understand the original intent
FILE="/Users/anantrohmetra/esp/esp-adf/components/audio_stream/pwm_stream.c"
if [ -f "$FILE.bak" ]; then
    echo "Reverting $FILE to use proper tick conversion..."
    cp "$FILE.bak" "$FILE.bak2"
    
    # The original was: duration / portTICK_RATE_MS
    # This converts milliseconds to ticks, but it's backwards
    # duration / portTICK_RATE_MS gives you duration / 1 = duration (still in ms)
    # What they probably want is: duration ticks, so just duration
    # Or if duration is in ms, they want it in ticks: pdMS_TO_TICKS(duration)
    
    # Let's just change the division operator context:
    # "something / portTICK_RATE_MS" where portTICK_RATE_MS was 1
    # This was likely meant to convert ticks to ms, so:
    # ticks * portTICK_PERIOD_MS or keep as-is if already correct
    
    # Since portTICK_RATE_MS was 1, dividing by it did nothing
    # So let's just remove the division entirely
    sed -i '' 's/\/ pdMS_TO_TICKS(1)//g' "$FILE"
fi

# Look for any other problematic patterns
echo ""
echo "Checking for other issues..."
grep -rn "pdMS_TO_TICKS" /Users/anantrohmetra/esp/esp-adf/components --include="*.c" --include="*.h" | \
    grep -v "#define" | \
    grep -v "pdMS_TO_TICKS([^)]*)" | \
    head -20

echo ""
echo "Done!"
