# count files in each root subdir
echo $PWD
echo look into root:

cd /
declare -a dirs=($(ls /))

for d in  ${dirs[@]}
do
   cd /
   if [ -r $d ]
   then
    cd $d

    declare -a files=($(ls -p | grep -v /))
    count=0
    for f in  ${files[@]}
    do
      count=$((count + 1))
    done
    
    mytail="file"
    if [ "$count" -ne  1 ]
    then
      mytail="$mytail""s"
    fi

    echo $PWD $count $mytail
   fi
done
