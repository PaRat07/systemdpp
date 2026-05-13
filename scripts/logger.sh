#!/usr/bin/env bash

FILENAME="$1"

tail -f "$FILENAME" | while read -r LINE; do
    echo "$FILENAME" ";" "$( date )" ";" "$LINE" > /tmp/journal/journal.log 
done
