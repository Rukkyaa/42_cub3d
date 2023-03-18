for file in "./$folder_name"/*.png; do
    filename=$(basename "$file" .png)
    convert "$file" -resize 500x300 -transparent black "$folder_name/$filename.xpm"
done