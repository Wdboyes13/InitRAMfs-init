#!/bin/bash
git add .
TIME=$(date)
STAGED=$(git status --short | paste -sd' ' -  )
git commit -m "Updated $TIME $STAGED"
git push origin main