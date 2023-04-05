for file in ./*.xpm; do
    filename=$(basename "$file" .xpm)
    convert "$file" -fill red -opaque black "${filename}.xpm"
done
