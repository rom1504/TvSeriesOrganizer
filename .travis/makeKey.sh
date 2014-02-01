#!/bin/bash
dir=`dirname $0`

rm -rf $dir/id_rsa_deploy.enc
rm -rf $dir/../secret
mkdir -p $dir/../secret

ssh-keygen -f $dir/../secret/id_rsa_deploy -t rsa -N ''

# generate the password/secret you will store encrypted in the .travis.yml and use to encrypt your private key
cat /dev/urandom | head -c 10000 | openssl sha1 | cut -d' ' -f2 > $dir/../secret/secret

# encrypt your private key using your secret password
openssl aes-256-cbc -pass "file:$dir/../secret/secret" -in $dir/../secret/id_rsa_deploy -out $dir/id_rsa_deploy.enc -a

travis pubkey --pem > $dir/../secret/id_travis.pub
sed -i "s/RSA PUBLIC KEY/PUBLIC KEY/g" $dir/../secret/id_travis.pub
chmod 600 $dir/../secret/id_travis.pub
 
# now encrypt your secure environment variable and secret password using the public key
echo "MY_SECRET_ENV=`cat $dir/../secret/secret`" | openssl rsautl -encrypt -pubin -inkey $dir/../secret/id_travis.pub | base64