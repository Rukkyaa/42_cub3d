for file in ./*.xpm; do
    filename=$(basename "$file" .xpm)
    convert "$file" -crop 124x169+61+70 "${filename}_crop.xpm"
done
