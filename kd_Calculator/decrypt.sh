FILE=values.tar.gz
openssl enc -aes-256-cbc -d -in $FILE.crypted > $FILE
tar xvvf $FILE
