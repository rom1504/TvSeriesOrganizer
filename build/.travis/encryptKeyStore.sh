#!/bin/bash

dir=`dirname $0`

openssl aes-256-cbc -pass "file:$dir/../../../secret/secret" -in $dir/../../../secret/android_release.keystore -out $dir/android_release.keystore.enc -a
openssl aes-256-cbc -pass "file:$dir/../../../secret/secret" -in $dir/../../../secret/keystore_password -out $dir/keystore_password.enc -a
