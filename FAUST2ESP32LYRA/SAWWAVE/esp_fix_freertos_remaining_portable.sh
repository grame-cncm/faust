#!/usr/bin/env bash
# Portable macOS/zsh-friendly script to fix remaining deprecated FreeRTOS names & tick macros.
# Creates backups under .freertos_fix_backups_<timestamp> in the esp-adf root.

set -euo pipefail

ROOT="/Users/anantrohmetra/esp/esp-adf"
BACKUP_ROOT="$ROOT/.freertos_fix_backups_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$BACKUP_ROOT"

PATTERN='xSemaphoreHandle|xTaskHandle|xQueueHandle|xTimerHandle|portTICK_RATE_MS'

echo "Backup root: $BACKUP_ROOT"
echo "Searching for files containing deprecated FreeRTOS tokens..."

# Find candidate source files and process them one-by-one (portable)
find "$ROOT" -type f \( -iname '*.c' -o -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' \) -print0 \
| while IFS= read -r -d '' f; do
  # skip any files under our backup dir (defensive)
  case "$f" in
    "$BACKUP_ROOT"/*) continue ;;
  esac

  if grep -IqE "$PATTERN" "$f"; then
    echo "Will process: $f"

    # Backup single file preserving directory structure
    rel="${f#$ROOT/}"
    bak_dir="$BACKUP_ROOT/$(dirname "$rel")"
    mkdir -p "$bak_dir"
    cp "$f" "$bak_dir/$(basename "$f").bak"

    # Apply conservative text-only replacements (macOS/BSD sed)
    sed -i '' 's/\bxSemaphoreHandle\b/SemaphoreHandle_t/g' "$f" || true
    sed -i '' 's/\bxTaskHandle\b/TaskHandle_t/g' "$f" || true
    sed -i '' 's/\bxQueueHandle\b/QueueHandle_t/g' "$f" || true
    sed -i '' 's/\bxTimerHandle\b/TimerHandle_t/g' "$f" || true

    # common typedef lines (conservative)
    sed -i '' 's/typedef[[:space:]]\+xSemaphoreHandle[[:space:]]\+/typedef SemaphoreHandle_t /g' "$f" || true
    sed -i '' 's/typedef[[:space:]]\+xTaskHandle[[:space:]]\+/typedef TaskHandle_t /g' "$f" || true

    # simple tick conversions
    sed -i '' -E 's/([0-9]+)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS/pdMS_TO_TICKS(\1)/g' "$f" || true
    sed -i '' -E 's/\btime_ms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS\b/pdMS_TO_TICKS(time_ms)/g' "$f" || true
    sed -i '' -E 's/\bms[[:space:]]*\/[[:space:]]*portTICK_RATE_MS\b/pdMS_TO_TICKS(ms)/g' "$f" || true

    # some macro definitions like DEFAULT_ESP_PERIPH_WAIT_TICK (conservative)
    sed -i '' -E 's/#define[[:space:]]+([A-Z0-9_]+)[[:space:]]*\([[:space:]]*([0-9]+)[[:space:]]*\/[[:space:]]*portTICK_RATE_MS[[:space:]]*\)/#define \1 pdMS_TO_TICKS(\2)/g' "$f" || true
  fi
done

echo
echo "Patch pass complete. Now listing remaining matches (if any)."

# Summarize remaining occurrences
tokens=( "portTICK_RATE_MS" "xSemaphoreHandle" "xTaskHandle" "xQueueHandle" "xTimerHandle" )
for t in "${tokens[@]}"; do
  cnt=$(grep -RIn --exclude-dir="$BACKUP_ROOT" --include=\*.{c,h,cpp,hpp} -e "$t" "$ROOT" 2>/dev/null | wc -l || true)
  printf "%-20s : %d\n" "$t" "$cnt"
done

echo
echo "Up to 200 remaining matches (if any):"
grep -RIn --exclude-dir="$BACKUP_ROOT" --include=\*.{c,h,cpp,hpp} -e "xSemaphoreHandle" -e "xTaskHandle" -e "xQueueHandle" -e "xTimerHandle" -e "portTICK_RATE_MS" "$ROOT" 2>/dev/null | head -n 200 || true

echo
echo "Backups stored at: $BACKUP_ROOT"
echo "If remaining matches exist, they are likely complex expressions/macros and should be fixed manually or with targeted edits."
