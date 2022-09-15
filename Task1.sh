sudo grep -oE '\w{3,15}' tester.txt | sort -u | tr [:upper:] [:lower:] > temp.txt;
grep -oE "[a-zA-Z&-]*" temp.txt > shell-file.txt;


