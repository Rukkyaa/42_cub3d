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

for file in "./$folder_name"/*.xpm; do
    filename=$(basename "$file" .xpm)
    convert "$file" -resize 500x300 -fuzz 1% -transparent black "$folder_name/$filename.xpm"
done

