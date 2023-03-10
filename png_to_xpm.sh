for file in ./RUN_SLICED/*.png; do
    filename=$(basename "$file" .png)
    convert "$file" "RUN_SLICED_XPM/$filename.xpm"
done