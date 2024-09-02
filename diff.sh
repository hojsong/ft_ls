make re

export a1=-arRlt
export a2=-Rla
export b="."
export c="Makefile ft_ls diff.sh src/libft.c header src"
export d=""

touch ../a{1..6} ../b{1..6} ../c{1..6}

echo "./ft_ls $a1 $b > ../a1"
./ft_ls $a1 $b > ../a1
echo "ls $a1 $b > ../b1" 
ls $a1 $b > ../b1
echo "diff -s ../a1 ../b1 > ../c1" "cat ../c1"
diff -s ../a1 ../b1 > ../c1
cat ../c1
echo

echo "./ft_ls $a2 $b > ../a2"
./ft_ls $a2 $b > ../a2
echo "ls $a2 $b > ../b2"
ls $a2 $b > ../b2
echo "diff -s ../a2 ../b2 > ../c2"
diff -s ../a2 ../b2 > ../c2
echo cat ../c2
cat ../c2
echo

echo "./ft_ls $a1 $c > ../a3"
./ft_ls $a1 $c > ../a3
echo "ls $a1 $c > ../b3"
ls $a1 $c > ../b3
echo "diff -s ../a3 ../b3 > ../c3"
diff -s ../a3 ../b3 > ../c3
echo cat ../c3
cat ../c3
echo

echo "./ft_ls $a2 $c > ../a4"
./ft_ls $a2 $c > ../a4
echo "ls $a2 $c > ../b4"
ls $a2 $c > ../b4
echo "diff -s ../a4 ../b4 > ../c4"
diff -s ../a4 ../b4 > ../c4
echo cat ../c4
cat ../c4
echo

echo "./ft_ls $a1 $d > ../a5"
./ft_ls $a1 $d > ../a5
echo "ls $a1 $d > ../b5"
ls $a1 $d > ../b5
echo "diff -s ../a5 ../b5 > ../c5"
diff -s ../a5 ../b5 > ../c5
echo cat ../c5
cat ../c5
echo

echo "./ft_ls $a2 $d > ../a6"
./ft_ls $a2 $d > ../a6
echo "ls $a2 $d > ../b6"
ls $a2 $d > ../b6
echo "diff -s ../a6 ../b6 > ../c6"
diff -s ../a6 ../b6 > ../c6
echo cat ../c6
cat ../c6
