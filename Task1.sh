sudo grep -oE '\w{3,15}' wlist_match1.txt | sort -u | tr [:upper:] [:lower:] > temp.txt;
grep -oE "[a-zA-Z&-]*" temp.txt > shell-file.txt;


