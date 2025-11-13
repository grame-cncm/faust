#!/usr/bin/env bash
# esp_fix_freertos_remaining_fixed.sh
# Safer macOS-friendly script to fix remaining deprecated FreeRTOS names & tick macros.
# Creates backups under .freertos_fix_backups_<timestamp> in the esp-adf root.

set -euo pipefail

ROOT="/Users/anantrohmetra/esp/esp-adf"
BACKUP_ROOT="$ROOT/.freertos_fix_backups_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$BACKUP_ROOT"

# Regex of tokens to find
PATTERN='xSemaphoreHandle|xTaskHandle|xQueueHandle|xTimerHandle|portTICK_RATE_MS'

echo "Backup root: $BACKUP_ROOT"
echo "Searching for files containing deprecated FreeRTOS tokens..."

# Build list of candidate source files (c, h, cpp, hpp)
mapfile -t CANDIDATES < <(find "$ROOT" -type f \( -iname '*.c' -o -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' \) -print0 | xargs -0 -n1 echo)

# Collect only files that actually match the pattern
files=()
for f in "${CANDIDATES[@]}"; do
  if grep -IqE "$PATTERN" "$f"; then
    files+=("$f")
  fi
done

if [ ${#files[@]} -eq 0 ]; then
  echo "No matching files found. Nothing to do."
  exit 0
fi

echo "Found ${#files[@]} files to process."

# Backup originals (preserve directory structure under BACKUP_ROOT)
for f in "${files[@]}"; do
  rel="${f#$ROOT/}"
  bak_dir="$BACKUP_ROOT/$(dirname "$rel")"
  mkdir -p "$bak_dir"
  cp "$f" "$bak_dir/$(basename "$f").bak"
done

# Conservative replacements (macOS/BSD sed -i '')
for f in "${files[@]}"; do
  echo "Patching: $f"

  # Replace deprecated handle types
  sed -i '' 's/\bxSemaphoreHandle\b/SemaphoreHandle_t/g' "$f" || true
  sed -i '' 's/\bxTaskHandle\b/TaskHandle_t/g' "$f" || true
  sed -i '' 's/\bxQueueHandle\b/QueueHandle_t/g' "$f" || true
  sed -i '' 's/\bxTimerHandle\b/TimerHandle_t/g' "$f" || true

  # Common typedef lines (conservative)
  sed -i '' 's/typedef[[:space:]]\+xSemaphoreHandle[[:space:]]\+/typedef SemaphoreHandle_t /g' "$f" || true
  sed -i '' 's/typedef[[:space:]]\+xTaskHandle[[:space:]]\+/typedef TaskHandle_t /g' "$f" || true

  # Replace simple tick expressions:
  # numeric / portTICK_RATE_MS  => pdMS_TO_TICKS(number)
  sed -i '' -E 's/([0-9]+)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(\1)/g' "$f" || true
  # named/time variables
  sed -i '' -E 's/\btime_ms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS\b/pdMS_TO_TICKS(time_ms)/g' "$f" || true
  sed -i '' -E 's/\bms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS\b/pdMS_TO_TICKS(ms)/g' "$f" || true

  # Some macro definitions e.g. DEFAULT_ESP_PERIPH_WAIT_TICK (conservative)
  sed -i '' -E 's/#define[[:space:]]+([A-Z0-9_]+)[[:space:]]*\([[:space:]]*([0-9]+)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS[[:space:]]*\)/#define \1 pdMS_TO_TICKS(\2)/g' "$f" || true

done

echo
echo "Patch pass complete. Now listing remaining matches (if any)."

# Count remaining occurrences
declare -A remaining
tokens=( "portTICK_RATE_MS" "xSemaphoreHandle" "xTaskHandle" "xQueueHandle" "xTimerHandle" )
for t in "${tokens[@]}"; do
  count=$(grep -RIn --exclude-dir="$BACKUP_ROOT" --exclude="*.bak" --include=\*.{c,h,cpp,hpp} -e "$t" "$ROOT" | wc -l || true)
  remaining["$t"]=$count
done

echo "Remaining occurrences after patch:"
for t in "${!remaining[@]}"; do
  printf "  %s : %s\n" "$t" "${remaining[$t]}"
done

echo
echo "Files still containing deprecated tokens (up to 200 matches):"
grep -RIn --exclude-dir="$BACKUP_ROOT" --exclude="*.bak" --include=\*.{c,h,cpp,hpp} \
  -e "xSemaphoreHandle" -e "xTaskHandle" -e "xQueueHandle" -e "xTimerHandle" -e "portTICK_RATE_MS" "$ROOT" | head -n 200 || true

echo
echo "Backups of originals are in: $BACKUP_ROOT"
echo
echo "Next steps:"
echo "  1) Inspect the remaining files the script printed (they may contain complex expressions or macros)."
echo "  2) Manually edit any remaining tricky cases (or ask me to prepare targeted fixes)."
echo "  3) Rebuild: idf.py clean && idf.py -B build flash monitor"