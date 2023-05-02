while getopts "d:" opt; do
  case $opt in
    d)
      folder_name=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

if [ -z "$folder_name" ]; then
  echo "Folder name not provided. Please use the -d option to specify the folder name."
  exit 1
fi

mkdir "./$folder_name"_rename

echo i=1

for file in "./$folder_name"/*.png; do
    filename=$(basename "$file" .png)
    convert "$folder_name/$filename.png" -crop 35x35+30+30 "$folder_name"_rename"/$filename.xpm"
    i=$((i+1))
done


