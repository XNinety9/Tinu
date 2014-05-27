rm -f ../list.zip
rm -f list.md5
echo -n `md5 -q list.xml` > list.md5
zip -x compile.sh -b ../ list.zip *.*
mv ./list.zip ../list.zip