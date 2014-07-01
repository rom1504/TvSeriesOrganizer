#!/bin/bash

set -e

mkdir -p ~/.ssh
openssl aes-256-cbc -pass "pass:$MY_SECRET_ENV" -in build/.travis/id_rsa_deploy.enc -out ~/.ssh/id_rsa -d -a
chmod 600 ~/.ssh/id_rsa