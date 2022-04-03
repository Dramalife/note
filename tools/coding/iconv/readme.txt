
#
file -i readme.txt

#
iconv -l

# -f : --from-code
# -t : --to-encoding
#iconv -f ISO-8859-1 -t UTF-8//TRANSLIT input.file -o out.file
iconv -f ISO-8859-1 -t UTF-8//TRANSLIT input.file -o out.file
