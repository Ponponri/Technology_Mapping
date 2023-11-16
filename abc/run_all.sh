# search_dir=../PA2/ISCAS85
search_dir=$1
mkdir -p ./results
for entry in "$search_dir"/*
do
  ./abc -c "read "$entry"; strash; hw2"
  filename=$(basename ${entry})
  mv ${filename}.mbench ./results
done
echo "finish!"