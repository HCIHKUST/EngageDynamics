qibuild config --wizard
qibuild clean -f
qibuild configure
qibuild make

appName="test_dialog"
scp ./build-naoqisdk32/sdk/bin/$appName nao@192.168.1.102:~/mingfei

# 
# scp nao@192.168.1.102:~/naoqi/preferences/autoload.ini ./autoload.ini
# 
# # file rewrite
# touch autoload1.ini
# while read -r line; do
#   echo "$line">>autoload1.ini
#   if [ "$line" == "\[program\]\n" ]; then
#     echo "/home/nao/mingfei/$appName\n">>autoload1.ini
#   fi
# done < autoload.ini
# 
# scp ./autoload1.ini nao@192.168.1.102:~/naoqi/preferences/autoload.ini
# 
# rm autoload.ini autoload1.ini
# 
echo "done"
