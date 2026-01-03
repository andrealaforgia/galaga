#!/bin/bash

INPUT_FILE="$HOME/dev/galaga/game/assets/sounds/13. Sound Effects.mp3"
OUTPUT_DIR="$HOME/dev/galaga/game/assets/sounds/split_effects"

# Create output directory
mkdir -p "$OUTPUT_DIR"

# First, detect silence to get timestamps
echo "Detecting silence in audio file..."
ffmpeg -i "$INPUT_FILE" -af silencedetect=noise=-30dB:d=0.5 -f null - 2>&1 | grep "silence_" > /tmp/silence_log.txt

# Parse silence timestamps
echo "Parsing silence timestamps..."
awk '/silence_end/ {print $5}' /tmp/silence_log.txt > /tmp/split_times.txt

# Add start time (0)
echo "0" > /tmp/all_times.txt
cat /tmp/split_times.txt >> /tmp/all_times.txt

# Get total duration
DURATION=$(ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 "$INPUT_FILE")
echo "$DURATION" >> /tmp/all_times.txt

# Split the audio
echo "Splitting audio into separate files..."
counter=1
prev_time=0

while IFS= read -r time; do
    if [ "$prev_time" != "0" ] || [ "$time" != "0" ]; then
        if [ "$time" != "$prev_time" ]; then
            duration=$(echo "$time - $prev_time" | bc)
            if (( $(echo "$duration > 0.5" | bc -l) )); then
                echo "Extracting segment $counter: ${prev_time}s to ${time}s (duration: ${duration}s)"
                ffmpeg -i "$INPUT_FILE" -ss "$prev_time" -t "$duration" -acodec libmp3lame -q:a 2 "$OUTPUT_DIR/sound_effect_$(printf "%02d" $counter).mp3" -y 2>/dev/null
                counter=$((counter + 1))
            fi
        fi
    fi
    prev_time=$time
done < <(sort -n /tmp/all_times.txt)

echo "Done! Created $((counter - 1)) sound effect files in $OUTPUT_DIR"
