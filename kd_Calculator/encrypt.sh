DIR=values
FILE=values.tar.gz
tar cvfz $FILE $DIR
openssl enc -aes-256-cbc -in $FILE -out $FILE.crypted
