# IMAC LAFONTAINE LAURINE - MALLET FLORA

Attention certains ajouts de LUTs ont été essayé mais n'ont pas fonctionné, ils ont donc été implémenté dans effets.c

Lignes de commandes à tester : 

./bin/minigimp img/nier.ppm -h ADDLUM 150

./bin/minigimp img/nier.ppm -h SEPIA 150

./bin/minigimp img/nier.ppm -h LOG 15 DIMCON 35

./bin/minigimp img/Lena.512.ppm -h ADDPIXEL 'v' 100

./bin/minigimp img/nier.ppm -h REMOVEPIXEL 'b' 15 -o ./img/monimage.ppm

./bin/minigimp img/Lena.512.ppm -h SWAP
