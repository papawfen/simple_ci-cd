#!/bin/bash

echo 'student' | sudo -S apt-get -y install sshpass
sshpass -p "student" ssh student@172.24.116.8 'echo student | sudo -S rm /usr/local/bin/s21* 2>/dev/null'
sshpass -p "student" scp src/cat/s21_cat student@172.24.116.8:/tmp/s21_cat
sshpass -p "student" scp src/grep/s21_grep student@172.24.116.8:/tmp/s21_grep
sshpass -p "student" ssh student@172.24.116.8 'echo student | sudo -S mv /tmp/s21* /usr/local/bin 2>/dev/null | ls /usr/local/bin'
