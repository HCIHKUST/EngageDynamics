START=$(date +%s)
curl -XPOST 'https://api.wit.ai/speech?v=20160526' -i -L -H "Authorization: Bearer W36NPJ4UZ2RFE2Q5UUQQNWJL62BRITGA" -H "Content-Type: audio/wav" --data-binary "@/home/nao/mingfei/dialogAudio/test.wav"
END=$(date +%s)
echo $(($END - $START))
