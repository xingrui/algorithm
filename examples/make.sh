mkdir -p bin
for file in *.cpp
do
    echo "compile ${file}"
    exe_file_name=$(echo ${file%.*})
    g++ -O0 -g -Wall ${file} -o bin/${exe_file_name}
done
