for file in ./*.xpm; do
    filename=$(basename "$file" .xpm)
    convert "$file" -crop 112x187+84+69 "${filename}_crop.xpm"
done